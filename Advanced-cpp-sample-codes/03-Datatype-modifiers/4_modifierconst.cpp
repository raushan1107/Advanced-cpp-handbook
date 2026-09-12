// const — a variable that can be initialized once and never reassigned.
//
// Compile: g++ -std=c++17 4_modifierconst.cpp -o modifierconst
// Run:     modifierconst.exe   (Windows)   or   ./modifierconst   (Linux/macOS)

#include <iostream>

using namespace std;

int main() {

    // initialize a const PI

    // const double PI = 3.14
    // `const` means this variable must be given a value right here, at
    // declaration, and the compiler will REFUSE to compile any later line
    // that tries to assign PI a different value (e.g. `PI = 3.0;` below
    // this line would be a compile error, not a runtime one).
    const double PI = 3.14;

    int radius = 4;

    // use the const in a calculation

    // PI * radius * radius
    // A const variable can still be READ and used in calculations freely
    // — const only blocks REASSIGNING it, not using its value.
    double area = PI * radius * radius;

    cout << "Area of circle with radius " << radius << " is: " << area;

    return 0;

}


// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  PI is initialized to 3.14 and locked — no later line in this
//         file can change it.
// STEP 2  radius is set to 4.
// STEP 3  area = PI * radius * radius = 3.14 * 4 * 4 = 3.14 * 16 = 50.24.
// STEP 4  The cout line prints "Area of circle with radius 4 is: 50.24".
// STEP 5  main() returns 0.
//
// Try this: add the line `PI = 3.14159;` right after PI's declaration and
// try to compile — you'll get a compiler error like "assignment of
// read-only variable 'PI'", proving the restriction is enforced at COMPILE
// time, before the program ever runs.
