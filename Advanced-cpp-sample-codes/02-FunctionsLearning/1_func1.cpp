// Functions — declaring several, and function OVERLOADING (same name,
// different parameter lists).
//
// Compile: g++ -std=c++17 1_func1.cpp -o func1
// Run:     func1.exe   (Windows)   or   ./func1   (Linux/macOS)
//
// Most of main() below is commented out on purpose — uncomment one block
// at a time and rebuild to see each function run in isolation, rather than
// all five firing in one confusing burst of output.

#include <iostream>

using namespace std;

// declaring a function
void greet() {
    cout << "Hello from greet() function!";
}

// AddAreaofCircle(radius)
//   radius - the circle's radius; squared and multiplied by an
//            approximation of pi to compute the area.
double AddAreaofCircle(int radius) {
    return 3.14 * radius * radius;
}

// Add(a, b)
//   a, b - the two ints to sum.
int Add(int a, int b) {
    return a + b;
}

// Add(a, b, c) — OVERLOAD #1: same name "Add", but THREE int parameters
// instead of two. The compiler picks this one over the two-parameter
// version purely by counting arguments at the call site.
//   a, b, c - the three ints to sum.
int Add(int a, int b, int c) {
    return a + b + c;
}

// Add(x, y) — OVERLOAD #2: same name again, but the parameter TYPE is now
// double instead of int. Calling Add(5.5, 10) matches this version because
// double parameters accept int arguments (10 converts to 10.0), while the
// int-parameter versions above would need to narrow 5.5 down to an int.
//   x, y - the two doubles to sum.
double Add(double x, double y) {
    return x + y;
}

// PrintValue(x)
//   x - any value convertible to double; prints it labeled as "Value is:".
void PrintValue(double x){
    cout << "Value is: " << x << endl;
}

int main() {

    int n = 11;
    // PrintValue(n)
    //   n - an int (11), implicitly converted to double (11.0) to match
    //       PrintValue's double parameter — no explicit cast needed since
    //       int-to-double is a "widening" conversion the compiler performs
    //       automatically.
    PrintValue(n);
    // calling the function
    // greet();

    // int radius;
    // cout << "\nEnter radius of circle: ";
    // cin >> radius;
    // double area = AddAreaofCircle(radius);
    // cout << "Area of circle with radius " << radius << " is: " << area << endl;

    // int sum1 = Add(5, 10);
    // cout << "Sum of 5 and 10 is: " << sum1 << endl;
    // int sum2 = Add(5, 10, 15);
    // cout << "Sum of 5, 10 and 15 is: " << sum2 << endl;
    // double sum3 = Add(5.5, n);
    // cout << "Sum of 5.5 and 10.3 is: " << float(sum3) << endl;

    return 0;
}



// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  n is declared and set to 11.
// STEP 2  PrintValue(n) is called: the compiler converts n (int 11) to a
//         double (11.0) to match PrintValue's parameter type, then prints
//         "Value is: 11".
// STEP 3  Everything else in main() is commented out, so the program does
//         nothing further and returns 0.
//
// If you uncomment the "int sum2 = Add(5, 10, 15);" line, overload
// resolution picks the THREE-int-parameter Add specifically because there
// are three arguments — sum2 becomes 5+10+15 = 30. If you instead
// uncomment "double sum3 = Add(5.5, n);", the compiler picks the
// double-parameter Add because 5.5 is a double, converting n (11) to 11.0
// first — sum3 becomes 5.5 + 11.0 = 16.5.
