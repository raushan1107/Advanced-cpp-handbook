// What is Vtable Mechanism in C++?
// Vtable (Virtual Table) is a mechanism used in C++ to support dynamic (runtime) polymorphism.
// It is essentially a table of function pointers maintained per class that has virtual functions.
//
// Compile: g++ -std=c++17 11_vtablemechanism.cpp -o vtablemechanism
// Run:     vtablemechanism.exe   (Windows)   or   ./vtablemechanism   (Linux/macOS)
#include <iostream>
using namespace std;

class Plugin {
public:
    virtual void execute() = 0; // Pure virtual function
    virtual ~Plugin() {}
};
class VideoPlugin : public Plugin {
public:
    void execute() override {
        cout << "Executing Video Plugin" << endl;
    }
};

class AudioPlugin : public Plugin {
public:
    void execute() override {
        cout << "Executing Audio Plugin" << endl;
    }
};

// runPlugin(plugin)
//   plugin - a Plugin*, actually pointing at SOME concrete subclass
//            (VideoPlugin or AudioPlugin); this function has no idea
//            which one at compile time.
void runPlugin(Plugin* plugin) {
    plugin->execute(); // Calls the appropriate execute() based on the actual object type
}


class Base {
public:
    virtual void show() { // Virtual function
        cout << "Base class show function called." << endl;
    }
    void display() {
        cout << "Base class display function called." << endl;
    }
    virtual ~Base() {} // Virtual destructor
};
class Derived : public Base {
public:
    void show() override { // Overriding the virtual function
        cout << "Derived class show function called." << endl;
    }
    // void display() — hides (does not override) Base::display, since
    // Base's version is NOT virtual; a Base* calling display() always
    // runs Base's version regardless of the real object type.
    void display() {
        cout << "Derived class display function called." << endl;
    }
};
int main() {

    // Demonstrating Vtable Mechanism
    Plugin* p1 = new VideoPlugin();
    Plugin* p2 = new AudioPlugin();

    // runPlugin(p1)
    //   p1 - a Plugin* pointing at a VideoPlugin; inside runPlugin, the
    //        vtable lookup resolves execute() to VideoPlugin's version.
    runPlugin(p1);
    runPlugin(p2);

    delete p1;
    delete p2;

    // Base* bptr = new Derived()
    // Base class pointer
    Base* bptr = new Derived(); // Base class pointer

    // Virtual function, binded at runtime (Runtime polymorphism)
    bptr->show(); // Calls Derived's show()
    bptr->display(); // Calls Base's display()
    // how we can see vtable mechanism in action
    cout << "Address of Base class pointer: " << bptr << endl;
    // static_cast<Derived*>(bptr)
    //   bptr - a Base*, known (by the programmer, not the compiler) to
    //          actually point at a Derived object; static_cast performs
    //          this DOWNCAST without a runtime check (unlike
    //          dynamic_cast — see Module 8's RTTI folder), so it's only
    //          safe when you're certain of the real type.
    cout << "Address of Derived class object: " << static_cast<Derived*>(bptr) << endl;
    // Note: The actual vtable address is not directly accessible in standard C++.
    // how to call the base class function
    // bptr->Base::show()
    //   Base:: - explicitly qualifies WHICH class's show() to call,
    //           bypassing virtual dispatch entirely and forcing Base's
    //           own version even though bptr's real object is a Derived.
    bptr->Base::show(); // Calls Base's show()
    // how to call the base class function from derived class object
    Derived* dptr = static_cast<Derived*>(bptr); // Downcasting to Derived class pointer. Detailed explanation: https://stackoverflow.com/questions/2954555/what-is-downcasting-in-c
    dptr->Base::show(); // Calls Base's show()

    return 0;
}

// what is difference between pointer variable and reference variable in C++?
// A pointer variable holds the memory address of another variable and can be reassigned to point to different variables.
// A reference variable is an alias for another variable and cannot be changed to refer to a different variable after its initialization.

// Base b vs Base* bptr
// Base b; // 'b' is an object of type Base, allocated on the stack
// Base* bptr = new Base(); // 'bptr' is a pointer to a Base object, allocated on the heap
// delete bptr; // Free the memory allocated for the Base object
// bptr = nullptr; // Avoid dangling pointer
// In summary, 'b' is a direct instance of Base, while 'bptr' is a pointer that can reference a Base object.

// Is this possible Base b = new Derived();?
// No, this is not possible. 'new Derived()' returns a pointer to a Derived object, while 'Base b' expects an object of type Base. You would need to use a pointer or reference to achieve polymorphism, like so: Base* bptr = new Derived();

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  p1 -> VideoPlugin, p2 -> AudioPlugin. runPlugin(p1) resolves
//         execute() via the vtable to VideoPlugin's version -> prints
//         "Executing Video Plugin". runPlugin(p2) similarly prints
//         "Executing Audio Plugin".
// STEP 2  bptr = new Derived() (through a Base* pointer). bptr->show() IS
//         virtual -> resolves to Derived's override -> "Derived class
//         show function called." bptr->display() is NOT virtual -> always
//         resolves to Base's version regardless of the real object ->
//         "Base class display function called."
// STEP 3  Two address lines print bptr's raw pointer value, twice (once
//         directly, once after a static_cast<Derived*> that doesn't
//         change the actual address, only the compiler's TYPE
//         information about it) — both print the SAME address.
// STEP 4  bptr->Base::show() explicitly bypasses virtual dispatch,
//         forcing Base's own show() to run regardless of the real object
//         -> "Base class show function called."
// STEP 5  dptr (a Derived*, from the earlier static_cast) also calls
//         ->Base::show() the same explicit way -> "Base class show
//         function called." again.
// STEP 6  main() returns 0.
