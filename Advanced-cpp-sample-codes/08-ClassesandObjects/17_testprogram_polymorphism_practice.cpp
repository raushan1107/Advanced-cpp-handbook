// Personal practice file — the smallest possible virtual-override demo:
// one base class, one override, called through a base-class pointer.
//
// Compile: g++ -std=c++17 17_testprogram_polymorphism_practice.cpp -o polymorphism_practice
// Run:     polymorphism_practice.exe   (Windows)   or   ./polymorphism_practice   (Linux/macOS)
#include<iostream>
using namespace std;

class Parent
{
    public:
        // virtual void func1()
        // No parameters — marking this virtual is what lets Child's
        // override below actually get called through a Parent* pointer.
        virtual void func1(){cout<<"Parent-Func1" << endl;}
};
class Child : public Parent
{
    public:
        // void func1() — no `override` keyword written here, but since
        // the signature matches Parent's exactly, this is STILL a valid
        // override; `override` is a helpful compiler check, not a
        // requirement for overriding to work.
        void func1(){cout<<"Child-Func1" << endl;}
};

int main()
{
    // Child c;
    // Parent* obj = new Child()
    // A Child object, referenced through a Parent* pointer — the setup
    // that makes virtual dispatch matter: obj's declared type is Parent,
    // but its REAL object is a Child.
    Parent* obj = new Child();
    obj->func1();

    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  obj = new Child(), stored in a Parent* pointer.
// STEP 2  obj->func1(): because func1 is virtual, the call resolves via
//         the vtable to the REAL object's type (Child), not the pointer's
//         declared type (Parent) -> prints "Child-Func1", not
//         "Parent-Func1".
// STEP 3  main() returns 0 (the heap-allocated Child is never explicitly
//         deleted in this short practice file — a real program should
//         call `delete obj;` before returning).
