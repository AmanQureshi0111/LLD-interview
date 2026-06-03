#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Interference
class Observer{
public:
    virtual void update(string message) = 0;
    virtual ~Observer(){}
};

class User: public Observer{
    string name;
public:
    User(string name){
        this->name=name;
    }
    void update(string msg) override {
        cout
            <<name
            <<" received: "
            <<msg
            <<endl;
    }
    string getName(){
        return name;
    }
};

class NotificationService{
    vector<Observer*> observers;
public:
    void subscribe(Observer* observer){
        observers.push_back(observer);
    }
    void unsubscribe(Observer* observer){
        observers.erase(
            remove(
                observers.begin(),
                observers.end(),
                observer
            ),
            observers.end()
        );
    }
    void notifyAll(string msg){
        for(auto observer:observers){
            observer->update(msg);
        }
    }
};

int main(){
    User aman("Aman");
    User rahul("Rahul");
    User rohit("Rohit");

    NotificationService service;

    service.subscribe(&rahul);
    service.subscribe(&aman);
    service.subscribe(&rohit);

    service.notifyAll("Cashback of Rs 100 credited");

    service.unsubscribe(&rohit);
    service.notifyAll("Cashback of Rs 200 credited");

    return 0;
}