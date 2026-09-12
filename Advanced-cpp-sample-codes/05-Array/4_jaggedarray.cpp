// Jagged arrays — an array of ROWS where each row can be a DIFFERENT
// length (unlike 3_twodarray.cpp's grid, where every row has the same
// column count). Built here with an array of int* and manual new[]/delete[].
//
// Compile: g++ -std=c++17 4_jaggedarray.cpp -o jaggedarray
// Run:     jaggedarray.exe   (Windows)   or   ./jaggedarray   (Linux/macOS)
// Interaction: enter marks for 3 students in Class 1, 5 in Class 2, 2 in
// Class 3 (the class sizes are fixed by `sizes` below, not asked for).

#include <iostream>
using namespace std;

int main() {
    int classes = 3;
    // int* students[3]
    // An array of 3 POINTERS (not 3 ints) — each students[i] will point
    // at its OWN separately-allocated array, and those arrays don't have
    // to be the same length, which is exactly what makes this "jagged"
    // rather than a uniform grid.
    int* students[3];     // array of 3 int* (each points to an array)

    int sizes[] = {3, 5, 2};  // number of students in each class

    // Allocate memory dynamically for each class
    for (int i = 0; i < classes; ++i) {
        // new int[sizes[i]]
        //   sizes[i] - how many ints to allocate for THIS class only
        //              (3 for class 0, 5 for class 1, 2 for class 2) —
        //              a DIFFERENT size each time through the loop, which
        //              a fixed 2D array (int[3][5], say) could not
        //              represent without wasting space on the shorter
        //              rows.
        students[i] = new int[sizes[i]];
        cout << "Enter marks for Class " << i + 1 << ": ";
        for (int j = 0; j < sizes[i]; ++j) {
            cin >> students[i][j];
        }
    }

    // Display the data
    cout << "\n--- Marks by Class ---\n";
    for (int i = 0; i < classes; ++i) {
        cout << "Class " << i + 1 << ": ";
        for (int j = 0; j < sizes[i]; ++j) {
            cout << students[i][j] << " ";
        }
        cout << endl;
    }

    // Free memory
    // delete[] students[i]
    //   students[i] - each class's array was allocated with `new[]`, so
    //                 it MUST be released with the matching `delete[]`
    //                 (not plain `delete`) or the program leaks memory —
    //                 one delete[] call per new[] call, run in a loop
    //                 here since there are 3 separate allocations to free.
    for (int i = 0; i < classes; ++i)
        delete[] students[i];

    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  i=0: students[0] = new int[3] (room for 3 marks); user enters 3
//         marks for Class 1, filling students[0][0..2].
// STEP 2  i=1: students[1] = new int[5] (room for 5 marks — a DIFFERENT
//         size than Class 1's array); user enters 5 marks.
// STEP 3  i=2: students[2] = new int[2]; user enters 2 marks.
// STEP 4  The display loop reads sizes[i] for each class, so it prints
//         exactly 3 marks for Class 1, 5 for Class 2, 2 for Class 3 —
//         never reading past the end of any one class's actual array.
// STEP 5  The cleanup loop calls delete[] students[0], then
//         delete[] students[1], then delete[] students[2] — three
//         separate deallocations, matching the three separate new[]
//         calls from STEPS 1-3.
// STEP 6  main() returns 0. If any delete[] call were missed, that
//         class's memory would leak (stay allocated with nothing left
//         pointing at it) for the rest of the program's run.
