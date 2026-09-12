// String capacity — size() vs capacity(): how many characters a string
// HOLDS vs how much memory it has ALLOCATED, and reserve()/shrink_to_fit()
// to control that allocation explicitly.
//
// Compile: g++ -std=c++17 7_stringCapacity.cpp -o stringCapacity
// Run:     stringCapacity.exe   (Windows)   or   ./stringCapacity   (Linux/macOS)

#include<iostream>
#include<string>
using namespace std;

int main() {
    string str = "Hello, World!";

    cout << "String: " << str << endl;
    cout << "Size: " << str.size() << endl;          // Number of characters in the string
    cout << "Length: " << str.length() << endl;      // Same as size()
    cout << "Capacity: " << str.capacity() << endl;  // Size of allocated storage
    cout << "Max Size: " << str.max_size() << endl;  // Maximum size the string can reach

    // str.reserve(500)
    //   500 - a HINT: "make sure at least 500 characters fit without
    //         reallocating," even though `str` only currently holds 13.
    //         size() stays 13 (reserve doesn't add characters); capacity()
    //         grows to at least 500.
    str.reserve(500); // Reserve space for at least 50 characters
    cout << "After reserving capacity of 500:" << endl;
    cout << "String: " << str << endl;
    cout << "Size: " << str.size() << endl;          // Number of characters in the string
    cout << "Length: " << str.length() << endl;      // Same as size()
    cout << "Capacity: " << str.capacity() << endl;  // Size of allocated storage
    cout << "Max Size: " << str.max_size() << endl; // Maximum size the string can reach

    string s;
    cout << "Initial capacity of empty string: " << s.capacity() << endl;
    // s += "C++ Programming"
    //   "C++ Programming" - 16 characters appended to the empty string
    //                       `s`; since `s` had no reserved capacity, this
    //                       forces at least one allocation.
    s += "C++ Programming";
    cout << "Capacity after adding 'C++ Programming': " << s.capacity() << endl;

    s.reserve(1000); // Reserve space for at least 1000 characters
    cout << "Capacity after reserving 1000: " << s.capacity() << endl;
    for(int i = 0; i < 800; i++)
    {
        // s += 'a'
        //   'a' - one character appended per iteration; because 1000
        //         characters were already reserved above, none of these
        //         800 appends needs to trigger a reallocation.
        s += 'a'; // Append 800 'a' characters
    };
    cout << "Capacity after adding 800 'a' characters: " << s.capacity() << endl;

    // s.shrink_to_fit()
    // No parameters — a (non-binding) REQUEST to the implementation to
    // reduce capacity down to match the current size exactly, releasing
    // whatever reserved-but-unused memory is left.
    s.shrink_to_fit(); // Reduce capacity to fit size
    cout << "Capacity after shrink_to_fit: " << s.capacity() << endl;

    // s.clear()
    // No parameters — empties the string's CONTENT (size becomes 0), but
    // does NOT necessarily release the underlying buffer — that's why the
    // next line's capacity print may still show a nonzero number.
    s.clear(); // Clear the string
    cout << "Capacity after clearing the string: " << s.capacity() << endl;

    cout << "Final String: '" << s << "'" << endl;

    return 0;
}

// Where do we use string capacity functions?
// 1. Performance Optimization: Pre-allocating memory to avoid multiple reallocations.
// 2. Memory Management: Controlling memory usage in applications with large strings.
// 3. Dynamic String Handling: Efficiently managing strings that change size frequently.
// 4. Game Development: Managing in-game text and dialogues efficiently.
// 5. Real-time Systems: Ensuring predictable memory usage and performance.
// 6. Text Processing Applications: Handling large volumes of text data efficiently.
// 7. Network Programming: Managing buffers for incoming and outgoing data.
// 8. Embedded Systems: Optimizing memory usage in resource-constrained environments.
// 9. Database Systems: Efficiently managing string data in databases.
// 10. User Interface Development: Handling dynamic text in UI elements efficiently.
// This code demonstrates the use of string capacity functions in C++.
// It shows how to check and manipulate the capacity of strings for performance optimization and memory management.

// How it works?
// 1. The program starts by including the necessary headers and using the std namespace.
// 2. It initializes a string with "Hello, World!" and prints its size, length, capacity, and max size.
// 3. It then reserves a capacity of 500 for the string and prints the updated properties.
// 4. An empty string is created, and its initial capacity is printed.
// 5. The program appends "C++ Programming" to the string and prints the new capacity.
// 6. It reserves a capacity of 1000 and appends 800 'a' characters, printing the capacity after each operation.
// 7. The shrink_to_fit function is called to reduce the capacity to fit the current
//    size, and the new capacity is printed.
// 8. The string is cleared, and the capacity is printed again.
// 9. Finally, the program prints the final state of the string and returns 0 to indicate successful execution. size, and the new capacity is printed.
// 8. The string is cleared, and the capacity is printed again.
// 9. Finally, the program prints the final state of the string and returns 0 to indicate successful execution. size, and the new capacity is printed.

// --------------------------------------------------------------------------
// Step-by-step execution trace (exact capacity NUMBERS are implementation-
// defined and will vary by standard library/compiler — the RELATIONSHIPS
// described below always hold)
// --------------------------------------------------------------------------
// STEP 1  str = "Hello, World!" (13 characters). size()==length()==13;
//         capacity() is whatever the library allocated for a 13-char
//         string (often >=13, sometimes exactly 15 due to small-string
//         optimization).
// STEP 2  str.reserve(500): size() stays 13 (unchanged), capacity()
//         becomes AT LEAST 500 — reserve never shrinks capacity or
//         changes the string's content, it only guarantees a minimum.
// STEP 3  s starts empty: size()==0, capacity() is whatever the
//         implementation's default empty-string capacity is (often 15,
//         due to small-string optimization avoiding heap allocation for
//         very short strings).
// STEP 4  s += "C++ Programming" (16 chars): size() becomes 16; if 16
//         exceeds the small-string-optimization threshold, capacity()
//         jumps to whatever the library over-allocates to (commonly more
//         than 16, to leave room for future growth).
// STEP 5  s.reserve(1000): capacity() becomes at least 1000; size() stays
//         16.
// STEP 6  The loop appends 800 more characters one at a time: size()
//         grows to 16+800=816, but capacity() stays at (at least) 1000
//         throughout, since STEP 5 already reserved enough room — no
//         reallocation happens mid-loop.
// STEP 7  s.shrink_to_fit(): capacity() is reduced toward size() (816),
//         though the standard doesn't guarantee it becomes EXACTLY 816.
// STEP 8  s.clear(): size() becomes 0; capacity() is left up to the
//         implementation — many implementations keep the existing buffer
//         (capacity unchanged) rather than freeing it, since the memory
//         might be reused by the next append.
// STEP 9  Final string prints as '' (empty), confirming clear() emptied
//         the CONTENT even though capacity may still be nonzero.
