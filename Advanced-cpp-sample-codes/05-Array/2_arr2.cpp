// Variable-length arrays (VLAs) — an array whose SIZE is decided at
// runtime by user input, a GCC/Clang extension (not standard C++ — MSVC
// does not support this, use std::vector there instead).
//
// Compile: g++ -std=c++17 2_arr2.cpp -o arr2
// Run:     arr2.exe   (Windows)   or   ./arr2   (Linux/macOS)
// Interaction: enter how many elements, then that many numbers.

#include<iostream>
using namespace std;

int main()
{
    cout << "How many elements you want to store in array: ";
    int n;
    cin >> n;
    // int arr[n]
    //   n - a variable, not a compile-time constant like 1_arr1.cpp's
    //       literal 5. GCC/Clang allow this as an extension (a Variable
    //       Length Array); standard, portable C++ would use
    //       `vector<int> arr(n);` instead (see 12-DataStrucCollections for
    //       vector).
    int arr[n];
    for(int i = 0; i < n; i++)
    {
        cout << "Enter element " << i + 1 << ": ";
        cin >> arr[i];
    }

    cout << "The elements in the array are: ";
    for(int n: arr)
    {
        cout << n << "  ";
    }
}

// --------------------------------------------------------------------------
// Step-by-step execution trace (example run: n=3, entering 10, 20, 30)
// --------------------------------------------------------------------------
// STEP 1  User types "3" -> n = 3; arr is created with room for exactly 3
//         ints (decided just now, at runtime).
// STEP 2  i=0: user enters 10 -> arr[0] = 10.
// STEP 3  i=1: user enters 20 -> arr[1] = 20.
// STEP 4  i=2: user enters 30 -> arr[2] = 30. Loop ends (i becomes 3,
//         `i < n` (3 < 3) is false).
// STEP 5  The final range-based for loop visits arr's 3 elements in
//         order, printing "10  20  30  ".
//
// Note the inner loop's variable is also named `n`, SHADOWING the outer
// `n` (the element count) for the scope of that loop only — outside the
// loop, `n` still refers to the original count (3), not whatever the last
// element happened to be.
