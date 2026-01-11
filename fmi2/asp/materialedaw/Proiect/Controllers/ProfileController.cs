using markly.Data;
using markly.Data.Entities;
using markly.ViewModels;
using markly.Models;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace markly.Controllers;

public class ProfileController : Controller
{
    private readonly UserManager<ApplicationUser> _userManager;
    private readonly ApplicationDbContext _context;

    public ProfileController(
        UserManager<ApplicationUser> userManager,
        ApplicationDbContext context)
    {
        _userManager = userManager;
        _context = context;
    }

    [HttpGet("u/{username}")]
    public async Task<IActionResult> Index(string username)
    {
        var user = await _userManager.FindByNameAsync(username);
        if (user == null)
        {
            return NotFound();
        }

        var isOwner = User.Identity?.IsAuthenticated == true &&
                        string.Equals(User.Identity.Name, username, StringComparison.OrdinalIgnoreCase);
        var currentUserId = _userManager.GetUserId(User);

        var rawBookmarks = await _context.Bookmarks
            .Where(b => b.UserId == user.Id && (b.IsPublic || isOwner))
            .OrderByDescending(b => b.CreatedAt)
            .Take(20)
            .Select(b => new
            {
                b.Id,
                b.Title,
                b.Description,
                UserName = b.User.UserName,
                b.CreatedAt,
                VoteCount = b.Votes.Count,
                b.Content,
                b.IsPublic,
                IsLikedByCurrentUser = currentUserId != null && b.Votes.Any(v => v.UserId == currentUserId)
            })
            .ToListAsync();

        var bookmarks = rawBookmarks.Select(b =>
        {
            var media = BookmarkMediaContent.SafeFromJson(b.Content);
            return new BookmarkListItemViewModel
            {
                Id = b.Id,
                Title = b.Title,
                Description = b.Description,
                AuthorName = b.UserName ?? "Unknown",
                CreatedAt = b.CreatedAt,
                VoteCount = b.VoteCount,
                MediaImageUrl = media.ImageUrl,
                MediaTextPreview = Helpers.UserHelper.BuildTextPreview(media.TextContent),
                IsPrivate = !b.IsPublic,
                IsLikedByCurrentUser = b.IsLikedByCurrentUser
            };
        }).ToList();

        var categories = await _context.Categories
            .Where(c => c.UserId == user.Id && (c.IsPublic || isOwner))
            .ToListAsync();

        var viewModel = new UserProfileViewModel
        {
            Username = user.UserName!,
            FirstName = user.FirstName ?? "",
            LastName = user.LastName ?? "",
            Bio = user.Bio ?? "",
            ProfilePictureUrl = user.ProfilePictureUrl,
            JoinedDate = user.CreatedAt,
            Bookmarks = bookmarks,
            Categories = categories,
            IsOwner = isOwner
        };

        return View(viewModel);
    }
}
