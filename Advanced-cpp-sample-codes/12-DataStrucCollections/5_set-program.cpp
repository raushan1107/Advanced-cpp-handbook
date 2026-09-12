// std::set — a sorted collection with NO duplicates; insertion order is
// irrelevant, iteration always visits elements in sorted order.
//
// Compile: g++ -std=c++17 5_set-program.cpp -o set_program
// Run:     set_program.exe   (Windows)   or   ./set_program   (Linux/macOS)
#include <iostream>
#include <set>
using namespace std;

int main()
{
    // set<int> numSet = {10, 20, 30, 40, 50, 50, 30, 20, 10, 20}
    // Every duplicate in this initializer list is silently collapsed down
    // to ONE copy — a set can never hold the same value twice.
    set<int> numSet = {10, 20, 30, 40, 50, 50, 30, 20, 10, 20}; // Duplicates will be ignored

    // Inserting elements
    numSet.insert(60);
    numSet.insert(70);
    numSet.insert(20); // Duplicate, will be ignored
    cout << "Elements in the set after insertions: ";
    for (const auto& num : numSet) {
        cout << num << " ";
    }
    cout << endl;

    // numSet.count(30)
    // For a set (no duplicates possible), count() can only ever return 0
    // or 1 — it's really just a yes/no existence check spelled as a
    // count.
    cout<< "Has 30? " << (numSet.count(30) ? "Yes" : "No") << endl;
    // numSet.find(80) != numSet.end()
    //   find(80) - returns an iterator to 80 if present, or end() if not.
    // The MORE common way to check existence — comparing against end() —
    // shown here as an alternative to count() above.
    cout<< "Has 80? " << (numSet.find(80) != numSet.end() ? "Yes" : "No") << endl;

    // numSet.lower_bound(30)
    // Returns an iterator to the FIRST element NOT LESS than 30 — since
    // 30 is itself in the set, this returns an iterator pointing directly
    // AT 30.
    auto it = numSet.lower_bound(30);;
    if (it != numSet.end()) {
        cout << "Lower bound of 30: " << *it << endl;
    } else {
        cout << "Lower bound of 30 not found." << endl;
    }

    // numSet.erase(40)
    //   40 - a VALUE (not an iterator); erase removes the element equal
    //        to it, if present.
    numSet.erase(40); // Remove element 40
    cout << "Elements in the set after erasing 40: ";
    for (const auto& num : numSet) {
        cout << num << " ";
    }
    cout << endl;

    // Custom comparator for descending order
    // Explanation:
    // Here, we create a set with a custom comparator 'greater<int>'
    // which sorts the elements in descending order.
    // This demonstrates how to use custom sorting criteria with sets in C++.
    // How it works?
    // By specifying 'greater<int>' as the second template parameter for the set,
    // we enable custom sorting behavior.
    // Can we use smaller than operator or ascending order?
    // Yes, by default, sets use 'less<int>' which sorts elements in ascending order.
    // Use cases of custom comparators:
    // 1. Custom Sorting: To sort elements in a specific order (e.g., descending).
    // 2. Complex Data Types: When storing user-defined types, custom comparators
    //    can define how to compare those types.
    // 3. Priority Queues: Implementing priority-based data structures.

    // set<int, greater<int>> descSet
    //   greater<int> - the comparator; the set's DEFAULT (unstated,
    //                  elsewhere in this file) is less<int>, giving
    //                  ascending order — greater<int> flips iteration to
    //                  descending order instead.
    set<int, greater<int>> descSet;
    descSet.insert(10);
    descSet.insert(20);
    descSet.insert(30);
    cout << "Elements in descending order set: ";
    for (const auto& num : descSet) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  The initializer list has values 10,20,30,40,50,50,30,20,10,20 —
//         after collapsing duplicates and sorting, numSet is {10, 20, 30,
//         40, 50}.
// STEP 2  insert(60), insert(70) add two new values; insert(20) is
//         silently ignored (already present). numSet is now {10, 20, 30,
//         40, 50, 60, 70} — printed in that SORTED order regardless of
//         insertion order.
// STEP 3  count(30) returns 1 (present) -> "Has 30? Yes". find(80) returns
//         end() (not present) -> "Has 80? No".
// STEP 4  lower_bound(30) points directly at 30 (since 30 IS in the set)
//         -> "Lower bound of 30: 30".
// STEP 5  erase(40) removes it: numSet becomes {10, 20, 30, 50, 60, 70}.
// STEP 6  descSet: insert 10, 20, 30 in that order, but with greater<int>
//         as the comparator, iteration visits them in DESCENDING order:
//         "30 20 10 ".
// STEP 7  main() returns 0.
