using System.Collections.Generic;

namespace Task1
{
    class Bus : Transport
    {
        protected struct Route
        {
            public List<string> stations;
            public string name;

            public Route(string name)
            {
                this.name = name;
                stations = new List<string>();
            }

            public void AddStations(List<string> temp)
            {
                foreach(var i in temp){
                    stations.Add(i);
                }
            }

            public string GetAllStations()
            {
                string line = "";

                foreach(var i in stations)
                {
                    line += i + "\n";
                }

                return line;
            }
        }

        protected int height, width;
        protected List<Route> routes;


        public Bus(int horsePower, int maxSpeed, double fuelСonsump, int hight, int width, string brand, string model) : base(horsePower, maxSpeed, fuelСonsump, brand, model) {
            Height = width;
            Width = height;
        }

        public Bus(int horsePower, int maxSpeed, double fuelСonsump, int hight, int width, string brand) : base(horsePower, maxSpeed, fuelСonsump, brand) {
            Height = width;
            Width = height;
        }

        public Bus(int horsePower, int maxSpeed, double fuelСonsump, int hight, int width) : base(horsePower, maxSpeed, fuelСonsump) {
            Height = width;
            Width = height;
        }
        
        public int Height {
            get { return height; }
            set { height = value > 50 ? value : 120; }
        }

        public int Width
        {
            get { return width; }
            set { width = value > 50 ? value : 120; }
        }

        public bool CheckPatency(int height, int width) {
            if (this.height < height && this.width < width) return true;
            else return false;
        }

        delegate int FindElement(List<Route> array, string element);

        FindElement GetNumber = delegate (List<Route> array, string name)
        {
            int counter = 0;

            foreach (var i in array)
            {
                if (name == i.name)
                {
                    return counter;
                }
                counter++;
            }
            return counter;
        };

        delegate bool CheckList(List<Route> link);
        CheckList CheckLink = (link) => link != null;

        public int GetNumberOfRoute(string name) {

            if (CheckLink(routes))
            {
                return GetNumber(routes, name);
            }
            return -1;
        }


        public void AddRoute(string name, List<string> stations)
        {
            if (!CheckLink(routes))
            {
                routes = new List<Route>();
            }

            routes.Add(new Route(name));
            routes[(routes.Count - 1)].AddStations(stations);
        }

        public string GetAllStations(string nameOfRoute)
        {

            if (GetNumberOfRoute(nameOfRoute) >= 0)
            {
                return routes[GetNumberOfRoute(nameOfRoute)].GetAllStations();
            }
            return " ";
        }


        public void AddStations(string nameOfRoute, List<string> stations) {
            if (GetNumberOfRoute(nameOfRoute) >= 0)
            {
               routes[GetNumberOfRoute(nameOfRoute)].AddStations(stations);
            }
        }
    }
}
