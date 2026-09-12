// Reading strings from the console — cin >> (stops at whitespace) vs.
// getline (reads a whole line, spaces included).
//
// Compile: g++ -std=c++17 2_stringinput.cpp -o stringinput
// Run:     stringinput.exe   (Windows)   or   ./stringinput   (Linux/macOS)
// Interaction: enter one word, then a full sentence.

#include<iostream>
#include<string>
using namespace std;

int main()
{
    string oneword;
    cout << "Enter a single word: ";
    cin >> oneword; // Input stops at whitespace
    cout << "You entered: " << oneword << endl;
    // cin.ignore()
    // After `cin >> oneword` reads the word itself, the newline character
    // (from pressing Enter) is STILL sitting in the input buffer, unread.
    // Without clearing it, the getline() call below would immediately
    // read that leftover newline as an empty line instead of waiting for
    // the user's next real input.
    cin.ignore(); // Clear the newline character from the input buffer

    //cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush rest of line
    string sentence;
    cout << "Enter a sentence: ";
    // getline(cin, sentence)
    //   cin      - the input stream to read from.
    //   sentence - filled with the ENTIRE line typed, including any
    //              spaces — unlike `cin >>`, which would stop at the
    //              first space.
    getline(cin, sentence); // Using getline to allow spaces in the sentence
    cout << "You entered: " << sentence << endl;


    // string feedback;
    // cout << "Enter your feedback: ";
    // getline(cin, feedback); // Using getline to allow spaces in the name
    // cout << "Feedback: " << feedback << "\nWelcome to C++ programming raining session with Raushan!" << endl;


    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace (example run: "Hello", then "This is a test")
// --------------------------------------------------------------------------
// STEP 1  User types "Hello" and presses Enter -> cin >> oneword reads
//         "Hello" into oneword, but LEAVES the newline from Enter still
//         waiting in the input buffer.
// STEP 2  "You entered: Hello" prints.
// STEP 3  cin.ignore() consumes exactly that one leftover newline
//         character, leaving the input buffer clean.
// STEP 4  User types "This is a test" and presses Enter -> getline(cin,
//         sentence) reads the WHOLE line, spaces included, into sentence.
//         Without STEP 3's cin.ignore(), this getline() would have
//         immediately returned an EMPTY string (matching the leftover
//         newline from STEP 1) instead of waiting for new input.
// STEP 5  "You entered: This is a test" prints.
// STEP 6  main() returns 0.
