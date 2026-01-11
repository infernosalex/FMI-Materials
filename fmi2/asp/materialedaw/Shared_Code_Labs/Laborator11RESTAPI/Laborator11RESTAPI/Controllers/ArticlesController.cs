using Laborator11RESTAPI.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Security.Claims;

namespace Laborator11RESTAPI.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    //[Route("all-articles")]
    public class ArticleController : ControllerBase
    {
        private readonly AppDbContext db;

        public ArticleController(AppDbContext context)
        {
            db = context;
        }

        [HttpGet]
        public async Task<ActionResult<IEnumerable<Article>>> Index()
        {
            var articles = await db.Articles
                                    .Include(a => a.Category)
                                    .Include(a => a.User)
                                    .ToListAsync();

            if (articles == null || articles.Count == 0)
                return NotFound(); // returnează 404 daca nu sunt articole

            return Ok(articles); // returneaza OK si lista de articole
        }

        [HttpPost]
        public async Task<IActionResult> New([FromBody] Article article)
        {
            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            // preluam Id-ul utilizatorului care posteaza articolul
            var userId = User.FindFirstValue(ClaimTypes.NameIdentifier);

            if(userId is null)
            {
                return Unauthorized(new
                {
                    Message = "User not authenticated"
                });
            }

            article.UserId = userId;

            var category = await db.Categories.FindAsync(article.CategoryId);

            if (category == null)
                return NotFound(new { Message = "Category not found" });

            db.Articles.Add(article);
            await db.SaveChangesAsync();

            return CreatedAtAction(nameof(Index), new { id = article.Id }, article);
        }

        [HttpPut("{id}")]
        public async Task<IActionResult> Edit(int id, [FromBody] Article updatedArticle)
        {
            if (id != updatedArticle.Id)
            {
                return BadRequest(new { Message = "Article Id mismatch" });
            }

            var article = await db.Articles.FindAsync(id);
            if (article == null)
            {
                return NotFound(new { Message = "Article not found" });
            }

            var userId = User.FindFirstValue(ClaimTypes.NameIdentifier);

            if (userId is null)
            {
                return Unauthorized(new
                {
                    Message = "User not authenticated"
                });
            }

            if (article.UserId != userId)
            {
                return Unauthorized(new { Message = "You are not allowed to edit this article" });
            }


            // se actualizeaza campurile articolului
            article.Title = updatedArticle.Title;
            article.Content = updatedArticle.Content;
            article.Date = updatedArticle.Date;
            article.CategoryId = updatedArticle.CategoryId;

            try
            {
                await db.SaveChangesAsync();
            }
            catch (DbUpdateException ex)
            {
                return BadRequest(new { Message = "An error occurred while updating the article", Error = ex.Message });
            }

            return Ok(new { Message = "Article updated successfully" });
        }

        [HttpDelete("{id}")]
        public async Task<IActionResult> Delete(int id)
        {
            var article = await db.Articles.FindAsync(id);
            if (article == null)
            {
                return NotFound(new { Message = "Article not found" });
            }

            var userId = User.FindFirstValue(ClaimTypes.NameIdentifier);

            if (userId is null)
            {
                return Unauthorized(new
                {
                    Message = "User not authenticated"
                });
            }

            if (article.UserId != userId)
            {
                return Unauthorized(new { Message = "You are not allowed to delete this article" });
            }

            db.Articles.Remove(article);

            try
            {
                await db.SaveChangesAsync();
            }
            catch (DbUpdateException ex)
            {
                return BadRequest(new { Message = "An error occurred while deleting the article", Error = ex.Message });
            }

            return Ok(new { Message = "Article deleted successfully" });
        }
    }
}
