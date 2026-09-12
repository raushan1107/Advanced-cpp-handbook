// C++ version check — confirms which C++ standard your compiler is
// actually building with, before anything else in this course.
//
// Compile: g++ -std=c++17 1_cppversioncheck.cpp -o cppversioncheck
// Run:     cppversioncheck.exe   (Windows)   or   ./cppversioncheck   (Linux/macOS)
//
// Try recompiling with a different -std flag (e.g. -std=c++20) and rerun —
// the printed number changes to match, since __cplusplus reflects the
// standard the COMPILE COMMAND requested, not a fixed property of the
// compiler itself.

#include<iostream>
using namespace std;

int main() {
    // __cplusplus
    // A predefined macro the preprocessor fills in automatically — no
    // parameters, no function call, just a number substituted at compile
    // time. Its value encodes the C++ standard version as a date:
    // 201703L means C++17 (year 2017, revision 03), 201402L means C++14,
    // 202002L means C++20, and so on.
    cout << "C++ version: " << __cplusplus << endl;

    // cin >> ws
    //   ws - std::ws, an I/O manipulator (not a variable) that tells cin to
    //        skip and discard any leading whitespace (spaces, tabs,
    //        newlines) waiting in the input buffer. Here it's used with no
    //        real input pending — its only purpose in this program is to
    //        make the console window pause briefly if run by double-click
    //        rather than from an already-open terminal.
    cin >> ws;
    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  The preprocessor replaces __cplusplus with a literal number
//         BEFORE compilation even starts — by the time main() actually
//         runs, the line is equivalent to
//         `cout << "C++ version: " << 201703L << endl;` (for -std=c++17).
// STEP 2  cout prints "C++ version: 201703" followed by a newline (endl
//         both writes '\n' and flushes the output buffer immediately).
// STEP 3  cin >> ws runs; with no piped input waiting, this simply does
//         nothing observable and the program proceeds to `return 0;`.
// STEP 4  main() returns 0, telling the operating system the program
//         finished successfully.
