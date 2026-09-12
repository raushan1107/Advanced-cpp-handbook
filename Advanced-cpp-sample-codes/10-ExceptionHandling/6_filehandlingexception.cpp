// File-related exceptions — a near-duplicate of 5_fileexception.cpp (one
// extra inline comment noting the intent). See that file for the fully
// commented, currently-taught version of this pattern.
//
// Compile: g++ -std=c++17 6_filehandlingexception.cpp -o filehandlingexception
// Run:     filehandlingexception.exe   (Windows)   or   ./filehandlingexception   (Linux/macOS)
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

void readFile(const string& filename) {
    ifstream file(filename);
    // Check if file opened successfully and throw exception if not,
    // using standard runtime_error exception.

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

    catch (runtime_error &e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << "Program finished safely." << endl;

}

// --------------------------------------------------------------------------
// Step-by-step execution trace — identical program to
// 5_fileexception.cpp; see that file for the fully worked trace
// --------------------------------------------------------------------------
// STEP 1  readFile attempts to open the hardcoded path.
// STEP 2  On this (or most) machines, the file doesn't exist ->
//         file.is_open() is false -> throw runtime_error(...) fires.
// STEP 3  The catch clause prints "Error: File not found: ...".
// STEP 4  "Program finished safely." prints; main() ends.
