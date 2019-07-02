using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _2._3
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Введите любое число");
            Random f1 = new Random(1408+Int32.Parse(Console.ReadLine()));
            Console.Write("\nСтрока = ");
            for (int i = 0; i < 4; i++) Console.Write((char)('a'+f1.Next(26)));

            Console.ReadKey();
        }
    }
}
