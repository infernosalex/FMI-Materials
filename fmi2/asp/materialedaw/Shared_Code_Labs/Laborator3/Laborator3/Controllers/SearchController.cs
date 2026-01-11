using Microsoft.AspNetCore.Mvc;

namespace Laborator3.Controllers
{
    public class SearchController : Controller
    {
   
        public string NumarTelefon(string? telef)
        {
            if (telef == null)
            {
                return "Introduceti numarul de telefon";
            }

            if (telef.Length < 10)
                return "Numarul de telefon nu are suficiente cifre";

            else if (telef.Length > 10)
                return "Numarul de telefon are prea multe cifre";
            else
                return "Cautare pentru nr de telefon: " + telef;
        }
    }
}
