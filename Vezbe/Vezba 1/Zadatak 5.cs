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
            string ime, prezime;

            Console.WriteLine("Unesite ime");
            ime = Console.ReadLine();

            Console.WriteLine("Unesite prezime");
            prezime = Console.ReadLine();
            
            Console.WriteLine("Ime je {0} a prezime {1}", ime,prezime);
            Console.ReadKey();
            
        }
            
    }
}
