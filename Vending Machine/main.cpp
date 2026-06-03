#include <iostream>
#include <unordered_map>

using namespace std;

class Product {

    string name;
    int price;

public:

    Product(
        string name,
        int price
    ) : name(name),
        price(price) {}

    string getName() {
        return name;
    }

    int getPrice() {
        return price;
    }
};

class Inventory {

    unordered_map<
        string,
        pair<Product*, int>
    > products;

public:

    void addProduct(
        Product* product,
        int quantity
    ) {

        products[
            product->getName()
        ] =
        {
            product,
            quantity
        };
    }

    bool available(
        string name
    ) {

        return products.count(name)
            &&
            products[name].second
            > 0;
    }

    Product* getProduct(
        string name
    ) {

        return products[name]
            .first;
    }

    void reduceQuantity(
        string name
    ) {

        products[name]
            .second--;
    }
};

class VendingMachine;
class State;
class IdleState;
class HasMoneyState;

class State {

public:

    virtual void insertMoney(
        VendingMachine*,
        int
    ) {}

    virtual void selectProduct(
        VendingMachine*,
        string
    ) {}

    virtual ~State() {}
};

class VendingMachine {

    State* state;

    Inventory inventory;

    int money;

public:

    VendingMachine();

    void setState(
        State* s
    ) {
        state = s;
    }

    Inventory&
    getInventory() {
        return inventory;
    }

    int getMoney() {
        return money;
    }

    void addMoney(
        int amount
    ) {
        money += amount;
    }

    void resetMoney() {
        money = 0;
    }

    void insertMoney(
        int amount
    ) {
        state->insertMoney(
            this,
            amount
        );
    }

    void selectProduct(
        string name
    ) {
        state->selectProduct(
            this,
            name
        );
    }
};

class IdleState :
    public State {

public:

    void insertMoney(
        VendingMachine* vm,
        int amount
    ) override;
};

class HasMoneyState :
    public State {

public:

    void selectProduct(
        VendingMachine* vm,
        string product
    ) override;
};

void IdleState::insertMoney(
    VendingMachine* vm,
    int amount
) {

    vm->addMoney(amount);

    cout
        << "Inserted Rs "
        << amount
        << endl;

    vm->setState(
        new HasMoneyState()
    );
}

void HasMoneyState::selectProduct(
    VendingMachine* vm,
    string productName
) {

    Inventory& inv =
        vm->getInventory();

    if(
        !inv.available(
            productName
        )
    ) {

        cout
            << "Unavailable\n";

        return;
    }

    Product* product =
        inv.getProduct(
            productName
        );

    if(
        vm->getMoney()
        < product->getPrice()
    ) {

        cout
            << "Insufficient Money\n";

        return;
    }

    inv.reduceQuantity(
        productName
    );

    cout
        << "Dispensed "
        << productName
        << endl;

    cout
        << "Change = "
        << vm->getMoney()
           - product->getPrice()
        << endl;

    vm->resetMoney();

    vm->setState(
        new IdleState()
    );
}

VendingMachine::
VendingMachine() {

    state =
        new IdleState();

    money = 0;
}

int main() {

    Product coke(
        "Coke",
        40
    );

    Product chips(
        "Chips",
        20
    );

    VendingMachine vm;

    vm.getInventory()
      .addProduct(
          &coke,
          10
      );

    vm.getInventory()
      .addProduct(
          &chips,
          5
      );

    vm.insertMoney(
        50
    );

    vm.selectProduct(
        "Coke"
    );

    return 0;
}