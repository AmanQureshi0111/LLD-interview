# Parking Lot System (LLD - C++)

## Sample Output

```text
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
```

---

## Design Decisions

### Why Inheritance?

The `Vehicle` class serves as the base class for all vehicle types.

```text
Vehicle
├── Car
└── Bike
```

Benefits:

- Promotes code reuse.
- Supports polymorphism.
- Makes the system extensible.

New vehicle types can be added easily:

```text
Vehicle
├── Car
├── Bike
├── Truck
├── Bus
└── EVCar
```

No existing code needs to be modified.

---

### Why Composition?

A Parking Lot contains multiple Parking Spots.

```text
ParkingLot
    └── ParkingSpot
```

This represents a **HAS-A** relationship.

Benefits:

- Better modularity.
- Easier maintenance.
- Loose coupling between components.

---

## SOLID Principles Used

### 1. Single Responsibility Principle (SRP)

Each class has a single responsibility.

| Class | Responsibility |
|---------|--------------|
| Vehicle | Stores vehicle information |
| ParkingSpot | Manages parking spot state |
| Ticket | Handles ticket generation |
| ParkingLot | Coordinates parking operations |

---

### 2. Open/Closed Principle (OCP)

The system is open for extension but closed for modification.

Example:

To support a new vehicle type:

```cpp
class Truck : public Vehicle {
};
```

No existing classes need to be changed.

---

## Possible Interview Extensions

### Q1. How would you support Trucks?

Add a new vehicle type:

```cpp
enum class VehicleType {
    CAR,
    BIKE,
    TRUCK
};
```

Create a new derived class:

```cpp
class Truck : public Vehicle {
public:
    Truck(string number)
        : Vehicle(number, VehicleType::TRUCK) {}
};
```

---

### Q2. How would you calculate Parking Fees?

Use the Strategy Design Pattern.

```cpp
class PricingStrategy {
public:
    virtual int calculateFee(int hours) = 0;
    virtual ~PricingStrategy() = default;
};
```

Example strategies:

```cpp
class CarPricingStrategy : public PricingStrategy {};
class BikePricingStrategy : public PricingStrategy {};
```

Benefits:

- Supports different pricing rules.
- Follows OCP.
- Easy to extend.

---

### Q3. How would you support Multiple Floors?

Introduce a new abstraction:

```text
ParkingLot
    └── ParkingFloor
            └── ParkingSpot
```

Example:

```cpp
class ParkingFloor {
    vector<ParkingSpot> spots;
};
```

Benefits:

- Supports large parking structures.
- Better scalability.

---

### Q4. How would you find the Nearest Available Spot Efficiently?

### Current Approach

```cpp
vector<ParkingSpot>
```

Time Complexity:

```text
O(N)
```

Linear search through all spots.

### Optimized Approach

Maintain available spots separately:

```cpp
queue<ParkingSpot*>
```

or

```cpp
priority_queue<ParkingSpot*>
```

Time Complexity:

```text
O(1)  -> queue
O(log N) -> priority_queue
```

Benefits:

- Faster allocation.
- Better performance at scale.

---

## Class Diagram

```text
+----------------+
|    Vehicle     |
+----------------+
| vehicleNumber  |
| vehicleType    |
+----------------+
        ^
        |
  +-----+-----+
  |           |
+------+   +------+
| Car  |   | Bike |
+------+   +------+

+----------------+
|  ParkingSpot   |
+----------------+
| id             |
| occupied       |
+----------------+

+----------------+
|     Ticket     |
+----------------+
| ticketId       |
| vehicle        |
| spot           |
+----------------+

+----------------+
|   ParkingLot   |
+----------------+
| spots          |
+----------------+
```

---
