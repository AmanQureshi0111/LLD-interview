#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class VehicleType{
    CAR,
    BIKE
};

class Vehicle{
protected:
    string number;
    VehicleType type;
public: 
    Vehicle(string num,VehicleType t) : number(num), type(t) {}

    string getNumber(){
        return number;
    }
    VehicleType getType(){
        return type;
    }

    virtual ~Vehicle(){}
};

class Car:public Vehicle{
public:
    Car(string num) : Vehicle(num,VehicleType::CAR){}
};

class Bike : public Vehicle{
public:
    Bike(string num) : Vehicle(num,VehicleType::BIKE){}
};

class ParkingSpot{
private:
    int spotId;
    VehicleType allowedType;
    bool occupied;
    Vehicle* vehicle;
public:
    ParkingSpot(int id,VehicleType t)
        : spotId(id),
          allowedType(t),
          occupied(false),
          vehicle(nullptr) {}

    bool canPark(Vehicle* v){
        return !occupied && v->getType()==allowedType;
    }
    bool parkVehicle(Vehicle* v){
        if(!canPark(v)){
            return false;
        }
        occupied=true;
        vehicle=v;
        return true;
    }
    void removeVehicle(){
        occupied=false;
        vehicle=nullptr;
    }
    int getSpotId(){
        return spotId;
    }
    Vehicle* getVehicle(){
        return vehicle;
    }
    bool isOccupied(){
        return occupied;
    }
};

class Ticket{
private:
    static int nextId;
    int ticketId;
    string vehicleNumber;
    int spotId;
public: 
    Ticket(string vehicleNumber,int spotId)
    : vehicleNumber(vehicleNumber),
      spotId(spotId){
        ticketId=++nextId;
      }
    
    void printTicket(){
        cout<<"\n**********TICKET**********\n";
        cout<<"Ticket ID    : "<<ticketId<<endl;
        cout<<"Vehicle      : "<<vehicleNumber<<endl;
        cout<<"Spot ID      : "<<spotId<<endl;
        cout<<"**************************\n";  
    }
};

int Ticket::nextId=0;

class ParkingLot{
private:
    vector<ParkingSpot*> spots;
public:
    void addSpot(ParkingSpot* spot){
        spots.push_back(spot);
    }
    Ticket* parkVehicle(Vehicle* vehicle){
        for(auto spot:spots){
            if(spot->parkVehicle(vehicle)){
                cout<<vehicle->getNumber()
                    <<" parked at spot "
                    <<spot->getSpotId()
                    <<endl;
                return new Ticket(
                    vehicle->getNumber(),
                    spot->getSpotId()
                );
            }
        }
        cout<<"No spot available for "
            <<vehicle->getNumber()
            <<endl;
        return nullptr;
    }
    void displayStatus(){
        cout<<"\nParking Status\n";
        for(auto spot:spots){
            cout<<"Spot "
                <<spot->getSpotId()
                <<" -> ";
            if(spot->isOccupied()){
                cout<<"Occupied";
            }else{
                cout<<"Available";
            }
            cout<<endl;
        }
    }
};

int main(){
    ParkingLot lot;
    lot.addSpot(new ParkingSpot(1,VehicleType::CAR));
    lot.addSpot(new ParkingSpot(2,VehicleType::CAR));
    lot.addSpot(new ParkingSpot(3,VehicleType::BIKE));
    Car car1("TN01CAR123");
    Car car2("TN02CAR456");
    Bike bike1("TN01BIKE1");

    Ticket* t1=lot.parkVehicle(&car1);
    Ticket* t2=lot.parkVehicle(&car2);
    Ticket* t3=lot.parkVehicle(&bike1);

    if(t1) t1->printTicket();
    if(t2) t2->printTicket();
    if(t3) t3->printTicket();

    lot.displayStatus();

    return 0;
}