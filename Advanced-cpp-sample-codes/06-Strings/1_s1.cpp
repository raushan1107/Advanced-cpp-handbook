// String manipulation in C++ using C++17 standard
// This program demonstrates various string operations such as concatenation, substring extraction, and searching.
// What is a string? In C++, a string is a sequence of characters used to represent text. The C++ Standard Library provides the `std::string` class, which offers a convenient way to work with strings, including dynamic sizing and various member functions for manipulation.
// Analogy: Think of a string as a necklace made up of individual beads (characters). You can add more beads, remove some, or rearrange them to create different patterns (manipulate the string).
//
// Compile: g++ -std=c++17 1_s1.cpp -o s1
// Run:     s1.exe   (Windows)   or   ./s1   (Linux/macOS)

#include <iostream>
#include <string>
using namespace std;

int main() {
    // Creating and initializing strings
    string str1 = "Hello, ";
    string str2 = "World!";

    // Concatenation
    string str3 = str1 + str2;
    cout << "Concatenated String: " << str3 << endl;

    // str3.substr(7, 5)
    //   7 - the starting index to extract from (0-based; str3 is
    //       "Hello, World!", so index 7 is 'W').
    //   5 - how many characters to extract, starting at index 7 —
    //       "World" is exactly 5 characters.
    // Substring extraction
    string subStr = str3.substr(7, 5); // Extract "World" // from str3 starting at index 7 with length 5
    cout << "Extracted Substring: " << subStr << endl;

    // str3.find("World")
    //   "World" - the substring to search for; returns the index of its
    //             FIRST occurrence, or the special value string::npos if
    //             it isn't found anywhere in str3.
    // Searching for a substring
    size_t pos = str3.find("World");
    if (pos != string::npos) {
        cout << "'World' found at position: " << pos << endl;
    } else {
        cout << "'World' not found!" << endl;
    }

    // accessing characters using indexing
    cout << "First character of str3: " << str3[0] << endl;
    cout << "str3[9]: " << str3[9] << endl;

    // String length
    cout << "Length of str3: " << str3.length() << endl;

    // Iterating through characters
    cout << "Characters in str3: ";
    for (char c : str3) {
        cout << c << ' ';
    }
    cout << endl;

    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  str1 = "Hello, ", str2 = "World!". str3 = str1 + str2 =
//         "Hello, World!" (13 characters, indices 0-12).
// STEP 2  str3.substr(7, 5): counting from index 0, str3 is
//         H(0) e(1) l(2) l(3) o(4) ,(5) (space)(6) W(7) o(8) r(9) l(10)
//         d(11) !(12) — so index 7 is 'W', and the next 5 characters
//         (indices 7-11) spell "World". subStr = "World".
// STEP 3  str3.find("World") returns 7 (matching STEP 2's index) — since
//         7 != string::npos, "found at position: 7" prints.
// STEP 4  str3[0] is 'H'; str3[9] is 'r' (counting from STEP 2's index
//         map).
// STEP 5  str3.length() returns 13.
// STEP 6  The for loop visits every character of str3 in order, printing
//         each one followed by a space: "H e l l o ,   W o r l d ! ".
// STEP 7  main() returns 0.
