// String comparison — ==, .compare(), and case-insensitive comparison via
// std::transform + std::tolower.
//
// Compile: g++ -std=c++17 3_stringscompare.cpp -o stringscompare
// Run:     stringscompare.exe   (Windows)   or   ./stringscompare   (Linux/macOS)
// Interaction: enter a sentence (spaces allowed), then a single word.

#include<iostream>
#include<string>
#include<algorithm>
#include<cctype>
using namespace std;

int main(){
    string str1;
    cout << "Enter a string: ";
    getline(cin, str1); // Using getline to read string with spaces
    cout << "You entered: " << str1 << endl;

    string str2;
    cout << "Enter another string: ";
    cin >> str2; // Using cin to read string without spaces
    cout << "You entered: " << str2 << endl;

    // Comparing strings
    cout << "Comparing the two strings..." << endl;
    cout << boolalpha; // to print bool as true/false
    cout << "str1 == str2: " << (str1 == str2) << endl;

    // str1.compare(str2)
    //   str2 - returns 0 if the two strings are identical, a negative
    //          number if str1 sorts BEFORE str2 lexicographically, and a
    //          positive number if str1 sorts AFTER str2 — unlike ==, this
    //          also tells you the ORDERING, not just equal/not-equal.
    cout << "string1.compare(string2): " << str1.compare(str2) << endl; // 0 if equal, <0 if str1<str2, >0 if str1>str2

    // case-sensitive comparison
    string str3 = str1, str4 = str2;
    // std::transform(str3.begin(), str3.end(), str3.begin(), lambda)
    //   str3.begin(), str3.end() - the INPUT range: every character of
    //                              str3, start to end.
    //   str3.begin() (3rd arg)   - the OUTPUT destination: where the
    //                              transformed characters get written —
    //                              here, back into str3 itself, so it's
    //                              modified in place.
    //   lambda [](unsigned char c){ return static_cast<char>(tolower(c)); }
    //                             - applied to EVERY character in turn;
    //                              `c` is each original character, and the
    //                              lambda's return value REPLACES it.
    std::transform(str3.begin(), str3.end(), str3.begin(),
        [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
    std::transform(str4.begin(), str4.end(), str4.begin(),
        [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
    cout << "Case-insensitive comparison (after converting to lowercase): " << (str3 == str4) << endl;
    cout << "----------------------------------------" << endl;
    // Explanation of above comparison methods for case insensitive.
    // at line 26 -> str3 = str1 and str4 = str2,
    // then we convert both strings to lowercase using std::transform and std::tolower.
    // This allows us to perform a case-insensitive comparison by checking if the
    // lowercase versions
    // of the strings are equal.

    // syntax breakdown -> transform(str3.begin(), str3.end(), str3.begin(), [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
    // std::transform is a standard algorithm that applies a function to a range of elements.
    // str3.begin() and str3.end() define the range of elements in str3
    // The third argument, str3.begin(), specifies where to store the transformed elements
    // (in this case, back into str3).
    // The fourth argument is a lambda function that takes an unsigned char c and returns its lowercase
    // equivalent using std::tolower. The static_cast<char> is used to ensure the return type is char,
    // as std::tolower returns an int.
    // This effectively converts each character in str3 to lowercase, allowing for a
    // case-insensitive comparison with str4.
    // what is static_cast<char> -> static_cast is a C++ operator used for type conversion.
    // In this context, it converts the result of std::tolower (which returns an int) back to a
    // char type. This is necessary because std::tolower can return values outside the range of
    // char, and we want to ensure that the transformed characters are stored as char in the string.
    // Why we use unsigned char in the lambda function -> std::tolower expects an unsigned char
    // as input to avoid undefined behavior for negative values. By using unsigned char,
    // we ensure that the input to std::tolower is always valid, preventing potential issues with
    // character encoding and ensuring correct case conversion.

    return 0;
}

// When to use a.compare(b) vs a==b?
// a.compare(b) provides more detailed information about the lexicographical relationship between the strings (
// whether one is less than, equal to, or greater than the other), while a==b simply checks for equality.
// Use a.compare(b) when you need to know the ordering of the strings, and use a==b when you only need to check if they are identical.
// Analogy: Think of a.compare(b) like comparing two books to see which one comes first in alphabetical order, while a==b is like checking if two books are exactly the same edition.
// Note: The comparison is case-sensitive. "Hello" and "hello" are considered different strings.
// For case-insensitive comparison, you can convert both strings to the same case (either upper or lower) before comparing.
// Example of case-insensitive comparison is shown above using std::transform and std::tolower.
// Additional string comparison methods:
// 1. Using relational operators: <, >, <=, >=
// 2. Using std::equal from <algorithm> for custom comparison logic
// 3. Using locale-aware comparison with std::use_facet and std::collate for internationalization support
// Remember to include <algorithm> and <cctype> for case conversion functions.

// --------------------------------------------------------------------------
// Step-by-step execution trace (example run: str1="Hello World", str2="hello")
// --------------------------------------------------------------------------
// STEP 1  str1 = "Hello World" (getline captured the space). str2 =
//         "hello" (cin >> stopped there since there's no second word to
//         worry about in this example).
// STEP 2  str1 == str2 is false (different text entirely, and different
//         case too) -> prints "false".
// STEP 3  str1.compare(str2): 'H' (72) is less than 'h' (104) in ASCII, so
//         str1 sorts BEFORE str2 -> compare() returns a negative number.
// STEP 4  str3 = "Hello World", str4 = "hello" (copies of str1/str2
//         before transform runs).
// STEP 5  std::transform lowercases str3 in place, character by
//         character: str3 becomes "hello world". The SAME happens to
//         str4, which is already all-lowercase, so str4 stays "hello".
// STEP 6  str3 == str4 compares "hello world" to "hello" — these are
//         still DIFFERENT strings (one has an extra " world"), so this
//         prints "false" too, even though the case-insensitive step ran
//         correctly — case-insensitivity only helps when the underlying
//         TEXT (ignoring case) actually matches.
//
// A worked trace of the transform loop ITSELF (a separate, smaller
// example the file's original author included, showing why str3 must be
// read from BEFORE it's written to at each index — reading and writing
// the SAME string in one pass is safe here because transform always reads
// index i before writing index i, never reading an index it already
// overwrote):
// Initial state: ['S', 'u', 'r', 'a', 'j'] (indices 0, 1, 2, 3, 4)
// Step 1 (i = 0): Reads str3[0] ('S'), converts to 's', writes to str3[0].
// Step 2 (i = 1): Reads str3[1] ('u'), converts to 'u', writes to str3[1].
// Step 3 (i = 2): Reads str3[2] ('r'), converts to 'r', writes to str3[2].
// ...continuing through every index leaves the final string "suraj" —
// each position is read once and written once, in order, with no position
// read AFTER a later position has already overwritten anything it depends
// on.
