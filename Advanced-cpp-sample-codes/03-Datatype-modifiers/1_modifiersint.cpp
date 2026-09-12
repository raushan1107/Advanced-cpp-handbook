// Integer type modifiers — short/long/long long/unsigned/signed, and how
// much range each one actually buys you.
//
// Compile: g++ -std=c++17 1_modifiersint.cpp -o modifiersint
// Run:     modifiersint.exe   (Windows)   or   ./modifiersint   (Linux/macOS)

#include <iostream>

using namespace std;

int main() {

    short int a = 32000;         // short: typically 2 bytes, max ~32767

    int b = 2147483647;          // int: typically 4 bytes, max 2^31-1

    long int c = 2147483647L;    // long: 4 or 8 bytes (platform dependent)

    long long int d = 9223372036854775807LL; // long long: guaranteed at least 8 bytes

    // unsigned int e = 4294967295
    // "unsigned" removes the negative half of the range entirely, so all
    // of int's usual bits go toward positive values instead: 0 to
    // 4,294,967,295 instead of roughly -2.1 billion to +2.1 billion.
    unsigned int e = 4294967295; // unsigned: 0 to 4,294,967,295 (no negatives)

    signed int f = -2147483648; // signed: -2,147,483,648 to 2,147,483,647

    cout << "short int: " << a << endl;

    cout << "int: " << b << endl;

    cout << "long int: " << c << endl;

    cout << "long long int: " << d << endl;

    cout << "unsigned int: " << e << endl;

    return 0;

}


// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  Six variables are initialized with the literal values shown
//         above; each fits comfortably within its declared type's range
//         (that's deliberate — this file doesn't demonstrate overflow).
// STEP 2  The five cout lines print a, b, c, d, e in order:
//           short int: 32000
//           int: 2147483647
//           long int: 2147483647
//           long long int: 9223372036854775807
//           unsigned int: 4294967295
// STEP 3  `f` (signed int) is set but never printed in this version —
//         uncomment (or add) a cout line for it to see -2147483648.
// STEP 4  main() returns 0.
//
// Try this: change `a` to 32768 (one more than short's usual max of
// 32767) and rerun — on most platforms this silently wraps around to a
// large negative number instead of raising an error, which is exactly why
// picking a type with enough headroom for your actual data matters.
