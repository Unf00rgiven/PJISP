using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ConsoleApplication2
{
    class Program
    {
        static void Main(string[] args)
        {
            int broj;

            Console.Write("Unesite broj=");
            broj = int.Parse(Console.ReadLine());

            Console.WriteLine("Broj je {0}", broj);
            Console.ReadKey();
        }
    }
}
