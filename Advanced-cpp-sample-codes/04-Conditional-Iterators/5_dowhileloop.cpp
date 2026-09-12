// do-while loop — like while, but the condition is checked AFTER the body
// runs, so the body always executes at least once, even if the condition
// would have been false from the start.
//
// Compile: g++ -std=c++17 5_dowhileloop.cpp -o dowhileloop
// Run:     dowhileloop.exe   (Windows)   or   ./dowhileloop   (Linux/macOS)
// Interaction: keep entering numbers until you enter one 10 or below.

#include <iostream>

using namespace std;

int main() {
    int n;
    // do { ... } while (n > 10)
    // The body between `do` and `while` runs FIRST, unconditionally —
    // `n` doesn't even have a value yet the first time the body starts,
    // which is fine because the body's own `cin >> n` sets it before the
    // condition is ever checked (at the closing `while`).
    do
    {
        cout<< "Enter a number less than or equal to 10: " << endl;
        cin >> n;
        cout << "You entered: " << n << endl;

    } while (n > 10);



    return 0;

}

// --------------------------------------------------------------------------
// Step-by-step execution trace (example run: entering 15, then 8)
// --------------------------------------------------------------------------
// STEP 1  The body runs FIRST, before any condition is checked: user
//         types "15" -> n = 15; "You entered: 15" prints.
// STEP 2  NOW the condition is checked: `n > 10` -> 15 > 10 is true ->
//         loop back to the top of the body.
// STEP 3  Body runs again: user types "8" -> n = 8; "You entered: 8"
//         prints.
// STEP 4  Condition checked again: `n > 10` -> 8 > 10 is false -> loop
//         ends.
// STEP 5  main() returns 0.
//
// Contrast with 4_whileloop.cpp: a while loop checks its condition BEFORE
// the first iteration, so if the very first input were already <= 10 in
// an equivalent while-loop version, the body might never need to run a
// second time — but it would still need to run once to GET that first
// input, which is exactly why this pattern (read input, then decide
// whether to keep going) is do-while's classic use case.

