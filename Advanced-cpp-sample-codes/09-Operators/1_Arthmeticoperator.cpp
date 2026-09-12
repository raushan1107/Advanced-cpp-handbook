// Arithmetic operators — +, -, *, /, % on integers.
//
// Compile: g++ -std=c++17 1_Arthmeticoperator.cpp -o Arthmeticoperator
// Run:     Arthmeticoperator.exe   (Windows)   or   ./Arthmeticoperator   (Linux/macOS)

#include <iostream>

using namespace std;

int main() {

    int a, b;

    a = 7;

    b = 2;

    // printing the sum of a and b

    cout << "a + b = " << (a + b) << endl;

    // printing the difference of a and b

    cout << "a - b = " << (a - b) << endl;

    // printing the product of a and b

    cout << "a * b = " << (a * b) << endl;

    // printing the division of a by b
    // a / b
    // INTEGER division: since both a and b are int, the result is
    // truncated toward zero, not rounded — 7 / 2 gives 3, not 3.5.
    cout << "a / b = " << (a / b) << endl;

    // printing the modulo of a by b
    // a % b
    // The REMAINDER left over after integer division — 7 / 2 = 3
    // remainder 1, so a % b is 1. Only defined for integer operand types.
    cout << "a % b = " << (a % b) << endl;

    return 0;

}


// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  a = 7, b = 2.
// STEP 2  a + b = 9.
// STEP 3  a - b = 5.
// STEP 4  a * b = 14.
// STEP 5  a / b: integer division truncates the true result (3.5) down
//         to 3.
// STEP 6  a % b: 7 = (2*3) + 1, so the remainder — and a % b's value — is
//         1.
// STEP 7  main() returns 0.
