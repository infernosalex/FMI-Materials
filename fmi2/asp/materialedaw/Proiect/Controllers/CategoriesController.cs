using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using markly.Data;
using markly.Data.Entities;
using markly.Helpers;
using markly.Models;
using markly.ViewModels;

namespace markly.Controllers;

[Authorize]
public class CategoriesController : Controller
{
    private readonly ApplicationDbContext _context;
    private readonly UserManager<ApplicationUser> _userManager;
    private readonly ILogger<CategoriesController> _logger;

    public CategoriesController(
        ApplicationDbContext context,
        UserManager<ApplicationUser> userManager,
        ILogger<CategoriesController> logger)
    {
        _context = context;
        _userManager = userManager;
        _logger = logger;
    }

    [HttpGet]
    public async Task<IActionResult> Index()
    {
        var user = await _userManager.GetUserAsync(User);
        if (user == null) return Challenge();

        // Query 1: Get categories with bookmark count (no full bookmark entities loaded)
        var categories = await _context.Categories
            .Where(c => c.UserId == user.Id)
            .OrderByDescending(c => c.CreatedAt)
            .Select(c => new CategoryFormViewModel
            {
                Id = c.Id,
                Name = c.Name,
                Description = c.Description,
                IsPublic = c.IsPublic,
                BookmarkCount = c.BookmarkCategories.Count,
                CreatedAt = c.CreatedAt,
                PreviewImages = new List<string>()
            })
            .ToListAsync();

        // Query 2: Get only Content field for bookmarks that have content
        var categoryIds = categories.Select(c => c.Id!.Value).ToList();
        var bookmarkContent = await _context.Set<BookmarkCategory>()
            .Where(bc => categoryIds.Contains(bc.CategoryId) && bc.Bookmark.Content != null)
            .Select(bc => new { bc.CategoryId, bc.Bookmark.Content })
            .ToListAsync();

        // Process in memory: extract image URLs and group by category
        var previewsByCategory = bookmarkContent
            .GroupBy(x => x.CategoryId)
            .ToDictionary(
                g => g.Key,
                g => g.Select(x => BookmarkMediaContent.SafeFromJson(x.Content))
                      .Where(m => !string.IsNullOrWhiteSpace(m.ImageUrl))
                      .Select(m => m.ImageUrl!)
                      .Take(4)
                      .ToList()
            );

        foreach (var category in categories)
        {
            if (category.Id.HasValue && previewsByCategory.TryGetValue(category.Id.Value, out var images))
            {
                category.PreviewImages = images;
            }
        }

        return View(categories);
    }

    [AllowAnonymous]
    [HttpGet]
    public async Task<IActionResult> Details(int id)
    {
        var category = await _context.Categories
            .Include(c => c.User)
            .FirstOrDefaultAsync(c => c.Id == id);

        if (category == null) return NotFound();

        var currentUser = await _userManager.GetUserAsync(User);
        bool isOwner = currentUser != null && category.UserId == currentUser.Id;

        // Privacy Check
        if (!category.IsPublic && !isOwner)
        {
            return NotFound();
        }

        // Fetch bookmarks
        var currentUserId = currentUser?.Id;
        var bookmarksRaw = await _context.BookmarkCategories
            .Where(bc => bc.CategoryId == id)
            .Where(bc => isOwner || bc.Bookmark.IsPublic)
            .Include(bc => bc.Bookmark)
                .ThenInclude(b => b.User)
            .Include(bc => bc.Bookmark)
                .ThenInclude(b => b.Votes)
            .Select(bc => bc.Bookmark)
            .OrderByDescending(b => b.CreatedAt)
            .ToListAsync();

        var bookmarks = bookmarksRaw.Select(b =>
        {
            var media = BookmarkMediaContent.SafeFromJson(b.Content);
            return new BookmarkListItemViewModel
            {
                Id = b.Id,
                Title = b.Title,
                Description = b.Description,
                AuthorName = UserHelper.GetAuthorName(b.User),
                CreatedAt = b.CreatedAt,
                VoteCount = b.Votes.Count,
                MediaImageUrl = media.ImageUrl,
                MediaTextPreview = UserHelper.BuildTextPreview(media.TextContent, 160),
                IsPrivate = !b.IsPublic,
                IsLikedByCurrentUser = currentUserId != null && b.Votes.Any(v => v.UserId == currentUserId)
            };
        }).ToList();

        var model = new CategoryDetailsViewModel
        {
            Id = category.Id,
            Name = category.Name,
            Description = category.Description,
            IsPublic = category.IsPublic,
            CreatedAt = category.CreatedAt,
            OwnerId = category.UserId,
            OwnerName = UserHelper.GetAuthorName(category.User),
            IsOwner = isOwner,
            Bookmarks = bookmarks
        };

        return View(model);
    }

    [HttpGet]
    public async Task<IActionResult> Create()
    {
        var user = await _userManager.GetUserAsync(User);
        if (user == null) return Challenge();

        var model = new CategoryFormViewModel
        {
            RecentBookmarks = await GetRecentBookmarksAsync(user.Id)
        };

        return View(model);
    }

