# ATM Machine System (LLD - C++)

## Problem Statement

Design an ATM Machine that supports:

- Card Insertion
- PIN Authentication
- Balance Inquiry
- Cash Withdrawal
- Exit Session

The primary goal of this design is to demonstrate the **State Design Pattern**, one of the most frequently asked LLD concepts in interviews.

---

## Requirements

### Functional Requirements

- Insert Card
- Enter PIN
- Check Balance
- Withdraw Cash
- Exit Session

---

## ATM Flow

```text
Idle
 ↓
Insert Card
 ↓
Enter PIN
 ↓
Select Operation
 ↓
Withdraw Cash / Check Balance
 ↓
Exit
```

---

## Entities

### ATM

Represents the ATM machine.

Responsibilities:

- Maintain current state
- Hold available cash
- Coordinate operations

---

### ATMState

Defines ATM behavior for each state.

Responsibilities:

- Insert Card
- Authenticate User
- Withdraw Cash
- Check Balance
- Exit

---

### Card

Represents a debit/ATM card.

Responsibilities:

- Card number
- PIN verification
- Linked bank account

---

### BankAccount

Represents user's account.

Responsibilities:

- Store balance
- Debit money
- Credit money

---

## Relationships

### Composition

```text
ATM
 ├── ATMState
 ├── CashDispenser
 └── Card

Card
 └── BankAccount
```

---

## Why State Pattern?

### Bad Design

```cpp
if(state == IDLE)
{
}
else if(state == CARD_INSERTED)
{
}
else if(state == AUTHENTICATED)
{
}
```

As requirements grow:

```text
Maintenance
Cash Refill
Blocked Card
Network Failure
```

Code becomes difficult to maintain.

---

### Better Design

Create separate state classes.

```text
ATMState
   |
   +-- IdleState
   +-- HasCardState
   +-- AuthenticatedState
```

Each state handles its own behavior.

Benefits:

- Cleaner code
- Easy extension
- Follows Open/Closed Principle
- Interview-friendly design

---

## State Flow

```text
+-------------------+
|     IdleState     |
+-------------------+
          |
          v
+-------------------+
|   HasCardState    |
+-------------------+
          |
          v
+-------------------+
| AuthenticatedState|
+-------------------+
          |
          v
+-------------------+
|     IdleState     |
+-------------------+
```

---

## SOLID Principles Used

### 1. Single Responsibility Principle (SRP)

| Class | Responsibility |
|---------|--------------|
| ATM | Coordinates ATM operations |
| ATMState | Defines ATM behavior |
| Card | Stores card information |
| BankAccount | Manages account balance |
| CashDispenser | Dispenses cash |

---

### 2. Open/Closed Principle (OCP)

New ATM states can be added without modifying existing states.

Example:

```cpp
class MaintenanceState
    : public ATMState
{
};
```

---

### 3. Dependency Inversion Principle (DIP)

ATM depends on abstraction:

```cpp
ATMState
```

instead of concrete states.

---

## Sample Flow

### Insert Card

```text
Current State:
IdleState
```

User inserts card.

```text
Transition:
IdleState
    →
HasCardState
```

---

### Enter PIN

```text
PIN Correct
```

Transition:

```text
HasCardState
    →
AuthenticatedState
```

---

### Withdraw Cash

```text
Balance = ₹10,000
Withdraw = ₹2,000
```

Result:

```text
Cash Dispensed
Remaining Balance = ₹8,000
```

---

### Exit

```text
Card Returned
Session Closed
```

Transition:

```text
AuthenticatedState
    →
IdleState
```

---

## Interview Follow-Up Questions

### Q1. How to Support Check Balance?

Add to state interface:

```cpp
virtual void checkBalance()
{
}
```

Implement inside:

```cpp
AuthenticatedState
```

Only authenticated users can view balance.

---

### Q2. How to Support Deposit?

Add:

```cpp
virtual void deposit()
{
}
```

to:

```cpp
ATMState
```

Implementation:

```cpp
AuthenticatedState
```

Flow:

```text
Insert Card
→ Enter PIN
→ Deposit Money
→ Balance Updated
```

---

### Q3. How to Support Cash Denominations?

Introduce:

```cpp
class CashDispenser
{
};
```

Supported notes:

```text
₹2000
₹500
₹200
₹100
```

Example:

```text
Withdraw ₹3700
```

Output:

```text
1 × ₹2000
3 × ₹500
1 × ₹200
```

---

### Q4. How to Support Multiple Banks?

Create abstraction:

```cpp
class BankService
{
public:
    virtual bool validatePIN() = 0;
    virtual double getBalance() = 0;
    virtual bool withdraw() = 0;
};
```

Implementations:

```text
HDFCBankService
ICICIBankService
SBIBankService
AxisBankService
```

Benefits:

- ATM becomes bank-independent.
- Easy integration of new banks.

---

## Cash Withdrawal Design

```text
ATM
  |
  v
BankAccount
  |
  v
CashDispenser
```

Steps:

```text
1. Validate PIN
2. Check Balance
3. Check ATM Cash
4. Debit Account
5. Dispense Cash
6. Print Receipt
```

---

## Class Diagram

```text
+----------------+
|      ATM       |
+----------------+
| currentState   |
| cashAvailable  |
+----------------+
| setState()     |
+----------------+

        |
        v

+----------------+
|    ATMState    |
+----------------+
| insertCard()   |
| enterPIN()     |
| withdraw()     |
| checkBalance() |
| exit()         |
+----------------+
        ^
        |
+-------+--------+
|       |        |
v       v        v

Idle   HasCard  Authenticated


+----------------+
|      Card      |
+----------------+
| cardNumber     |
| pin            |
+----------------+

        |
        v

+----------------+
| BankAccount    |
+----------------+
| balance        |
+----------------+

+----------------+
| CashDispenser  |
+----------------+
| dispenseCash() |
+----------------+
```

---

## Time Complexity

### PIN Verification

```text
O(1)
```

### Check Balance

```text
O(1)
```

### Withdraw Cash

```text
O(D)
```

Where:

```text
D = Number of denominations
```

Typically:

```text
D = 4
```

Therefore:

```text
O(1)
```

---

## Future Enhancements

- Deposit Cash
- Mini Statement
- PIN Change
- Receipt Printing
- Card Blocking
- Cash Refill State
- Maintenance Mode
- Multi-Bank Support
- Biometric Authentication
- UPI Cash Withdrawal
- Contactless ATM Cards

---

## Design Patterns Discussed

### State Pattern ⭐

Used for:

```text
IdleState
HasCardState
AuthenticatedState
MaintenanceState
```

Most important pattern in this design.

---

### Strategy Pattern

For:

```text
Cash Dispensing Algorithms
Authentication Methods
```

---

### Factory Pattern

Create ATM states dynamically.

```cpp
ATMStateFactory
```

---

### Singleton Pattern (Optional)

Single ATM Controller:

```cpp
ATMController
```

if system requires centralized monitoring.