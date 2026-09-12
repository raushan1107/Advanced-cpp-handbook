// while loop — repeats for as long as a condition stays true, checked
// BEFORE every iteration (unlike do-while, checked after — see
// 5_dowhileloop.cpp).
//
// Compile: g++ -std=c++17 4_whileloop.cpp -o whileloop
// Run:     whileloop.exe   (Windows)   or   ./whileloop   (Linux/macOS)
// Interaction: keep entering numbers; entering a negative one exits the loop.

#include<iostream>
using namespace std;
int main()
{
    cout << "Welcome to C++ Learnings with Raushan!" << endl;
    int x=1;
    // while (x >= 0)
    // x is never actually changed anywhere in this loop's body — the
    // REAL exit condition is the `break` below, triggered by user input,
    // not by x itself changing. x >= 0 being always true here means this
    // loop would otherwise run forever without that break.
    while (x >= 0)
    {
        cout << "Enter any number: " << endl;
        int n;
        cin >> n;
        if(n<0)
        {
            cout << "Negative number entered. Exiting the loop." << endl;
            // break
            // Immediately exits the while loop, skipping the rest of this
            // iteration's body AND every remaining check of `x >= 0`.
            break;
        }
        cout << "You entered: " << n << endl;
        cout << "Square of " << n << " is " << n*n << endl;
        cout << "Cube of " << n << " is " << n*n*n << endl
                << endl;

    }

    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace (example run: entering 3, then 5, then -1)
// --------------------------------------------------------------------------
// STEP 1  x = 1; `x >= 0` is true -> enters the loop.
// STEP 2  User types "3" -> n = 3. `n < 0` is false, so the loop prints
//         "You entered: 3", "Square of 3 is 9", "Cube of 3 is 27".
// STEP 3  Loop re-checks `x >= 0` — still true (x was never modified) ->
//         loops again. User types "5" -> n = 5, prints square (25) and
//         cube (125) the same way.
// STEP 4  Loop re-checks `x >= 0` — still true -> loops again. User types
//         "-1" -> n = -1. `n < 0` is true this time -> prints "Negative
//         number entered. Exiting the loop." and `break` exits
//         immediately, without printing a square or cube for -1.
// STEP 5  main() returns 0.
