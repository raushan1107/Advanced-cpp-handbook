// Polymorphism in C++
// Compile with: g++ -std=c++17 8_polymorphismcls.cpp -o polymorphismcls
// Run: polymorphismcls.exe (Windows) or ./polymorphismcls (Linux/macOS)
// Compile time and Run time polymorphism:
// Compile time polymorphism is achieved through function overloading and operator overloading.
// Run time polymorphism is achieved through inheritance and virtual functions.
// Analogy: Think of polymorphism like a Swiss Army knife. It can perform multiple functions (like a knife, scissors, screwdriver) depending on how you use it. Similarly, in programming, polymorphism allows methods to do different things based on the object that it is acting upon.
// Function Overloading Example (Compile Time Polymorphism)
// Function overloading allows multiple functions to have the same name but different parameters (different type or number of parameters).
// Operator Overloading Example (Compile Time Polymorphism)
// Operator overloading allows you to redefine the way operators work for user-defined types (classes).
// Virtual Functions Example (Run Time Polymorphism)
// A virtual function is a member function in the base class that you expect to override in derived
// classes. When you use a base class pointer to refer to a derived class object, the derived class's version of the function is called.
// Early Binding (Static Binding) vs Late Binding (Dynamic Binding):
// Early binding (Compile Time Polymorphism) occurs when the function to be called is determined at compile time.
// Late binding (Run Time Polymorphism) occurs when the function to be called is determined.
// What is VTable?
// A VTable (Virtual Table) is a mechanism used in C++ to support dynamic (run-time) polymorphism. It is essentially a table of function pointers maintained per class that has virtual functions. Each entry in the VTable corresponds to a virtual function that can be called on objects of that class.
// analogy for virtual functions and VTable: Think of a VTable like a menu in a restaurant. Each dish on the menu corresponds to a virtual function in a class. When you order a dish (call a virtual function), the restaurant (program) looks up the menu (VTable) to see which specific dish (function implementation) to prepare based on your order (the actual object type at runtime).
// Function overriding Example (Run Time Polymorphism)

#include <iostream>
using namespace std;

class Account
{
public:
    // virtual void displayAccountType()
    // No parameters — `virtual` marks this as OVERRIDABLE: calling it
    // through a base-class pointer/reference runs the MOST-DERIVED
    // object's version, decided at runtime, not the version matching the
    // pointer's declared type.
    virtual void displayAccountType() {
        cout << "This is a general account." << endl;
    }
    virtual void calculateInterest() {
        cout << "Calculating interest for general account." << endl;
    }
};

class SavingsAccount : public Account
{
public:
    // void displayAccountType() override
    //   override - not required by the compiler, but tells it "I intend
    //              to override a base class virtual function of this
    //              exact signature" — if the base class's signature ever
    //              changes and no longer matches, `override` turns that
    //              mismatch into a compile ERROR instead of silently
    //              creating an unrelated new function.
    void displayAccountType() override {
        cout << "This is a savings account." << endl;
    }
    void calculateInterest() override {
        cout << "Calculating interest for savings account." << endl;
    }
};
class CurrentAccount : public Account
{
public:
    void displayAccountType() override {
        cout << "This is a current account." << endl;
    }
    void calculateInterest() override {
        cout << "Calculating interest for current account." << endl;
    }
};


class Base {
public:
    // void show() — NOT virtual
    // Calls to show() through a Base* are resolved at COMPILE time
    // (early/static binding), based on the POINTER's declared type, not
    // the actual object it points to — the opposite of display() below.
    void show() {
        cout << "Base class show function called!" << endl;
    }

    virtual void display() {
        cout << "Base class display function called!" << endl;
    }
};

class Derived : public Base {
public:
    // void show() — hides (does NOT override) Base::show, since Base's
    // version isn't virtual; calling it through a Base* still calls
    // Base's version, not this one.
    void show() {
        cout << "Derived class show function called!" << endl;
    }

    void display() override {
        cout << "Derived class display function called!" << endl;
    }
};

int main() {


    // Account* accountPtr[2]
    // An array of BASE-CLASS pointers, each actually pointing at a
    // DIFFERENT derived type — this is exactly the setup that makes
    // virtual dispatch worth having: one array, one loop, two different
    // behaviors.
    Account* accountPtr[2];
    accountPtr[0] = new SavingsAccount();
    accountPtr[1] = new CurrentAccount();

    for(int i = 0; i < 2; i++) {
        // accountPtr[i]->calculateInterest()
        // Even though accountPtr's declared type is Account*, calling a
        // VIRTUAL function through it runs whichever override matches the
        // REAL object at that index — SavingsAccount's version for index
        // 0, CurrentAccount's for index 1.
        accountPtr[i]->calculateInterest(); // Calls respective version
        // accountPtr[i]->calculateInterest();   // Calls respective version
    }

    delete accountPtr[0];
    delete accountPtr[1];

    cout << "End of Polymorphism Example-01!" << endl;

    // Account* accPtr = new SavingsAccount();
    // accPtr->displayAccountType(); // Calls SavingsAccount version

    // accPtr = new CurrentAccount();
    // accPtr->displayAccountType(); // Calls CurrentAccount version

    // delete accPtr; // Free allocated memory

    // Base b;
    // Derived d;

    // // Compile Time Polymorphism
    // b.show(); // Calls Base class show
    // d.show(); // Calls Derived class show

    // // Run Time Polymorphism
    // Base* basePtr;
    // basePtr = &b;
    // basePtr->display(); // Calls Base class display

    // basePtr = &d;
    // basePtr->display(); // Calls Derived class display due to virtual function

    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  accountPtr[0] = new SavingsAccount() — a SavingsAccount object,
//         accessed through an Account* pointer. accountPtr[1] = new
//         CurrentAccount() — likewise.
// STEP 2  i=0: accountPtr[0]->calculateInterest() looks up the ACTUAL
//         object's type (SavingsAccount) via the vtable, not the
//         pointer's declared type (Account) -> prints "Calculating
//         interest for savings account."
// STEP 3  i=1: accountPtr[1]->calculateInterest() resolves to
//         CurrentAccount's override -> prints "Calculating interest for
//         current account."
// STEP 4  Both objects are deleted; "End of Polymorphism Example-01!"
//         prints.
// STEP 5  main() returns 0 (everything below that line is commented out).
//
// If the commented-out Base/Derived block were uncommented instead:
// `b.show()` and `d.show()` would each print their OWN class's message
// (early binding, decided purely by which object's method you called
// directly). But `basePtr->display()` — display IS virtual — would print
// "Base class display..." when basePtr points at `b`, then switch to
// "Derived class display..." the moment basePtr is reassigned to point at
// `d`, even though basePtr's declared TYPE (Base*) never changes. That
// contrast (show() ignores the real object type; display() honors it) is
// the entire difference between non-virtual and virtual functions.
