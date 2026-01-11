using System.ComponentModel.DataAnnotations;
using Microsoft.AspNetCore.Mvc.ModelBinding.Validation;

namespace markly.ViewModels;

public class CategoryFormViewModel
{
    public int? Id { get; set; }

    [Required(ErrorMessage = "Category name is required")]
    [StringLength(50, MinimumLength = 1, ErrorMessage = "Category name must be between 1 and 50 characters")]
    public string Name { get; set; } = string.Empty;

    [StringLength(200, ErrorMessage = "Description must be between 0 and 200 characters")]
    public string? Description { get; set; }

    [Display(Name = "Public")]
    public bool IsPublic { get; set; } = false;

    public int BookmarkCount { get; set; }

    // Preview image URLs from bookmarks in this category (up to 4 images for the preview mosaic)
    public List<string> PreviewImages { get; set; } = new();

    public DateTime? CreatedAt { get; set; }

    // Quick add bookmarks when creating a category
    public List<int> SelectedBookmarkIds { get; set; } = new();

    [ValidateNever]
    public List<QuickAddBookmarkViewModel> RecentBookmarks { get; set; } = new();
}

public class QuickAddBookmarkViewModel
{
    public int Id { get; set; }
    public string Title { get; set; } = string.Empty;
    public string? ImageUrl { get; set; }
    public DateTime CreatedAt { get; set; }
}
