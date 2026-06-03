# Notification System (LLD - C++)

## Problem Statement

Design a Notification System capable of:

- Subscribing users
- Unsubscribing users
- Sending notifications to all subscribers
- Supporting multiple notification channels
- Extending notification types without modifying existing code

This problem is one of the most common examples used to demonstrate the **Observer Design Pattern**.

---

## Real-World Examples

- UPI Transaction Alerts
- Cashback Notifications
- Email Notifications
- SMS Alerts
- Stock Price Alerts
- YouTube Subscriber Notifications
- E-commerce Order Updates

---

## Requirements

### Functional Requirements

- Users can subscribe.
- Users can unsubscribe.
- Send notifications to all subscribers.
- Support multiple notification channels.
- Support user notification preferences.

---

## Example

```text
POP sends cashback notification

Subscribers:
Aman
Rahul
Rohit
```

Output:

```text
Notification sent to Aman
Notification sent to Rahul
Notification sent to Rohit
```

---

## Entities

### Observer

Represents a subscriber interface.

### User

Concrete observer implementation.

### NotificationService

Publisher responsible for notifying all subscribers.

---

## Relationships

### Observer Pattern

```text
        Observer
            ^
            |
          User

NotificationService
        |
        +---- List<Observer*>
```

---

## Why Observer Pattern?

### Bad Design

```cpp
user1.notify();
user2.notify();
user3.notify();
user4.notify();
```

Problems:

- Tight coupling
- Hard to maintain
- New users require code changes

---

### Better Design

```cpp
service.subscribe(user);
```

Then:

```cpp
service.notifyAll();
```

Benefits:

- Loose coupling
- Easy to extend
- Supports dynamic subscribers

Follows:

```text
Open Closed Principle
```

---

## Sample Flow

### Subscribe Users

```cpp
service.subscribe(aman);
service.subscribe(rahul);
service.subscribe(rohit);
```

---

### Send Notification

```cpp
service.notifyAll(
    "Cashback credited!"
);
```

Output:

```text
Aman received:
Cashback credited!

Rahul received:
Cashback credited!

Rohit received:
Cashback credited!
```

---

## SOLID Principles Used

### 1. Single Responsibility Principle (SRP)

| Class | Responsibility |
|---------|--------------|
| Observer | Notification contract |
| User | Receive notifications |
| NotificationService | Manage subscribers |

---

### 2. Open Closed Principle (OCP)

New observer types can be added without changing NotificationService.

Example:

```cpp
class MobileUser
    : public Observer
{
};
```

---

### 3. Dependency Inversion Principle (DIP)

NotificationService depends on:

```cpp
Observer
```

instead of:

```cpp
User
```

---

## Design Pattern: Observer Pattern ⭐

### Publisher

```cpp
NotificationService
```

### Subscribers

```cpp
User
```

Flow:

```text
Subscribe
      |
      v
NotificationService
      |
      v
Notify All Observers
```

---

## Class Diagram

```text
+----------------+
|   Observer     |
+----------------+
| update(msg)    |
+----------------+
         ^
         |
+----------------+
|      User      |
+----------------+
| name           |
+----------------+
| update()       |
+----------------+

+----------------------+
| NotificationService  |
+----------------------+
| observers            |
+----------------------+
| subscribe()          |
| unsubscribe()        |
| notifyAll()          |
+----------------------+
```

---

# Interview Follow-Up Questions

## Q1. How to Support Multiple Notification Types?

Examples:

```text
Email
SMS
Push Notification
```

Create abstraction:

```cpp
class NotificationChannel {
public:
    virtual void send(
        string msg
    ) = 0;

    virtual ~NotificationChannel() = default;
};
```

Implement:

```cpp
EmailChannel
SMSChannel
PushChannel
```

Architecture:

```text
NotificationChannel
        ^
        |
 +------+------+ 
 |      |      |
Email   SMS   Push
```

This introduces the:

```text
Strategy Pattern
```

---

## Q2. How to Support Notification Priority?

Introduce:

```cpp
enum class Priority {
    LOW,
    MEDIUM,
    HIGH
};
```

Store notifications using:

```cpp
priority_queue
```

Example:

```text
HIGH
MEDIUM
LOW
```

Higher priority notifications are delivered first.

---

## Q3. How to Support Async Notifications?

Real-world systems rarely send notifications directly.

Architecture:

```text
Notification Service
        |
        v
 Message Queue
        |
        v
Consumers
```

Technologies:

```text
Kafka
RabbitMQ
Amazon SQS
```

Producer:

```text
NotificationService
```

Consumers:

```text
Email Service
SMS Service
Push Service
```

Benefits:

- Scalability
- Reliability
- Retry mechanisms
- High throughput

---

## Q4. How to Support User Preferences?

Example:

```text
Aman:
Email
Push

Rahul:
SMS Only
```

Store channels inside User:

```cpp
vector<NotificationChannel*>
```

Class Diagram:

```text
User
 |
 +---- EmailChannel
 |
 +---- PushChannel
```

During notification:

```cpp
for(channel : channels)
{
    channel->send(msg);
}
```

Benefits:

- Personalized delivery
- Extensible design

---

## Time Complexity

### Subscribe

```text
O(1)
```

### Unsubscribe

```text
O(N)
```

### Notify All Users

```text
O(N)
```

Where:

```text
N = Number of Subscribers
```

---

## Future Enhancements

- Notification Scheduling
- Notification Templates
- Retry Mechanism
- User Preferences
- Notification History
- Read/Unread Tracking
- Delivery Reports
- Multi-Channel Delivery
- Distributed Messaging
- Real-Time Push Notifications

---

## Design Patterns Discussed

### Observer Pattern ⭐

Core pattern used for:

```text
Subscribe
Unsubscribe
Notify
```

---

### Strategy Pattern

Used for:

```text
Email Notifications
SMS Notifications
Push Notifications
```

---

### Factory Pattern

Create channels dynamically.

```cpp
NotificationChannelFactory
```

---

### Singleton Pattern (Optional)

Single notification manager:

```cpp
NotificationService
```

throughout the application.

---

## Interview Summary

### Concepts Tested

- Observer Pattern ⭐
- Strategy Pattern
- OOP
- SOLID Principles
- Extensible Design
- Event-Driven Architecture
- Async Processing
- Queue Systems

### Key Interview Answer

**Why Observer Pattern?**

> NotificationService does not need to know who its subscribers are. It only maintains a list of observers and notifies them. New subscribers can be added without modifying NotificationService, which follows the Open/Closed Principle.