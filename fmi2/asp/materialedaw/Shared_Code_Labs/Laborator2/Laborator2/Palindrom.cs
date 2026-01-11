using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laborator2
{
    public class Palindrom
    {
        public void Verif_Palindrom(int n)
        {
            int temp, u, inv = 0;

            temp = n;

            if (n < 10)
                Console.WriteLine("Numarul este palindrom");
            else
            {
                while (n != 0)
                {
                    u = n % 10;
                    inv = inv * 10 + u;
                    n = n / 10;
                }

                if (inv == temp)
                    Console.WriteLine("Numarul este palindrom");
                else
                    Console.WriteLine("Numarul nu este palindrom");
            }
        }
    }
}
