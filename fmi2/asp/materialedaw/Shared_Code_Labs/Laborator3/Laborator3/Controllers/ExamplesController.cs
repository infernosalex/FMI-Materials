using Microsoft.AspNetCore.Mvc;

namespace Laborator3.Controllers
{
    public class ExamplesController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }

        public string Concatenare(string? str1, string? str2)
        {
            return str1 + " " + str2;
        }

        public string Produs(int param1, int? param2)
        {
            if (param2 == null)
            {
                return "Introduceti ambele valori";
            }

            return (param1 * param2).ToString();
        }

        public string Operatie(int? param1, int? param2, string? op)
        {
            if (param1 == null || param1 is not int)
            {
                return "Introduceti parametrul 1. Nu poate fi null si trebuie sa fie numar intreg";
            }
            if (param2 == null || param2 is not int)
            {
                return "Introduceti parametrul 2. Nu poate fi null si trebuie sa fie numar intreg";
            }
            if (op == null)
            {
                return "Introduceti parametrul 3";
            }

            if (op == "plus")
                return (param1 + param2).ToString();
            else
                if (op == "minus")
                return (param1 - param2).ToString();
            else
                if (op == "ori")
                return (param1 * param2).ToString();
            else
                if (op == "div")
                return ((double)param1 / param2).ToString();
            else
                return "Operatie invalida";
        }
    } 
}
