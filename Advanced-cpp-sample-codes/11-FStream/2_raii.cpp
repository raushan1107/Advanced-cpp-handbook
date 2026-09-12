// RAII (Resource Acquisition Is Initialization) with file streams — why
// you rarely need to call .close() explicitly.
//
// Compile: g++ -std=c++17 2_raii.cpp -o raii
// Run:     raii.exe   (Windows)   or   ./raii   (Linux/macOS)
// Interaction: enter your name, then your age. Creates user_data.txt in
// the current working directory.

#include <iostream>
#include <fstream>

using namespace std;

void fileWriteOperations() {
    cout << "File operations will be handled here." << endl;
    // RAII principle ensures that resources are released when they go out of scope.
    // In this case, file streams will automatically close when they go out of scope.
    cout << "Enter your name: ";
    string name;
    cin >> name;
    cout << "Enter your age: ";
    int age;
    cin >> age;

    // ofstream outfile("user_data.txt")
    // `outfile` is a LOCAL variable — its lifetime ends when
    // fileWriteOperations() returns. RAII means the resource (the open
    // file) is tied to that object's lifetime: the file is guaranteed to
    // close when `outfile` is destroyed, whether that's from reaching the
    // end of the function normally OR an exception unwinding through it.
    ofstream outfile("user_data.txt");
    if (outfile.is_open()) {
        outfile << "Name: " << name << endl;
        outfile << "Age: " << age << endl;
        //outfile.close();        // No need to explicitly close the file, RAII will handle it.

        cout << "User data written to file successfully." << endl;
    } else {
        cerr << "Error creating file." << endl;
    }

}

void fileReadOperations() {
    cout << "File read operations will be handled here." << endl;
    // RAII principle ensures that resources are released when they go out of scope.
    // In this case, file streams will automatically close when they go out of scope.
    ifstream infile("user_data.txt");
    if (infile.is_open()) {
        string line;
        cout << "Reading user data from file:" << endl;
        while (getline(infile, line)) {
            cout << line << endl;
        }
        // infile.close();        // No need to explicitly close the file, RAII will handle it.

    } else {
        cerr << "Error opening file." << endl;
    }
}


int main() {

    // Demonstrating RAII with file operations
    fileWriteOperations();
    fileReadOperations();
    return 0;
}



// with fstream class we don't need to explicitly close the files
// as the destructor of fstream will take care of closing the files using RAII principle.

// then in which case i need to handle is explicitly closing the files?
// One such case is when you are dealing with temporary files or when you want to ensure
// that a file is closed at a specific point in your code before the object goes out of scope.
// or, when you want to handle errors during file operations
// and need to close the file immediately after an error is detected.
// or, when working with c style file handling using FILE* pointers
// where you need to explicitly call fclose() to release the resource.

// --------------------------------------------------------------------------
// Step-by-step execution trace (example run: name="Asha", age=27)
// --------------------------------------------------------------------------
// STEP 1  fileWriteOperations() runs: user enters "Asha" and "27".
//         outfile opens user_data.txt and writes "Name: Asha" and "Age:
//         27".
// STEP 2  fileWriteOperations() returns WITHOUT ever calling
//         outfile.close() explicitly. At the closing brace of the
//         function, `outfile` (a local variable) goes out of scope — its
//         DESTRUCTOR runs automatically at that moment, and ofstream's
//         destructor closes the underlying file handle. This is RAII: the
//         file's lifetime is tied to the C++ object's lifetime, not to a
//         manually-remembered close() call.
// STEP 3  fileReadOperations() runs: infile opens the NOW-closed
//         user_data.txt (opening it for reading only works reliably
//         because STEP 2 already flushed and closed the write handle) and
//         reads it back line by line, printing "Name: Asha" then "Age:
//         27".
// STEP 4  fileReadOperations() returns; infile's destructor closes it the
//         same automatic way.
// STEP 5  main() returns 0.
