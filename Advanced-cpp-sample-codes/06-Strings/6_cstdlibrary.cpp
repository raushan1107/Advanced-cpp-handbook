// cstlibrary.cpp
// Compile with: g++ -std=c++17 6_cstdlibrary.cpp -o cstd
// Run: cstd.exe (Windows) or ./cstd (Linux/macOS)
// this library provides functions for converting strings to numbers and vice versa, as well as other string manipulations.
// Analogy: Think of these functions as translators that convert between different languages (data types).
// For example, converting a string of digits into an integer is like translating a written number into a spoken number.
// Real-world scenario: When reading user input from a console or a file, the input is often in string format. To perform calculations, you need to convert these strings into numeric types using functions like stoi (string to integer) or stod (string to double). Conversely, when displaying results, you might need to convert numbers back into strings using to_string.
// Note: These functions are part of the C++ Standard Library and are defined in the <string> header.
#include <iostream>
#include <string>
#include <cstdlib>    // strtol, strtod if needed
using namespace std;

int main() {

    string s = "12345";
    // stoi(s)
    //   s - a string holding only digit characters (optionally a leading
    //       sign); parses it and returns the equivalent int.
    int x = stoi(s);                  // to int
    cout << "x = " << x << '\n';
    // stod("3.14159")
    //   "3.14159" - a string literal parsed directly (no variable needed)
    //               as a double.
    double d = stod("3.14159");
    cout << "d = " << d << '\n';

    // number to string
    // to_string(42)
    //   42 - the int being converted; to_string has overloads for every
    //        built-in numeric type, so the SAME function name works for
    //        int, double, long, etc.
    string sx = to_string(42);
    cout << "sx = " << sx << '\n';

    // c_str()
    string str1 = "Hello, C++17!";
    // str1.c_str()
    // No parameters — returns a `const char*` pointing at str1's
    // internal buffer as a null-terminated C-style string, for handing to
    // APIs (C libraries, older interfaces) that expect that form rather
    // than a std::string object.
    const char* c = str1.c_str();
    cout << "C-string: " << c << '\n';

      // safe parsing with error handling
    try {
        // stoi("10cbv")
        //   "10cbv" - stoi parses digits from the START of the string
        //             ("10") and STOPS at the first non-digit character
        //             ('c') — it does not throw just because trailing
        //             junk exists, only if NO valid number can be parsed
        //             at all, or the number is too large to fit.
        int val = stoi("10cbv"); // will parse up to 'a' and then stop?
        // stops when any non-numeric character/value comes and then convert rest and proceed as it is.
        cout << val << '\n';
    } catch (const invalid_argument& e) {
        // invalid_argument
        // Thrown when the string has NO valid number at its start at all
        // (e.g. stoi("abc") — not triggered by "10cbv", since "10" IS a
        // valid leading number there).
        cout << "Invalid argument in stoi\n";
    } catch (const out_of_range& e) {
        // out_of_range
        // Thrown when the parsed number is too large/small to fit in the
        // target type (e.g. stoi() on a string representing a number
        // bigger than INT_MAX).
        cout << "Out of range\n";
    }
    return 0;

}

// Explanation:
// In this code, we demonstrate the use of C++ Standard Library functions for string manipulation and
// conversion between strings and numeric types. We use `stoi` to convert a string to an integer, `stod` to convert
// a string to a double, and `to_string` to convert a number back to a string. We also show how to obtain a C-style string
// using the `c_str()` method of the `std::string` class. Additionally, we demonstrate error handling when
// converting strings to numbers, catching exceptions for invalid arguments and out-of-range values.
// Real-world scenario: These functions are commonly used when processing user input, reading data from files, or
// performing calculations that require numeric values. Proper error handling ensures that the program can gracefully handle
// unexpected input without crashing.

// Analogy: Think of these functions as translators that convert between different languages (data types).
// For example, converting a string of digits into an integer is like translating a written number into a spoken number.

// can we do the same with c_str() in c++17?
// Yes, the `c_str()` method is available in C++17 and can be used to obtain a C-style string
// (null-terminated character array) from a `std::string` object. The method returns a pointer to the
// internal character array of the string, which can be used in functions that require C-style strings.
// However, it's important to note that the pointer returned by `c_str()` is only valid as long as the `std::string`
// object is not modified or destroyed.


// can we do typecast into any type in c++17?
// In C++17, you can perform type casting to convert between different data types, but there are some rules and limitations.
// C++ provides several casting operators, including `static_cast`, `dynamic_cast`, `const_cast`, and `reinterpret_cast`,
// each serving different purposes. However, not all type conversions are valid or safe. For example,
// you cannot directly cast a string to an integer without using a conversion function like `stoi`. Similarly,
// casting between unrelated pointer types can lead to undefined behavior. Always ensure that the type conversion is
// meaningful and safe in the context of your program.

// do we have like stod or stof for converting string to double or float in c++17?
// Yes, in C++17, you have functions like `stod` (string to double) and `stof` (string to float) for converting strings to
// floating-point numbers. These functions are part of the C++ Standard Library and are defined in the `<string>` header.

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  s = "12345"; x = stoi(s) = 12345 (all digits, parses cleanly).
//         "x = 12345" prints.
// STEP 2  d = stod("3.14159") = 3.14159. "d = 3.14159" prints.
// STEP 3  sx = to_string(42) = "42" (a string, not an int anymore).
//         "sx = 42" prints.
// STEP 4  c = str1.c_str() points at "Hello, C++17!\0" in memory (the
//         hidden trailing '\0' is what makes it a valid C-style string).
//         "C-string: Hello, C++17!" prints.
// STEP 5  stoi("10cbv") parses "10" from the start and stops at 'c' —
//         val = 10, no exception thrown (the string DOES start with a
//         valid number, it just has extra text after it that stoi
//         ignores). "10" prints; neither catch block runs.
// STEP 6  main() returns 0.
