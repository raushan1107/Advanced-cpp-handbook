// decltype — deducing a function's return type FROM an expression
// involving its own parameters, so it works correctly no matter what types
// are passed in.
//
// Compile: g++ -std=c++17 6_dectTypeTool.cpp -o dectTypeTool
// Run:     dectTypeTool.exe   (Windows)   or   ./dectTypeTool   (Linux/macOS)

#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;


// template<typename T3, typename T4> auto add(a, b) -> decltype(a + b)
//   T3, T4 - two INDEPENDENT template type parameters — a and b don't have
//            to be the same type (the call below passes an int and a
//            double).
//   a, b   - the two values to add.
//   decltype(a + b) - AFTER the parameter list, this asks the compiler
//            "what type would `a + b` produce?" and uses THAT as the
//            function's actual return type. For int + double, that's
//            double (C++'s usual arithmetic promotion rules), so this
//            function returns double when called as add(10, 12.5) —
//            without decltype, you'd have to write out that resolved type
//            by hand, or pick the wrong one.
template<typename T3, typename T4>
auto add(T3 a, T4 b) -> decltype(a + b) {
    return a + b;
}

int main() {
    auto start1 = high_resolution_clock::now();
    // add(10, 12.5)
    //   10   - deduces T3 = int.
    //   12.5 - deduces T4 = double.
    // decltype(a + b) resolves to double here, so val1 is a double, even
    // though this exact template could just as easily return int, float,
    // or something else entirely for a different pair of argument types.
    auto val1 = add(10, 12.5);
    auto end1 = high_resolution_clock::now();
    cout << "Result of add(10, 12.5): " << val1 << endl;
    cout << "Time taken: "
         << duration_cast<nanoseconds>(end1 - start1).count()
         << " ns" << endl;

    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  start1 captures the current time before the call.
// STEP 2  add(10, 12.5) is called: T3 deduces to int, T4 deduces to
//         double. Inside the function, a (int 10) + b (double 12.5)
//         triggers C++'s usual arithmetic conversion — the int is promoted
//         to double first — giving 10.0 + 12.5 = 22.5, a double. Because
//         decltype(a + b) already told the compiler the return type is
//         double, val1 is declared as a double holding 22.5.
// STEP 3  end1 captures the time right after the call returns.
// STEP 4  "Result of add(10, 12.5): 22.5" prints.
// STEP 5  The elapsed nanoseconds between start1 and end1 print — this
//         single call is so fast the number is mostly measuring the
//         clock's own overhead, not the addition itself; see
//         29-WrapUp-MiniProjects/3_performance_debugging.cpp for timing
//         work that's actually large enough to measure meaningfully.

// What is the meaning of decltype in C++?
// decltype is a keyword in C++ that is used to query the type of an expression at compile time.
// It allows you to declare variables or return types based on the type of an existing expression without explicitly specifying the type.
// How it works?
// When you use decltype with an expression, the compiler evaluates the expression and deduces its type.
// This is particularly useful in templates and generic programming where the types may not be known in advance
// or when you want to ensure that a variable has the same type as another variable or expression.
// Example:
// int x = 10;
// decltype(x) y = 20; // y will be of type int
// In this example, decltype(x) deduces the type of x (which is int
// and declares y to be of the same type.
// Another example with functions:
// template<typename T1, typename T2>
// auto add(T1 a, T2 b) -> decltype(a + b) {
//     return a + b;
// }
// In this function template, decltype(a + b) deduces the return type based on
// the types of a and b, allowing the function to work with different types seamlessly.
// Use cases of decltype:
// 1. Generic Programming: In templates to deduce types based on expressions.
// 2. Type Safety: To ensure variables have the same type as other expressions.
// 3. Complex Types: When dealing with complex types or expressions where the type is not
// straightforward to determine.
// Is this same as auto keyword?
// decltype and auto are related but serve different purposes.
// auto is used for type inference when declaring variables, allowing the compiler to deduce the type
// based on the initializer expression.
// decltype, on the other hand, is used to query the type of an expression without creating a variable.
// They can be used together effectively, especially in template programming.
// Example combining both:
// template<typename T1, typename T2>
// auto add(T1 a, T2 b) -> decltype(a + b) {
//     return a + b;
// }
// In this example, auto is used to declare the function return type, allowing the function to work with different types seamlessly.
// Conclusion:
// decltype is a powerful feature in C++ that enhances type safety and flexibility in generic programming
// by allowing you to deduce types based on expressions at compile time.
