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
            int a = 0, i = 0, s = 0, ipar = 0;
            decimal srv = 0;


            do
            {
                Console.Write("Unesite broj=");
                a = int.Parse(Console.ReadLine());



                if (a % 5 == 0)
                {
                    i++;
                }

                if (a % 3 == 0) i = 0;

                if (a % 2 == 0)
                {
                    s += s;
                    ipar++;

                }

            } while (i < 2);

            srv = (decimal)s / ipar;
            Console.WriteLine("Srednja vrednost parnih brojeva je {0}", srv);
            Console.ReadKey;
        }
    }
}
