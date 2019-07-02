using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1
{
    class Car : Transport
    {
        public Car(int horsePower, int maxSpeed, double fuelСonsump, string brand, string model) : base(horsePower, maxSpeed, fuelСonsump, brand, model){ }
        public Car(int horsePower, int maxSpeed, double fuelСonsump, string brand) : base(horsePower, maxSpeed, fuelСonsump, brand) { }
        public Car(int horsePower, int maxSpeed, double fuelСonsump) : base(horsePower, maxSpeed, fuelСonsump){  }

        public enum TypeOfCar { coupe, sedan, hatchback, limousine, pickup }

        private TypeOfCar carType;
        private int seats;


        public TypeOfCar CarType
        {
            get
            {
                return carType;
            }
            set
            {
                if (value >= TypeOfCar.coupe && value <= TypeOfCar.pickup)
                {
                    carType = value;
                }
            }
        }

        public int Seats { get => seats; set => seats = (value > 0) ? value : 1 ; }

        public override string ToString()
        {
            return $"\nМарка: {brand} \nМодель: {model} \nТип: {carType.ToString()}";
        }

        bool CheckCapacity(int num) { return (num <= Seats); }

    }
}
