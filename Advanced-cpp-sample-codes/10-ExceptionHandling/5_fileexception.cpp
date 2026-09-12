// File-related exceptions — throwing a standard std::runtime_error when a
// file fails to open, instead of a custom exception class.
//
// Compile: g++ -std=c++17 5_fileexception.cpp -o fileexception
// Run:     fileexception.exe   (Windows)   or   ./fileexception   (Linux/macOS)
// Note: this file hardcodes a specific path (C:\Users\raush\Downloads\
// CppTasks.txt) that likely doesn't exist on your machine — that's
// exactly what makes the exception path the one you'll actually see run;
// change the path to a real file on your system to see the "success" path
// instead.
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

// readFile(filename)
//   filename - the path to open and print, line by line.
void readFile(const string& filename) {
    ifstream file(filename);

    // file.is_open()
    // No parameters — returns false if the file couldn't be opened (wrong
    // path, no read permission, etc.); `throw runtime_error(...)` here
    // uses a STANDARD library exception type instead of a custom class
    // like 3_customexception.cpp's InsufficientFundsException — a
    // reasonable choice when you don't need extra structured data beyond
    // a message.
    if (!file.is_open())
        throw runtime_error("File not found: " + filename);
    string line;

    while (getline(file, line)) {
        cout << line << endl;
    }
}

int main() {
    try {
        readFile("C:\\Users\\raush\\Downloads\\CppTasks.txt");
    }

    // catch (runtime_error &e)
    //   e - the thrown runtime_error, caught by (non-const) reference;
    //       e.what() returns the message built in readFile() above.
    catch (runtime_error &e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << "Program finished safely." << endl;

}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  readFile("C:\\Users\\raush\\Downloads\\CppTasks.txt") attempts
//         to open that exact path.
// STEP 2  If that file doesn't exist on the machine running this program
//         (the common case, since this is a hardcoded path from one
//         specific developer's machine), file.is_open() returns false ->
//         throw runtime_error("File not found: C:\\Users\\raush\\
//         Downloads\\CppTasks.txt") fires.
// STEP 3  The catch clause matches; "Error: File not found:
//         C:\Users\raush\Downloads\CppTasks.txt" prints.
// STEP 4  "Program finished safely." prints — the program didn't crash
//         even though the file was missing.
//
// If the file DID exist and open successfully, readFile would instead
// loop through getline(file, line), printing each line of the file to
// cout, and the catch block would simply never run.
