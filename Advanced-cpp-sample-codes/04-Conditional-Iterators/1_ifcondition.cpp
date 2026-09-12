// if / else if / else — branching based on a runtime value.
//
// Compile: g++ -std=c++17 1_ifcondition.cpp -o ifcondition
// Run:     ifcondition.exe   (Windows)   or   ./ifcondition   (Linux/macOS)
// Interaction: enter your name, then any number, when prompted.

#include<iostream>
using namespace std;

int main() {
    cout << "Welcome to C++ Learnings with Raushan!" << endl;
    cout << "Please Enter Your Name:" << endl;
    string name;
    // cin >> name
    //   name - filled with one whitespace-delimited token typed at the
    //          console (a name containing a space would only capture the
    //          first word, same limitation noted in 01-Structs).
    cin >> name;
    cout << "Hello, " << name << "! Let's start learning C++ together." << endl;

    cout << "\nEnter any number" << endl;
    int number;

    cin >> number;
    // if(number>0) ... else if(number<0) ... else ...
    // Exactly ONE of these three branches runs, in order: the first whose
    // condition is true wins; `else` only runs if BOTH prior conditions
    // were false (meaning number is exactly 0).
    if(number>0)
    {
        cout << number << " is a Positive Number." << endl;
    }
    else if(number<0)
    {
        cout << number << " is a Negative Number." << endl;
    }
    else
    {
        cout << "You entered Zero." << endl;
    }
    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace (example run: name="Priya", number=-7)
// --------------------------------------------------------------------------
// STEP 1  User types "Priya" -> name = "Priya"; greeting prints.
// STEP 2  User types "-7" -> number = -7.
// STEP 3  `number > 0` is false (-7 is not greater than 0) -> the if
//         branch is skipped.
// STEP 4  `number < 0` is true (-7 is less than 0) -> this branch runs,
//         printing "-7 is a Negative Number." — and since this branch ran,
//         the trailing `else` is skipped entirely.
// STEP 5  main() returns 0.
//
// If number had been 0 instead, both `number>0` and `number<0` would be
// false, and only the final `else` would run, printing "You entered Zero."
