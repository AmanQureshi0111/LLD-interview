# Elevator System (LLD - C++)

## Problem Statement

Design an Elevator System that can:

- Handle multiple floor requests.
- Move between floors.
- Accept destination selections.
- Process requests efficiently.
- Scale to support multiple elevators.

For simplicity, this implementation supports:

- Single Elevator
- Multiple Requests
- FIFO Scheduling

---

## Requirements

### Functional Requirements

- User can request an elevator.
- User can choose a destination floor.
- Elevator moves accordingly.
- Multiple requests can be handled.
- Elevator state is maintained correctly.

---

## Entities

### Elevator

Responsible for:

- Current floor tracking
- Movement
- Processing requests

### Request

Represents:

- Source floor
- Destination floor

### ElevatorController

Responsible for:

- Managing elevator requests
- Assigning requests to elevators
- Scheduling

---

## Relationships

### Composition

```text
ElevatorController
        |
        └── Elevator
                |
                └── Requests
```

### Why Composition?

An Elevator Controller manages one or more elevators.

An Elevator owns and processes requests.

This follows a **HAS-A** relationship.

---

## Sample Flow

```text
Current Floor: 0

Request -> Floor 5
Elevator moves:
0 → 1 → 2 → 3 → 4 → 5

Request -> Floor 2
Elevator moves:
5 → 4 → 3 → 2
```

---

## Design Decisions

### Why Queue?

```cpp
queue<int> requests;
```

Requests are processed in the order they arrive.

Benefits:

- Simple implementation
- Fair scheduling
- Easy to understand

---

## Limitations

Current implementation uses:

```text
FIFO Scheduling
```

Example:

```text
Current Floor = 1

Requests:
10
2
8
```

Processing order:

```text
1 → 10 → 2 → 8
```

This causes unnecessary movement.

---

## SOLID Principles Used

### 1. Single Responsibility Principle (SRP)

| Class | Responsibility |
|---------|--------------|
| Elevator | Elevator movement and state |
| Request | Request data |
| ElevatorController | Request scheduling |

---

### 2. Open/Closed Principle (OCP)

New scheduling strategies can be added without modifying existing classes.

Example:

```cpp
class SchedulingStrategy {
public:
    virtual int getNextFloor() = 0;
};
```

Possible implementations:

```cpp
class FIFOStrategy;
class NearestFloorStrategy;
class SCANStrategy;
```

---

## Interview Follow-Up Questions

### Q1. How do we choose the Best Elevator?

Instead of a single elevator:

```cpp
vector<Elevator> elevators;
```

Inside:

```cpp
class ElevatorController
```

Choose:

- Nearest elevator
- Least loaded elevator
- Idle elevator

Example:

```text
Elevator A -> Floor 2
Elevator B -> Floor 8

Request at Floor 3

Assign Elevator A
```

---

### Q2. How can movement be optimized?

Current approach:

```cpp
queue<int>
```

Optimized approaches:

```cpp
priority_queue<int>
```

or

```cpp
set<int>
```

Example:

```text
Current Floor = 5

Requests:
2, 8, 6, 10
```

Process:

```text
5 → 6 → 8 → 10
```

Then:

```text
10 → 2
```

Much less travel.

---

### Q3. How would you support Multiple Elevators?

```text
ElevatorController
    |
    +-- Elevator 1
    +-- Elevator 2
    +-- Elevator 3
```

Controller responsibilities:

- Receive requests
- Select best elevator
- Assign requests
- Track elevator status

Benefits:

- Better scalability
- Faster response time
- Reduced waiting time

---

### Q4. How would you support Emergency Mode?

Introduce elevator states:

```cpp
enum class ElevatorState {
    IDLE,
    MOVING,
    MAINTENANCE,
    EMERGENCY
};
```

Behavior:

```text
IDLE         → Waiting
MOVING       → Serving requests
MAINTENANCE  → Unavailable
EMERGENCY    → Stop operation
```

This naturally leads to the **State Design Pattern**.

---

## Class Diagram

```text
+----------------------+
| ElevatorController   |
+----------------------+
| elevators            |
+----------------------+
          |
          v

+----------------------+
|      Elevator        |
+----------------------+
| currentFloor         |
| state                |
| requests             |
+----------------------+
| move()               |
| addRequest()         |
+----------------------+

          |
          v

+----------------------+
|      Request         |
+----------------------+
| sourceFloor          |
| destinationFloor     |
+----------------------+
```

---

## Time Complexity

### FIFO Queue

```text
Add Request     : O(1)
Process Request : O(1)
```

### Priority Queue

```text
Add Request     : O(log N)
Get Next Floor  : O(log N)
```

---

## Future Enhancements

- Multiple Elevators
- Smart Scheduling (SCAN/LOOK Algorithm)
- Priority Requests
- Emergency Handling
- Maintenance Mode
- Weight Sensors
- Overload Detection
- Door Open/Close Control
- Floor Display System
- Elevator Analytics Dashboard
- Nearest Elevator Assignment

---

## Design Patterns Discussed

### Strategy Pattern

For scheduling algorithms:

```text
FIFO
Nearest Floor
SCAN
LOOK
```

### State Pattern

For elevator states:

```text
IDLE
MOVING
MAINTENANCE
EMERGENCY
```

### Singleton Pattern (Optional)

For ElevatorController if only one controller exists in the system.