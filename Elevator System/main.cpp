#include <iostream>
#include <queue>
using namespace std;

enum class Direction{
    UP,
    DOWN,
    IDLE
};

class Request{
private:
    int sourceFloor;
    int destinationFloor;
public:
    Request(int source,int dest)
    :   sourceFloor(source),
        destinationFloor(dest)
    {}
};

class Elevator{
private:
    int currentFloor;
    Direction direction;
    queue<int> requests;
public:
    Elevator(){
        currentFloor=0;
        direction=Direction::IDLE;
    }

    int getCurrentFloor() {
        return currentFloor;
    }
    Direction getDirection(){
        return direction;
    }
    void addRequest(int floor){
        requests.push(floor);
    }
    bool hasPendingRequests(){
        return !requests.empty();
    }
    void moveOneStep(){
        if(requests.empty()){
            direction=Direction::IDLE;
            return;
        }
        int targetFloor=requests.front();
        if(currentFloor<targetFloor){
            direction=Direction::UP;
            currentFloor++;
        }else if(currentFloor>targetFloor){
            direction=Direction::DOWN;
            currentFloor--;
        }

        cout
            <<"Elevator at Floor"
            <<currentFloor
            <<endl;
        if(currentFloor==targetFloor){
            cout
                <<"Reached Floor "
                <<targetFloor
                <<endl;
            requests.pop();
        }
    }
};

class ElevatorController{
private:
    Elevator elevator;
public:
    void submitRequest(
        int source,
        int dest
    ){
        elevator.addRequest(source);
        elevator.addRequest(dest);
    }
    void run(){
        while(elevator.hasPendingRequests()){
            elevator.moveOneStep();
        }
    }
};

int main(){
    ElevatorController controller;
    controller.submitRequest(3,7);
    controller.submitRequest(2,5);
    controller.run();
    return 0;
}

/*
Sample Output:
Elevator at Floor1
Elevator at Floor2
Elevator at Floor3
Reached Floor 3
Elevator at Floor4
Elevator at Floor5
Elevator at Floor6
Elevator at Floor7
Reached Floor 7
Elevator at Floor6
Elevator at Floor5
Elevator at Floor4
Elevator at Floor3
Elevator at Floor2
Reached Floor 2
Elevator at Floor3
Elevator at Floor4
Elevator at Floor5
Reached Floor 5

*/