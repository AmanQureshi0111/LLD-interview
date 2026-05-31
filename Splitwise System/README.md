# Splitwise System (LLD - C++)

## Problem Statement

Design a Splitwise-like expense sharing system where users can:

- Add users
- Add expenses
- Split expenses equally
- Split expenses exactly
- Split expenses by percentage
- View balances between users

---

## Requirements

### Functional Requirements

- Create users.
- Record expenses.
- Support multiple split types:
  - Equal Split
  - Exact Split
  - Percentage Split
- Track balances.
- Show who owes whom.

---

## Example

### Expense

```text
Aman paid ₹300

Participants:
Aman
Rahul
Rohit
```

### Equal Split

```text
300 / 3 = ₹100
```

Result:

```text
Rahul owes Aman ₹100
Rohit owes Aman ₹100
```

---

## Entities

### User

Represents a person using the application.

### Expense

Represents a payment made by a user.

### Split

Represents how an expense is distributed among users.

### ExpenseManager

Responsible for:

- Managing expenses
- Updating balances
- Viewing balances

---

## Relationships

### Composition

```text
Expense
    ├── Paid By (User)
    └── Splits

ExpenseManager
    └── Expenses
```

### Why Composition?

- An Expense contains multiple splits.
- ExpenseManager manages expenses and balances.

This follows a **HAS-A** relationship.

---

## Sample Flow

```text
Expense Added

Paid By: Aman
Amount : ₹300

Participants:
Aman
Rahul
Rohit
```

Output:

```text
Rahul owes Aman ₹100
Rohit owes Aman ₹100
```

---

## Balance Representation

Store balances using nested hash maps.

```cpp
unordered_map<
    string,
    unordered_map<string,double>
> balances;
```

Example:

```text
balances["Rahul"]["Aman"] = 100
balances["Rohit"]["Aman"] = 100
```

Meaning:

```text
Rahul owes Aman ₹100
Rohit owes Aman ₹100
```

---

## Design Decisions

### Why HashMap?

Balances can be updated efficiently.

```cpp
O(1)
```

average time complexity.

Benefits:

- Fast lookup
- Fast updates
- Scales well for many users

---

## SOLID Principles Used

### 1. Single Responsibility Principle (SRP)

| Class | Responsibility |
|---------|--------------|
| User | User information |
| Split | Split details |
| Expense | Expense data |
| ExpenseManager | Balance management |

---

### 2. Open/Closed Principle (OCP)

New split types can be added without modifying existing code.

Example:

```cpp
class CustomSplitStrategy
    : public SplitStrategy {
};
```

---

## Interview Follow-Up Questions

### Q1. How to Support Equal Split?

Already supported.

Example:

```text
Amount = 300
Users = 3

Share = 100
```

Result:

```text
Rahul owes Aman ₹100
Rohit owes Aman ₹100
```

---

### Q2. How to Support Exact Split?

Example:

```text
Aman paid ₹300

Rahul owes ₹120
Rohit owes ₹80
Aman owes ₹100
```

Input:

```cpp
vector<double> exactAmounts;
```

Example:

```cpp
{100,120,80}
```

Validation:

```text
Sum of exact amounts
must equal expense amount.
```

---

### Q3. How to Support Percentage Split?

Example:

```text
Aman  = 50%
Rahul = 30%
Rohit = 20%
```

Expense:

```text
₹1000
```

Calculated Shares:

```text
Aman  = ₹500
Rahul = ₹300
Rohit = ₹200
```

Create:

```cpp
class PercentSplit : public Split {
};
```

---

## Strategy Pattern (Important)

Instead of hardcoding split logic inside ExpenseManager:

Create an abstraction.

```cpp
class SplitStrategy {
public:
    virtual vector<Split*>
    calculate() = 0;

    virtual ~SplitStrategy() = default;
};
```

Implementations:

```cpp
EqualSplitStrategy
ExactSplitStrategy
PercentSplitStrategy
```

Architecture:

```text
ExpenseManager
        |
        v
  SplitStrategy
        |
   +----+----+
   |    |    |
 Equal Exact Percent
```

Benefits:

- Easily extensible
- Cleaner code
- Follows OCP

ExpenseManager doesn't care how splits are calculated.

---

## Follow-Up Q4: How to Simplify Debts?

Current Balances:

```text
Rahul owes Aman ₹100
Aman owes Rohit ₹100
```

Can be simplified to:

```text
Rahul owes Rohit ₹100
```

### Approach

Compute net balance for each user.

Example:

```text
Aman  :  0
Rahul : -100
Rohit : +100
```

Generate minimum transactions:

```text
Rahul → Rohit ₹100
```

This is called:

```text
Debt Simplification
Debt Netting
```

Used in real Splitwise systems.

---

## Class Diagram

```text
+----------------+
|      User      |
+----------------+
| id             |
| name           |
+----------------+

+----------------+
|     Split      |
+----------------+
| user           |
| amount         |
+----------------+

+----------------+
|    Expense     |
+----------------+
| paidBy         |
| amount         |
| splits         |
+----------------+

+----------------------+
|   SplitStrategy      |
+----------------------+
| calculate()          |
+----------------------+
           ^
           |
   +-------+-------+
   |       |       |
 Equal   Exact  Percent

+----------------------+
|   ExpenseManager     |
+----------------------+
| expenses             |
| balances             |
+----------------------+
```

---

## Time Complexity

### Add Expense

```text
O(K)
```

where K = number of participants.

### View Balance

```text
O(1)
```

average lookup using HashMap.

### Debt Simplification

```text
O(N log N)
```

where N = number of users.

---

## Future Enhancements

- Group Expenses
- Expense Categories
- Recurring Expenses
- Currency Conversion
- Debt Simplification
- Expense History
- Expense Editing
- Settlement Tracking
- Notifications
- Splitwise Group Support
- Multi-Currency Support

---

## Design Patterns Discussed

### Strategy Pattern

Used for:

```text
Equal Split
Exact Split
Percentage Split
```

### Factory Pattern (Optional)

Create split strategies dynamically.

```cpp
SplitStrategyFactory
```

### Singleton Pattern (Optional)

Single instance of:

```cpp
ExpenseManager
```

throughout the application.