using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1
{
    class TestTransport
    {
        public static void Main(String[] args)
        {
            Transport first = new Transport(120, 240, 0.1, "BMW", "X5");
            Console.WriteLine("PersonalId: "+first.PersonalId+"\n"+first.ToString());

            Console.WriteLine("Введите расстояние(км.) для подсчета расхода топлива");
            Console.WriteLine("Объём топлива: "+first.CalcFuel(Int32.Parse(Console.ReadLine()))+"л.");

            Console.WriteLine("\nВведите время(в часах) для подсчета дистанции");
            Console.WriteLine("Дистанция: " + first.CalcDistance(Int32.Parse(Console.ReadLine())) + "км.");

            Console.ReadKey();
        }
    }
}
