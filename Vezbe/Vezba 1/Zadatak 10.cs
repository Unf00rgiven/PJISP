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
            int a = 0, b = 0, c = 0, d = 0;

            Console.WriteLine("Unesite a");
            a = int.Parse(Console.ReadLine());
            Console.WriteLine("Unesite b");
            b = int.Parse(Console.ReadLine());
            Console.WriteLine("Unesite a");
            c = int.Parse(Console.ReadLine());
            Console.WriteLine("Unesite a");
            d = int.Parse(Console.ReadLine());

            Console.WriteLine("Sabiranje=" + (a+b+c+d));
            Console.WriteLine("Oduzimanje=" + (a-b-c-d));
            Console.WriteLine("Mnozenje=" + (a*b*c*d));
            Console.WriteLine("Deljenje=" + (a/b/c/d));
            Console.ReadKey();
        }
    }
}
