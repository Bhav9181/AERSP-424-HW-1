/*
Bhavya Patel
AERSP 424 HW 1
*/


#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
#include <string>


int main()
{
    double empty_weight, empty_weight_moment, gallons_usable_fuel;
    int num_front_occupants, num_rear_occupants;
    double front_seat_arm, rear_seat_arm;
    double fuel_weight_per_gallon, fuel_tank_arm, baggage_weight, baggage_arm;

    // Receive input from the user
    std::cout << "Enter airplane empty weight (pounds): ";
    std::cin >> empty_weight;
    std::cout << "Enter airplane empty-weight moment (pounds-inches): ";
    std::cin >> empty_weight_moment;
    std::cout << "Enter the number of front seat occupants: ";
    std::cin >> num_front_occupants;

    // Vector to store weights of front seat passengers
    std::vector<double> front_seat_weights(num_front_occupants);
    double total_front_seat_weight = 0.0;

    // Input weights for front seat occupants
    for (int i = 0; i < num_front_occupants; ++i)
    {
        std::cout << "Enter weight of front seat occupant " << i + 1 << " (pounds): ";
        std::cin >> front_seat_weights[i];
        total_front_seat_weight += front_seat_weights[i];
    }

    std::cout << "Enter front seat moment arm (inches): ";
    std::cin >> front_seat_arm;
    std::cout << "Enter the number of rear seat occupants: ";
    std::cin >> num_rear_occupants;

    // Vector to store weights of rear seat passengers
    std::vector<double> rear_seat_weights(num_rear_occupants);
    double total_rear_seat_weight = 0.0;

    // Input weights for rear seat occupants
    for (int i = 0; i < num_rear_occupants; ++i)
    {
        std::cout << "Enter weight of rear seat occupant " << i + 1 << " (pounds): ";
        std::cin >> rear_seat_weights[i];
        total_rear_seat_weight += rear_seat_weights[i];
    }

    std::cout << "Enter rear seat moment arm (inches): ";
    std::cin >> rear_seat_arm;
    std::cout << "Enter the number of gallons of usable fuel (gallons): ";
    std::cin >> gallons_usable_fuel;
    std::cout << "Enter usable fuel weight per gallon (pounds): ";
    std::cin >> fuel_weight_per_gallon;
    std::cout << "Enter fuel tank moment arm (inches): ";
    std::cin >> fuel_tank_arm;
    std::cout << "Enter baggage weight (pounds): ";
    std::cin >> baggage_weight;
    std::cout << "Enter baggage moment arm (inches): ";
    std::cin >> baggage_arm;

    // Calculate weights and moments
    double total_weight = (empty_weight
        + total_front_seat_weight
        + total_rear_seat_weight
        + gallons_usable_fuel * fuel_weight_per_gallon
        + baggage_weight);
    double total_moment = (empty_weight_moment
        + total_front_seat_weight * front_seat_arm
        + total_rear_seat_weight * rear_seat_arm
        + gallons_usable_fuel * fuel_tank_arm * fuel_weight_per_gallon
        + baggage_weight * baggage_arm);

    double cg_location = total_moment / total_weight;
    double gallonweight = gallons_usable_fuel * fuel_weight_per_gallon;
    double requiredFuel = gallonweight / fuel_weight_per_gallon;

    std::cout << "Weight above(+)/below(-) gross weight limit: " << total_weight - 2950 << " pounds" << std::endl;

    while (total_weight > 2950 || cg_location < 82.1 || cg_location > 84.7)
    {
        if (total_weight > 2950)
        {
            gallonweight = gallonweight - 0.01;
            total_weight = total_weight - 0.01;
            requiredFuel = gallonweight / fuel_weight_per_gallon;
            cg_location = total_moment / total_weight;
        }
        else
        {
            total_weight = total_weight;
            requiredFuel = gallonweight / fuel_weight_per_gallon;
            cg_location = total_moment / total_weight;
        }

        if (cg_location < 82.1)
        {
            gallonweight = gallonweight - 0.01;
            total_weight = total_weight - 0.01;
            requiredFuel = gallonweight / fuel_weight_per_gallon;
            cg_location = total_moment / total_weight;
        }
        else
        {
            total_weight = total_weight;
            requiredFuel = gallonweight / fuel_weight_per_gallon;
            cg_location = total_moment / total_weight;
        }

        if (cg_location > 84.7)
        {
            gallonweight = gallonweight + 0.01;
            total_weight = total_weight + 0.01;
            requiredFuel = gallonweight / fuel_weight_per_gallon;
            cg_location = total_moment / total_weight;
        }
        else
        {
            total_weight = total_weight;
            requiredFuel = gallonweight / fuel_weight_per_gallon;
            cg_location = total_moment / total_weight;
        }
    }

    std::cout << "Required fuel to be added(+)/drained(-) to meet the gross weight limit: " << std::fixed << std::setprecision(2) << requiredFuel - gallons_usable_fuel << " gallons" << std::endl;
    std::cout << "New gross weight: " << total_weight << " lbs." << std::endl;
    std::cout << "New C.G. location: " << cg_location << " inches" << std::endl;

    // Define a type for the map of distances
    typedef std::map<std::string, int> DistanceMap;

    // Define a type for the container storing flights
    typedef std::map<std::string, DistanceMap> FlightContainer;

    // Create the container to store flight information
    FlightContainer flights;

    // Define a type for the map of distances
    typedef std::map<std::string, int> DistanceMap;

    // Forward declaration of the Plane class
    class Plane;

    class Pilot
    {
    private:
        std::string name;
        Plane* myPlane; // Pointer to an object of the Plane class

    public:
        // Constructor
        Pilot(const std::string& pilotName, Plane* planePtr) : name(pilotName), myPlane(planePtr)
        {
            std::cout << "Pilot " << name << " with certificate number " << this << " is at the gate, ready to board the plane." << std::endl;
        }

        // Destructor
        ~Pilot()
        {
            std::cout << "Pilot " << name << " is out of the plane." << std::endl;
        }

        // Getter function for the name
        std::string getName() const
        {
            return name;
        }

        // Getter function for the plane pointer
        Plane* getPlane() const
        {
            return myPlane;
        }
    };

    class Plane
    {
    private:
        double pos;
        double vel;
        double distance;
        bool at_SCE;
        std::string origin;
        std::string destination;
        std::map<std::string, DistanceMap> flights; // Container from Question 2

    public:
        // Constructor
        Plane(const std::string& from, const std::string& to) : pos(0.0), vel(0.0), at_SCE(true), origin(from), destination(to)
        {
            // Add flight information
            flights["SCE"]["PHL"] = 160;
            flights["SCE"]["ORD"] = 640;
            flights["SCE"]["EWR"] = 220;
            flights["PHL"]["SCE"] = 160;
            flights["ORD"]["SCE"] = 640;
            flights["EWR"]["SCE"] = 220;
            distance = flights[from][to]; // Get the distance between origin and destination
            std::cout << "Plane Created with a tail number " << this << std::endl;
        }

        // Destructor
        ~Plane()
        {
            std::cout << "Plane Destroyed" << std::endl;
        }

        // Function to operate the plane
        void operate(double dt)
        {
            // Update position based on velocity and time
            if (pos < distance)
            {
                pos += vel * dt / 3600;
                at_SCE = false;
            }
            else if (destination == "SCE")
            {
                at_SCE = true;
                swap(origin, destination);
                pos = 0.0;
            }
            else
            {
                swap(origin, destination);
                pos = 0.0;
            }

        }

        // Getter and setter functions
        double getPos() const { return pos; }
        double getVel() const { return vel; }
        void setVel(double newVel) { vel = newVel; }
        std::string getOrigin() const { return origin; }
        std::string getDestination() const { return destination; }
        bool getAtSCE() const { return at_SCE; }
        double getDistance() const { return distance; }
    };

    // Plane class
    std::string origin, destination;

    // Prompt the user to enter the origin and destination airports
    std::cout << "Enter the origin airport code: ";
    std::cin >> origin;

    std::cout << "Enter the destination airport code: ";
    std::cin >> destination;

    // Create a plane object with user-input origin and destination
    Plane myPlane(origin, destination);

    std::cout << "Plane Origin: " << myPlane.getOrigin() << std::endl;
    std::cout << "Plane Destination: " << myPlane.getDestination() << std::endl;
    std::cout << "Distance between " << origin << " and " << destination << ": " << myPlane.getDistance() << " miles" << std::endl;


    // Set the speed of the airplane between 400-500 mph
    double speed = 400 + rand() % 101; // Random speed between 400 and 500 mph
    myPlane.setVel(speed);

    std::cout << "Current Position: " << myPlane.getPos() << " miles" << std::endl;


    // Pick a timestep between [10, 100]
    double timestep = 10 + rand() % 91; // Random timestep between 10 and 100

    // Choose the maximum number of iterations between [1000, 2000]
    int max_iterations = 1000 + rand() % 1001; // Random number of iterations between 1000 and 2000

    double flighttime = 0;

    // Iteratively call the operate function with timestep as input
    for (int i = 0; i < max_iterations; ++i)
    {
        myPlane.operate(timestep);

        // Print out the airplane position at each timestep
        std::cout << "Time: " << flighttime << " seconds, Current Position: " << myPlane.getPos() << " miles" << std::endl;

        flighttime += timestep;

    }

    // Create Pilot objects
    Pilot pilot1("Alpha", &myPlane);
    Pilot pilot2("Bravo", &myPlane);

    // Iteratively call the operate function with timestep as input
    for (int i = 0; i < max_iterations; ++i)
    {
        myPlane.operate(timestep);

        if (myPlane.getAtSCE())
        {
            std::cout << "The Plane " << &myPlane << " is at SCE" << std::endl;
            if (i % 2 == 0)
            {
                myPlane.operate(timestep);
                std::cout << "Pilot " << pilot1.getName() << " with certificate number " << &pilot1 << " is in control of a plane: " << &myPlane << std::endl;
                std::cout << "Pilot " << pilot2.getName() << " with certificate number " << &pilot2 << " is in control of a plane: " << "0000000000000000" << std::endl;

            }
            else
            {
                myPlane.operate(timestep);
                std::cout << "Pilot " << pilot2.getName() << " with certificate number " << &pilot2 << " is in control of a plane: " << &myPlane << std::endl;
                std::cout << "Pilot " << pilot1.getName() << " with certificate number " << &pilot1 << " is in control of a plane: " << "0000000000000000" << std::endl;

            }

        }

    }

////    Old CPP Style
//
//   // Create Pilot objects
//    Pilot* pilot1 = new Pilot("Alpha", &myPlane);
//    Pilot* pilot2 = new Pilot("Bravo", &myPlane);
//
//    // Iteratively call the operate function with timestep as input
//    for (int i = 0; i < max_iterations; ++i)
//    {
//        myPlane.operate(timestep);
//
//        if (myPlane.getAtSCE())
//        {
//            std::cout << "The Plane " << &myPlane << " is at SCE" << std::endl;
//            if (i % 2 == 0)
//            {
//                myPlane.operate(timestep);
//                std::cout << "Pilot " << pilot1->getName() << " with certificate number " << pilot1 << " is in control of a plane: " << &myPlane << std::endl;
//                std::cout << "Pilot " << pilot2->getName() << " with certificate number " << pilot2 << " is in control of a plane: " << "0000000000000000" << std::endl;
//
//            }
//            else
//            {
//                myPlane.operate(timestep);
//                std::cout << "Pilot " << pilot2->getName() << " with certificate number " << pilot2 << " is in control of a plane: " << &myPlane << std::endl;
//                std::cout << "Pilot " << pilot1->getName() << " with certificate number " << pilot1 << " is in control of a plane: " << "0000000000000000" << std::endl;
//
//            }
//
//        }
//
//    }
//
//    // Free memory allocated for Pilot objects
//    delete pilot1;
//    delete pilot2;
//

    return 0;
}
