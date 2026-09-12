/*
What is a map in C++?
A map in C++ is an associative container that stores elements in key-value pairs.
Each key is unique, and it is used to access the corresponding value.

How does a map work?
Internally, a map is typically implemented as a balanced binary search tree (like a Red-Black tree).
When you insert a key-value pair into the map, the map organizes the elements based on the keys,
allowing for efficient searching, insertion, and deletion operations.

When to use a map?
Use a map when you need to associate unique keys with specific values and require fast lookups, insertions, and deletions.

Compile: g++ -std=c++17 6_map-program.cpp -o map_program
Run:     map_program.exe   (Windows)   or   ./map_program   (Linux/macOS)
*/

#include <iostream>
#include <map>
using namespace std;

int main()
{
    // Creating and initializing a map
    map<int, string> studentMap;
    // studentMap[101] = "Raushan"
    //   101 - the KEY; operator[] creates a new entry if 101 doesn't
    //         exist yet (default-constructing its value first), or
    //         overwrites the existing entry's value if it does.
    studentMap[101] = "Raushan";
    studentMap[102] = "Ritu";
    studentMap[103] = "Suchitra";

    // Inserting elements using insert() method
    // studentMap.insert({104, "Rahul"})
    //   {104, "Rahul"} - a key-value pair; unlike operator[], insert()
    //                   does NOT overwrite an existing key — if 104
    //                   already existed, this call would silently do
    //                   nothing.
    studentMap.insert({104, "Rahul"});
    // studentMap.insert(make_pair(105, "Suman"))
    //   make_pair(105, "Suman") - builds the same kind of pair as the
    //                            braced {104, "Rahul"} above, just via an
    //                            explicit function call instead of brace
    //                            syntax — both forms are equivalent here.
    studentMap.insert(make_pair(105, "Suman"));

    // Accessing elements using keys
    cout << "Student with ID 102: " << studentMap[102] << endl;
    // studentMap.at(104)
    // Like vector's at() vs [] (see 1_vectorprog.cpp): at() throws
    // std::out_of_range if the key doesn't exist, instead of silently
    // creating a new blank entry the way operator[] would.
    cout << "Student with ID 104: " << studentMap.at(104) << endl;

    // Iterating through the map
    cout << "All students in the map:" << endl;
    // for (const auto& pair : studentMap)
    //   pair - each key-value entry, in ASCENDING KEY ORDER (a map keeps
    //          its keys sorted, same as std::set); pair.first is the key,
    //          pair.second is the value.
    for (const auto& pair : studentMap) {
        cout << "ID: " << pair.first << ", Name: " << pair.second << endl;
    }

    // Checking if a key exists
    int searchID = 101;
    if (studentMap.find(searchID) != studentMap.end())
    // Lets understnad this condition:
    // studentMap.find(searchID) returns an iterator to the element with key searchID if it exists,
    // or studentMap.end() if it does not exist.
    // The condition checks if the iterator returned by find is not equal to end(),
    // which means the key exists in the map.
    {

        cout << "Student with ID " << searchID << " found: " << studentMap[searchID] << endl;
    } else {
        cout << "Student with ID " << searchID << " not found." << endl;
    }

    // Removing an element by key
    // studentMap.erase(103)
    //   103 - a KEY (not an iterator); erase removes the entry with this
    //         key, if present.
    studentMap.erase(103); // Removes Suchitra
    cout << "After removing student with ID 103:" << endl;
    for (const auto& pair : studentMap) {
        cout << "ID: " << pair.first << ", Name: " << pair.second << endl;
    }

    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  studentMap[101]="Raushan", [102]="Ritu", [103]="Suchitra" — map
//         now has keys {101,102,103}.
// STEP 2  insert({104,"Rahul"}) adds key 104. insert(make_pair(105,
//         "Suman")) adds key 105. Map now has keys {101,102,103,104,105}.
// STEP 3  studentMap[102] reads "Ritu"; studentMap.at(104) reads "Rahul".
// STEP 4  The for loop visits entries in ASCENDING key order (101 through
//         105), printing "ID: 101, Name: Raushan" through "ID: 105, Name:
//         Suman" — five lines.
// STEP 5  find(101) finds it (!=end()) -> "Student with ID 101 found:
//         Raushan".
// STEP 6  erase(103) removes the "Suchitra" entry: map now has keys
//         {101,102,104,105}. The final loop prints four lines, skipping
//         103 entirely.
// STEP 7  main() returns 0.
