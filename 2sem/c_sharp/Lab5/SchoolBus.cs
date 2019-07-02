using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1
{
    class SchoolBus : Bus
    {
        public SchoolBus(int horsePower, int maxSpeed, double fuelСonsump, int hight, int width, string brand, string model) : base(horsePower, maxSpeed, fuelСonsump, hight, width, brand, model) {}
        public SchoolBus(int horsePower, int maxSpeed, double fuelСonsump, int hight, int width, string brand) : base(horsePower, maxSpeed, fuelСonsump, hight, width, brand) { }
        public SchoolBus(int horsePower, int maxSpeed, double fuelСonsump, int hight, int width) : base(horsePower, maxSpeed, fuelСonsump, hight, width) { }


        public enum TypeOfBus { school, lyceum, gymnasium };

        private TypeOfBus busType;

        public TypeOfBus BusType
        {
            get
            {
                return busType;
            }
            set
            {
                if (value >= TypeOfBus.school && value <= TypeOfBus.gymnasium )
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
