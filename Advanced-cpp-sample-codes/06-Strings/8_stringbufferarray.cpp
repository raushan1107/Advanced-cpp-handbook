// c string interoperability using string buffer and array
//
// Compile: g++ -std=c++17 8_stringbufferarray.cpp -o stringbufferarray
// Run:     stringbufferarray.exe   (Windows)   or   ./stringbufferarray   (Linux/macOS)
#include <iostream>
#include <string>
#include <cstring> // for std::strlen, std::strcpy, std::strcat
using namespace std;

int main()
{
    char buffer[100]; // Create a character buffer (C-style string)
    // strcpy(buffer, "Hello, C-Style String!")
    //   buffer                    - the destination char array; MUST be
    //                                large enough to hold the source text
    //                                plus its terminating '\0', or this
    //                                overflows the buffer (undefined
    //                                behavior — strcpy does NOT check the
    //                                destination's size).
    //   "Hello, C-Style String!"  - the null-terminated source text being
    //                                copied in.
    strcpy(buffer, "Hello, C-Style String!"); // Copy a C-style string into the buffer
    cout << "C-Style String: " << buffer << endl;
    buffer[sizeof(buffer) - 1] = '\0'; // Ensure null-termination
    cout << "buffer: "<< buffer << endl;

    //safer copy: strncpy ensures no buffer overflow
    char safeBuffer[100];
    // strncpy(safeBuffer, buffer, sizeof(safeBuffer) - 1)
    //   safeBuffer             - destination.
    //   buffer                 - source text to copy.
    //   sizeof(safeBuffer) - 1 - the MAXIMUM number of characters to
    //                            copy, leaving room for the manual '\0'
    //                            added on the next line — unlike strcpy,
    //                            strncpy will stop at this limit instead
    //                            of overflowing, but it does NOT
    //                            guarantee null-termination itself if the
    //                            source is exactly that long or longer.
    strncpy(safeBuffer, buffer, sizeof(safeBuffer) - 1);
    safeBuffer[sizeof(safeBuffer) - 1] = '\0'; // Ensure
    cout << "Safe Buffer: " << safeBuffer << endl;

    // concatenate using strcat
    // strcat(safeBuffer, " - Appended Text")
    //   safeBuffer         - the destination, which the new text is
    //                        appended to the END of (it must already be
    //                        null-terminated, and have enough spare room
    //                        for the addition).
    //   " - Appended Text" - the text appended.
    strcat(safeBuffer, " - Appended Text");
    cout << "After strcat: " << safeBuffer << endl;

    //compare using strcmp
    // strcmp(safeBuffer, "Hello, C-Style String! - Appended Text")
    // Returns 0 only if the two C-strings are IDENTICAL character for
    // character (like std::string's .compare(), but for char arrays).
    if (strcmp(safeBuffer, "Hello, C-Style String! - Appended Text") == 0) {
        cout << "Strings are equal." << endl;
    } else {
        cout << "Strings are not equal." << endl;
    }

    // strcmp vs (s.compare) vs (==) in c++ strings?
    // strcmp is a C-style function that compares two C-style strings and returns an integer.
    // s.compare() is a C++ string method that compares two C++ strings and returns an integer.
    // == is the equality operator for C++ strings, which returns a boolean value.

    // what is the differemce between c-style string vs c++ string?
    // A C-style string is a null-terminated array of characters,
    // while a C++ string is an object of the std::string class that provides a more
    // convenient and safer way to work with strings.
    // Which one to use depends on the context and requirements of your program.

    // For example, if you are working with legacy C code or need to interface with C libraries,
    // you may need to use C-style strings. However, if you are writing modern C++ code,
    // it is generally recommended to use C++ strings for their safety and convenience.

    // Initialize a C++ string
    string cppStr = "Hello, C++ String!";
    cout << "C++ String: " << cppStr << endl;

    // Convert C++ string to C-style string (char array)
    // cppStr.c_str()
    // No parameters — returns a `const char*` view into cppStr's own
    // internal buffer (not a copy); valid only as long as cppStr itself
    // isn't modified or destroyed afterward.
    const char* cStr = cppStr.c_str();
    cout << "C-style String (from C++ string): " << cStr << endl;

    // Create a char array (C-style string) and copy the C++ string into it
    char charArray[50];
    // strcpy(charArray, cStr)
    //   charArray - destination, big enough here (50 bytes) for cStr's
    //               19 characters plus the terminator.
    //   cStr      - source, from cppStr.c_str() above.
    strcpy(charArray, cStr);
    cout << "Char Array after strcpy: " << charArray << endl;

    // Modify the char array
    strcat(charArray, " - Modified in C-style");
    cout << "Char Array after strcat: " << charArray << endl;

    // Convert back to C++ string
    // string newCppStr(charArray)
    //   charArray - a C-style (null-terminated) string; std::string's
    //               constructor reads it up to the '\0' and copies those
    //               characters into a proper std::string object.
    string newCppStr(charArray);
    cout << "New C++ String (from Char Array): " << newCppStr << endl;

    // newCppStr.replace(newCppStr.find("C"), 1, "P")
    //   newCppStr.find("C") - the index of the FIRST "C" found (used
    //                         directly as replace's starting-index
    //                         argument, without storing it separately).
    //   1                   - how many characters to replace (just the
    //                         one "C").
    //   "P"                 - the replacement text.
    newCppStr.replace(newCppStr.find("C"), 1, "P");
    // replace(para1, para2, para3)
    // -> para1 = starting index, para2 = length of substring to replace, para3 = new substring
    cout << "After replace in C++ String: " << newCppStr << endl;
    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  strcpy fills buffer with "Hello, C-Style String!\0". Both cout
//         lines print that same text.
// STEP 2  strncpy copies up to 99 characters of buffer into safeBuffer,
//         and the manual '\0' assignment guarantees termination even in
//         the (here, not-reached) case where the source was 99+ chars.
//         safeBuffer == "Hello, C-Style String!".
// STEP 3  strcat appends " - Appended Text" onto the end of safeBuffer:
//         it becomes "Hello, C-Style String! - Appended Text".
// STEP 4  strcmp compares that exact text against the literal
//         "Hello, C-Style String! - Appended Text" — they match
//         character-for-character, so strcmp returns 0, and "Strings are
//         equal." prints.
// STEP 5  cppStr = "Hello, C++ String!"; cStr points at its internal
//         buffer; both print the same text.
// STEP 6  strcpy copies cStr's 19 characters into charArray; strcat
//         appends " - Modified in C-style", making charArray
//         "Hello, C++ String! - Modified in C-style".
// STEP 7  newCppStr is constructed from that char array — an independent
//         std::string copy, not a view into charArray.
// STEP 8  newCppStr.find("C") locates the FIRST "C" — that's the one in
//         "C++" (index 7), not any letter in "C-style" further along, so
//         replace(7, 1, "P") turns "C++" into "P++": final output is
//         "Hello, P++ String! - Modified in C-style".
