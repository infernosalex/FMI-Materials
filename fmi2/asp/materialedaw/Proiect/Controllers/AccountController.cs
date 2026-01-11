using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using markly.Data.Entities;
using markly.ViewModels;
using markly.Services.Interfaces;

namespace markly.Controllers;

public class AccountController : Controller
{
    private readonly UserManager<ApplicationUser> _userManager;
    private readonly SignInManager<ApplicationUser> _signInManager;
    private readonly ILogger<AccountController> _logger;
    private readonly IFileStorageService _fileStorage;

    public AccountController(
        UserManager<ApplicationUser> userManager,
        SignInManager<ApplicationUser> signInManager,
        ILogger<AccountController> logger,
        IFileStorageService fileStorage)
    {
        _userManager = userManager;
        _signInManager = signInManager;
        _logger = logger;
        _fileStorage = fileStorage;
    }

    [HttpGet]
    public IActionResult Login(string? returnUrl = null)
    {
        ViewData["ReturnUrl"] = returnUrl;
        return View();
    }

    [HttpPost]
    [ValidateAntiForgeryToken]
    public async Task<IActionResult> Login(LoginViewModel model, string? returnUrl = null)
    {
        ViewData["ReturnUrl"] = returnUrl;

        if (ModelState.IsValid)
        {
            var result = await _signInManager.PasswordSignInAsync(
                model.Email,
                model.Password,
                model.RememberMe,
                lockoutOnFailure: false);

            if (result.Succeeded)
            {
                _logger.LogInformation("User logged in.");
                TempData["SuccessMessage"] = "Welcome back!";
                return RedirectToLocal(returnUrl);
            }
            else
            {
                ModelState.AddModelError(string.Empty, "Invalid login attempt.");
                return View(model);
            }
        }

        return View(model);
    }

    [HttpGet]
    public IActionResult Register(string? returnUrl = null)
    {
        ViewData["ReturnUrl"] = returnUrl;
        return View();
    }

    [HttpPost]
    [ValidateAntiForgeryToken]
    public async Task<IActionResult> Register(RegisterViewModel model, string? returnUrl = null)
    {
        ViewData["ReturnUrl"] = returnUrl;

        if (ModelState.IsValid)
        {
            var user = new ApplicationUser
            {
                UserName = model.Email,
                Email = model.Email,
                FirstName = model.FirstName,
                LastName = model.LastName,
                CreatedAt = DateTime.UtcNow
            };

            var result = await _userManager.CreateAsync(user, model.Password);

            if (result.Succeeded)
            {
                _logger.LogInformation("User created a new account with password.");
                await _signInManager.SignInAsync(user, isPersistent: false);
                TempData["SuccessMessage"] = "Welcome to Markly!";
                return RedirectToLocal(returnUrl);
            }

            foreach (var error in result.Errors)
            {
                ModelState.AddModelError(string.Empty, error.Description);
            }
        }

        return View(model);
    }

    [HttpPost]
    [ValidateAntiForgeryToken]
    public async Task<IActionResult> Logout()
    {
        await _signInManager.SignOutAsync();
        _logger.LogInformation("User logged out.");
        TempData["SuccessMessage"] = "You have been logged out successfully.";
        return RedirectToAction(nameof(HomeController.Index), "Home");
    }

    [HttpGet]
    [Authorize]
    public async Task<IActionResult> Manage()
    {
        var user = await _userManager.GetUserAsync(User);
        if (user == null)
        {
            return NotFound();
        }

        var model = new ManageViewModel
        {
            Email = user.Email ?? string.Empty,
            FirstName = user.FirstName ?? string.Empty,
            LastName = user.LastName ?? string.Empty,
            Bio = user.Bio,
            CurrentProfilePictureUrl = user.ProfilePictureUrl
        };

        return View(model);
    }

