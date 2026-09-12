// constexpr — functions the compiler can evaluate at COMPILE time, not
// just at runtime.
//
// Compile: g++ -std=c++17 5_Contexpression.cpp -o Contexpression
// Run:     Contexpression.exe   (Windows)   or   ./Contexpression   (Linux/macOS)
//
// A constexpr function is one the compiler is ALLOWED to evaluate while
// compiling your program, instead of waiting until the program runs, as
// long as every argument it's called with is itself known at compile time
// (a literal or another constexpr value). This can move real work from
// runtime into the build step, at the cost of zero runtime execution time
// for that specific call.

#include <iostream>
using namespace std;

// constexpr int square(x)
//   x - the number to square. Because this function is declared
//       constexpr and its body is simple enough (one return statement, no
//       side effects), the compiler CAN compute square(5) itself while
//       compiling, rather than generating code that multiplies at runtime.
constexpr int square(int x) {
    return x * x;
}

int main() {
    // constexpr int result = square(5)
    //   square(5) - called with a literal (5), so the COMPILER computes
    //               25 right now, during compilation; `result` is baked
    //               into the compiled program as the literal 25 — no
    //               multiplication instruction runs when main() executes
    //               this line.
    constexpr int result = square(5);
    cout << "The square of 5 is: " << result << endl; // This will be evaluated at compile time, and the value of result
    // will be known at compile time.
    cout<< "Calling square func temp: " << endl;
    // square(10)
    //   10 - also a literal, so this call is ALSO evaluated at compile
    //        time (the compiler is permitted, though not strictly
    //        required, to fold it into a constant here since it isn't
    //        stored in a constexpr variable this time).
    cout<< "The square of 10 is: " << square(10) << endl; // This will be evaluated at compile time as well,
    // since the argument is a constant expression.
    return 0;
}


// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  (Compile time, before the program ever runs) The compiler sees
//         `constexpr int result = square(5);` and, because both `square`
//         and the argument 5 are compile-time-evaluable, computes
//         result = 25 during compilation — the generated program simply
//         contains the number 25, not a function call.
// STEP 2  (Runtime) The program prints "The square of 5 is: 25".
// STEP 3  "Calling square func temp: " prints.
// STEP 4  square(10) is called with the literal 10; whether the compiler
//         folded this to 100 at compile time or generates a real call
//         depends on optimization settings, but the OBSERVABLE result is
//         identical either way: "The square of 10 is: 100" prints.
// STEP 5  main() returns 0.
//
// The commented-out block below (never compiled as part of this file) is
// a sketch comparing constexpr's compile-time path against an ordinary
// runtime function using <chrono> timing — see
// 29-WrapUp-MiniProjects/3_performance_debugging.cpp for a working,
// actually-compiled version of that same "time two versions and compare"
// idea.

// #include <iostream>
// #include <chrono>
// using namespace std;
// using namespace std::chrono;

// constexpr int square(int x) {
//     return x * x;
// }

// int runtime_square(int x) {
//     return x * x;
// }

// int main() {
//     // Compile-time computation
//     constexpr int result = square(5);
//     cout << "Compile-time square of 5: " << result << endl;

//     // Runtime computation (constexpr used at runtime)
//     auto start1 = high_resolution_clock::now();
//     int val1 = square(1000000);
//     auto end1 = high_resolution_clock::now();
//     cout << "Runtime constexpr square(1000000): " << val1 << endl;
//     cout << "Time taken: "
//          << duration_cast<nanoseconds>(end1 - start1).count()
//          << " ns" << endl;

//     // Regular function
//     auto start2 = high_resolution_clock::now();
//     int val2 = runtime_square(1000000);
//     auto end2 = high_resolution_clock::now();
//     cout << "Normal square(1000000): " << val2 << endl;
//     cout << "Time taken: "
//          << duration_cast<nanoseconds>(end2 - start2).count()
//          << " ns" << endl;

//     return 0;
// }
