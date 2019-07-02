using System;
using System.Runtime.InteropServices;

namespace ConsoleApp2
{
    class Program
    {
        [DllImport("Dll1.dll")]
        public static extern char getKey();

        [DllImport("Dll1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PrintWithCesarsCode();

        static void Main(string[] args)
        {
            Console.WriteLine("Выберите пункт меню: 1)Кейлоге 2)Вывод в шифре цезаря");
            switch (Int32.Parse(Console.ReadLine()))
            {
                case 1:
                    Console.WriteLine("Введите ноль, чтобы остановить программу");

                    char c;

                    while((c = getKey()) != '0' )
                    {
                        Console.WriteLine(c);
                    }
                break;

                case 2:
                    while (true)
                    {
                        PrintWithCesarsCode();
                    }

            }
        }
    }
}
