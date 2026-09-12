// Inheritance — single-level, multiple, and multi-level, plus the base
// class's constructor running automatically before the derived class's own.
//
// Compile: g++ -std=c++17 7_inheritancecls.cpp -o inheritancecls
// Run:     inheritancecls.exe   (Windows)   or   ./inheritancecls   (Linux/macOS)
#include<iostream>
using namespace std;


// Single Level Inheritance Example:
//Accessing Parent class members in Child class.
// Inheritance is a mechanism where a new class (derived class or child class) inherits properties and behaviors (data members and member functions) from an existing class (base class or parent class).
// It promotes code reusability and establishes a hierarchical relationship between classes.
class Parent
{
public:
    // Parent()
    // No parameters — runs BEFORE Child's own constructor body, every
    // time a Child object is created, even though main() never
    // constructs a Parent directly.
    Parent() {
        cout << "Parent Constructor called!" << endl;
    }
    void showParentMessage() {
        cout << "Hello from Parent class!" << endl;
    }
};

// class Child : public Parent
//   public Parent - Child inherits every public member of Parent
//                   (showParentMessage becomes callable on a Child
//                   object too, with no extra code needed in Child).
class Child : public Parent // Inheritance
{
public:
    // Child()
    // No parameters of its own — but before this constructor's BODY runs,
    // C++ automatically calls Parent's default constructor first (since
    // no base-class constructor is explicitly named in an initializer
    // list here).
    Child() {
        cout << "Child Constructor is called!"<< endl;
    }
    void display() {
        cout << "Hello from Child class!" << endl;
    }
    void ShowChildMessage()
    {
        cout << "Child class accessing Parent class method:" << endl;
    }
};

// Multiple Inheritance Example:
class Teacher
{
public:
    void Teach() {
        cout << "Hello from Teacher class!" << endl;
    }
};

class Researcher
{
public:
    void Research() {
        cout << "Hello from Researcher class!" << endl;
    }
};

// class Professor: public Teacher, public Researcher
// MULTIPLE inheritance — Professor inherits from TWO base classes at
// once, gaining both Teach() (from Teacher) and Research() (from
// Researcher) without redefining either.
class Professor: public Teacher, public Researcher
{
public:
    void Guide() {
        cout << "Hello from Professor class!" << endl;
    }
};

//Multi-Level Inheritance Example:
class GrandParent
{
    public:
    GrandParent() {
        cout << "GrandParent Constructor called!" << endl;
    };
    void showGrandParentMessage() {
        cout << "Hello from GrandParent class!" << endl;
    };
};
// class Parent1 : public GrandParent
// MULTI-LEVEL inheritance (a chain, not multiple parents at once):
// Parent1 inherits from GrandParent, and Child1 (below) will inherit from
// Parent1 — so Child1 ends up with members from BOTH ancestors, two
// levels up.
class Parent1 : public GrandParent
{
    public:
    Parent1() {
        cout << "Parent1 Constructor called!" << endl;
    }
    void showParent1Message() {
        cout << "Hello from Parent1 class!" << endl;
    };
};
class Child1 : public Parent1
{
    public:
    Child1() {
        cout << "Child1 Constructor called!" << endl;
    }
    void showChild1Message() {
        cout << "Hello from Child1 class!" << endl;
    };
};

class Employee {
public:
    int id;
    string name;
    static int count; // Declaration of static data member

    // Employee(n)
    //   n - the employee's name.
    Employee(string n) {
        name = n;
        id = ++count; // Increment count each time an object is created
    }

    void display() {
        cout << "Employee ID: " << id << ", Name: " << name << endl;
    }

    static void showCount() {
        cout << "Total Employees: " << count << endl;
    }
};
// class Manager : public Employee
// A THIRD level about to be added below (SeniorManager -> Manager ->
// Employee), showing multi-level inheritance applied to a more realistic
// hierarchy than GrandParent/Parent1/Child1.
class Manager : public Employee {
public:
    // Manager(n)
    //   n - forwarded straight to Employee's constructor via `: Employee(n)`.
    Manager(string n) : Employee(n) {
        // Manager-specific initialization can go here
    }
};

class SeniorManager : public Manager {
public:
    SeniorManager(string n) : Manager(n) {
        // SeniorManager-specific initialization can go here
    }
};

int main()
{
    // Child c
    // Creating a Child object automatically triggers Parent's
    // constructor FIRST, then Child's own — this is the ONLY thing that
    // actually executes in this file; everything below is commented out
    // as separate, standalone examples to uncomment individually.
    Child c;
    // c.display();
    // c.ShowChildMessage();
    // c.showParentMessage(); // Accessing Parent class method

    // //Example of Multiple Inheritance
    // Professor p;
    // p.Teach();      // From Teacher class
    // p.Research();   // From Researcher class
    // p.Guide();      // From Professor class

    // //Example of Multi-Level Inheritance
    // Child1 c1;
    // c1.showChild1Message();       // From Child1 class
    // c1.showParent1Message();      // From Parent1 class
    // c1.showGrandParentMessage();  // From GrandParent class

    // //Example of Multi-Level Inheritance with Employee classes
    // Employee e1("Pratibha");
    // Manager m1("Raushan");
    // SeniorManager sm("Vatan");
    // sm.display();
    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  Child c; begins constructing a Child object.
// STEP 2  BEFORE Child's own constructor body runs, C++ automatically
//         invokes Parent's default constructor first (since a derived
//         class's base is always initialized before the derived class's
//         own body executes) — "Parent Constructor called!" prints.
// STEP 3  Child's own constructor body now runs — "Child Constructor is
//         called!" prints.
// STEP 4  main() returns 0. Nothing else in the file executes, since
//         every other line is commented out.
//
// If `Employee e1("Pratibha"); Manager m1("Raushan");
// SeniorManager sm("Vatan"); sm.display();` were uncommented instead, the
// SeniorManager construction chain would run Employee's constructor
// FIRST (via Manager's `: Employee(n)`), incrementing the shared static
// `count` — the same multi-level "base constructs before derived" rule
// from STEP 2, just three levels deep instead of two.
