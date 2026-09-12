// std::stack — LIFO (Last In, First Out): push/pop/top only touch the
// most-recently-added element.
//
// Compile: g++ -std=c++17 3_stack.cpp -o stack_demo
// Run:     stack_demo.exe   (Windows)   or   ./stack_demo   (Linux/macOS)
#include<iostream>
#include<stack>
using namespace std;

int main()
{
    stack<int> numStack;

    // Adding elements to the stack
    // numStack.push(10)
    //   10 - placed on TOP of the stack; each subsequent push goes on top
    //        of whatever was pushed before it.
    numStack.push(10);
    numStack.push(20);
    numStack.push(30);
    cout << "Top element: " << numStack.top() << endl; // Outputs 30
    cout << "Stack size: " << numStack.size() << endl; // Outputs 3

    // Removing elements from the stack
    // numStack.pop()
    // No parameters, no return value — removes the TOP element (30);
    // to actually READ what's being removed, you must call top() BEFORE
    // pop() (this file never captures 30 anywhere, it's simply discarded).
    numStack.pop();
    cout << "Top element after pop: " << numStack.top() << endl; // Outputs 20
    cout << "Stack size after pop: " << numStack.size() << endl; // Outputs 2

    // numStack.emplace(40)
    //   40 - constructed directly in place on top of the stack; for a
    //        simple type like int, behaves identically to push(40).
    numStack.emplace(40); // Adds 40 to the top of the stack
    cout << "Top element after emplace: " << numStack.top() << endl; // Outputs 40
    cout << "Final Stack size: " << numStack.size() << endl; // Outputs 3

    // pop untill stack is empty
    while (!numStack.empty()) {
        cout << "Popping element: " << numStack.top() << endl;
        numStack.pop();
    }

    stack<int> a,b;
    a.push(1);
    a.push(2);
    a.push(3);
    b.push(40);
    b.push(50);
    b.push(60);
    // a.swap(b)
    //   b - the OTHER stack to exchange contents with; after this call,
    //       `a` holds everything `b` used to hold, and vice versa — done
    //       in constant time (no element-by-element copying).
    a.swap(b); // Swaps contents of stack a and b
    cout << "Top element of stack a after swap: " << a.top() << endl; // Outputs 6
    cout << "Top element of stack b after swap: " << b.top() << endl; // Outputs 3

    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  push(10), push(20), push(30): stack (bottom to top) is
//         [10, 20, 30]. top()==30, size()==3.
// STEP 2  pop() removes 30: stack is [10, 20]. top()==20, size()==2.
// STEP 3  emplace(40) adds 40 on top: stack is [10, 20, 40]. top()==40,
//         size()==3.
// STEP 4  The while loop pops until empty, printing each top element as
//         it's removed, in LIFO order: "Popping element: 40", "Popping
//         element: 20", "Popping element: 10" — the REVERSE of the order
//         they were pushed.
// STEP 5  a=[1,2,3] (top=3), b=[40,50,60] (top=60). a.swap(b) exchanges
//         their entire contents: a becomes [40,50,60] (top=60), b becomes
//         [1,2,3] (top=3).
// STEP 6  "Top element of stack a after swap: 60" and "Top element of
//         stack b after swap: 3" print.
// STEP 7  main() returns 0.
