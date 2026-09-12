// Exception handling basics — throw/catch with plain literal types (a
// string, an int), then with a standard exception type.
//
// Compile: g++ -std=c++17 1_GetStartedCode.cpp -o GetStartedCode
// Run:     GetStartedCode.exe   (Windows)   or   ./GetStartedCode   (Linux/macOS)
// Interaction: enter a name when prompted (try "Raushan" vs. anything else).
#include<iostream>
#include<stdexcept>
using namespace std;

// Divide(a, b)
//   a - the numerator.
//   b - the denominator; if it's 0, this THROWS instead of returning
//       infinity or crashing — `throw "..."` throws a plain C-string
//       literal, a simple (but not usually recommended — see
//       3_customexception.cpp for the better pattern) exception type.
double Divide(double a, double b) {
    if (b == 0) {
        throw "Division by zero error"; // Throwing a string literal as an exception
    }
    return a / b;
}

// FunctionThatThrows(n)
//   n - a name to check; throws a plain INT (401) if it doesn't match
//       "Raushan" — different exception TYPES (string literal here,
//       versus int) need different `catch` clauses to be caught, which is
//       exactly what main() below demonstrates.
void FunctionThatThrows(string n) {
    if(n!="Raushan"){
        throw 401; // Throwing an integer as an exception
    }
    else{
        cout << "Welcome " << n << "! Happy to see you back." << endl;
    }
}

// Runtime Exception Handling using Standard Exceptions
void StandardExceptionDemo() {
    try {
        int* arr = new int[5];
        // Accessing out of bounds to trigger an exception
        for (int i = 0; i <= 5; i++) {
            arr[i] = i;
        }
        delete[] arr;
    }
    catch (const std::out_of_range& e) {
        cerr << "Out of Range error: " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cerr << "Standard exception: " << e.what() << endl;
    }
}
int main() {
    // int num1, num2;
    // cout << "Enter two integers: ";
    // cin >> num1 >> num2;

    // try {
    //     double result = Divide(num1, num2);
    //     cout << "Result: " << result << endl;
    // }
    // catch (const char* msg) { // Catching the string literal exception
    //     cerr << "Error: " << msg << endl;
    // }

    // cout << "Demonstrating with exception Program didn't stopped." << endl;
    cout << "Now demonstrating another exception type." << endl;
    try {
        cout << "Enter name: ";
        string name;
        cin >> name;
        FunctionThatThrows(name);
    }
    // catch (int e)
    //   e - the thrown value (401), bound to `e` only if the type thrown
    //       matches `int` exactly — this catch clause would NOT catch a
    //       thrown string literal or a std::exception; each thrown type
    //       needs a matching catch clause.
    catch (int e) { // Catching the integer exception
        cerr << "Error Code: " << e << endl;
    }
    cout << "Demonstrating with exception Program didn't stopped." << endl;
    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace (the ACTIVE code — the Divide() try/catch
// block in main() is commented out; StandardExceptionDemo() is defined
// but never called from main() in this version)
// --------------------------------------------------------------------------
// STEP 1  "Now demonstrating another exception type." prints.
// STEP 2  User is prompted "Enter name: " and types, say, "Priya".
// STEP 3  FunctionThatThrows("Priya") runs: "Priya" != "Raushan", so
//         `throw 401;` fires — this immediately abandons the rest of
//         FunctionThatThrows and unwinds back to the nearest matching
//         catch.
// STEP 4  The `catch (int e)` clause matches (401 IS an int) -> e = 401
//         -> "Error Code: 401" prints to cerr.
// STEP 5  "Demonstrating with exception Program didn't stopped." prints
//         — proving the thrown exception didn't crash the program, it
//         was caught and handled, and execution continued normally after
//         the try/catch block.
// STEP 6  main() returns 0.
//
// If the user had typed "Raushan" instead at STEP 2, FunctionThatThrows
// would print "Welcome Raushan! Happy to see you back." and return
// normally — no throw, so the catch block simply never runs.
