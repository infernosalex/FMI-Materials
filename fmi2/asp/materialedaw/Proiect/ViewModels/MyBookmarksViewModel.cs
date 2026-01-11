namespace markly.ViewModels;

public class MyBookmarksViewModel
{
    public List<BookmarkListItemViewModel> Bookmarks { get; set; } = new();
    public string CurrentFilter { get; set; } = "all";
    public string CurrentSort { get; set; } = "recent";

    public bool HasBookmarks => Bookmarks.Count > 0;
}
