// switch — branching on one variable's exact value, an alternative to a
// long if/else-if chain when every branch compares the SAME variable
// against different constants.
//
// Compile: g++ -std=c++17 2_switchcondition.cpp -o switchcondition
// Run:     switchcondition.exe   (Windows)   or   ./switchcondition   (Linux/macOS)
// Interaction: enter an operator (+, -, *, /) then two numbers.

#include<iostream>
using namespace std;
int main()
{
    char operatorChoice;
    float num1, num2, result;
    cout << "Enter operator (+, -, *, /): ";
    cin >> operatorChoice;
    cout << "Enter two operands: ";
    // cin >> num1 >> num2
    // Chained extraction: reads TWO whitespace-separated numbers from one
    // line of input in a single statement, filling num1 first, then num2.
    cin >> num1 >> num2;

    // switch(operatorChoice)
    // Jumps straight to the `case` label matching operatorChoice's exact
    // value — faster to read than an equivalent if/else-if chain when
    // every branch is comparing the same one variable.
    switch(operatorChoice)
    {
        case '+':
            result = num1 + num2;
            cout << num1 << " + " << num2 << " = " << result;
            // break
            // Stops execution from "falling through" into the NEXT case
            // label below it — without this, hitting case '+' would also
            // run case '-''s code right after, which is almost never what
            // you want.
            break;
        case '-':
            result = num1 - num2;
            cout << num1 << " - " << num2 << " = " << result;
            break;
        case '*':
            result = num1 * num2;
            cout << num1 << " * " << num2 << " = " << result;
            break;
        case '/':
            if(num2 != 0)
            {
                result = num1 / num2;
                cout << num1 << " / " << num2 << " = " << result;
            }
            else
            {
                cout << "Error! Division by zero.";
            }
            break;
        // default
        // Runs only if operatorChoice matched NONE of the case labels
        // above — the switch equivalent of a trailing `else`.
        default:
            cout << "Error! Operator is not correct";
            break;
    }
    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace (example run: operatorChoice='*', num1=6, num2=7)
// --------------------------------------------------------------------------
// STEP 1  operatorChoice = '*', num1 = 6, num2 = 7.
// STEP 2  switch jumps directly to `case '*':` (skipping '+' and '-'
//         entirely — this is the key difference from if/else-if, which
//         would have to test each condition in sequence).
// STEP 3  result = 6 * 7 = 42; "6 * 7 = 42" prints.
// STEP 4  `break` stops execution from continuing into `case '/':`'s code.
// STEP 5  main() returns 0.
//
// If operatorChoice had been '/' with num2 = 0, the inner `if(num2 != 0)`
// would be false, skipping the division and printing "Error! Division by
// zero." instead — proving division-by-zero is caught explicitly here,
// rather than crashing or producing "inf".
