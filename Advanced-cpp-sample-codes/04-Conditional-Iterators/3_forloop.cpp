// for loop — running a fixed number of iterations, counting with a loop
// variable.
//
// Compile: g++ -std=c++17 3_forloop.cpp -o forloop
// Run:     forloop.exe   (Windows)   or   ./forloop   (Linux/macOS)
// Interaction: enter one number to see its multiplication table (1-10).

#include<iostream>
using namespace std;
int main()
{
    cout << "Welcome to C++ Learnings with Raushan!" << endl;
    int n;
    cout << "Enter a number to print its multiplication table: " << endl;
    cin >> n;
    cout << "Multiplication Table of " << n << " is: " << endl;
    // for(int i=1; i<=10; i++)
    //   int i=1  - runs ONCE, before the first iteration: declares and
    //              initializes the loop counter.
    //   i<=10    - checked BEFORE every iteration (including the first);
    //              the loop body only runs while this stays true.
    //   i++      - runs AFTER every iteration's body finishes, incrementing
    //              i by 1 before the condition is checked again.
    for(int i=1; i<=10; i++)
    {
        cout << n << " x " << i << " = " << n*i << endl;
    }
    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace (example run: n=4)
// --------------------------------------------------------------------------
// STEP 1  n = 4.
// STEP 2  i is initialized to 1. Condition 1<=10 is true -> body runs:
//         prints "4 x 1 = 4". Then i++ makes i become 2.
// STEP 3  Condition 2<=10 is true -> prints "4 x 2 = 8". i becomes 3.
// STEP 4  ... this repeats, printing "4 x 3 = 12" up through
//         "4 x 10 = 40" ...
// STEP 5  After the i=10 iteration finishes, i++ makes i become 11.
//         Condition 11<=10 is now FALSE, so the loop stops — the body
//         never runs with i=11.
// STEP 6  main() returns 0, having printed exactly 10 lines (i = 1 through
//         10, never 11).
