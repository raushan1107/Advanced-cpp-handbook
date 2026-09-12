// File handling modes — ofstream's default (overwrite) mode vs. explicit
// append mode (std::ios::app), then reading everything back with ifstream.
//
// Compile: g++ -std=c++17 1_filehandlingmodes.cpp -o filehandlingmodes
// Run:     filehandlingmodes.exe   (Windows)   or   ./filehandlingmodes   (Linux/macOS)
// Creates/overwrites output.txt in the current working directory.
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    // Step 1: Write initial content (overwrite mode)

    // ofstream outFile("output.txt")
    //   "output.txt" - the file to open; with NO second argument, ofstream
    //                  defaults to std::ios::out, which TRUNCATES
    //                  (erases) any existing content the moment the file
    //                  is opened — this is why the file's final content
    //                  won't include anything from BEFORE this program ran.
    ofstream outFile("output.txt"); // Default is std::ios::out
    if (outFile.is_open()) {
        outFile << "Hello, this is a test file.\n";
        outFile << "Writing to a file using ofstream.\n";
        outFile.close();
        cout << "Initial data written to output.txt\n";
    } else {
        cerr << "Failed to open file for writing.\n";
    }

    // ofstream outFile2("output.txt")
    // A SECOND ofstream, opened in the SAME default overwrite mode —
    // this ERASES everything outFile just wrote, since overwrite mode
    // truncates on open, every time a new ofstream targets that path.
    ofstream outFile2("output.txt"); // Default is std::ios::out
    if (outFile2.is_open()) {
        outFile2 << "Hello, this is a test2 file.\n";
        outFile2 << "2. Writing to a file using ofstream.\n";
        outFile2.close();
        cout << "Initial data written to output.txt\n";
    } else {
        cerr << "Failed to open file for writing.\n";
    }
    // Step 2: Append new content
    // ofstream appendFile("output.txt", std::ios::app)
    //   std::ios::app - APPEND mode: new writes are added to the END of
    //                  the file's EXISTING content instead of erasing it
    //                  first — this is the line that actually preserves
    //                  outFile2's text instead of truncating it again.
    ofstream appendFile("output.txt", std::ios::app); // Open in append mode
    if (appendFile.is_open()) {
        appendFile << "This line is appended to the file.\n";
        appendFile << "Appending more data without overwriting.\n";
        appendFile.close();
        cout << "Additional data appended to output.txt\n";
    } else {
        cerr << "Failed to open file for appending.\n";
    }

    // Step 3: Read and display the final content of the file
    ifstream inFile("output.txt");
    if (inFile.is_open()) {
        string line;
        cout << "Final content of output.txt:\n";
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cerr << "Failed to open file for reading.\n";
    }
    return 0;
}


// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  outFile opens output.txt in (default) overwrite mode, writing
//         two lines: "Hello, this is a test file." and "Writing to a
//         file using ofstream." — the file NOW contains exactly these two
//         lines.
// STEP 2  outFile2 opens the SAME path, ALSO in overwrite mode — this
//         truncates the file, discarding STEP 1's two lines entirely, and
//         writes two DIFFERENT lines instead: "Hello, this is a test2
//         file." and "2. Writing to a file using ofstream." — the file
//         now contains ONLY these two lines, with no trace of STEP 1.
// STEP 3  appendFile opens the same path in std::ios::app mode — this
//         does NOT erase STEP 2's content; it adds two MORE lines after
//         it: "This line is appended to the file." and "Appending more
//         data without overwriting." The file now has FOUR lines total.
// STEP 4  inFile reads the file back line by line and prints all four:
//         "Hello, this is a test2 file.", "2. Writing to a file using
//         ofstream.", "This line is appended to the file.", "Appending
//         more data without overwriting." — STEP 1's two lines never
//         appear, since they were overwritten before ever being read.
// STEP 5  main() returns 0.
