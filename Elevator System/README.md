Elevator System 

Elevator is probably the most common LLD problem.

It teaches:

OOP
State management
Scheduling
Queue handling
Controller design

Step 1: Requirements
Functional Requirements
Multiple elevators
User presses Up/Down button
User selects destination floor
Elevator moves accordingly
Handle multiple requests

Simplification for Interview
We'll implement:
1 Elevator
Multiple requests
FIFO scheduling

Then discuss improvements.

Step 2: Identify Entities
Elevator
Request
ElevatorController

Step 3: Relationships
ElevatorController HAS-A Elevator
Elevator HAS-A Requests

Step 4: Code all Entities with their functionalites

Interview Discussion
Why Queue?
queue<int> requests;

Requests are processed in order.

Limitation
Current implementation:
FIFO scheduling
Not optimal.

Follow-up Question 1
How do we choose the best elevator?

Create:
class ElevatorController
with
vector<Elevator>
Then choose:
Nearest elevator

Follow-up Question 2
How to optimize movement?

Instead of:
FIFO
Maintain:
priority_queue
or
set
for floors.

Follow-up Question 3
How to support multiple elevators?
ElevatorController
    |
    +-- Elevator 1
    +-- Elevator 2
    +-- Elevator 3

Controller assigns requests.

Follow-up Question 4
How to support emergency mode?
Add:
enum class ElevatorState {
    MOVING,
    IDLE,
    MAINTENANCE,
    EMERGENCY
};

This introduces the State Pattern.