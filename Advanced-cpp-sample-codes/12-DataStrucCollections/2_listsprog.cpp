// std::list — a doubly-linked list: insert/remove anywhere in O(1) once
// you have an iterator, splice() to move elements between lists without
// copying.
//
// Compile: g++ -std=c++17 2_listsprog.cpp -o listsprog
// Run:     listsprog.exe   (Windows)   or   ./listsprog   (Linux/macOS)
#include<iostream>
#include<list>
using namespace std;

int main()
{
    //list vs vector in c++?
    // A list is a doubly-linked list, while a vector is a dynamic array.
    // Lists provide constant-time insertion and deletion of elements at any position,
    // but have slower random access compared to vectors.
    // Vectors provide fast random access but slower insertion and deletion at arbitrary positions.
    list<int> myList = {100, 20, 30, 140, 60};
    list<string> fruits = {"Apple", "Banana", "Cherry"};
    list<int> numbers(5, 100); // List of size 5, initialized with 100s
    list<string> moreFruits;

    // auto it = myList.begin(); advance(it, 1)
    //   myList.begin() - an iterator to the FIRST element (100).
    //   advance(it, 1) - moves `it` forward by 1 position; a list has NO
    //                    random access ([] doesn't exist for list), so
    //                    advance() is how you move an iterator a specific
    //                    number of steps.
    auto it = myList.begin();
    advance(it, 1); // Move iterator to the 2nd position
    // myList.insert(it, 25)
    //   it - the position to insert BEFORE (currently pointing at 20,
    //        the 2nd element).
    //   25 - the value to insert.
    myList.insert(it, 25); // Insert 25 at the 2nd position

    cout << "Elements in myList after adding 25 at 2nd Position: ";
    for (const auto& elem : myList) {
        cout << elem << " ";
    }
    cout << endl;
    // myList.remove(30)
    //   30 - a VALUE (not a position/iterator) — remove() searches the
    //        whole list and removes every element equal to 30.
    myList.remove(30); // Remove element with value 30
    cout << "myList after removing 30: ";
    for (const auto& elem : myList) {
        cout << elem << " ";
    }
    cout << endl;

    myList.sort(); // Sort the list
    cout << "Sorted myList: ";
    for (const auto& elem : myList) {
        cout << elem << " ";
    }
    cout << endl;

    fruits.reverse(); // Reverse the list
    cout << "Reversed fruits list: ";
    for (const auto& fruit : fruits) {
        cout << fruit << " ";
    }
    cout << endl;

    // moreFruits.splice(moreFruits.begin(), fruits, next(fruits.begin()), next(fruits.begin(), 3))
    //   moreFruits.begin()      - WHERE in moreFruits the moved elements
    //                             land (at the very front).
    //   fruits                  - the SOURCE list elements are moved FROM.
    //   next(fruits.begin())    - start of the range to move: the SECOND
    //                             element of fruits (skipping the first).
    //   next(fruits.begin(), 3) - end of the range (exclusive): the 4th
    //                             position — so exactly 2 elements
    //                             (positions 2 and 3) are moved.
    moreFruits.splice(moreFruits.begin(), fruits, next(fruits.begin()), next(fruits.begin(), 3)); // Move all elements from fruits to moreFruits except the first one
    cout << "moreFruits after splicing from fruits: ";
    for (const auto& fruit : moreFruits) {
        cout << fruit << " ";
    }
    cout << endl;

    cout << "fruits after splicing to moreFruits: ";
    for (const auto& fruit : fruits) {
        cout << fruit << " ";
    }

    list<int> a = {1, 2, 3, 4, 5};
    list<int> b;

    // b.splice(b.begin(), a, next(a.begin()), next(a.begin(), 3))
    // Same pattern as above: moves the 2nd and 3rd elements of `a`
    // (values 2 and 3) into `b`, at b's beginning.
    b.splice(b.begin(), a, next(a.begin()), next(a.begin(), 3)); // Move all elements from list a to list b
    cout << "\nElements in list b after splicing from list a: ";
    for (const auto& elem : b) {
        cout << elem << " ";
    }
    cout << endl;
    cout << "Elements in list a after splicing to list b: ";
    for (const auto& elem : a) {
        cout << elem << " ";
    }
    cout << endl;
    return 0;

}

// splice explanation:
// The splice operation transfers elements from one list to another.
// In this example, we transfer all elements from the fruits list to the moreFruits list except the first one.
// We use the splice method of the moreFruits list, specifying the position to insert (the beginning of moreFruits),
// the source list (fruits), and the range of elements to transfer (from the second element to the end).
// This operation is efficient because it does not involve copying or moving the elements;
// it simply adjusts the internal pointers of the lists.
// After the splice operation, the moreFruits list contains "Banana" and "Cherry",
// while the fruits list retains only "Apple".

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  myList = {100, 20, 30, 140, 60}. it points at the 2nd element
//         (20) after advance(it, 1). insert(it, 25) places 25 BEFORE that
//         position: myList becomes {100, 25, 20, 30, 140, 60}.
// STEP 2  remove(30) deletes every element equal to 30: myList becomes
//         {100, 25, 20, 140, 60}.
// STEP 3  sort() reorders in place: myList becomes {20, 25, 60, 100,
//         140}.
// STEP 4  fruits = {"Apple","Banana","Cherry"}; reverse() makes it
//         {"Cherry","Banana","Apple"}.
// STEP 5  splice moves fruits' 2nd and 3rd elements (positions
//         next(begin) and next(begin,3) mark a HALF-OPEN range: index 1
//         up to but not including index 3, i.e. "Banana" and "Apple") to
//         the front of moreFruits: moreFruits becomes {"Banana",
//         "Apple"}; fruits is left holding just {"Cherry"}.
// STEP 6  a = {1,2,3,4,5}, b = {}. The same splice pattern moves a's 2nd
//         and 3rd elements (2 and 3) to the front of b: b becomes {2, 3};
//         a becomes {1, 4, 5} (the moved elements are GONE from a, not
//         copied).
// STEP 7  main() returns 0.
