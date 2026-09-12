// Virtual destructors — why deleting a derived object through a BASE
// class pointer needs the base's destructor marked `virtual`, or the
// derived destructor is silently skipped.
//
// Compile: g++ -std=c++17 10_virtualdestructor.cpp -o virtualdestructor
// Run:     virtualdestructor.exe   (Windows)   or   ./virtualdestructor   (Linux/macOS)
#include<iostream>
using namespace std;

class Base {
public:
    Base() {
        cout << "Base class constructor called." << endl;
    }
    // ~Base() — NOT virtual
    // Deleting a Derived object through a Base* pointer will call ONLY
    // this destructor, never Derived's own — the compiler decides which
    // destructor to call based on the POINTER's declared type (Base),
    // since there's no virtual dispatch to look up the real object type.
    ~Base() {
        cout << "Base class destructor called." << endl;
    }
};

class Derived : public Base {
public:
    Derived() {
        cout << "Derived class constructor called." << endl;
    }
    ~Derived() {
        cout << "Derived class destructor called." << endl;
    }
};

class CorrectBase {
public:
    CorrectBase() {
        cout << "CorrectBase class constructor called." << endl;
    }
    // virtual ~CorrectBase()
    // Marking the destructor virtual fixes the problem above: deleting a
    // CorrectDerived object through a CorrectBase* now correctly calls
    // CorrectDerived's destructor FIRST, then CorrectBase's — the exact
    // same virtual-dispatch mechanism used for any other virtual function.
    virtual ~CorrectBase() {
        cout << "CorrectBase class destructor called." << endl;
    }
};
class CorrectDerived : public CorrectBase {
public:
    CorrectDerived() {
        cout << "CorrectDerived class constructor called." << endl;
    }
    ~CorrectDerived() {
        cout << "CorrectDerived class destructor called." << endl;
    }
};

class A
{
    public:
    A() { cout << "Constructor A" << endl; }
};
class B : public A
{
    public:
    B() { cout << "Constructor B" << endl; }
};

int main() {
    // cout << "Creating Derived class object using Base class pointer." << endl;
    // Base* obj = new Derived();
    // cout << "Deleting Base class pointer pointing to Derived class object." << endl;
    // delete obj; // Undefined behavior: Derived destructor won't be called

    cout << "\nCreating CorrectDerived class object using CorrectBase class pointer." << endl;
    // CorrectBase* correctObj = new CorrectDerived()
    // A CorrectDerived object, referenced through a CorrectBase* pointer
    // — the exact same pointer-vs-object-type setup as the commented-out
    // Base/Derived version above, but this time it will clean up
    // correctly because CorrectBase's destructor is virtual.
    CorrectBase* correctObj = new CorrectDerived();
    cout << "Deleting CorrectBase class pointer pointing to CorrectDerived class object." << endl;
    delete correctObj; // Correct behavior: CorrectDerived destructor will be called

    // Demonstrating constructor calls in inheritance
    // cout << "\nCreating object of class B which inherits from A." << endl;
    // A* newObjwithoutDestructor = new B();
    // delete newObjwithoutDestructor;

    // Note: In this case, since there are no destructors defined in classes A and B,
    // the default destructors will be called, and there won't be any output related to destruct
    // ion. However, if there were resources to free in class B, not having a virtual destructor
    // in class A could lead to resource leaks when deleting through a base class pointer.
    // Always ensure to define virtual destructors in base classes when dealing with inheritance.
    // to avoid such issues.
    return 0;
}

// Output Explanation:
// In the first case, when we delete the Base class pointer pointing to a Derived class object
// without a virtual destructor, only the Base class destructor is called, leading to potential
// resource leaks if the Derived class allocated resources in its constructor.
// In the second case, with a virtual destructor in the CorrectBase class, both the CorrectDerived
// and CorrectBase destructors are called in the correct order, ensuring proper resource cleanup.

// why virtual destructor is important in C++?
// When a base class has a virtual destructor, it ensures that the destructor of the derived class
// is called when an object of the derived class is deleted through a base class pointer.
// This is crucial for proper resource management and avoiding memory leaks in polymorphic scenarios.
// If the base class destructor is not virtual, deleting a derived class object through a base class pointer
// results in undefined behavior, as the derived class destructor will not be invoked.

// what is memory leak?
// A memory leak occurs when a program allocates memory on the heap but fails to release it
// when it is no longer needed. This can lead to increased memory usage over time,
// potentially exhausting available memory and causing the program to crash or behave unexpectedly.

// --------------------------------------------------------------------------
// Step-by-step execution trace (the ACTIVE code — the Base/Derived block
// at the top of main() is commented out and never runs)
// --------------------------------------------------------------------------
// STEP 1  correctObj = new CorrectDerived(): construction runs BASE-first
//         (same rule as 7_inheritancecls.cpp) -> "CorrectBase class
//         constructor called." prints, then "CorrectDerived class
//         constructor called."
// STEP 2  delete correctObj: because ~CorrectBase() is virtual, the
//         REAL object type (CorrectDerived) is looked up at runtime, so
//         destruction runs DERIVED-first, base-last (destructors always
//         run in the opposite order from constructors) -> "CorrectDerived
//         class destructor called." prints, then "CorrectBase class
//         destructor called."
// STEP 3  main() returns 0.
//
// If the commented-out `Base* obj = new Derived(); delete obj;` block
// were uncommented instead (with Base's destructor NOT virtual), deleting
// `obj` would print ONLY "Base class destructor called." — Derived's
// destructor would never run at all, silently skipping any cleanup it was
// responsible for.
