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
            decimal a = 0, b = 0;

            Console.WriteLine("Unesite a");
            a = decimal.Parse(Console.ReadLine());
            Console.WriteLine("Unesite b");
            b = decimal.Parse(Console.ReadLine());

            Console.WriteLine("a/b=" + (a / b));
            Console.ReadKey();
        }
    }
}
