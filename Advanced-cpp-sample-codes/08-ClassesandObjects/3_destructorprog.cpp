// Destructors — the counterpart to a constructor, running automatically
// when an object's lifetime ends.
//
// Compile: g++ -std=c++17 3_destructorprog.cpp -o destructorprog
// Run:     destructorprog.exe   (Windows)   or   ./destructorprog   (Linux/macOS)

#include<iostream>
using namespace std;

class Demo{
    public:
    // Constructor
    // Demo()
    // No parameters — runs once, the moment a Demo object is created.
    Demo(){
        cout<<"Constructor called!"<<endl;
    }

    // Destructor
    //why it is public? because when object goes out of scope destructor is called automatically
    // Destructor has same name as class name but is preceded by a tilde(~) symbol.
    // It does not take any parameters and does not return any value.
    // It is called automatically when the object goes out of scope or is explicitly deleted.
    // It is used to release resources that were acquired by the object during its lifetime, such as memory, file handles, network connections, etc.
    // ~Demo()
    // No parameters (destructors NEVER take parameters, and there can
    // only be ONE per class, unlike constructors which can be overloaded).
    ~Demo(){
        cout<<"Destructor called!"<<endl;
    }
};

int main(){
    // Demo d1
    // A STACK-allocated object: its destructor runs AUTOMATICALLY when
    // main() ends and d1 goes out of scope — no explicit call needed.
    Demo d1;
    // Demo* d2 = new Demo()
    // A HEAP-allocated object: `new` runs the constructor, but its
    // destructor will NOT run automatically just because the pointer d2
    // goes out of scope — only an explicit `delete d2;` triggers it.
    Demo* d2 = new Demo(); //dynamic object creation
    delete d2; //explicitly calling destructor for dynamic object
    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  Demo d1; runs the constructor immediately: "Constructor
//         called!" prints.
// STEP 2  Demo* d2 = new Demo(); ALSO runs the constructor (for the
//         second, heap-allocated object): a second "Constructor called!"
//         prints.
// STEP 3  delete d2; explicitly runs d2's destructor RIGHT NOW: "Destructor
//         called!" prints — this is the ONLY way a heap object's
//         destructor fires; forgetting this `delete` would leak the
//         object with its destructor never running.
// STEP 4  main() reaches `return 0;`. As main() exits, d1 (the stack
//         object) goes out of scope, and ITS destructor runs
//         automatically: a second "Destructor called!" prints.
// STEP 5  Final printed order: "Constructor called!" (d1), "Constructor
//         called!" (d2), "Destructor called!" (d2, via explicit delete),
//         "Destructor called!" (d1, automatic on scope exit).
