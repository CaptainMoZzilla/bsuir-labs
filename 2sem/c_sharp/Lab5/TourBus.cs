using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1
{
    class TourBus : Bus
    {
        public TourBus(int horsePower, int maxSpeed, double fuelСonsump, int hight, int width, string brand, string model) : base(horsePower, maxSpeed, fuelСonsump, hight, width, brand, model) { }
        public TourBus(int horsePower, int maxSpeed, double fuelСonsump, int hight, int width, string brand) : base(horsePower, maxSpeed, fuelСonsump, hight, width, brand) { }
        public TourBus(int horsePower, int maxSpeed, double fuelСonsump, int hight, int width) : base(horsePower, maxSpeed, fuelСonsump, hight, width) { }


        public enum TypeOfBus {multi_day, weekend, excursion };

        private TypeOfBus busType;
        private string tourName;

        public TypeOfBus BusType
        {
            get
            {
                return busType;
            }
            set
            {
                if (value >= TypeOfBus.multi_day && value <= TypeOfBus.excursion)
                {
                    busType = value;
                }
            }
        }

        public string TourName { get => tourName; set => tourName = value; }

        public override string ToString()
        {
            return $"\nМарка: {brand} \nМодель: {model} \nТип: {busType.ToString()}\nИмя тура:{TourName}";
        }
    }
}
