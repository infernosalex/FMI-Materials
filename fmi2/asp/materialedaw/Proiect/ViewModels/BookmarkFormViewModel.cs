using System.ComponentModel.DataAnnotations;
using Microsoft.AspNetCore.Mvc.ModelBinding.Validation;

namespace markly.ViewModels;

public class BookmarkFormViewModel
{
    public int? Id { get; set; }

    [Required(ErrorMessage = "Title is required")]
    [StringLength(150, MinimumLength = 1, ErrorMessage = "Title must be between 1 and 150 characters")]
    public string Title { get; set; } = string.Empty;

    [Required(ErrorMessage = "Description is required")]
    [StringLength(500, MinimumLength = 1, ErrorMessage = "Description must be between 1 and 500 characters")]
    public string Description { get; set; } = string.Empty;

    [Display(Name = "Text Content")]
    [StringLength(2000, ErrorMessage = "Text content must be between 0 and 2000 characters")]
    public string? TextContent { get; set; }

    [Display(Name = "Image URL")]
    [Url(ErrorMessage = "Please enter a valid image URL.")]
    public string? ImageUrl { get; set; }

    [Display(Name = "Video URL")]
    [Url(ErrorMessage = "Please enter a valid video URL.")]
    public string? VideoUrl { get; set; }

    [Display(Name = "Make bookmark public")]
    public bool IsPublic { get; set; } = true;

    [Display(Name = "Categories")]
    public List<int> SelectedCategoryIds { get; set; } = new List<int>();

    [ValidateNever]
    public IEnumerable<Microsoft.AspNetCore.Mvc.Rendering.SelectListItem> AvailableCategories { get; set; } = new List<Microsoft.AspNetCore.Mvc.Rendering.SelectListItem>();

    [Display(Name = "Tags")]
    public List<int> SelectedTagIds { get; set; } = new List<int>();

    [ValidateNever]
    public IEnumerable<Microsoft.AspNetCore.Mvc.Rendering.SelectListItem> AvailableTags { get; set; } = new List<Microsoft.AspNetCore.Mvc.Rendering.SelectListItem>();
}
