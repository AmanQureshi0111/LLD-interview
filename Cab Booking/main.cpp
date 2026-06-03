#include <iostream>
#include <vector>

using namespace std;

class Rider {

    string name;

public:

    Rider(string name)
        : name(name) {}

    string getName() {
        return name;
    }
};

class Driver {

    string name;
    bool available;

public:

    Driver(string name)
        : name(name),
          available(true) {}

    string getName() {
        return name;
    }

    bool isAvailable() {
        return available;
    }

    void setAvailable(
        bool value
    ) {
        available = value;
    }
};

class PricingStrategy {

public:

    virtual double calculateFare(
        double distance
    ) = 0;

    virtual ~PricingStrategy() {}
};

class NormalPricing :
    public PricingStrategy {

public:

    double calculateFare(
        double distance
    ) override {

        return distance * 10;
    }
};

class Trip {

    Rider* rider;
    Driver* driver;
    double fare;

public:

    Trip(
        Rider* rider,
        Driver* driver,
        double fare
    )
    : rider(rider),
      driver(driver),
      fare(fare) {}

    void display() {

        cout
            << "Driver Assigned: "
            << driver->getName()
            << endl;

        cout
            << "Rider: "
            << rider->getName()
            << endl;

        cout
            << "Fare = Rs "
            << fare
            << endl;
    }
};

class CabService {

    vector<Driver*> drivers;

    PricingStrategy* pricing;

public:

    CabService(
        PricingStrategy* pricing
    )
    : pricing(pricing) {}

    void addDriver(
        Driver* driver
    ) {

        drivers.push_back(
            driver
        );
    }

    Trip* bookRide(
        Rider* rider,
        double distance
    ) {

        for(
            auto driver :
            drivers
        ) {

            if(
                driver->isAvailable()
            ) {

                driver->setAvailable(
                    false
                );

                double fare =
                    pricing
                    ->calculateFare(
                        distance
                    );

                return new Trip(
                    rider,
                    driver,
                    fare
                );
            }
        }

        return nullptr;
    }
};

int main() {

    Driver d1("Rahul");
    Driver d2("Rohit");

    Rider rider("Aman");

    NormalPricing pricing;

    CabService service(
        &pricing
    );

    service.addDriver(&d1);
    service.addDriver(&d2);

    Trip* trip =
        service.bookRide(
            &rider,
            12
        );

    if(trip)
        trip->display();
    else
        cout
            << "No Driver Available";
    return 0;
    
}