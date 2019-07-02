using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1
{
    class Transport
    {
        protected int horsePower, maxSpeed;
        protected double fuelСonsump;
        protected string model, brand, personalId;
        static int counterOfObjects = 0;

        public Transport(int horsePower, int maxSpeed, double fuelСonsump, string brand, string model)
        {
            this.HorsePower = horsePower;
            this.maxSpeed = maxSpeed;
            this.fuelСonsump = fuelСonsump;
            this.brand = brand;
            this.model = model;
            personalId = "Object" + counterOfObjects;
            counterOfObjects++;
        }

        public Transport(int horsePower, int maxSpeed, double fuelСonsump, string brand) : this(horsePower, maxSpeed, fuelСonsump, brand, "Noname") { }
        public Transport(int horsePower, int maxSpeed, double fuelСonsump) : this(horsePower, maxSpeed, fuelСonsump, "Noname", "Noname") { }

        public int HorsePower
        {
            get { return horsePower; }
            set { horsePower = value > 0 ? value : 0; }
        }

        public int MaxSpeed
        {
            get { return maxSpeed; }
            set { maxSpeed = value > 0 ? value : 0; }
        }

        public double FuelConsump
        {
            get { return fuelСonsump; }
            set { fuelСonsump = value > 0 ? value : 0; }
        }

        public string Model
        {
            get { return model; }
            set { model = value.Length > 0 ? value : "Noname"; }
        }

        public string Brand
        {
            get { return brand; }
            set { brand = value.Length > 1 ? value : "Noname"; }
        }

        public string PersonalId{
        get { return personalId; }
        }


        public override string ToString()
        {
            return $"\nМарка: {brand} \nМодель: {model} \nКол-во лошад. сил:{horsePower} \nСредний расход топлива(на км.): {fuelСonsump} л. \nМаксимальная скорость: {maxSpeed} км/ч";
        }

        public double CalcDistance(double time) { return time * maxSpeed; }
        public double CalcFuel(int distance) { return distance*fuelСonsump;}

    }
}