    [HttpPost]
    [ValidateAntiForgeryToken]
    public async Task<IActionResult> Create(CategoryFormViewModel model)
    {
        var user = await _userManager.GetUserAsync(User);
        if (user == null) return Challenge();

        if (!ModelState.IsValid)
        {
            model.RecentBookmarks = await GetRecentBookmarksAsync(user.Id);
            return View(model);
        }

        // Validate and normalize name (trim and collapse multiple spaces)
        model.Name = NormalizeName(model.Name);
        var validationError = await ValidateCategoryName(model.Name, user.Id, null);
        if (validationError != null)
        {
            ModelState.AddModelError("Name", validationError);
            model.RecentBookmarks = await GetRecentBookmarksAsync(user.Id);
            return View(model);
        }

        var category = new Category
        {
            Name = model.Name,
            Description = model.Description?.Trim(),
            IsPublic = model.IsPublic,
            UserId = user.Id,
            CreatedAt = DateTime.UtcNow
        };

        _context.Categories.Add(category);

        try
        {
            await _context.SaveChangesAsync();

            // Add selected bookmarks to the new category
            if (model.SelectedBookmarkIds.Any())
            {
                var validBookmarkIds = await _context.Bookmarks
                    .Where(b => b.UserId == user.Id && model.SelectedBookmarkIds.Contains(b.Id))
                    .Select(b => b.Id)
                    .ToListAsync();

                foreach (var bookmarkId in validBookmarkIds)
                {
                    _context.BookmarkCategories.Add(new BookmarkCategory
                    {
                        BookmarkId = bookmarkId,
                        CategoryId = category.Id
                    });
                }

                await _context.SaveChangesAsync();
            }
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error saving category");
            ModelState.AddModelError("", "Failed to save category. Please try again.");
            model.RecentBookmarks = await GetRecentBookmarksAsync(user.Id);
            return View(model);
        }

        return RedirectToAction(nameof(Index));
    }

    [HttpGet]
    public async Task<IActionResult> Edit(int id)
    {
        var user = await _userManager.GetUserAsync(User);
        if (user == null) return Challenge();

        var category = await _context.Categories.FirstOrDefaultAsync(c => c.Id == id && c.UserId == user.Id);
        if (category == null) return NotFound();

        return View(new CategoryFormViewModel
        {
            Id = category.Id,
            Name = category.Name,
            Description = category.Description,
            IsPublic = category.IsPublic
        });
    }

    [HttpPost]
    [ValidateAntiForgeryToken]
    public async Task<IActionResult> Edit(CategoryFormViewModel model)
    {
        if (!ModelState.IsValid) return View(model);

        var user = await _userManager.GetUserAsync(User);
        if (user == null) return Challenge();

        var category = await _context.Categories.FirstOrDefaultAsync(c => c.Id == model.Id && c.UserId == user.Id);
        if (category == null) return NotFound();

        // Validate and normalize name (trim and collapse multiple spaces)
        model.Name = NormalizeName(model.Name);
        if (category.Name.ToLower() != model.Name.ToLower())
        {
            var validationError = await ValidateCategoryName(model.Name, user.Id, model.Id);
            if (validationError != null)
            {
                ModelState.AddModelError("Name", validationError);
                return View(model);
            }
        }

        category.Name = model.Name;
        category.Description = model.Description?.Trim();
        category.IsPublic = model.IsPublic;

        try
        {
            await _context.SaveChangesAsync();
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error updating category");
            ModelState.AddModelError("", "Failed to update category. Please try again.");
            return View(model);
        }

        return RedirectToAction(nameof(Index));
    }

    [HttpGet]
    public async Task<IActionResult> Delete(int id)
    {
        var user = await _userManager.GetUserAsync(User);
        if (user == null) return Challenge();

        var category = await _context.Categories.FirstOrDefaultAsync(c => c.Id == id && c.UserId == user.Id);
        if (category == null) return NotFound();

        return View(new CategoryFormViewModel
        {
            Id = category.Id,
            Name = category.Name,
            IsPublic = category.IsPublic
        });
    }

    [HttpPost, ActionName("Delete")]
    [ValidateAntiForgeryToken]
    public async Task<IActionResult> DeleteConfirmed(int id)
    {
        var user = await _userManager.GetUserAsync(User);
        if (user == null) return Challenge();

        var category = await _context.Categories
            .Include(c => c.BookmarkCategories)
            .FirstOrDefaultAsync(c => c.Id == id && c.UserId == user.Id);
        if (category == null) return NotFound();

        // Remove associated BookmarkCategories first
        _context.BookmarkCategories.RemoveRange(category.BookmarkCategories);
        _context.Categories.Remove(category);

        try
        {
            await _context.SaveChangesAsync();
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error deleting category");
            TempData["ErrorMessage"] = "Failed to delete category. Please try again.";
            return RedirectToAction(nameof(Index));
        }

        return RedirectToAction(nameof(Index));
    }

