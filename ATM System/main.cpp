#include <iostream>
using namespace std;

class ATM;
class ATMState;
class IdleState;
class HasCardState;
class AuthenticatedState;

class BankAccount{
    double balance;
public:
    BankAccount(double bal) : balance(bal){}
    double getBalance(){
        return balance;
    }
    bool withdraw(double amount){
        if(balance<amount){
            return false;
        }
        balance-=amount;
        return true;
    }
};

class Card{
    string pin;
    BankAccount* account;
public:
    Card(string pin,BankAccount* account)
        : pin(pin), account(account){}
    bool validatePin(string enteredPin){
        return pin==enteredPin;
    }
    BankAccount* getAccount(){
        return account;
    }
};

class ATMState{
public:
    virtual void insertCard(ATM*,Card*){}
    virtual void enterPin(ATM*,string){}
    virtual void withdraw(ATM*,double){}
    virtual ~ATMState(){}
};

class ATM{
    ATMState* state;
    Card* card;
public:
    ATM();

    void setState(ATMState* s){
        state=s;
    }
    ATMState* getState(){
        return state;
    }
    void setCard(Card* c){
        card=c;
    }
    Card* getCard(){
        return card;
    }
    void insertCard(Card* card){
        state->insertCard(this,card);
    }
    void enterPin(string pin){
        state->enterPin(this,pin);
    }
    void withdraw(double amount){
        state->withdraw(this,amount);
    }
};

class AuthenticatedState;

class HasCardState: public ATMState{
public:
    void enterPin(ATM* atm,string pin) override;
};


class IdleState: public ATMState{
public:
    void insertCard(
        ATM* atm,
        Card* card
    ) override;
};

class AuthenticatedState: public ATMState{
public:
    void withdraw(ATM* atm,double amount) override {
        BankAccount* account=atm->getCard()->getAccount();
        if(account->withdraw(amount)){
            cout
                <<"Withdraw Rs "
                <<amount
                <<endl;
            cout
                <<"Balance = "
                <<account->getBalance()
                <<endl;
        }else{
            cout<<"Insufficient Balance\n";
        }
    }
};

void IdleState::insertCard(ATM* atm,Card* card){
    cout<<"Card Inserted\n";
    atm->setCard(card);
    atm->setState(new HasCardState());
}

void HasCardState::enterPin(
    ATM* atm,
    string pin
){
    if(atm->getCard()->validatePin(pin)){
        cout<<"PIN Verified\n";
        atm->setState(new AuthenticatedState());
    }else{
        cout<<"Invalid PIN\n";
    }
}

ATM::ATM(){
    state=new IdleState();
}

int main(){
    BankAccount account
    (5000);
    Card card("1234",&account);
    ATM atm;

    atm.insertCard(&card);

    atm.enterPin("12344");

    atm.enterPin("1234");

    atm.withdraw(1000);

    return 0;
}