// Structured bindings (C++17) — unpacking a pair/tuple's fields directly
// into named variables in one line, instead of std::get<0>(...), get<1>(...).
//
// Compile: g++ -std=c++17 7_strucBinding.cpp -o strucBinding
// Run:     strucBinding.exe   (Windows)   or   ./strucBinding   (Linux/macOS)

#include <iostream>
#include <chrono>
#include<utility>
#include <tuple>

using namespace std;
using namespace std::chrono;

// getPerson()
// No parameters — returns a pair<int, string> as a braced initializer
// {25, "Alice"}, which the compiler matches against pair's two-argument
// constructor (age first, name second, matching the declared return type).
pair<int, string> getPerson() {
    return {25, "Alice"};
}

constexpr double interestRate = 7.5;

// getCustomer()
// No parameters — returns a tuple<int, string, double>, the
// three-different-types generalization of pair, again built from a
// braced initializer matched positionally to the return type.
tuple<int, string, double> getCustomer() {
    return {101, "Sanjiva", 50000.25};
}
int main()
{
    // auto [age, name1] = getPerson()
    //   getPerson() - returns a pair<int, string>.
    //   [age, name1] - a STRUCTURED BINDING: unpacks the pair's two
    //                  members directly into two new variables, `age`
    //                  (taking the pair's .first) and `name1` (taking
    //                  .second), with types deduced automatically — no
    //                  `.first`/`.second` or `get<0>`/`get<1>` needed at
    //                  the call site.
    auto [age, name1] = getPerson();
    cout << "Name: " << name1 << ", Age: " << age << endl;
    cout << "------------------------" << endl;
    // auto [id, name2, balance] = getCustomer()
    // Same idea, extended to THREE fields since getCustomer() returns a
    // tuple with three elements instead of a pair's two.
    auto [id, name2, balance] = getCustomer();

    cout << "Customer ID: " << id << endl;
    cout << "Name: " << name2 << endl;
    cout << "Balance: " << balance << endl;

    // decltype(balance) newBalance = ...
    //   decltype(balance) - reuses whatever type the structured binding
    //                       deduced `balance` to be (double, from
    //                       getCustomer()'s tuple) as newBalance's type,
    //                       without spelling "double" out a second time.
    //   balance + (balance * interestRate / 100) - the new balance after
    //                       applying interestRate as a percentage.
    decltype(balance) newBalance = balance + (balance * interestRate / 100);
    cout << "New Balance (with interest): " << newBalance << endl;
    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  getPerson() returns pair{25, "Alice"}; the structured binding
//         `auto [age, name1]` sets age = 25, name1 = "Alice".
// STEP 2  "Name: Alice, Age: 25" prints, followed by the divider line.
// STEP 3  getCustomer() returns tuple{101, "Sanjiva", 50000.25}; the
//         structured binding `auto [id, name2, balance]` sets id = 101,
//         name2 = "Sanjiva", balance = 50000.25.
// STEP 4  Three cout lines print "Customer ID: 101", "Name: Sanjiva",
//         "Balance: 50000.25" — in that order.
// STEP 5  newBalance = 50000.25 + (50000.25 * 7.5 / 100)
//                    = 50000.25 + 3750.01875
//                    = 53750.26875
// STEP 6  "New Balance (with interest): 53750.26875" prints (the exact
//         number of digits shown depends on cout's default float
//         formatting).
// STEP 7  main() returns 0.

// Explanation:
// This code demonstrates the use of structured bindings in C++17.
// The getPerson function returns a pair containing an integer (age) and a string (name).
// In the main function, structured bindings are used to unpack the returned pair into two separate variables
// age and name. This allows for more readable and convenient access to the individual elements of the pair.
// Structured bindings can be used with various types such as pairs, tuples, and structs,
// making it easier to work with multiple return values and complex data structures.
// How it works?
// When the getPerson function is called, it returns a pair<int, string>.
// The structured binding declaration auto [age, name] unpacks the pair into two variables:
// age and name. The compiler automatically deduces the types of these variables based on the types
// in the pair.
// This feature enhances code readability and reduces the need for explicit type declarations
// when dealing with multiple return values or complex data structures.
// Use cases of structured bindings:
// 1. Returning Multiple Values: Functions can return multiple values in a more readable way.
// 2. Working with Tuples and Pairs: Simplifies access to elements in tuples
//    and pairs without needing to use std::get.
// 3. Range-based for Loops: Can be used to unpack elements in range-based
//    for loops when iterating over collections of pairs or tuples.
// 4. Decomposing Structs: Allows for easy unpacking of struct members into
//    separate variables.
// 5. Improved Readability: Enhances code clarity by providing meaningful
