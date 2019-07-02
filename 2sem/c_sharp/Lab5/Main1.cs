using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1
{
    class Main1
    {
        public static void Main()
        {

            List<string> stations;
            string nameOfRoute = "Minsk3", nameOfRoute2 = "Airport";

            Bus bus1 = new Bus(120, 120, 3.4, 3, 4, "VW", "Bus v.0.1");
            Console.WriteLine(bus1.ToString());

            Bus x = new CityBus(120, 120, 3.4, 3, 4, "VW", "Bus v.0.1");
            x.ToString();
            //x.HorsePower = 0;

            Console.WriteLine("-------------------------------------------------");

            CityBus bus2 = new CityBus(120, 120, 3.4, 3, 4, "VW", "Bus v.0.1");

            stations = new List<string>();
            stations.Add("Independent square");
            stations.Add("Minskaya");
            stations.Add("Circus");

            bus2.AddRoute(nameOfRoute, stations);
            Console.WriteLine($"{bus2.ToString()} \nStations:\n{bus2.GetAllStations(nameOfRoute)}");

            bus2.AddStations(nameOfRoute, stations);
            Console.WriteLine($"\n \nStations:\n{bus2.GetAllStations(nameOfRoute)}");

            bus2.AddRoute(nameOfRoute2, stations);
            Console.WriteLine($"\n \nStations:\n{bus2.GetAllStations(nameOfRoute2)}");


            Console.WriteLine("-------------------------------------------------");
            SchoolBus bus3 = new SchoolBus(100, 90, 3.4, 4, 5,"Audi","BusBus");
            Console.WriteLine(bus3.ToString());

            bus3.BusType = SchoolBus.TypeOfBus.gymnasium;
            Console.WriteLine(bus3.ToString());

            Console.ReadKey();
        }
    }
}