    [HttpPost]
    [Authorize]
    [ValidateAntiForgeryToken]
    public async Task<IActionResult> Manage(ManageViewModel model)
    {
        var user = await _userManager.GetUserAsync(User);
        if (user == null)
        {
            return NotFound();
        }

        if (!ModelState.IsValid)
        {
            model.CurrentProfilePictureUrl = user.ProfilePictureUrl;
            return View(model);
        }

        var oldProfilePictureUrl = user.ProfilePictureUrl;
        string? newProfilePicturePath = null;

        // Handle profile picture upload
        if (model.ProfilePicture != null)
        {
            if (!IsValidImage(model.ProfilePicture))
            {
                ModelState.AddModelError("ProfilePicture", "Invalid image file. Only JPG, PNG, and GIF are allowed (max 2MB).");
                model.CurrentProfilePictureUrl = user.ProfilePictureUrl;
                return View(model);
            }

            try
            {
                newProfilePicturePath = await _fileStorage.SaveFileAsync(model.ProfilePicture, "images/profiles");
                user.ProfilePictureUrl = "/" + newProfilePicturePath;
            }
            catch (Exception)
            {
                ModelState.AddModelError("ProfilePicture", "File upload failed. Please try again.");
                model.CurrentProfilePictureUrl = user.ProfilePictureUrl;
                return View(model);
            }
        }

        // Update basic profile information
        user.FirstName = model.FirstName;
        user.LastName = model.LastName;
        user.Bio = model.Bio;

        // Update email if changed
        if (user.Email != model.Email)
        {
            var setEmailResult = await _userManager.SetEmailAsync(user, model.Email);
            if (!setEmailResult.Succeeded)
            {
                // Rollback uploaded file if email update fails
                if (!string.IsNullOrEmpty(newProfilePicturePath))
                {
                    await _fileStorage.DeleteFileAsync(newProfilePicturePath);
                }
                foreach (var error in setEmailResult.Errors)
                {
                    ModelState.AddModelError(string.Empty, error.Description);
                }
                model.CurrentProfilePictureUrl = oldProfilePictureUrl;
                return View(model);
            }

            var setUserNameResult = await _userManager.SetUserNameAsync(user, model.Email);
            if (!setUserNameResult.Succeeded)
            {
                // Rollback uploaded file if username update fails
                if (!string.IsNullOrEmpty(newProfilePicturePath))
                {
                    await _fileStorage.DeleteFileAsync(newProfilePicturePath);
                }
                foreach (var error in setUserNameResult.Errors)
                {
                    ModelState.AddModelError(string.Empty, error.Description);
                }
                model.CurrentProfilePictureUrl = oldProfilePictureUrl;
                return View(model);
            }
        }

        var updateResult = await _userManager.UpdateAsync(user);
        if (!updateResult.Succeeded)
        {
            // Rollback uploaded file if update fails
            if (!string.IsNullOrEmpty(newProfilePicturePath))
            {
                await _fileStorage.DeleteFileAsync(newProfilePicturePath);
            }
            foreach (var error in updateResult.Errors)
            {
                ModelState.AddModelError(string.Empty, error.Description);
            }
            model.CurrentProfilePictureUrl = oldProfilePictureUrl;
            return View(model);
        }

        // Success: Delete old profile picture if we uploaded a new one
        if (!string.IsNullOrEmpty(newProfilePicturePath) && !string.IsNullOrEmpty(oldProfilePictureUrl))
        {
            var oldPath = oldProfilePictureUrl.TrimStart('/');
            await _fileStorage.DeleteFileAsync(oldPath);
        }

        // Handle password change if requested
        if (model.ChangePassword && !string.IsNullOrEmpty(model.CurrentPassword) && !string.IsNullOrEmpty(model.NewPassword))
        {
            var changePasswordResult = await _userManager.ChangePasswordAsync(user, model.CurrentPassword, model.NewPassword);
            if (!changePasswordResult.Succeeded)
            {
                foreach (var error in changePasswordResult.Errors)
                {
                    ModelState.AddModelError(string.Empty, error.Description);
                }
                model.CurrentProfilePictureUrl = user.ProfilePictureUrl;
                return View(model);
            }

            await _signInManager.RefreshSignInAsync(user);
            _logger.LogInformation("User changed their password successfully.");
            TempData["SuccessMessage"] = "Your profile and password have been updated successfully.";
        }
        else
        {
            TempData["SuccessMessage"] = "Your profile has been updated successfully.";
        }

        return RedirectToAction(nameof(Manage));
    }

    private static bool IsValidImage(IFormFile file)
    {
        if (file == null || file.Length == 0 || file.Length > 2 * 1024 * 1024)
            return false;

        Span<byte> header = stackalloc byte[8];
        try
        {
            using var stream = file.OpenReadStream();
            if (stream.Read(header) < 8)
                return false;

            // JPEG: FF D8
            if (header[0] == 0xFF && header[1] == 0xD8) return true;

            // PNG: 89 50 4E 47 0D 0A 1A 0A
            if (header.SequenceEqual(new byte[] { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A })) return true;

            // GIF: 47 49 46 38
            if (header[0] == 0x47 && header[1] == 0x49 && header[2] == 0x46 && header[3] == 0x38) return true;

            return false;
        }
        catch
        {
            return false;
        }
    }

    [HttpGet]
    public IActionResult AccessDenied()
    {
        return View();
    }

    private IActionResult RedirectToLocal(string? returnUrl)
    {
        if (Url.IsLocalUrl(returnUrl))
        {
            return Redirect(returnUrl);
        }
        return RedirectToAction(nameof(HomeController.Index), "Home");
    }
}
