using System.ComponentModel.DataAnnotations;
using System.Text.Json.Serialization;

namespace Laborator11RESTAPI.Models
{
    public class Category
    {
        [Key]
        public int Id { get; set; }

        [Required(ErrorMessage = "Categoria este obligatorie")]
        public string CategoryName { get; set; } 

        // Relatia 1:M cu Article
        [JsonIgnore]
        public virtual ICollection<Article> Articles { get; set; } = new List<Article>();
    }

}
