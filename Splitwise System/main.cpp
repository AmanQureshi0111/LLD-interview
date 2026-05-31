#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class User{
private:
    string id;
    string name;
public:
    User(string id,string name)
        : id(id), name(name){}
    
    string getName(){
        return name;
    }
};

class Split{
public:
    User* user;
    double amount;
    Split(
        User* user,
        double amount
    ):
        user(user),
        amount(amount) {}
    
};

class Expense{
public:
    User* paidBy;
    double amount;
    vector<Split*> splits;
    Expense(
        User* paidBy,
        double amount,
        vector<Split*> splits
    ):
        paidBy(paidBy),
        amount(amount),
        splits(splits){}
};

class ExpenseManager{
private:
    unordered_map<string,unordered_map<string,double>> balances;
public:
    void addExpense(Expense* expense){
        string payer=expense->paidBy->getName();
        for(auto split:expense->splits){
            string user=split->user->getName();
            if(user==payer) continue;
            balances[user][payer]+=split->amount;
            balances[payer][user]-=split->amount;
        }
    }
    void showBalances(){
        cout<<"\nCurrent Balance\n";
        
        for(auto &u:balances){
            for(auto &e:u.second){
                if(e.second>0){
                    cout
                        <<u.first
                        <<" owes "
                        <<e.first
                        <<" Rs "
                        <<e.second
                        <<endl;
                }
            }
        }
    }
};

int main(){
    User aman("1","Aman");
    User rahul("2","Rahul");
    User rohit("3","Rohit");

    vector<Split*> splits;

    splits.push_back(new Split(&aman,100));
    splits.push_back(new Split(&rahul,100));
    splits.push_back(new Split(&rohit,100));

    Expense* expense=
        new Expense(&aman,300,splits);
    
    ExpenseManager manager;

    manager.addExpense(expense);
    manager.showBalances();

    return 0;
}
/*
Sample Output:
Current Balance
Rohit owes Aman Rs 100
Rahul owes Aman Rs 100
*/