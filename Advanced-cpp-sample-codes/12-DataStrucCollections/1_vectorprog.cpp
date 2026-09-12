// std::vector — a dynamic array: capacity vs. size, reserve(), and
// shrink_to_fit().
//
// Compile: g++ -std=c++17 1_vectorprog.cpp -o vectorprog
// Run:     vectorprog.exe   (Windows)   or   ./vectorprog   (Linux/macOS)

// include<bits/stdc++.h> vs include<vector>
// #include<bits/stdc++.h> is a non-standard header file that includes all standard library headers.
// It is often used in competitive programming for convenience, but it can lead to longer compilation times
// and is not portable across different compilers.
// On the other hand, #include<vector> specifically includes only the vector header from the standard library.
// This is the preferred approach in production code as it improves compilation time and code clarity.

#include <iostream>
#include <vector>
#include<bits/stdc++.h> // Not recommended for production code
using namespace std;

int main()
{
    // Creating and initialising a vector
    vector<int> numbers = {10, 20, 30, 40, 50};
    vector<string> fruits = {"Apple", "Banana", "Cherry"};
    // vector<int> v(5, 100)
    //   5   - the number of elements to create.
    //   100 - the value EVERY one of those 5 elements is initialized to.
    vector<int> v (5, 100); // Vector of size 5, initialized with 100s

    // Accessing elements using index
    cout << "First number: " << numbers[0] << endl;
    // numbers.at(0)
    // Same result as numbers[0] here, but at() checks the index is in
    // range and THROWS std::out_of_range if it isn't, instead of
    // undefined behavior like operator[] would give on a bad index.
    cout << "First fruit: " << fruits.at(0) << endl;

    // Iterating through the vector using range-based for loop
    cout << "Numbers: ";
    for ( auto n: numbers)
    {
        cout << n << " ";
    }
    cout << numbers.capacity() << endl;
    cout << numbers.size() << endl;
    // numbers.reserve(10)
    //   10 - guarantees room for at least 10 elements without a
    //        reallocation, even though numbers.size() is still 5 —
    //        capacity and size are independent numbers (see
    //        06-Strings/7_stringCapacity.cpp for the same idea applied to
    //        std::string).
    numbers.reserve(10); // Reserves space for 10 elements
    cout << "\nCapacity after reserve(10): " << numbers.capacity() << endl;
    cout << "Size of vector: " << numbers.size() << endl;

    numbers.push_back(60); // Adds an element at the end
    numbers.push_back(70);
    numbers.push_back(80);
    cout << "Capacity after adding elements: " << numbers.capacity() << endl;
    cout << "Size of vector after adding elements: " << numbers.size() << endl;
    // numbers.shrink_to_fit()
    // No parameters — a (non-binding) request to release any reserved
    // capacity beyond the current size, mirroring string's own
    // shrink_to_fit().
    numbers.shrink_to_fit(); // Reduces capacity to fit size
    cout << "Capacity after shrink_to_fit(): " << numbers.capacity() << endl;



    // numbers.push_back(90);
    // numbers.push_back(100);
    // numbers.push_back(110);
    // numbers.shrink_to_fit(); // Reduces capacity to fit size
    // cout << "Capacity after shrink_to_fit(): " << numbers.capacity() << endl;


    // fruits.erase(fruits.begin() + 1); // Removes the second element (Banana)
    // fruits.insert(fruits.begin() + 1, "Blueberry"); // Inserts "Blueberry" at index 1
    // fruits.insert(fruits.begin() + 1, "Mango"); // Inserts "Mango" at index 1
    // fruits[0] = "Avocado"; // Modifies the first element
    // cout << "\nFruits after erasing second element: ";
    // for(auto i = fruits.begin(); i != fruits.end(); ++i)
    // {
    //     cout<< *i << " ";
    // }
    // // for( auto f: fruits)
    // // {
    // //     cout<< f << " ";
    // // }
    // numbers.push_back(120);
    // numbers.emplace_back(130); // Constructs element in place at the end
    // cout << "\nNumbers after emplace_back(130): ";
    // numbers.erase(numbers.begin() + 2); // Removes the element at index 2 (30)

    // sort(numbers.begin(), numbers.end(), greater<int>()); // Sorts in descending order
    // numbers.swap(v); // Swaps contents with vector v
    // // difference between push_back and emplace_back
    // // push_back adds a copy of the element to the end of the vector,
    // // while emplace_back constructs the element in place at the end of the vector,
    // for( auto &n: numbers)
    // {
    //     cout<< n << " ";
    // }



    // why do we need to reserve vector?
    // Because reserving space in a vector helps to minimize the number of reallocations
    // that occur when new elements are added. Each reallocation involves allocating new memory,
    // copying existing elements to the new memory, and freeing the old memory, which can be expensive.
    // By reserving enough space in advance, we can improve performance when we know the number of elements
    // that will be added to the vector.
    // Real world example: Preallocating memory for a dynamic array that will store user inputs.
    // If you expect to store 1000 integers based on user input, reserving space for 1000 elements
    // in advance can help avoid multiple reallocations as the user adds integers to the array.

}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  numbers = {10,20,30,40,50} (size 5). Its STARTING capacity is
//         implementation-defined — many standard libraries allocate
//         EXACTLY enough for the initializer list, so capacity()==5 here
//         is common (but not guaranteed by the standard).
// STEP 2  The range-based for loop prints "10 20 30 40 50 ", then
//         capacity() and size() print (5 and 5, in the common case from
//         STEP 1).
// STEP 3  numbers.reserve(10): size() stays 5 (reserve never adds
//         elements), capacity() becomes AT LEAST 10.
// STEP 4  Three push_back calls bring size() to 8 — since capacity was
//         already reserved to at least 10, none of these three appends
//         needs to trigger a reallocation. capacity() is unchanged from
//         STEP 3 (still at least 10).
// STEP 5  numbers.shrink_to_fit(): capacity() is reduced TOWARD size()
//         (8), though the exact resulting number depends on the standard
//         library implementation.
// STEP 6  main() reaches its closing brace (no explicit `return 0;` in
//         this file — falling off the end of main() implicitly returns 0,
//         same as writing it out).
