// std::sort — sorting a C-style array in place, ascending (default) or
// descending (with a comparator).
//
// Compile: g++ -std=c++17 5_sorting.cpp -o sorting_demo
// Run:     sorting_demo.exe   (Windows)   or   ./sorting_demo   (Linux/macOS)
#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    //  how it is calulating n?
    // sizeof(arr)/sizeof(arr[0])
    //   sizeof(arr)    - the TOTAL size of the array in bytes (7 ints *
    //                    4 bytes each = 28, typically).
    //   sizeof(arr[0]) - the size of ONE element (4 bytes for an int).
    // Dividing total bytes by one element's bytes gives the ELEMENT
    // COUNT (7) — this trick only works for a real array, never for a
    // pointer (which is why vector/array-based code elsewhere in this
    // course uses .size() instead).
    int n = sizeof(arr)/sizeof(arr[0]);

    // Using sort function from algorithm header
    // sort(arr, arr + n)
    //   arr     - a pointer to the array's first element (an array name
    //             decays to this automatically, same as in
    //             07-Pointers/2_pointer2var.cpp).
    //   arr + n - a pointer one PAST the last element — pointer
    //             arithmetic, scaled by sizeof(int), exactly like that
    //             same pointers file. Together these two pointers mark
    //             the full range to sort, in ASCENDING order by default.
    sort(arr, arr + n);
    // sort(para1, para2) -> sort from para1 to para2 in ascending order
    // sort(para1, para2, greater<int>()) -> sort from para1 to para2 in descending order

    cout << "Sorted array Ascending: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    // Using sort function to do ascending order
    // sort(arr, arr + n, greater<int>())
    //   greater<int>() - a COMPARATOR object replacing the default `<`;
    //                    sort now arranges elements so that EARLIER
    //                    positions hold LARGER values — descending order.
    sort(arr, arr + n, greater<int>());

    cout << "Sorted array Descending: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}

// Explanation:
// This code demonstrates the use of the sort function from the C++ Standard Library's
// algorithm header
// to sort an array of integers in ascending order.
// How it works?
// The sort function takes two iterators as arguments: the beginning and the end of the range
// to be sorted. It rearranges the elements in that range in ascending order by default.
// In this example, we calculate the size of the array and pass the beginning (arr)
// and the end (arr + n) of the array to the sort function.
// After sorting, we print the sorted array to the console.

// Use cases of sort function:
// 1. Sorting Data: To arrange data in a specific order (ascending or descending).
// 2. Preparing for Search: Sorted data allows for efficient searching algorithms like binary search.
// 3. Data Analysis: Sorting is often a preliminary step in data analysis tasks.
// 4. Custom Sorting: The sort function can also take a custom comparator to sort based on specific criteria.
// Can we sort in descending order?
// Yes, by providing a custom comparator function or using predefined comparators like greater<int>,
// we can sort the array in descending order.
// Example of sorting in descending order:
// sort(arr, arr + n, greater<int>());

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  arr = {64, 34, 25, 12, 22, 11, 90}, n = 7 (28 bytes / 4 bytes
//         per int).
// STEP 2  sort(arr, arr+n) rearranges IN PLACE to ascending order: {11,
//         12, 22, 25, 34, 64, 90}. Prints "Sorted array Ascending: 11 12
//         22 25 34 64 90 ".
// STEP 3  sort(arr, arr+n, greater<int>()) sorts the ALREADY-sorted array
//         again, this time descending: {90, 64, 34, 25, 22, 12, 11}.
//         Prints "Sorted array Descending: 90 64 34 25 22 12 11 ".
// STEP 4  main() returns 0.
