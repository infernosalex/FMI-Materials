using Microsoft.AspNetCore.Mvc;

namespace Laborator3.Controllers
{
    public class StudentsController : Controller
    {
        public string Index()
        {
            return "Afisarea tuturor studentilor";
        }

        public string Show(int? id)
        {
            if(id is null)
            {
                return "Parametrul este obligatoriu";
            }

            return "Afisare student cu ID: " + id.ToString();
        }
        public string Create()
        {
            return "Creare student in baza de date";
        }
        public string Edit(int? id)
        {
            return "Editare student cu ID: " + id.ToString();
        }
        public string Delete(int? id)
        {
            return "Stergere student cu ID: " + id.ToString();
        }
    }
}
