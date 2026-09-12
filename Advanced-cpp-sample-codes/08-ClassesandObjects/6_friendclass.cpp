// Friend classes — granting an ENTIRE other class access to your private
// members, not just one function.
//
// Compile: g++ -std=c++17 6_friendclass.cpp -o friendclass
// Run:     friendclass.exe   (Windows)   or   ./friendclass   (Linux/macOS)
#include<iostream>
using namespace std;
class B; // Forward declaration of class B

class A
{
private:
    int n1;
    // friend void add(A, B)
    // Grants ONE specific free function (not a whole class) access to A's
    // private members — a friend FUNCTION, same idea as
    // 5_friendFunction.cpp, shown here for contrast with the friend
    // CLASSES below.
    friend void add(A , B); // Declaration of friend class
};
class B
{
private:
    int n2;
    friend void add(A , B); // Declaration of friend class
};

// add(obj1, obj2)
//   obj1 - an A, passed by value.
//   obj2 - a B, passed by value.
// Because `add` was declared `friend` inside BOTH A and B, it can reach
// into both objects' private fields even though it's a free function
// belonging to neither class.
void add(A obj1, B obj2)
{
    obj1.n1 = 10;
    obj2.n2 = 20;
    cout << "Sum: " << obj1.n1 + obj2.n2 << endl;
    // Purpose of friend class is to allow access to private members of another class.
    // It is useful when two or more classes need to work closely together and share data.
    // Analogy: Think of a friend class like a trusted friend who is allowed to enter your house (class) and see things that others cannot (private members).
}


class Engine
{
private:
    int horsepower;
    // friend class Car
    // Grants EVERY member function of Car — not just one — access to
    // Engine's private members. This is the difference from the friend
    // FUNCTION above: a friend CLASS blankets the whole class's member
    // functions with access, not one function at a time.
    friend class Car; // Declare Car as a friend class
};

class Car
{
private:
    string model;
public:
    // Car(m, hp)
    //   m  - the car's model name.
    //   hp - the engine's horsepower, written directly into a LOCAL
    //        Engine object's private field, which is only possible
    //        because Car was declared `friend` inside Engine.
    Car(string m, int hp) : model(m) {
        Engine e;
        e.horsepower = hp; // Accessing private member of Engine
        cout << "Car Model: " << model << ", Horsepower: " << e.horsepower << endl;
    }

};

class BankAccount {
private:
    double balance;
    string name;
    friend class BankManager; // Declare BankManager as a friend class

public:
    // BankAccount(n, b)
    //   n - the account holder's name.
    //   b - the opening balance.
    BankAccount(string n, double b)
    {
        name = n;
        balance = b;
        cout << "Account created for " << name << " with balance " << balance << endl;
    }
};

class BankManager {
public:
    // setBalance(account, amount)
    //   account - the BankAccount being modified, taken by reference (so
    //             the change is visible to the caller's own object, not
    //             a throwaway copy).
    //   amount  - the new balance to set.
    void setBalance(BankAccount &account, double amount) {
        account.balance = amount; // Accessing private member of BankAccount
    }

    // getBalance(account)
    //   account - the BankAccount to read from, by reference (no copy
    //             needed just to read one field).
    double getBalance(BankAccount &account) {
        return account.balance; // Accessing private member of BankAccount
    }
};

int main()
{
    BankAccount account("John Doe", 500.0);
    BankManager manager;
    manager.setBalance(account, 1000.0);
    double accbal = manager.getBalance(account);
    cout << "Updated Balance: " << accbal << endl;
    //Car car("Toyota", 150);
    // A a;
    // B b;
    // add(a, b); // Call friend function
    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  BankAccount account("John Doe", 500.0) runs the constructor:
//         name="John Doe", balance=500.0. Prints "Account created for
//         John Doe with balance 500".
// STEP 2  manager.setBalance(account, 1000.0): because BankManager is a
//         friend of BankAccount, this reaches directly into account's
//         PRIVATE `balance` field and overwrites it to 1000.0.
// STEP 3  manager.getBalance(account) reads that same private `balance`
//         field, returning 1000.0, stored into accbal.
// STEP 4  "Updated Balance: 1000" prints.
// STEP 5  The Car/Engine friend-class example and the add(A,B)
//         friend-FUNCTION example are both left commented out in main()
//         — uncommenting `Car car("Toyota", 150);` would print "Car
//         Model: Toyota, Horsepower: 150", demonstrating the SAME
//         friend-class pattern as BankManager/BankAccount but between a
//         different pair of classes.
// STEP 6  main() returns 0.
