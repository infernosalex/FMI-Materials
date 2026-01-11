using Microsoft.AspNetCore.Identity;

// PASUL 1: useri si roluri

namespace ArticlesApp.Models
{
    public class ApplicationUser : IdentityUser
    {
        // PASUL 6: useri si roluri
        // un user poate posta mai multe comentarii
        public virtual ICollection<Comment> Comments { get; set; } = new List<Comment>();

        // un user poate posta mai multe articole
        public virtual ICollection<Article> Articles { get; set; } = [];
    }
}
