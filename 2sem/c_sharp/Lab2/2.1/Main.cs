using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _2._1
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Введите строку");
            string line = Console.ReadLine();
            //Program obj = new Program();
            Console.WriteLine("Большие бувы не английского алфавита: \n");
            for(int a=0; a < line.Length; a++)
            {
                if(checkAlphabet(line[a]) && char.IsUpper(line[a]))
                {
                    Console.WriteLine(line[a]);
                }
            }
            string abc  = Console.ReadLine();
           
        }

        static bool checkAlphabet(char a)
        {
            return !('A' <= a && a <= 'Z');
            
        }
    }
}
