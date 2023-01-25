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
            int a = 0, b = 0, c = 0 ;

            Console.WriteLine("Unesite a");
            a = int.Parse(Console.ReadLine());
            Console.WriteLine("Unesite b");
            b = int.Parse(Console.ReadLine());
            Console.WriteLine("Unesite a");
            c = int.Parse(Console.ReadLine());

            Console.WriteLine("(a+b)*c=" + ((a+b)*c));
            Console.ReadKey();
        }
    }
}
