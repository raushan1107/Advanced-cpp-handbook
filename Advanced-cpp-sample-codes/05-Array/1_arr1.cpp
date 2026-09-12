// Fixed-size arrays — a block of same-typed elements, visited with a
// range-based for loop (see 04-Conditional-Iterators/7_for-and-forrange.cpp
// for the same idea contrasted against a traditional indexed loop).
//
// Compile: g++ -std=c++17 1_arr1.cpp -o arr1
// Run:     arr1.exe   (Windows)   or   ./arr1   (Linux/macOS)

#include <iostream>

using namespace std;

int main() {

  // int numbers[5] = {7, 5, 6, 12, 35}
  // A fixed-size array: exactly 5 ints, whose SIZE is baked into the type
  // itself at compile time — it can never grow or shrink at runtime.
  int numbers[5] = {7, 5, 6, 12, 35};
  cout << "The numbers are: ";

  //  Printing array elements
  // using range based for loop
  for (int n : numbers) {
    cout << n << "  ";
  }
  return 0;

}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  numbers = {7, 5, 6, 12, 35}, five elements, indices 0-4.
// STEP 2  "The numbers are: " prints.
// STEP 3  The range-based for loop visits each element in array order:
//         n=7, n=5, n=6, n=12, n=35 — printing "7  5  6  12  35  ".
// STEP 4  main() returns 0.
