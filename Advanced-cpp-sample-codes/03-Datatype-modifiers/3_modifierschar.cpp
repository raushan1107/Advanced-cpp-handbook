// char type modifiers — signed vs unsigned char, and why char's numeric
// value sometimes needs an explicit cast to actually print as a number.
//
// Compile: g++ -std=c++17 3_modifierschar.cpp -o modifierschar
// Run:     modifierschar.exe   (Windows)   or   ./modifierschar   (Linux/macOS)

#include <iostream>

using namespace std;

int main() {

    char b = 'B';              // signed by default (−128 to 127)

    unsigned char d = 200;     // range 0–255

    signed char f = -50;       // explicit signed char

    // int(b)
    // A cast: char's default cout behavior prints it as the LETTER it
    // represents (cout treats char specially, unlike every other numeric
    // type). Casting to int forces cout to print the underlying NUMBER
    // instead — 'B' is ASCII/character code 66.
    cout << "char: " << b << " (" << int(b) << ")" << endl;

    // int(d)
    //   d - an unsigned char holding 200; without the cast, cout would try
    //       to print 200 as a character (an unprintable/extended symbol,
    //       not the digits "200") — the same special-casing as `b` above.
    cout << "unsigned char: " << int(d) << endl;

    cout << "signed char: " << int(f) << endl;

    return 0;

}


// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  b = 'B' (character code 66), d = 200 (an unsigned char, well
//         within its 0-255 range), f = -50 (a signed char, well within its
//         -128 to 127 range).
// STEP 2  "char: " << b << " (" << int(b) << ")" prints "char: B (66)" —
//         `b` alone prints as the letter B, but int(b) forces the numeric
//         code to print instead.
// STEP 3  "unsigned char: " << int(d) prints "unsigned char: 200".
// STEP 4  "signed char: " << int(f) prints "signed char: -50".
// STEP 5  main() returns 0.
//
// Try this: change `d` to 300 (outside unsigned char's 0-255 range) and
// rerun — it silently wraps around (300 - 256 = 44) instead of erroring,
// the same overflow behavior 1_modifiersint.cpp's trace describes for
// `short`.
