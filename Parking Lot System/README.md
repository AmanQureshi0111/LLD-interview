Sample Output:
TN01CAR123 parked at spot 1
TN02CAR456 parked at spot 2
TN01BIKE1 parked at spot 3

**********TICKET**********
Ticket ID    : 1
Vehicle      : TN01CAR123
Spot ID      : 1
**************************

**********TICKET**********
Ticket ID    : 2
Vehicle      : TN02CAR456
Spot ID      : 2
**************************

**********TICKET**********
Ticket ID    : 3
Vehicle      : TN01BIKE1
Spot ID      : 3
**************************

Parking Status
Spot 1 -> Occupied
Spot 2 -> Occupied
Spot 3 -> Occupied

Why inheritance?
Car : Vehicle
Bike : Vehicle

Allows easy addition of:

Truck
Bus
EVCar

without changing existing code.

Why composition?
ParkingLot HAS-A ParkingSpot

A parking lot contains spots.

SOLID Principles
SRP

Vehicle handles vehicle data.

ParkingSpot handles parking.

Ticket handles ticket details.

OCP

New vehicle types can be added without modifying old classes.

Q1. How would you support trucks?

Add:

enum class VehicleType {
    CAR,
    BIKE,
    TRUCK
};

and

class Truck : public Vehicle

Q2. How would you calculate parking fees?

Introduce Strategy Pattern:

class PricingStrategy {
public:
    virtual int calculateFee(int hours)=0;
};
Q3. How would you support multiple floors?

Add:

ParkingFloor

between:

ParkingLot
    ↓
ParkingFloor
    ↓
ParkingSpot
Q4. How would you find nearest spot efficiently?

Instead of linear search:

vector<ParkingSpot>

use:

queue<ParkingSpot*>

or

priority_queue

for available spots.