// std::find — a linear search over any iterator range for the first
// element equal to a given value.
//
// Compile: g++ -std=c++17 2_find.cpp -o find_demo
// Run:     find_demo.exe   (Windows)   or   ./find_demo   (Linux/macOS)
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{
    vector<int> arr = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n = arr.size();
    int target = 70;

    // Using std::find to search for the target element
    // find(arr.begin(), arr.end(), target)
    //   arr.begin(), arr.end() - the range to search, start to end.
    //   target                 - the value being searched for; returns an
    //                            iterator to its FIRST occurrence, or
    //                            arr.end() if it's nowhere in the range.
    auto it = find(arr.begin(), arr.end(), target);

    if (it != arr.end()) {
        // distance(arr.begin(), it)
        //   arr.begin(), it - the number of steps between these two
        //                     iterators — converts a found ITERATOR back
        //                     into a plain, printable INDEX.
        cout << "Element " << target << " found at index: " << distance(arr.begin(), it) << endl;
    } else {
        cout << "Element " << target << " not found in the array." << endl;
    }

    return 0;
}

// Find algorithm in C++
// The find algorithm is a part of the C++ Standard Library's <algorithm> header.
// It is used to search for a specific value within a range of elements.
// How it works?
// The find function takes three parameters: two iterators defining the range to search
// (begin and end) and the value to search for.
// It returns an iterator pointing to the first occurrence of the value within the range.
// If the value is not found, it returns the end iterator.
// In this example, we create a vector of integers and use the find function
// to search for a target value (70).
// If the value is found, we calculate the index using the distance function
// and print it; otherwise, we indicate that the element was not found.
// Use cases of find algorithm:
// 1. Searching Elements: To locate a specific value in a collection.
// 2. Validating Presence: To check if an element exists in a dataset.
// 3. Data Processing: In algorithms that require searching for elements as part of their logic
// Can we use find with other data structures?
// Yes, the find algorithm can be used with various data structures that support iterators,
// such as arrays, vectors, lists, and deques.
// Example with array:
// int arr[] = {10, 20, 30, 40, 50};
// auto it = find(begin(arr), end(arr), 30);
// In this example, we use the find function to search for the value 30 in a C-style array.
// Example with list:
// #include <list>
// list<int> myList = {10, 20, 30, 40, 50};
// auto it = find(begin(myList), end(myList), 30);
// In this example, we use the find function to search for the value 30 in a std::list.
// Conclusion:
// The find algorithm is a powerful and versatile tool in C++ for searching elements
// within various data structures, making it easier to implement search functionality
// in your programs.

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  arr = {10,20,30,40,50,60,70,80,90,100}; target = 70.
// STEP 2  find scans from arr.begin() forward: 10 (no match), 20, 30, 40,
//         50, 60 — all no match — then 70 AT INDEX 6 matches; it stops
//         there and returns an iterator pointing at that 70.
// STEP 3  it != arr.end() is true (a match was found) -> distance(begin,
//         it) computes 6 -> "Element 70 found at index: 6" prints.
// STEP 4  main() returns 0.
//
// If target had been, say, 999 (not in arr), find would scan the ENTIRE
// range without matching and return arr.end() — the if-check would then
// take the else branch, printing "Element 999 not found in the array."
