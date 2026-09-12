// Exception handling basics, continued — the FULL version of
// 1_GetStartedCode.cpp with the Divide()/division-by-zero try/catch block
// also active (it was commented out in that file).
//
// Compile: g++ -std=c++17 2_Prog1.cpp -o Prog1
// Run:     Prog1.exe   (Windows)   or   ./Prog1   (Linux/macOS)
// Interaction: enter two integers (try a nonzero and a zero second value),
// then a name (try "Raushan" vs. anything else).
#include<iostream>
#include<stdexcept>
using namespace std;

double Divide(double a, double b) {
    if (b == 0) {
        throw "Division by zero error"; // Throwing a string literal as an exception
    }
    return a / b;
}

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
    int num1, num2;
    cout << "Enter two integers: ";
    cin >> num1 >> num2;

    try {
        // Divide(num1, num2)
        //   num1, num2 - if num2 is 0, this throws a `const char*`
        //                literal ("Division by zero error"), caught by
        //                the matching `catch (const char* msg)` clause
        //                right below.
        double result = Divide(num1, num2);
        cout << "Result: " << result << endl;
    }
    catch (const char* msg) { // Catching the string literal exception
        cerr << "Error: " << msg << endl;
    }

    cout << "Demonstrating with exception Program didn't stopped." << endl;

    cout << "Now demonstrating another exception type." << endl;
    try {
        cout << "Enter name: ";
        string name;
        cin >> name;
        FunctionThatThrows(name);
    }
    catch (int e) { // Catching the integer exception
        cerr << "Error Code: " << e << endl;
    }
    cout << "Demonstrating with exception Program didn't stopped." << endl;
    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace (example run: num1=10, num2=0, name="Ravi")
// --------------------------------------------------------------------------
// STEP 1  User enters "10" and "0" -> num1=10, num2=0.
// STEP 2  Divide(10, 0) checks b==0 -> true -> throws the literal
//         "Division by zero error" — execution immediately leaves
//         Divide() and the try block, skipping the "Result: ..." line
//         entirely.
// STEP 3  The `catch (const char* msg)` clause matches (the thrown type
//         IS a const char*) -> msg = "Division by zero error" -> "Error:
//         Division by zero error" prints to cerr.
// STEP 4  "Demonstrating with exception Program didn't stopped." prints —
//         the program kept running past the caught exception.
// STEP 5  "Now demonstrating another exception type." prints. User enters
//         "Ravi" -> FunctionThatThrows("Ravi") throws 401 (since "Ravi" !=
//         "Raushan") -> caught by `catch (int e)` -> "Error Code: 401"
//         prints.
// STEP 6  "Demonstrating with exception Program didn't stopped." prints a
//         second time. main() returns 0.
//
// Had num2 been nonzero (say 2) at STEP 1, Divide(10, 2) would return 5.0
// normally, no throw at all, and "Result: 5" would print instead of
// jumping into the catch block.
