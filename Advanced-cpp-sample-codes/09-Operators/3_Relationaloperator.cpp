//In C++, the built-in relational operators (e.g., <, >, <=, >=, ==, !=) always return a value of type bool.
//This bool value represents the truth or falsity of the comparison, being either true or false.
//
// Compile: g++ -std=c++17 3_Relationaloperator.cpp -o Relationaloperator
// Run:     Relationaloperator.exe   (Windows)   or   ./Relationaloperator   (Linux/macOS)

#include <iostream>
using namespace std;

int main() {
    int x = 10;
    int y = 20;

    // Using relational operators
    // (x < y)
    // Every relational operator produces a bool (true/false), never an
    // int — even though cout prints an un-styled bool as 0 or 1 by
    // default (see the boolalpha manipulator further down).
    bool result1 = (x < y);   // true
    bool result2 = (x > y);   // false
    bool result3 = (x <= y);  // true
    bool result4 = (x >= y);  // false
    bool result5 = (x == y);  // false
    bool result6 = (x != y);  // true

    // Output the results
    cout << "x < y: " << result1 << endl;
    cout << "x > y: " << result2 << endl;
    cout << "x <= y: " << result3 << endl;
    cout << "x >= y: " << result4 << endl;
    cout << "x == y: " << result5 << endl;
    cout << "x != y: " << result6 << endl;

    cout << "===================================" <<endl;
    // Print bool values as true/false
    // cout << boolalpha
    // An I/O manipulator (like `fixed`/`setprecision` seen elsewhere in
    // this course) — STICKY, affecting every bool printed AFTER this
    // line: instead of "1"/"0", cout now prints "true"/"false".
    cout << boolalpha;

    // Output the results as true/false
    cout << "x < y: " << result1 << endl;
    cout << "x > y: " << result2 << endl;
    cout << "x <= y: " << result3 << endl;
    cout << "x >= y: " << result4 << endl;
    cout << "x == y: " << result5 << endl;
    cout << "x != y: " << result6 << endl;

    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  x = 10, y = 20. Each result variable is computed once, up
//         front: result1=true (10<20), result2=false (10>20 is false),
//         result3=true (10<=20), result4=false (10>=20 is false),
//         result5=false (10==20 is false), result6=true (10!=20 is true).
// STEP 2  The first six cout lines print the results WITHOUT boolalpha —
//         true prints as "1", false prints as "0": "x < y: 1", "x > y:
//         0", "x <= y: 1", "x >= y: 0", "x == y: 0", "x != y: 1".
// STEP 3  A divider line prints, then `cout << boolalpha;` is applied.
// STEP 4  The SAME six variables print again, now as words instead of
//         digits: "x < y: true", "x > y: false", "x <= y: true", "x >=
//         y: false", "x == y: false", "x != y: true" — proving the
//         underlying bool VALUES never changed, only how cout chooses to
//         DISPLAY them.
// STEP 5  main() returns 0.
