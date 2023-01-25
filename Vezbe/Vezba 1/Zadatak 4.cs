using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            int godine;
            string ime, prezime, pol;

            Console.WriteLine("Unesite ime");
            ime = Console.ReadLine();

            Console.WriteLine("Unesite prezime");
            prezime = Console.ReadLine();

            Console.WriteLine("Unesite pol");
            pol = Console.ReadLine();

            Console.WriteLine("Unesite godine");
            godine =int.Parse(Console.ReadLine());

            Console.WriteLine("Ime {0}\nPrezime {1}\nPol {2}\nGodine {3}",ime,prezime,pol,godine);
            Console.ReadKey();

        }
    }
}
