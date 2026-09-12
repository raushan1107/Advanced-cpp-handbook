// Find, substring, replace, insert, erase in C++ strings
//
// Compile: g++ -std=c++17 4_manipulatestring.cpp -o manipulatestring
// Run:     manipulatestring.exe   (Windows)   or   ./manipulatestring   (Linux/macOS)
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "Hello, World! Welcome to C++ programming.";

    // Find substring
    // str.find("World")
    //   "World" - the substring searched for; returns the index of its
    //             first occurrence (7 here), or string::npos if absent.
    int pos = str.find("World");
    cout << pos << endl; // prints the index of the first occurrence of "World" or -1 if not found
    cout << string::npos << endl; // prints the maximum value of size_t, which is used to indicate "not found"
    if (pos != string::npos) {
        // this condition should be always true as -1 is never equals to
        // string::npos, but we are checking for the sake of demonstration
        // is this getting implicitly converted to size_t?
        // Yes, the comparison between pos (int) and string::npos (size_t)
        // involves an implicit conversion of pos to size_t for the comparison.
        // This is because string::npos is of type size_t, and when comparing
        // different types, C++ performs implicit type conversions to ensure both
        // operands are of the same type. In this case, pos is converted to
        // size_t before the comparison.
        cout << "'World' found at position: " << pos << endl;
    }
    cout << "Word 'World' not found in the string." << endl;
    // why we used int not size_t? Because find() returns size_t,
    // but we are using int for simplicity in this example. In production code,
    // it's better to use size_t to avoid potential issues with large strings.

    // Replace substring
    // str.replace(pos, 5, "Universe")
    //   pos        - starting index of the substring to replace (7, from
    //                the find() above).
    //   5          - how many characters to remove starting at pos ("World"
    //                is 5 characters).
    //   "Universe" - the replacement text, which does NOT need to be the
    //                same length as what it's replacing.
    str.replace(pos, 5, "Universe");
    cout << "After replacement: " << str << endl;

    // Insert substring
    // str.insert(0, "Greeting: ")
    //   0            - the index to insert AT; existing characters from
    //                  this index onward shift right to make room.
    //   "Greeting: " - the text being inserted.
    str.insert(0, "Greeting: ");
    cout << "After insertion: " << str << endl;

    // Erase substring
    // str.erase(0, 10)
    //   0  - starting index to erase from.
    //   10 - how many characters to remove ("Greeting: " is exactly 10
    //        characters, including the trailing space).
    str.erase(0, 10); // Remove "Greeting: "
    cout << "After erasure: " << str << endl;

    cout << "--------------------------------------------" << endl;

    string s = "The quick brown fox jumps over the lazy dog";

    // find
    auto pos1 = s.find("fox");
    // what is auto? The auto keyword in C++ is used for type inference,
    // allowing the compiler to automatically deduce the type of a variable from its initializer.
    // In this case, pos1 will be of type size_t, which is the return type of the find() function.

    // can we use auto always or in specific use-cases?
    // Yes, auto can be used in most cases where the type of the variable is clear from its initializer.
    // However, it is generally recommended to use auto when the type is complex or verbose, or
    // when the exact type is not important for the context.
    if (pos1 != string::npos) cout << "'fox' at index: " << pos1 << '\n';

    // substring
    // s.substr(pos1, 3)
    //   pos1 - starting index (wherever "fox" was found).
    //   3    - length to extract ("fox" is 3 characters).
    string w = s.substr(pos1, 3); // "fox"
    cout << "substr: " << w << '\n';

    // replace: replace 'dog' with 'cat'
    // s.find("dog")
    //   "dog" - the substring to locate before replacing it.
    pos1 = s.find("dog");
    if (pos1 != string::npos) s.replace(pos1, 3, "cat");
    cout << "After replace: " << s << '\n';

    // insert: insert "very " before 'lazy'
    pos1 = s.find("lazy");
    // s.insert(pos1, "very ")
    //   pos1     - the index to insert AT, immediately before "lazy".
    //   "very "  - the text being inserted (note the trailing space, so
    //              it reads "very lazy" rather than "verylazy").
    if (pos1 != string::npos) s.insert(pos1, "very ");
    cout << "After insert: " << s << '\n';

    // erase: remove 'brown '
    pos1 = s.find("brown ");
    if (pos1 != string::npos) s.erase(pos1, 6);
    cout << "After erase: " << s << '\n';

    return 0;
}

// Explanation:
// In this code, we demonstrate various string manipulation functions in C++. We use `find` to locate a substring within a string,
// `replace` to replace a portion of the string with another substring, `insert` to add a substring at a specific position,
// and `erase` to remove a portion of the string. These functions are part of the C++ Standard Library and provide powerful
// tools for working with strings.
// Real-world scenario: String manipulation is essential in many applications, such as text processing, data parsing, and
// user input handling. Understanding how to effectively manipulate strings allows developers to create more dynamic and
// responsive programs.
// Analogy: Think of string manipulation functions as tools in a toolbox. Each function serves a specific purpose, allowing
// you to modify and work with strings in various ways, much like how different tools are used for different tasks in
// construction or repair work.
// Note: The output of the program will show the results of each string manipulation operation, demonstrating how the
// original string is modified step by step.

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  str = "Hello, World! Welcome to C++ programming." — find("World")
//         returns 7. string::npos prints as a huge number (the largest
//         possible size_t value, typically 18446744073709551615 on a
//         64-bit build) — a sentinel value chosen because it can never be
//         a REAL valid index.
// STEP 2  str.replace(7, 5, "Universe") removes the 5 characters starting
//         at index 7 ("World") and puts "Universe" there instead: str
//         becomes "Hello, Universe! Welcome to C++ programming."
// STEP 3  str.insert(0, "Greeting: ") shifts everything right and adds the
//         prefix: str becomes "Greeting: Hello, Universe! Welcome to C++
//         programming."
// STEP 4  str.erase(0, 10) removes the first 10 characters ("Greeting: ")
//         str is back to "Hello, Universe! Welcome to C++ programming."
// STEP 5  s = "The quick brown fox jumps over the lazy dog". s.find("fox")
//         returns 16; s.substr(16, 3) extracts "fox".
// STEP 6  s.find("dog") finds it at the end; s.replace(...,"cat") turns
//         "...lazy dog" into "...lazy cat".
// STEP 7  s.find("lazy") locates it; s.insert(...,"very ") turns "the lazy
//         cat" into "the very lazy cat".
// STEP 8  s.find("brown ") locates it (6 characters including the
//         trailing space); s.erase(...,6) removes it, turning "quick
//         brown fox" into "quick fox".
// STEP 9  Final s: "The quick fox jumps over the very lazy cat".
