// In C++, operators like +=, -=, *=, /=, and %= are known as compound assignment operators.
//They provide a shorthand way to perform an arithmetic operation on a variable and then assign the result back to the same variable.
//
// Compile: g++ -std=c++17 2_Assignmentoperator.cpp -o Assignmentoperator
// Run:     Assignmentoperator.exe   (Windows)   or   ./Assignmentoperator   (Linux/macOS)

#include <iostream>

using namespace std;

int main() {

    int a, b;

    // 4 is assigned to a

    a = 4;

    // 25 is assigned to b

    b = 25;

    cout << "a = " << a << endl;

    cout << "b = " << b << endl;

    cout << "\nAfter a += b;" << endl;

    // a += b
    //   b - the value added to `a`; equivalent to writing `a = a + b;`,
    //       just shorter and (for more complex left-hand expressions)
    //       evaluated only once instead of twice.
    // assigning the sum of a and b to a

    a += b;  // a = a +b

    cout << "a = " << a << endl;

    return 0;

}


// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  a = 4, b = 25. "a = 4" and "b = 25" print.
// STEP 2  a += b is evaluated as a = a + b = 4 + 25 = 29; a is now 29
//         (b is unchanged, still 25).
// STEP 3  "a = 29" prints.
// STEP 4  main() returns 0.
