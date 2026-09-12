// 2D arrays — a fixed-size grid, then a runtime-sized one (rows/columns
// entered by the user), each visited with a NESTED loop (outer = rows,
// inner = columns).
//
// Compile: g++ -std=c++17 3_twodarray.cpp -o twodarray
// Run:     twodarray.exe   (Windows)   or   ./twodarray   (Linux/macOS)
// Interaction: after the fixed 2x3 grid prints, enter a row count, a
// column count, then that many numbers.

#include<iostream>
using namespace std;

int main()
{
    // int testarr[2][3] = { {1,2,3}, {4,5,6} }
    // A 2-row, 3-column grid: testarr[0] is the first row {1,2,3},
    // testarr[1] is the second row {4,5,6}.
    int testarr[2][3] = { {1, 2, 3},
                          {4, 5, 6}
                        };

    // Printing 2D array
    // Using nested for loop
    cout << "The elements in the 2D array are: " << endl;
    // outer loop for rows
    for(int i = 0; i < 2; i++)
    {
        // inner loop for columns
        // For each FIXED row `i`, the inner loop walks across every
        // column `j` in that row before the outer loop moves to the next
        // row — this is why nested loops visit a grid row-by-row, not
        // column-by-column.
        for(int j = 0; j < 3; j++)
        {
            cout << testarr[i][j] << " ";
        }
        cout << endl;
    }


    int row, col;
    cout << "Enter number of rows and columns";
    cout << "Rows: ";
    cin >> row;
    cout << "Columns: ";
    cin >> col;
    // int arr[row][col]
    // A 2D Variable Length Array — same GCC/Clang extension as
    // 2_arr2.cpp's 1D version, just with BOTH dimensions decided at
    // runtime instead of compile time.
    int arr[row][col];
    // Taking input for 2D array
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            cout << "Enter element at position [" << i << "][" << j << "]: ";
            cin >> arr[i][j];
        }
    }
    // Printing 2D array
    cout << "The elements in the 2D array are: " << endl;
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace (fixed grid, then example run: row=2, col=2)
// --------------------------------------------------------------------------
// STEP 1  The fixed testarr prints first, row by row: i=0 walks j=0,1,2
//         printing "1 2 3 " then a newline; i=1 walks j=0,1,2 printing
//         "4 5 6 " then a newline.
// STEP 2  User enters row=2, col=2 -> arr becomes a 2x2 grid.
// STEP 3  Input loop: i=0,j=0 -> arr[0][0]; i=0,j=1 -> arr[0][1]; i=1,j=0
//         -> arr[1][0]; i=1,j=1 -> arr[1][1] — filled in that exact
//         row-then-column order (say the user enters 1, 2, 3, 4 in that
//         order).
// STEP 4  Print loop walks the same order: prints "1 2 " + newline, then
//         "3 4 " + newline — the row/column order the numbers went IN is
//         the same order they come back OUT.
