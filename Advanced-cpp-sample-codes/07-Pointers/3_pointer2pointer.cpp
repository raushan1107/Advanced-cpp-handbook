// Pointers to pointers — multiple levels of indirection (int*, int**,
// int***), each one more "hop" away from the actual value.
//
// Compile: g++ -std=c++17 3_pointer2pointer.cpp -o pointer2pointer
// Run:     pointer2pointer.exe   (Windows)   or   ./pointer2pointer   (Linux/macOS)

#include <iostream>
using namespace std;

int a = 5;
// int* p = &a
//   &a - p holds the ADDRESS of `a` (one level of indirection: *p reads a).
int* p = &a;
// int** q = &p
//   &p - q holds the ADDRESS of `p` itself (two levels: **q reads a,
//        since *q gives you p, and *p gives you a).
int** q = &p;
// int*** x = &q
//   &q - x holds the address of `q` (three levels: ***x reads a).
int *** x = &q;

int main() {
    cout << "Value of a: " << a << endl;
    // *p
    // One dereference: follows p's address straight to `a`.
    cout << "Value via *p: " << *p << endl;
    // **q
    // Two dereferences: the first *q gives you `p` (a pointer), the
    // second * on THAT result follows p to `a`.
    cout << "Value via **q: " << **q << endl;
    // ***x
    // Three dereferences: *x gives you `q`, **x gives you `p`, ***x
    // finally gives you `a`.
    cout << "Value via ***x: " << ***x << endl;
return 0;
}


// how many levels of indirection are there in the above code?
// In the provided code, there are three levels of indirection:1. The variable `a` is a simple integer variable.
// 2. The pointer `p` points to the integer variable `a`, which is the first level of indirection.
// 3. The pointer `q` points to the pointer `p`, which is the second level of indirection.
// 4. The pointer `x` points to the pointer `q`, which is the third level of indirection.

// how many levels of indrection is allowed in c++?
// In C++, there is no strict limit on the number of levels of indirection (i.e., pointers to pointers) that you can use.
// You can create pointers to pointers to pointers, and so on, as long as it makes sense in your
// program and you manage memory correctly. However, excessive levels of indirection can make code
// harder to read and maintain, so it's generally advisable to keep the levels of indirection to a
// reasonable number.

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  a = 5. p = &a (p's value is a's address). q = &p (q's value is
//         p's address). x = &q (x's value is q's address). Nothing has
//         been dereferenced yet — these four lines just wire up the
//         chain: x -> q -> p -> a.
// STEP 2  "Value of a: 5" prints directly.
// STEP 3  *p follows ONE hop (p -> a) and reads 5. "Value via *p: 5"
//         prints.
// STEP 4  **q follows TWO hops: first hop reads q's target, which is p
//         (a pointer value, i.e. a's address); the second * then follows
//         THAT to a, reading 5. "Value via **q: 5" prints.
// STEP 5  ***x follows THREE hops: x -> q (first *), q's target -> p
//         (second *), p's target -> a (third *), reading 5. "Value via
//         ***x: 5" prints.
// STEP 6  main() returns 0. All four expressions (a, *p, **q, ***x) print
//         the SAME value (5) because every hop in the chain ultimately
//         leads back to the one variable `a` — only the NUMBER OF
//         DEREFERENCES needed to reach it differs.
