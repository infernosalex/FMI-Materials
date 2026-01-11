using Laborator5.Models;
using Microsoft.AspNetCore.Mvc;

namespace Laborator5.Controllers
{
    public class ArticlesController : Controller
    {
        private readonly AppDbContext _db;

        public ArticlesController(AppDbContext context)
        {
            _db = context;
        }

        public IActionResult Index()
        {
            var articles = from article in _db.Articles
                           select article;

            ViewBag.Articles = articles;

            return View();
        }

        public ActionResult Show(int id)
        {
            Article? article = _db.Articles.Find(id);

            ViewBag.Article = article;

            return View();
        }

        /*
        public IActionResult New()
        {
            
        }

        [HttpPost]
        public IActionResult New(Article art)
        {
            

        }

        */

        /*
        public IActionResult Edit(int id)
        {
            
        }

        [HttpPost]
        public ActionResult Edit(int id, Article requestArticle)
        {
            
        }
        */


        [HttpPost]
        public ActionResult Delete(int id)
        {
            Article? article = _db.Articles.Find(id);

            if(article != null)
            {
                _db.Articles.Remove(article);
                _db.SaveChanges();
                return RedirectToAction("Index");
            }

            else
            {
                return StatusCode(StatusCodes.Status404NotFound);
            } 
        }
    }
}
