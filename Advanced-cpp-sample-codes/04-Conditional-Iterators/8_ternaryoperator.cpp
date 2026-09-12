// Ternary operator (?:) — a compact, single-expression if/else, useful
// when you just need to pick one of two VALUES rather than run different
// blocks of statements.
//
// Compile: g++ -std=c++17 8_ternaryoperator.cpp -o ternaryoperator
// Run:     ternaryoperator.exe   (Windows)   or   ./ternaryoperator   (Linux/macOS)
// Interaction: enter your age.

#include<iostream>
#include<string>
using namespace std;

int main()
{
    int age;
    cout << "Enter your age: ";
    cin >> age;

    // (age >= 18) ? "You are eligible to vote." : "You are not eligible to vote."
    //   age >= 18                        - the CONDITION, evaluated once.
    //   "You are eligible to vote."      - the value used if the
    //                                      condition is TRUE.
    //   "You are not eligible to vote."  - the value used if the
    //                                      condition is FALSE.
    // This single expression is equivalent to:
    //   string eligibility;
    //   if (age >= 18) eligibility = "You are eligible to vote.";
    //   else eligibility = "You are not eligible to vote.";
    // but reads as one line instead of a five-line if/else block, since
    // both branches are producing a VALUE to assign, not doing different
    // multi-step work.
    string eligibility = (age >= 18) ? "You are eligible to vote." : "You are not eligible to vote.";
    cout << eligibility << endl;

    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace (example run: age=16, then a second run age=20)
// --------------------------------------------------------------------------
// STEP 1  User types "16" -> age = 16.
// STEP 2  `age >= 18` evaluates to false (16 is not >= 18) -> the ternary
//         expression evaluates to "You are not eligible to vote.", which
//         is assigned to `eligibility`.
// STEP 3  "You are not eligible to vote." prints.
//
// A second run with age=20:
// STEP 1  User types "20" -> age = 20.
// STEP 2  `age >= 18` evaluates to true -> the ternary expression
//         evaluates to "You are eligible to vote.".
// STEP 3  "You are eligible to vote." prints.
