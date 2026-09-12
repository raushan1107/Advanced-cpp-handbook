// Pre-increment will increment the value before it is used in the expression
// Post-increment will increment the value after it is used in the expression
// Similarly for pre-decrement will decrement the value before it is used in the expression
// Post-decrement will decrement the value after it is used in the expression
//
// Compile: g++ -std=c++17 5_IncrementDecrementoperator.cpp -o IncrementDecrementoperator
// Run:     IncrementDecrementoperator.exe   (Windows)   or   ./IncrementDecrementoperator   (Linux/macOS)



//Exercise 1
#include <iostream>
using namespace std;

int main() {
    int a = 5;
    cout << "Initial value of a: " << a << endl;

    // Pre-increment
    // ++a
    // Increments `a` FIRST, then the (now-incremented) value is what gets
    // used/printed — a becomes 6, and 6 is what cout receives.
    cout << "Pre-increment: " << ++a << endl; // a becomes 6, then used
    cout << "Value of a after pre-increment: " << a << endl;

    // Post-increment
    // a++
    // The CURRENT value of `a` is used/printed FIRST, and only AFTER that
    // does `a` get incremented — cout receives 6 (a's value before this
    // line), and only afterward does a become 7.
    cout << "Post-increment: " << a++ << endl; // a used as 6, then becomes 7
    cout << "Value of a after post-increment: " << a << endl;

    // Pre-decrement
    cout << "Pre-decrement: " << --a << endl; // a becomes 6, then used
    cout << "Value of a after pre-decrement: " << a << endl;

    // Post-decrement
    cout << "Post-decrement: " << a-- << endl; // a used as 6, then becomes 5
    cout << "Value of a after post-decrement: " << a << endl;

    return 0;
}


// //Exercise 2
// #include <iostream>

// using namespace std;

// int main() {

//     int a = 200, b = 300, result_x, result_y;

//     // incrementing a by 1 and storing the result in result_x

//     result_x = ++a;

//     cout << "result_x = " << result_x << endl;


//     // decrementing b by 1 and storing the result in result_y

//     result_y = --b;

//     cout << "result_y = " << result_y << endl;

//     return 0;

// }

// --------------------------------------------------------------------------
// Step-by-step execution trace (Exercise 1 — the ACTIVE code; Exercise 2
// is commented out and never runs)
// --------------------------------------------------------------------------
// STEP 1  a = 5. "Initial value of a: 5" prints.
// STEP 2  ++a: a becomes 6 FIRST, then 6 is printed. "Pre-increment: 6"
//         prints; "Value of a after pre-increment: 6" confirms a is 6.
// STEP 3  a++: the CURRENT value (6) is printed first, THEN a becomes 7.
//         "Post-increment: 6" prints (not 7!); "Value of a after
//         post-increment: 7" confirms a is now 7.
// STEP 4  --a: a becomes 6 first, then 6 is printed. "Pre-decrement: 6"
//         prints; a is confirmed as 6.
// STEP 5  a--: the current value (6) prints first, then a becomes 5.
//         "Post-decrement: 6" prints; a is confirmed as 5 — back to its
//         STARTING value from STEP 1, since the net effect of one
//         pre-increment (+1), one post-increment (+1), one pre-decrement
//         (-1), and one post-decrement (-1) is zero change overall.
// STEP 6  main() returns 0.
