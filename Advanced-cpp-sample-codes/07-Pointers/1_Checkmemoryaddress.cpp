// The address-of operator (&) — every variable lives somewhere in memory,
// and & reveals exactly where.
//
// Compile: g++ -std=c++17 1_Checkmemoryaddress.cpp -o Checkmemoryaddress
// Run:     Checkmemoryaddress.exe   (Windows)   or   ./Checkmemoryaddress   (Linux/macOS)
// The actual addresses printed will differ every time you run this — the
// OS assigns memory addresses fresh per run, they are never a fixed value.

#include <iostream>
using namespace std;

int main()
{
    // declare variables
    int var1 = 3;
    int var2 = 24;
    int var3 = 17;

    // &var1
    // The address-of operator: NOT "the value of var1" (that's just
    // `var1`) but "where in memory var1's 4 bytes actually live." cout
    // recognizes an int* here and prints it in hexadecimal by default.
    // print address of var1
    cout << "Address of var1: "<< &var1 << endl;

    // print address of var2
    cout << "Address of var2: " << &var2 << endl;

    // print address of var3
    cout << "Address of var3: " << &var3 << endl;
    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  var1=3, var2=24, var3=17 are each given their own storage
//         location by the compiler/runtime when main() starts.
// STEP 2  &var1 prints something like "0x7ffee2a1c8ac" — a hexadecimal
//         memory address, not the value 3.
// STEP 3  &var2 prints a DIFFERENT address — since three separate local
//         variables need three separate storage locations, and (for
//         local variables declared consecutively like this) they often
//         land at addresses a small, consistent number of bytes apart
//         (commonly 4 bytes apart for three adjacent ints, since each int
//         is 4 bytes — though the compiler is free to order/pad them
//         differently).
// STEP 4  &var3 prints a third, distinct address.
// STEP 5  main() returns 0. Run the program again and every address
//         changes — modern operating systems deliberately randomize stack
//         addresses per run (a security feature called ASLR), so these
//         numbers are never something your code should hardcode or rely
//         on staying the same between runs.
