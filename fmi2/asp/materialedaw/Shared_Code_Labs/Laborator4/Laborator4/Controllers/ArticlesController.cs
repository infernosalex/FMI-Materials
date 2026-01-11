using Laborator4.Models;
using Microsoft.AspNetCore.Mvc;

namespace Laborator4.Controllers
{
    public class ArticlesController : Controller
    {
        [NonAction]
        public Article[] GetArticles()
        {
            // Se instantiaza un array de articole
            Article[] articles = new Article[3];

            // Se creeaza articolele
            for (int i = 0; i < 3; i++)
            {
                Article article = new Article();

                article.Id = i;

                article.Title = "Articol " + (i + 1).ToString();

                article.Content = "Continut articol " + (i + 1).ToString();

                article.Date = DateTime.Now;

                // Se adauga articolul in array
                articles[i] = article;
            }

            return articles;
        }

        // GET: Lista tuturor articolelor
         //[ActionName("listare")]
        public IActionResult Index()
        {
            Article[] articles = GetArticles();

            // Se adauga array-ul de articole in View
            ViewBag.Articles = articles;

           // return View("Index"); // in momentul redenumirii metodei in listare
           return View();   

        }

        // GET: Afisarea unui singur articol
        public IActionResult Show(int? id)
        {
            Article[] articles = GetArticles();
                
            try
            {
                ViewBag.Article = articles[(int)id];
                return View();
            }

            catch (Exception e)
            {
                ViewBag.ErrorMessage = e.Message;
                return View("Error");
               // return StatusCode(StatusCodes.Status404NotFound);
            }
            
        }

        // GET: Afisarea formularului de creare a unui articol 
        [HttpGet]
        public IActionResult New()
        {
            return View();
        }

        // POST: Trimiterea datelor despre articol catre server pentru adaugare in baza de date
        [HttpPost]
        public IActionResult New(Article article)
        {
            // ... cod creare articol ...
            return View("NewPostMethod"); 
        }

        // GET: Afisarea datelor unui articol pentru editare
        [HttpGet]
        public IActionResult Edit(int? id)
        {
            ViewBag.Id = id;
            return View();
        }

        // POST: Trimiterea modificarilor facute catre server pentru stocare in baza de date
        [HttpPost]
        public IActionResult Edit(Article article)
        {
            // ... cod adaugare articol editat in baza de date ... 
            // return Redirect("/Articles/Index");
             return View("EditMethod");
            // return RedirectToAction("Index");
            // return RedirectToAction("Show", new{ id = article.Id});
           // return RedirectToRoute("ArticlesShow", new{ id = article.Id });
        }

        // POST Stergere articol din baza de date
        [HttpPost]
        public IActionResult Delete(int? id)
        {
            // ... cod stergere articol din baza de date

            return Content("Articolul a fost sters din baza de date!");
        }
    }
}
