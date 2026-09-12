// Traditional indexed for loop vs. range-based for loop — two ways to
// visit every element of an array.
//
// Compile: g++ -std=c++17 7_for-and-forrange.cpp -o for-and-forrange
// Run:     for-and-forrange.exe   (Windows)   or   ./for-and-forrange   (Linux/macOS)

#include <iostream>

using namespace std;

int main() {

  int numbers[5] = {7, 5, 6, 12, 35};
  cout << "The numbers are: ";

  //  Printing array elements
  // using range based for loop
  // for (int n : numbers)
  //   n       - a COPY of each element in turn (not an index) — the loop
  //             reads "for every n in numbers."
  //   numbers - the whole array; the loop automatically knows to stop
  //             after all 5 elements, no manual bound (like `< 5`) needed.
  for (int n : numbers) {
    cout << n << "  ";
  }
  cout << "\nThe numbers are: ";

  //  Printing array elements
  // using traditional for loop
  // for (int i = 0; i < 5; ++i)
  //   i - an explicit INDEX, manually compared against the array's known
  //       size (5, hardcoded here) and used to look up numbers[i] each
  //       time — more verbose than the range-based version above, but
  //       gives you the index itself if you need it (e.g. to also print
  //       "element 0 is 7", not just the value 7).
  for (int i = 0; i < 5; ++i) {
    cout << numbers[i] << "  ";
  }

  return 0;

}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  numbers = {7, 5, 6, 12, 35}.
// STEP 2  The range-based for loop visits each element in array order:
//         n=7, then n=5, then n=6, then n=12, then n=35 — printing
//         "7  5  6  12  35  ".
// STEP 3  The traditional for loop then does the SAME visit, but via an
//         explicit index: i=0 -> numbers[0]=7, i=1 -> numbers[1]=5, ...,
//         i=4 -> numbers[4]=35, then i becomes 5 and `i < 5` is false, so
//         the loop stops — printing the identical sequence
//         "7  5  6  12  35  " a second time.
// STEP 4  main() returns 0. Both loops produced the exact same output,
//         just by two different mechanisms — proving they're
//         interchangeable for simple "visit every element" cases.
