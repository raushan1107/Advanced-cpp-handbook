// Static members — data and functions that belong to the CLASS itself,
// shared across every instance, rather than to any one object.
//
// Compile: g++ -std=c++17 4_staticmemandfunc.cpp -o staticmemandfunc
// Run:     staticmemandfunc.exe   (Windows)   or   ./staticmemandfunc   (Linux/macOS)

#include<iostream>
using namespace std;

class Employee {
public:
    int id;
    string name;
    static int count; // Declaration of static data member

    // Employee(n)
    //   n - the name for this new employee.
    Employee(string n) {
        name = n;
        // ++count
        // `count` is STATIC — there is exactly ONE copy of it shared by
        // every Employee object, not one copy per object. Incrementing it
        // here means every new Employee bumps the SAME shared counter,
        // which is how id ends up being a running, never-repeating
        // sequence (1, 2, 3, ...) across every object ever created.
        id = ++count; // Increment count each time an object is created
    }

    void display() {
        cout << "Employee ID: " << id << ", Name: " << name << endl;
    }

    // static void showCount()
    // No parameters — a STATIC member function: it can be called WITHOUT
    // any Employee object existing at all (`Employee::showCount();`
    // below), because it only touches `count`, which belongs to the class
    // itself, not to any particular object.
    static void showCount() {
        cout << "Total Employees: " << count << endl;
    }
};

// Definition (Initialization) of static member outside the class
// int Employee::count = 0
// A static member's DECLARATION lives inside the class (above), but it
// needs exactly one DEFINITION somewhere outside the class body — this is
// that one definition, giving `count` its actual storage and starting
// value.
int Employee::count = 0;

// class Demo{
// public:
//     // Static member variable
//     static int staticVar;

//     // Static member function
//     static void func1() {
//         cout << "Static member function called!" << endl;
//     }

//     Demo(){
//         cout<<"Constructor called!"<<endl;
//         staticVar++; // Increment static variable
//     }
// };

int main()
{

    // Calling static member function without creating an object
    Employee::showCount();
    Employee e1("Ravi");
    Employee e2("Meena");
    Employee e3("Karan");

    e1.display();
    e2.display();
    e3.display();

    cout << "Total Employees: " << Employee::count << endl;
    // e2.count
    // Accessing a STATIC member THROUGH an object (e2.count) is legal and
    // reads the exact same shared value as Employee::count — there's no
    // "e2's own count," since only one count exists for the whole class.
    cout << "Total Employees: " << e2.count << endl;

    return 0;
    // static int x = 10; // static memory allocation
    // cout << "Static variable x: " << x << endl;

    // // Dynamic memory allocation
    // int* p = new int; // allocating memory on heap
    // *p = 20;
    // cout << "Dynamically allocated variable *p: " << *p << endl;

    // delete p; // freeing dynamically allocated memory

    // Demo d1;
    // // Accessing static member variable
    // cout << "Static member variable Demo::staticVar: " << d1.staticVar << endl;
    // // Calling static member function
    // d1.func1();

    // return 0;
}

// Email: raushan.ranjan@koenig-solutions.com
//Assessment
// Extend the shape report
// Add a Triangle class and report the total area of all three shapes.

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  Employee::count = 0 (the file-scope definition runs before
//         main() starts).
// STEP 2  Employee::showCount() is called with NO Employee object in
//         existence yet — legal, since it's static. Prints "Total
//         Employees: 0".
// STEP 3  Employee e1("Ravi"): count becomes 1 (++count), so e1.id = 1.
// STEP 4  Employee e2("Meena"): count becomes 2, so e2.id = 2 — the SAME
//         shared count that e1's constructor already bumped once.
// STEP 5  Employee e3("Karan"): count becomes 3, so e3.id = 3.
// STEP 6  e1.display() prints "Employee ID: 1, Name: Ravi"; e2.display()
//         prints "Employee ID: 2, Name: Meena"; e3.display() prints
//         "Employee ID: 3, Name: Karan".
// STEP 7  Both remaining lines print "Total Employees: 3" — whether
//         accessed as Employee::count or through an object as e2.count,
//         it's reading the identical single shared variable.
// STEP 8  main() returns 0 (everything after the `return 0;` line is
//         commented out and never runs).
