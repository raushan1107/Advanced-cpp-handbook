// Lambda expressions — anonymous, inline functions, including capture
// modes (by value, by reference, mixed) and using lambdas as arguments to
// STL algorithms like sort() and find_if().
//
// Compile: g++ -std=c++17 7_lambda_examples.cpp -o lambda_examples
// Run:     lambda_examples.exe   (Windows)   or   ./lambda_examples   (Linux/macOS)
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <string>
#include <chrono>
using namespace std;
int add_function(int x, int y) {
        return x + y;
    };
int main() {

    // []() {return 5 + 10;}()
    //   []          - an EMPTY capture list: this lambda uses no
    //                 variables from its surrounding scope.
    //   ()          - no parameters.
    //   {return...} - the body.
    //   the trailing () - calls the lambda IMMEDIATELY, right where it's
    //                 defined, instead of storing it in a variable first.
    cout<< []() {return 5 + 10;}();
    cout << "==================== Example 1: Basic Lambda ====================" << endl;
    // auto sayHello = []() {...}
    // Here the lambda is instead STORED in a variable (`sayHello`) via
    // `auto`, to be called later by name.
    auto sayHello = []() {
        cout << "Hello, Lambda World!" << endl;
    };
    sayHello();

    // as we are calling sayHello() by name,
    // why it is called a lambda function?
    // Because it is defined as a lambda function, and we are just storing it in a
    // variable for later use.

    cout << "\n==================== Example 2: Parameters & Return ====================" << endl;
    // auto add = [](int a, int b) -> int {...}
    //   int a, int b - two parameters, same as any ordinary function.
    //   -> int       - an EXPLICIT trailing return type; often omittable
    //                  (the compiler can usually deduce it from the
    //                  `return` statement), but sometimes needed when the
    //                  body has multiple returns of different-looking
    //                  expression types.
    auto add = [](int a, int b) -> int {
        return a + b;
    };
    cout << "Sum = " << add(10, 20) << endl;

    // can define normal function as well, but lambda is more concise and can be defined inline.
    int result = add_function(10, 20);
    cout << "Sum using normal function = " << result << endl;

    cout << "\n==================== Example 3: Capture by Value ====================" << endl;
    // Capture by value means that the lambda function makes a copy of the
    // variables it captures.
    // In this case, x and y are captured by value, so the lambda function has its own
    // copies of x and y.
    // If x or y are modified outside the lambda, it won't affect the copies inside the lambda.
    // This is useful when you want to ensure that the lambda function has its own independent state.
    int x = 5, y = 10;
    // [x, y]() {...}
    //   [x, y] - captures x and y BY VALUE: the lambda gets its OWN
    //            frozen copies, taken at the moment the lambda is
    //            created, unaffected by any later changes to the real x/y.
    auto show = [x, y]() {

        cout << "x = " << x << ", y = " << y << endl;
    };
    show();



    cout << "\n==================== Example 4: Capture by Reference ====================" << endl;
    // Capture by reference means that the lambda function captures the variables by reference,
    // so any changes made to the variables inside the lambda will affect the original variables.
    // This is useful when you want the lambda function to modify the original variables.
    // In this case, counter is captured by reference, so the lambda function can modify the original counter variable.
    // This is useful when you want to maintain state across multiple calls to the lambda function.
    // Note: Be careful with capture by reference, as it can lead to dangling references if the original variables go out of scope.
    int counter = 0;
    // [&counter]() {...}
    //   [&counter] - captures counter BY REFERENCE: the lambda operates
    //                on the SAME variable, not a copy — `counter++`
    //                inside the lambda genuinely changes the outer
    //                `counter`.
    auto increment = [&counter]() {
        counter++;
        cout << "Counter: " << counter << endl;
    };
    increment();
    increment();
    increment();
    cout << "Final counter = " << counter << endl;

    cout << "\n==================== Example 5: Capture All ====================" << endl;
    int a = 2, b = 3;
    // [=]() {...}
    //   [=] - captures EVERY variable the lambda body references, all by
    //         value — a shorthand for naming each one individually.
    auto addAll = [=]() { cout << "Sum (by value) = " << a + b << endl; }; // it will take a and b by value, so it will not modify the original a and b
    // auto addAll = [&]() { cout << "Sum (by reference) = " << a + b << endl; }; // it will take a and b by reference, so it will modify the original a and b
    // auto addAll = [a, &b]() { cout << "Sum (mixed capture) = " << a + b << endl; }; // it will take a by value and b by reference
    // auto addAll = [&a, b]() { cout << "Sum (mixed capture) = " << a + b << endl; }; // it will take a by value and b by reference
    // [=] means capture all by value, [&] means capture all by reference, [ a,&b] means capture a by value and b by reference, [&, a] means capture all by reference except a which is captured by value
    addAll();

    // [&]() {...}
    //   [&] - captures EVERY referenced variable by reference (the
    //         opposite shorthand from [=] above) — `a++`/`b++` here
    //         genuinely modify main()'s own a and b.
    auto modifyAll = [&]() {
        a++;
        b++;
        cout << "Modified (by reference): a=" << a << ", b=" << b << endl;
    };
    modifyAll();
//
    cout << "\n==================== Example 6: Using Lambda with STL sort ====================" << endl;
    vector<int> nums = {5, 2, 9, 1, 7};
    cout << "Before sort: ";
    for (int n : nums) cout << n << " ";
    cout << endl;

    // sort(nums.begin(), nums.end(), lambda)
    //   [](int a, int b){ return a > b; } - the COMPARATOR: sort calls
    //           this with pairs of elements to decide ordering; returning
    //           true for "a should come before b" when a > b produces
    //           DESCENDING order (the reverse of sort's default `<`).
    sort(nums.begin(), nums.end(), [](int a, int b) {
        return a > b; // descending order
    });

    cout << "After sort: ";
    for (int n : nums) cout << n << " ";
    cout << endl;

    cout << "\n==================== Example 7: Using Lambda with find_if ====================" << endl;
    vector<int> values = {10, 25, 30, 45, 50};
    // find_if(values.begin(), values.end(), lambda)
    //   [](int n){ return n > 30; } - the PREDICATE: find_if returns an
    //           iterator to the FIRST element for which this returns
    //           true, or end() if none do.
    auto it = find_if(values.begin(), values.end(), [](int n) { return n > 30; });
    if (it != values.end())
        cout << "Found value > 30: " << *it << endl;

    // cout << "\n==================== Example 8: Lambda in Thread ====================" << endl;
    // thread t([] {
    //     cout << "Running in a thread using lambda!" << endl;
    // });
    // t.join();

    // cout << "\n==================== Example 9: Generic Lambda (C++14+) ====================" << endl;
    // auto genericAdd = [](auto x, auto y) {
    //     return x + y;
    // };

    // cout << "add(int,int) = " << genericAdd(2, 3) << endl;
    // cout << "add(double,double) = " << genericAdd(2.5, 3.7) << endl;
    // cout << "add(string,string) = " << genericAdd(string("Hi "), string("there!")) << endl;

    // cout << "\n==================== Example 10: Capture Behavior with Loop ====================" << endl;
    // vector<int> data = {1, 2, 3, 4, 5};
    // int total = 0;
    // for_each(data.begin(), data.end(), [&](int n) { total += n; });
    // cout << "Total using lambda = " << total << endl;

    // cout << "\n==================== Example 11: Lambda with Delay (Thread + chrono) ====================" << endl;
    // thread delayed([] {
    //     for (int i = 0; i < 5; ++i) {
    //         cout << "Processing " << i + 1 << "/5..." << endl;
    //         this_thread::sleep_for(chrono::milliseconds(500));
    //     }
    //     cout << "Done processing." << endl;
    // });
    // delayed.join();

    // cout << "\n==================== Example 12: Custom Sort by String Length ====================" << endl;
    // vector<string> names = {"Radar", "Sensor", "AI", "Telemetry", "BEL"};
    // sort(names.begin(), names.end(), [](const string& s1, const string& s2) {
    //     return s1.size() > s2.size(); // descending order by length
    // });

    // for (auto& n : names)
    //     cout << n << " ";
    // cout << endl;

    cout << "\n==================== End of Demonstration ====================" << endl;
    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace (Examples 1-7 — the ACTIVE code; Examples
// 8-12 are commented out and never run)
// --------------------------------------------------------------------------
// STEP 1  The immediately-invoked lambda prints "15" with no newline
//         (5+10), right before Example 1's header line.
// STEP 2  sayHello() prints "Hello, Lambda World!".
// STEP 3  add(10, 20) returns 30 -> "Sum = 30"; add_function(10, 20) also
//         returns 30 -> "Sum using normal function = 30" — same result,
//         two different ways to write a function.
// STEP 4  x=5, y=10 captured BY VALUE into `show` — show() prints "x = 5,
//         y = 10".
// STEP 5  counter=0 captured BY REFERENCE into `increment`. Three calls
//         each increment the SAME counter: "Counter: 1", "Counter: 2",
//         "Counter: 3"; "Final counter = 3" confirms the outer variable
//         was genuinely modified.
// STEP 6  a=2, b=3. addAll() (capture-by-value [=]) prints "Sum (by
//         value) = 5". modifyAll() (capture-by-reference [&]) increments
//         the REAL a and b: prints "Modified (by reference): a=3, b=4".
// STEP 7  nums = {5,2,9,1,7}. Before sort prints "5 2 9 1 7 ". Sorting
//         with `a > b` as the comparator produces DESCENDING order: {9,
//         7, 5, 2, 1}. After sort prints "9 7 5 2 1 ".
// STEP 8  values = {10,25,30,45,50}. find_if with predicate `n > 30`
//         matches the FIRST such element, 45 (30 itself fails the
//         predicate since 30 is not > 30) -> "Found value > 30: 45".
// STEP 9  "End of Demonstration" prints; main() returns 0.
