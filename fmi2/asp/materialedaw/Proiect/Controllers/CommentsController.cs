using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using markly.Data;
using markly.Data.Entities;
using markly.Helpers;
using markly.ViewModels;

namespace markly.Controllers;

[Authorize]
public class CommentsController : Controller
{
    private readonly ApplicationDbContext _context;
    private readonly UserManager<ApplicationUser> _userManager;
    private readonly ILogger<CommentsController> _logger;

    public CommentsController(
        ApplicationDbContext context,
        UserManager<ApplicationUser> userManager,
        ILogger<CommentsController> logger)
    {
        _context = context;
        _userManager = userManager;
        _logger = logger;
    }

    [HttpPost]
    [ValidateAntiForgeryToken]
    public async Task<IActionResult> Create([FromBody] CommentCreateDto dto)
    {
        var user = await _userManager.GetUserAsync(User);
        if (user == null) return Unauthorized(new { error = "User not authorized to perform this action" });

        if (string.IsNullOrWhiteSpace(dto.Content))
        {
            return BadRequest(new { success = false, message = "Comment content is required." });
        }

        if (dto.Content.Length > 2000)
        {
            return BadRequest(new { success = false, message = "Comment is too long (max 2000 characters)." });
        }

        var bookmark = await _context.Bookmarks.FindAsync(dto.BookmarkId);
        if (bookmark == null)
        {
            return NotFound(new { success = false, message = "Bookmark not found." });
        }

        // Allow comments on public bookmarks or bookmarks owned by the user
        if (!bookmark.IsPublic && bookmark.UserId != user.Id)
        {
            return NotFound(new { success = false, message = "Bookmark not found." });
        }

        var comment = new Comment
        {
            Content = dto.Content.Trim(),
            BookmarkId = dto.BookmarkId,
            UserId = user.Id,
            CreatedAt = DateTime.UtcNow
        };

        _context.Comments.Add(comment);

        try
        {
            await _context.SaveChangesAsync();
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error saving comment changes");
            return StatusCode(500, new { success = false, error = "Failed to save changes" });
        }

        return Ok(new
        {
            success = true,
            comment = new CommentDto
            {
                Id = comment.Id,
                Content = comment.Content,
                AuthorName = UserHelper.GetAuthorName(user),
                AuthorFirstName = UserHelper.GetAuthorFirstName(user),
                AuthorUserName = user.UserName ?? string.Empty,
                AuthorProfilePictureUrl = user.ProfilePictureUrl,
                CreatedAt = comment.CreatedAt,
                UpdatedAt = comment.UpdatedAt,
                IsOwner = true
            }
        });
    }

    [HttpPost]
    [ValidateAntiForgeryToken]
    public async Task<IActionResult> Edit([FromBody] CommentEditDto dto)
    {
        var user = await _userManager.GetUserAsync(User);
        if (user == null) return Unauthorized(new { error = "User not authorized to perform this action" });

        if (string.IsNullOrWhiteSpace(dto.Content))
        {
            return BadRequest(new { success = false, message = "Comment content is required." });
        }

        if (dto.Content.Length > 2000)
        {
            return BadRequest(new { success = false, message = "Comment is too long (max 2000 characters)." });
        }

        var comment = await _context.Comments.FindAsync(dto.Id);
        if (comment == null)
        {
            return NotFound(new { success = false, message = "Comment not found." });
        }

        if (!IsOwner(comment, user.Id))
        {
            return StatusCode(403, new { success = false, message = "You don't have permission to edit this comment." });
        }

        comment.Content = dto.Content.Trim();
        comment.UpdatedAt = DateTime.UtcNow;

        try
        {
            await _context.SaveChangesAsync();
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error saving comment changes");
            return StatusCode(500, new { success = false, error = "Failed to save changes" });
        }

        return Ok(new
        {
            success = true,
            comment = new CommentDto
            {
                Id = comment.Id,
                Content = comment.Content,
                AuthorName = UserHelper.GetAuthorName(user),
                AuthorFirstName = UserHelper.GetAuthorFirstName(user),
                AuthorUserName = user.UserName ?? string.Empty,
                AuthorProfilePictureUrl = user.ProfilePictureUrl,
                CreatedAt = comment.CreatedAt,
                UpdatedAt = comment.UpdatedAt,
                IsOwner = true
            }
        });
    }

    [HttpPost]
    [ValidateAntiForgeryToken]
    public async Task<IActionResult> Delete([FromBody] CommentDeleteDto dto)
    {
        var user = await _userManager.GetUserAsync(User);
        if (user == null) return Unauthorized(new { error = "User not authorized to perform this action" });

        var comment = await _context.Comments.FindAsync(dto.Id);
        if (comment == null)
        {
            return NotFound(new { success = false, message = "Comment not found." });
        }

        if (!IsOwner(comment, user.Id))
        {
            return StatusCode(403, new { success = false, message = "You don't have permission to delete this comment." });
        }

        _context.Comments.Remove(comment);

        try
        {
            await _context.SaveChangesAsync();
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error saving comment changes");
            return StatusCode(500, new { success = false, error = "Failed to save changes" });
        }

        return Ok(new { success = true });
    }

    private static bool IsOwner(Comment comment, string userId)
    {
        return !string.IsNullOrEmpty(userId) && comment.UserId == userId;
    }
}
