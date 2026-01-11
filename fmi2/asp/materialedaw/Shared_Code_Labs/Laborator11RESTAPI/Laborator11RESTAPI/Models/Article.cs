using Microsoft.AspNetCore.Identity;
using System.ComponentModel.DataAnnotations;

namespace Laborator11RESTAPI.Models
{
    public class Article
    {
        [Key]
        public int Id { get; set; }
        public string Title { get; set; }
        public string Content { get; set; }
        public DateTime Date { get; set; }

        // Relatia cu Category
        public int? CategoryId { get; set; }
        public virtual Category? Category { get; set; }

        // Relatia cu IdentityUser
        public string? UserId { get; set; }
        public virtual IdentityUser? User { get; set; }
    }

}
