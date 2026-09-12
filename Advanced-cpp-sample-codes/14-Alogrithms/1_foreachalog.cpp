// std::for_each — an STL algorithm that runs a function/lambda once per
// element in a range, as an alternative to writing the loop by hand.
//
// Compile: g++ -std=c++17 1_foreachalog.cpp -o foreachalog
// Run:     foreachalog.exe   (Windows)   or   ./foreachalog   (Linux/macOS)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << "Elements in the vector using for_each and lambda function:" << endl;
    // for_each(numbers.begin(), numbers.end(), lambda)
    //   numbers.begin(), numbers.end() - the range to visit, start to
    //                                    end.
    //   [](int num){ cout << num << " "; } - the lambda called ONCE per
    //                                    element, with that element's
    //                                    value passed in as `num`.
    for_each(numbers.begin(), numbers.end(), [](int num) {
        cout << num << " ";
    });

    // Above code: this uses lambda function internally:
    // for_each is a standard algorithm that applies the lambda function to each element in the range.
    // The lambda function takes an integer parameter num and prints it.

    cout << "\n\nElements in the vector using range-based for loop:" << endl;
    for (const auto& num : numbers) {
        cout << num << " ";
    }

    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  numbers = {1,2,...,10}. for_each calls the lambda once per
//         element, in order: num=1 prints "1 ", num=2 prints "2 ", ...,
//         num=10 prints "10 " — building the line "1 2 3 4 5 6 7 8 9 10 ".
// STEP 2  The range-based for loop visits the SAME elements in the SAME
//         order, printing the identical line again — proving for_each
//         and a range-based for loop are two different ways to express
//         the same "do something with every element" idea.
// STEP 3  main() returns 0.
