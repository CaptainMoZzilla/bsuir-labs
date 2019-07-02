using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class Program2
    {
        static void Main(string[] args)
        {
            DateTime date;
            bool checker = true;
            string language = "en-us";
            do
            {
                Console.WriteLine("Выберите язык месяца: \n1)Us\n2)Gb\n3)FR\n4)De\n5)Ru");
                switch (Int32.Parse(Console.ReadLine()))
                {
                    case 1:
                        language = "en-us";
                        break;

                    case 2:
                        language = "en-GB";
                        break;

                    case 3:
                        language = "fr-FR";
                        break;

                    case 4:
                        language = "de-DE";
                        break;

                    case 5:
                        language = "ru-RU";
                        break;

                    default:
                        checker = false;
                        break;
                }
                CultureInfo culture = new CultureInfo(language);
    
                for (int i =1; i <= 12; i++)
                {
                    date = new DateTime(1, i, 1);
                    Console.WriteLine(date.ToString("MMMMM", culture));
                }
               
            } while (checker);
        }

    }
}
