using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1
{
    class CityBus : Bus
    {
        public CityBus(int horsePower, int maxSpeed, double fuelСonsump, int hight, int width, string brand, string model) : base(horsePower, maxSpeed, fuelСonsump, hight, width, brand, model) { }
        public CityBus(int horsePower, int maxSpeed, double fuelСonsump, int hight, int width, string brand) : base(horsePower, maxSpeed, fuelСonsump, hight, width, brand) { }
        public CityBus(int horsePower, int maxSpeed, double fuelСonsump, int hight, int width) : base(horsePower, maxSpeed, fuelСonsump, hight, width) { }


        public enum TypeOfBus { express, standart };

        private TypeOfBus busType;

        public TypeOfBus BusType
        {
            get
            {
                return busType;
            }
            set
            {
                if (value >= TypeOfBus.express && value <= TypeOfBus.standart)
                {
                    busType = value;
                }
            }
        }

        public override string ToString()
        {
            return $"\nМарка: {brand} \nМодель: {model} \nТип: {busType.ToString()}";
        }
    }
}
