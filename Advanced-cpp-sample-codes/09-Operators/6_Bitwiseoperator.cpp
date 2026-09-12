// Bitwise operators — &, |, ^, ~, <<, >> — operating on an int's
// individual BITS rather than its value as a whole number.
//
// Compile: g++ -std=c++17 6_Bitwiseoperator.cpp -o Bitwiseoperator
// Run:     Bitwiseoperator.exe   (Windows)   or   ./Bitwiseoperator   (Linux/macOS)
#include<iostream>
using namespace std;

int main()
{
    int a = 10;      // Binary: 1010
    int b = 5;      // Binary: 0101

    // Bitwise AND
    // a & b
    // Compares a and b BIT BY BIT: each result bit is 1 only if BOTH
    // corresponding input bits are 1. 1010 & 0101: no position has a 1 in
    // both operands, so every result bit is 0.
    int andResult = a & b;  // Binary: 0000, Decimal:
    cout << "Bitwise AND (a & b): " << andResult << endl;

    // Bitwise OR
    // a | b
    // Each result bit is 1 if EITHER input bit is 1. 1010 | 0101: every
    // position has a 1 in at least one operand, so every result bit is 1
    // -> binary 1111 = decimal 15.
    int orResult = a | b;   // Binary: 1111, Decimal: 15
    cout << "Bitwise OR (a | b): " << orResult << endl;

    // Bitwise XOR
    // a ^ b
    // Each result bit is 1 if the two input bits DIFFER (exactly one of
    // them is 1). 1010 ^ 0101: every corresponding pair of bits differs,
    // so every result bit is 1 -> binary 1111 = decimal 15 (same result as
    // OR here, purely because a and b happen to share no 1-bits in
    // common).
    int xorResult = a ^ b;  // Binary: 1111, Decimal:
    cout << "Bitwise XOR (a ^ b): " << xorResult << endl;

    // Bitwise NOT
    // ~a
    // Flips EVERY bit of a (0 becomes 1, 1 becomes 0) across the FULL
    // width of an int (32 bits on virtually all modern systems, not just
    // the 4 bits shown in the shorthand comment below) — flipping all 32
    // bits of a positive number produces a negative one, in two's
    // complement representation.
    int notResult = ~a;     // Binary: 0101 (in 4 bits), Decimal: -11 (two's complement)
    cout << "Bitwise NOT (~a): " << notResult << endl;

    // Left Shift
    // a << 1
    // Shifts every bit of `a` one position to the LEFT, filling the
    // vacated rightmost bit with 0 — equivalent to multiplying by 2 (for
    // values that don't overflow). 1010 << 1 = 10100 = decimal 20.
    int leftShiftResult = a << 1; // Binary: 10100, Decimal
    cout << "Left Shift (a << 1): " << leftShiftResult << endl;

    // Right Shift
    // a >> 1
    // Shifts every bit one position to the RIGHT, equivalent to integer
    // division by 2. 1010 >> 1 = 0101 = decimal 5.
    int rightShiftResult = a >> 1; // Binary: 0101, Decimal
    cout << "Right Shift (a >> 1): " << rightShiftResult << endl;

    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  a=10 (binary ...00001010), b=5 (binary ...00000101) — note
//         these two share NO 1-bit in the same position, which is why AND
//         gives 0 and OR/XOR give the identical result (15) below.
// STEP 2  andResult = a & b = 0 (no shared 1-bits anywhere).
// STEP 3  orResult = a | b = 15 (1010 | 0101 = 1111).
// STEP 4  xorResult = a ^ b = 15 (same bits differ everywhere here, so XOR
//         and OR coincide for this particular pair of numbers — that
//         would NOT be true in general).
// STEP 5  notResult = ~a: flips all 32 bits of 10, producing -11 (two's
//         complement: ~x always equals -(x+1) for signed integers, and
//         -(10+1) = -11).
// STEP 6  leftShiftResult = a << 1 = 20 (10 * 2).
// STEP 7  rightShiftResult = a >> 1 = 5 (10 / 2).
// STEP 8  main() returns 0.
