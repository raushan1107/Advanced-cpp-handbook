// std::accumulate — folds a range down to a single value, using + by
// default, or a custom binary operation (here, multiplication).
//
// Compile: g++ -std=c++17 4_accumulate.cpp -o accumulate_demo
// Run:     accumulate_demo.exe   (Windows)   or   ./accumulate_demo   (Linux/macOS)
#include <iostream>
#include <algorithm>
#include<vector>
#include<numeric> // For accumulate
using namespace std;

int main()
{
    vector<int> arr = {10, 20, 30, 40, 50};

    // Using std::accumulate to calculate the sum of elements
    // accumulate(arr.begin(), arr.end(), 0)
    //   arr.begin(), arr.end() - the range to fold.
    //   0                      - the STARTING value the fold begins from
    //                            (the identity for addition — starting
    //                            from 0 means the first element just adds
    //                            to itself unchanged).
    int sum = accumulate(arr.begin(), arr.end(),0);
    cout << "Sum of elements: " << sum << endl;

    // Using std::accumulate to calculate the product of elements
    // accumulate(arr.begin(), arr.end(), 1, lambda)
    //   1      - the starting value (the identity for MULTIPLICATION —
    //            starting from 1 means the first element multiplies by
    //            itself unchanged, unlike 0 which would zero everything
    //            out).
    //   lambda - the binary operation applied at each step, REPLACING the
    //            default `+`.
    int product = accumulate(arr.begin(), arr.end(), 1, [](int a, int b) {
        cout << "a: " << a << ", b: " << b << endl; // Debugging output to show the values of a and b during each iteration
        return a * b;
    });

    // accumulate (para1, para2, initial_value, binary_operation)
    // In this case, we are using a lambda function to define the binary operation (multiplication)
    // for the accumulate function.
    // The lambda function takes two parameters (a and b) and returns their product.
    // what are a and b here?
    //   a - the RUNNING RESULT accumulated so far (starts as the initial
    //       value, 1, then becomes whatever the lambda returned last).
    //   b - the NEXT element of the vector being folded in.
    // The accumulate function iterates through the elements of the vector, applying the
    // binary operation (in this case, multiplication) to each element and accumulating the result.
    // The initial value for the accumulation is set to 1, which is the identity value for
    //  multiplication. This means that the first element of the vector will be multiplied by 1,
    // and then each subsequent element will be multiplied by the accumulated product so far.

    cout << "Product of elements: " << product << endl;

    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  arr = {10, 20, 30, 40, 50}. accumulate(...,0) with the default
//         `+` folds it as 0+10=10, +20=30, +30=60, +40=100, +50=150.
//         sum = 150. "Sum of elements: 150" prints.
// STEP 2  accumulate(...,1,lambda) starts with a=1 (the initial value):
//           call 1: a=1,  b=10 (first element)  -> returns 1*10  = 10
//           call 2: a=10, b=20 (second element)  -> returns 10*20 = 200
//           call 3: a=200,  b=30 (third element)  -> returns 200*30 = 6000
//           call 4: a=6000, b=40 (fourth element) -> returns 6000*40 = 240000
//           call 5: a=240000, b=50 (fifth element) -> returns 240000*50 = 12000000
//         Each call's a/b pair prints via the lambda's own debugging
//         cout line BEFORE the multiplication result is used as the next
//         call's `a`. product = 12000000.
// STEP 3  "Product of elements: 12000000" prints. main() returns 0.
//
// --------------------------------------------------------------------------
// Actual output
// --------------------------------------------------------------------------
// Sum of elements: 150
// a: 1, b: 10
// a: 10, b: 20
// a: 200, b: 30
// a: 6000, b: 40
// a: 240000, b: 50
// Product of elements: 12000000
