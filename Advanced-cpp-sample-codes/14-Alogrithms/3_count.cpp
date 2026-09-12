// std::count and std::count_if — counting elements that equal a value, or
// that satisfy an arbitrary predicate.
//
// Compile: g++ -std=c++17 3_count.cpp -o count_demo
// Run:     count_demo.exe   (Windows)   or   ./count_demo   (Linux/macOS)
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    vector<int> arr = {5,5, 3, 8,5, 6, 2, 7, 4, 1};

    // Counting occurrences of the number 5
    int n=5;
    // count(arr.begin(), arr.end(), n)
    //   arr.begin(), arr.end() - the range to scan, in full.
    //   n                       - the exact VALUE to count matches of.
    int count5 = count(arr.begin(), arr.end(), n);
    cout << "Number of occurrences of 5: " << count5 << endl;

    // Counting occurrences of numbers greater than 4
    // count_if(arr.begin(), arr.end(), lambda)
    //   [](int x){ return x > 4; } - a PREDICATE instead of a fixed
    //                                value — called once per element;
    //                                count_if tallies how many calls
    //                                returned true, letting you count by
    //                                any arbitrary condition, not just
    //                                equality.
    int countGreaterThan4 = count_if(arr.begin(), arr.end(), [](int x) { return x > 4; });
    cout << "Number of elements greater than 4: " << countGreaterThan4 << endl;

    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  arr = {5, 5, 3, 8, 5, 6, 2, 7, 4, 1}.
// STEP 2  count(arr.begin(), arr.end(), 5) scans every element, comparing
//         each to 5: matches at positions 0, 1, and 4 (three 5s total) ->
//         count5 = 3. "Number of occurrences of 5: 3" prints.
// STEP 3  count_if scans every element, calling the predicate `x > 4` on
//         each: 5>4 true, 5>4 true, 3>4 false, 8>4 true, 5>4 true, 6>4
//         true, 2>4 false, 7>4 true, 4>4 false, 1>4 false — six true
//         results (5, 5, 8, 5, 6, 7) -> countGreaterThan4 = 6. "Number of
//         elements greater than 4: 6" prints.
// STEP 4  main() returns 0.
