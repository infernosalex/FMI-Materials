using System.ComponentModel.DataAnnotations;

namespace markly.ViewModels;

public class CommentDto
{
    public int Id { get; set; }
    [Required(ErrorMessage = "Comment content is required")]
    [StringLength(500, MinimumLength = 1, ErrorMessage = "Comment must be between 1 and 500 characters")]
    public string Content { get; set; } = string.Empty;
    public string AuthorName { get; set; } = string.Empty;
    public string AuthorFirstName { get; set; } = string.Empty;
    public string AuthorUserName { get; set; } = string.Empty;
    public string? AuthorProfilePictureUrl { get; set; }
    public DateTime CreatedAt { get; set; }
    public DateTime? UpdatedAt { get; set; }
    public bool IsOwner { get; set; }
}

public class CommentCreateDto
{
    public int BookmarkId { get; set; }
    [Required(ErrorMessage = "Comment content is required")]
    [StringLength(500, MinimumLength = 1, ErrorMessage = "Comment must be between 1 and 500 characters")]
    public string Content { get; set; } = string.Empty;
}

public class CommentEditDto
{
    public int Id { get; set; }
    [Required(ErrorMessage = "Comment content is required")]
    [StringLength(500, MinimumLength = 1, ErrorMessage = "Comment must be between 1 and 500 characters")]
    public string Content { get; set; } = string.Empty;
}

public class CommentDeleteDto
{
    public int Id { get; set; }
}