    [HttpPost]
    [ValidateAntiForgeryToken]
    public async Task<IActionResult> CreateQuick([FromBody] CategoryFormViewModel model)
    {
        var user = await _userManager.GetUserAsync(User);
        if (user == null) return Unauthorized();

        var validationError = await ValidateCategoryName(model.Name, user.Id, null);
        if (validationError != null)
        {
            return BadRequest(new { success = false, message = validationError });
        }

        var category = new Category
        {
            Name = NormalizeName(model.Name),
            IsPublic = model.IsPublic,
            UserId = user.Id,
            CreatedAt = DateTime.UtcNow
        };

        _context.Categories.Add(category);

        try
        {
            await _context.SaveChangesAsync();
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error saving category");
            return StatusCode(500, new { success = false, error = "Failed to save changes" });
        }

        return Ok(new { success = true, category = new { id = category.Id, name = category.Name } });
    }

    [HttpPost]
    [ValidateAntiForgeryToken]
    public async Task<IActionResult> ToggleBookmark([FromBody] ToggleBookmarkCategoryDto dto)
    {
        var user = await _userManager.GetUserAsync(User);
        if (user == null) return Unauthorized();

        // Verify category belongs to user
        var category = await _context.Categories
            .FirstOrDefaultAsync(c => c.Id == dto.CategoryId && c.UserId == user.Id);
        if (category == null)
        {
            return NotFound(new { success = false, message = "Category not found." });
        }

        // Verify bookmark exists and is accessible
        var bookmark = await _context.Bookmarks
            .FirstOrDefaultAsync(b => b.Id == dto.BookmarkId && (b.IsPublic || b.UserId == user.Id));
        if (bookmark == null)
        {
            return NotFound(new { success = false, message = "Bookmark not found." });
        }

        // Check if relationship exists
        var existing = await _context.BookmarkCategories
            .FirstOrDefaultAsync(bc => bc.BookmarkId == dto.BookmarkId && bc.CategoryId == dto.CategoryId);

        bool isInCategory;
        if (existing != null)
        {
            // Remove from category
            _context.BookmarkCategories.Remove(existing);
            isInCategory = false;
        }
        else
        {
            // Add to category
            _context.BookmarkCategories.Add(new BookmarkCategory
            {
                BookmarkId = dto.BookmarkId,
                CategoryId = dto.CategoryId
            });
            isInCategory = true;
        }

        try
        {
            await _context.SaveChangesAsync();
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error toggling bookmark category");
            return StatusCode(500, new { success = false, error = "Failed to save changes" });
        }

        return Ok(new { success = true, isInCategory, categoryName = category.Name });
    }

    [HttpGet]
    public async Task<IActionResult> GetUserCategories(int bookmarkId)
    {
        var user = await _userManager.GetUserAsync(User);
        if (user == null) return Unauthorized();

        var categories = await _context.Categories
            .Where(c => c.UserId == user.Id)
            .OrderBy(c => c.Name)
            .Select(c => new
            {
                id = c.Id,
                name = c.Name,
                isInCategory = c.BookmarkCategories.Any(bc => bc.BookmarkId == bookmarkId)
            })
            .ToListAsync();

        return Ok(new { success = true, categories });
    }

    private static string NormalizeName(string name)
    {
        return System.Text.RegularExpressions.Regex.Replace(name.Trim(), @"\s+", " ");
    }

    private async Task<List<QuickAddBookmarkViewModel>> GetRecentBookmarksAsync(string userId)
    {
        var bookmarksRaw = await _context.Bookmarks
            .Where(b => b.UserId == userId)
            .OrderByDescending(b => b.CreatedAt)
            .Take(12)
            .Select(b => new { b.Id, b.Title, b.Content, b.CreatedAt })
            .ToListAsync();

        return bookmarksRaw.Select(b => new QuickAddBookmarkViewModel
        {
            Id = b.Id,
            Title = b.Title,
            ImageUrl = b.Content != null ? BookmarkMediaContent.SafeFromJson(b.Content).ImageUrl : null,
            CreatedAt = b.CreatedAt
        }).ToList();
    }

    private async Task<string?> ValidateCategoryName(string? name, string userId, int? categoryIdToExclude)
    {
        // Check if name is null/whitespace
        if (string.IsNullOrWhiteSpace(name))
        {
            return "Category name is required.";
        }

        // Normalize the name
        var normalizedName = NormalizeName(name);

        // Check length
        if (normalizedName.Length > 50)
        {
            return "Category name is too long.";
        }

        // Check for duplicate
        var normalizedNameLower = normalizedName.ToLower();
        var existingCategories = await _context.Categories
            .Where(c => c.UserId == userId && (categoryIdToExclude == null || c.Id != categoryIdToExclude))
            .Select(c => c.Name)
            .ToListAsync();

        if (existingCategories.Any(c =>
            System.Text.RegularExpressions.Regex.Replace(c.ToLower(), @"\s+", " ") == normalizedNameLower))
        {
            return "Category already exists.";
        }

        return null;
    }
}
