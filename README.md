# LLD Interview Preparation in C++

A collection of commonly asked Low-Level Design (LLD) interview problems implemented in C++ with clean Object-Oriented Design, SOLID principles, Design Patterns, UML-style diagrams, and interview discussion points.

---

## Repository Structure

```text
LLD-interview/
│
├── ATM System/
├── Elevator System/
├── Parking Lot System/
├── Splitwise System/
│
└── README.md
```

---

## Implemented Systems

### 1. Parking Lot System

Design a parking lot capable of:

- Parking vehicles
- Generating tickets
- Managing parking spots
- Supporting multiple vehicle types

#### Concepts Covered

- OOP
- Inheritance
- Composition
- SOLID Principles
- Extensible Design

#### Design Patterns Discussed

- Strategy Pattern (Pricing)
- Factory Pattern (Optional)

---

### 2. Elevator System

Design an elevator capable of handling floor requests and movement scheduling.

#### Concepts Covered

- Queue Management
- State Management
- Controller Design
- Scheduling Algorithms

#### Design Patterns Discussed

- Strategy Pattern
- State Pattern

---

### 3. Splitwise System

Design a bill-splitting application similar to Splitwise.

#### Features

- Equal Split
- Exact Split
- Percentage Split
- Balance Tracking

#### Concepts Covered

- HashMaps
- Business Logic Modeling
- OOP
- Extensible Architecture

#### Design Patterns Discussed

- Strategy Pattern
- Factory Pattern

---

### 4. ATM System

Design an ATM machine supporting:

- Card Insertion
- PIN Validation
- Cash Withdrawal
- Balance Inquiry
- Session Management

#### Concepts Covered

- State Management
- Cash Dispensing Logic
- Banking Abstractions
- OOP

#### Design Patterns Discussed

- State Pattern
- Strategy Pattern
- Factory Pattern

---

## Design Patterns Covered

| Pattern | Systems |
|----------|----------|
| State Pattern | ATM, Elevator |
| Strategy Pattern | Splitwise, ATM, Parking Lot |
| Factory Pattern | Splitwise, ATM |
| Singleton Pattern | Optional Discussion |
| Composition | All Systems |
| Inheritance | Parking Lot, Splitwise |

---

## SOLID Principles Covered

### Single Responsibility Principle (SRP)

Every class has a single responsibility.

Example:

```text
Vehicle → Vehicle Information
ParkingSpot → Parking Management
Ticket → Ticket Details
```

---

### Open Closed Principle (OCP)

Systems can be extended without modifying existing code.

Example:

```cpp
class Truck : public Vehicle
{
};
```

---

### Liskov Substitution Principle (LSP)

Derived classes can replace base classes safely.

Example:

```cpp
Vehicle* vehicle = new Car();
```

---

### Interface Segregation Principle (ISP)

Clients should not depend on methods they do not use.

Example:

```cpp
SplitStrategy
ATMState
```

---

### Dependency Inversion Principle (DIP)

Depend on abstractions instead of concrete implementations.

Example:

```cpp
ATMState
SplitStrategy
```

---

## Common Interview Topics Covered

- Object-Oriented Design
- Class Design
- State Management
- Scheduling
- Queue Handling
- HashMap-Based Design
- Design Patterns
- Extensibility
- Scalability
- Follow-Up Discussions

---

## How to Run

Compile using g++:

```bash
g++ *.cpp -o app
```

Run:

```bash
./app
```

Windows:

```bash
g++ *.cpp -o app.exe
app.exe
```

---

## Interview Roadmap

If you're preparing for LLD interviews, follow this order:

1. Parking Lot System
2. Elevator System
3. Splitwise System
4. ATM System

These four problems cover most beginner-to-intermediate LLD interview concepts.

---

## Future Additions

Planned implementations:

- Digital Wallet
- BookMyShow
- Rate Limiter
- Vending Machine
- Tic Tac Toe
- Chess
- Library Management System
- Hotel Management System
- Food Delivery System
- Snake and Ladder
- Cache (LRU/LFU)
- Notification Service

---

## Author

**Aman Qureshi**

Engineering Student | Competitive Programmer | Software Engineering Enthusiast

GitHub: https://github.com/AmanQureshi0111
