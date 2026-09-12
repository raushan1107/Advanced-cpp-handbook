// Logical operators — && (AND), || (OR), ! (NOT) — combining bool
// expressions, most often the results of relational comparisons.
//
// Compile: g++ -std=c++17 4_Logicaloperator.cpp -o Logicaloperator
// Run:     Logicaloperator.exe   (Windows)   or   ./Logicaloperator   (Linux/macOS)

#include <iostream>

using namespace std;

int main() {

    bool result;
    cout << boolalpha; // Print bool values as true/false

    // (3 != 5) && (3 < 5)
    //   (3 != 5) - true.
    //   (3 < 5)  - true.
    //   &&       - AND: true only if BOTH sides are true — here, both
    //              are, so the whole expression is true.
    result = (3 != 5) && (3 < 5);     // true

    cout << "(3 != 5) && (3 < 5) is " << result << endl;

    result = (3 == 5) && (3 < 5);    // false

    cout << "(3 == 5) && (3 < 5) is " << result << endl;

    result = (3 == 5) && (3 > 5);    // false

    cout << "(3 == 5) && (3 > 5) is " << result << endl;

    // (3 != 5) || (3 < 5)
    //   ||       - OR: true if AT LEAST ONE side is true — both sides
    //              happen to be true here, so the result is true.
    result = (3 != 5) || (3 < 5);    // true

    cout << "(3 != 5) || (3 < 5) is " << result << endl;

    result = (3 != 5) || (3 > 5);    // true

    cout << "(3 != 5) || (3 > 5) is " << result << endl;

    result = (3 == 5) || (3 > 5);    // false

    cout << "(3 == 5) || (3 > 5) is " << result << endl;

    // !(5 == 2)
    //   (5 == 2) - false.
    //   !        - NOT: flips a bool to its opposite — false becomes
    //              true.
    result = !(5 == 2);    // true

    cout << "!(5 == 2) is " << result << endl;

    result = !(5 == 5);    // false

    cout << "!(5 == 5) is " << result << endl;

    return 0;

}


// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  boolalpha is applied first, so every result prints as
//         "true"/"false" from the start (not "1"/"0").
// STEP 2  (3!=5)&&(3<5): true && true -> true. Prints "... is true".
// STEP 3  (3==5)&&(3<5): false && true -> false (AND short-circuits: once
//         the left side is false, the right side doesn't even need to be
//         true for the result to be false). Prints "... is false".
// STEP 4  (3==5)&&(3>5): false && false -> false.
// STEP 5  (3!=5)||(3<5): true || true -> true.
// STEP 6  (3!=5)||(3>5): true || false -> true (OR only needs ONE side
//         true).
// STEP 7  (3==5)||(3>5): false || false -> false.
// STEP 8  !(5==2): (5==2) is false, ! flips it -> true.
// STEP 9  !(5==5): (5==5) is true, ! flips it -> false.
// STEP 10 main() returns 0.
