// What is move semantics in C++?
// Move semantics is a feature in C++11 and later that allows the resources of temporary objects 
// to be 'moved' rather than copied.
// This is particularly useful for optimizing performance when dealing with large objects or 
// resources like dynamic memory,
// file handles, or network connections. Move semantics is implemented using rvalue references and 
// the std::move function.
// By using move semantics, we can avoid unnecessary deep copies of objects, leading to more efficient code.
// Move semantics is often used in conjunction with resource management classes, such as smart pointers,
// to ensure that resources are transferred correctly without duplication.

// Move semantics — transferring a temporary's internal buffer instead of
// deep-copying it, via std::move and rvalue references (T&&).
//
// Compile: g++ -std=c++17 1_movesemantics1.cpp -o movesemantics1
// Run:     movesemantics1.exe   (Windows)   or   ./movesemantics1   (Linux/macOS)

#include <iostream>
#include<vector>

using namespace std;

// createLargeVector()
// No parameters — builds a 10-million-element vector LOCALLY and returns
// it BY VALUE. Despite the "by value" return, this does NOT deep-copy 10
// million ints back to the caller: `temp` is a local variable about to be
// destroyed anyway, so the compiler moves (or elides entirely) its
// internal buffer into the caller's variable instead.
vector<int> createLargeVector() {
    vector<int> temp(10000000,11); // Large vector with 10 million elements initialized to 11
    cout << "Creating large vector from pre-defined function..." << endl;
    return temp; // Return by value, will invoke move semantics
}

// when we use & and && in function parameters?
// In C++, & is used to denote lvalue references, which refer to named objects that have a persistent state.
// && is used to denote rvalue references, which refer to temporary objects that are about to be destroyed.
// Lvalue references allow functions to modify the original object passed to them, while rvalue references 
// enable move semantics,
// allowing resources to be transferred from temporary objects without making copies.

// Overloaded function to handle lvalue references
// processVector(vec) — lvalue overload
//   vec - binds only to a NAMED vector (an lvalue) — the compiler picks
//         THIS overload when the argument has a persistent address.
void processVector(vector<int>& vec) {
    cout << "Processing lvalue vector of size: " << vec.size() << endl;
    // Further processing can be done here
}

// Overloaded function to handle rvalue references
// processVector(vec) — rvalue overload
//   vec - binds only to a TEMPORARY (an rvalue) — the compiler picks THIS
//         overload for a value that's about to be destroyed anyway,
//         signaling it's safe to steal from.
void processVector(vector<int>&& vec) {
    cout << "Processing rvalue vector of size: " << vec.size() << endl;
    // Further processing can be done here
}

int main() {

    vector<int> a = {1, 2, 3, 4, 5};
    // processVector(a)
    //   a - a NAMED variable -> matches the lvalue overload (T&).
    processVector(a); // Calls lvalue overload
    // processVector(vector<int>{6, 7, 8, 9, 10})
    //   vector<int>{...} - a TEMPORARY, constructed right here with no
    //                      name -> matches the rvalue overload (T&&).
    processVector(vector<int>{6, 7, 8, 9, 10}); // Calls rvalue overload

    cout << "Before move, size of a: " << a.size() << endl;
    // move(a)
    //   a - std::move does NOT move anything itself; it's a CAST that
    //       tells the compiler "treat `a` as an rvalue," giving
    //       permission for the next constructor (here, vector's move
    //       constructor, invoked by `vector<int> b = ...`) to steal a's
    //       internal buffer instead of copying it.
    vector<int> b = move(a); // Move constructor
    cout << "Size of a after move: " << a.size() << endl;
    cout << "Size of b after move: " << b.size() << endl;

    cout << "Demonstrating Move Semantics in C++" << endl;

    // Using move semantics to avoid unnecessary copies but how it works internally?
    // When we return temp from createLargeVector, instead of copying the entire vector,
    // the move constructor is invoked, transferring ownership of the resources from temp to the new vector.
    // This leaves temp in a valid but unspecified state, and the new vector now owns the resources.
    // But can we show that move constructor is invoked?
    // Yes, we can add print statements in the createLargeVector function to indicate when the vector is created and returned.
    // However, since std::vector already has move semantics implemented, we won't see explicit print statements for the move constructor.
    vector<int> largeVector = createLargeVector(); // Move constructor is invoked here
    cout << "Size of largeVector: " << largeVector.size() << endl;
    largeVector.push_back(42); // Modify the vector to show it's usable
    cout << "New Size of largeVector: " << largeVector.size() << endl;
    cout << "First element of largeVector: " << largeVector[0] << endl;

    cout << "size of Vector after move: " << createLargeVector().size() << endl;
    cout << "First element of Vector after move: " << createLargeVector()[0] << endl;


    // Print temp vector we have inside createLargeVector function, will it be accessible here?
    // No, temp is a local variable inside createLargeVector and goes out of scope when the function ends. 
    // But how to testify it is moved?
    // We can add print statements in createLargeVector to show when the vector is created and moved.
    // Let's create another vector to see the move in action: 
    // So here we are calling createLargeVector again to create another vector.
    // It will invoke the move constructor again.
    // This demonstrates that the resources are being moved rather than copied.
    // We can add print statements in createLargeVector to show when the vector is created and moved.
    // but how? 
    // We can add a print statement before returning the vector in createLargeVector function.
    

    // Overall, move semantics helps optimize performance by eliminating unnecessary copies,
    // especially for large objects, leading to more efficient resource management in C++.
    // Let's see rvalue reference in action:
    vector<int> vec1 = {1, 2, 3, 4, 5};
    vector<int> vec2 = move(vec1); // vec1 is now in a valid but unspecified state
    cout << "Size of vec1 after move: " << vec1.size() << endl; // vec1 size is now 0
    cout << "Size of vec2 after move: " << vec2.size() << endl; // vec2 size is 5

    // demostrating rvalue and lvalue:
    int x = 10; // x is an lvalue
    int&& rvalueRef = 20; // 20 is an rvalue
    // with or without && above, it is still a rvalue reference. 
    // The && indicates that rvalueRef is an rvalue reference, which can bind to temporary objects (rvalues).

    // then why do we need && in function parameters?
    // The && in function parameters allows us to create overloaded functions that can accept both lvalues and rvalues.
    // for example, we can have one function that takes an lvalue reference (T&) and another that takes an rvalue reference (T&&).

    // is this like dynamic variable?
    // No, rvalue references are not like dynamic variables. They are a type of reference that can bind to temporary objects (rvalues).
    // They allow us to implement move semantics by enabling the transfer of resources from temporary objects.
    // rvalue references are typically used in move constructors and move assignment operators to optimize resource management
    // for temporary objects.

    cout << "Lvalue x: " << x << endl;
    cout << "Rvalue reference rvalueRef: " << rvalueRef << endl;
    rvalueRef = 30; // Modify the rvalue reference
    cout << "New Rvalue reference rvalueRef: " << rvalueRef << endl;
    cout << "Elements in vec2 after move from vec1:" << endl;
    for(int n:vec2){
        cout << n << " ";
    }

    cout << "--------------" << endl;
    // Optional: simulate moved-from state check (not directly possible for returned local)
    // But we can demonstrate with an explicit move
    vector<int> original(1000000, 99);
    cout << "Original size before move = " << original.size() << endl;
 
    vector<int> movedTo = std::move(original);
    cout << "MovedTo size = " << movedTo.size() << endl;
    cout << "Original size after move = " << original.size() << endl; // Should be 0

    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  a = {1,2,3,4,5}. processVector(a) matches the LVALUE overload
//         (a has a name) -> "Processing lvalue vector of size: 5".
//         processVector(vector<int>{6,7,8,9,10}) matches the RVALUE
//         overload (a nameless temporary) -> "Processing rvalue vector of
//         size: 5".
// STEP 2  "Before move, size of a: 5" prints. b = move(a) invokes vector's
//         move constructor: b steals a's internal buffer; a is left in a
//         valid-but-unspecified state (empty, for std::vector in
//         practice, though not a language guarantee for every type).
//         "Size of a after move: 0" and "Size of b after move: 5" confirm
//         this.
// STEP 3  largeVector = createLargeVector(): the 10-million-element temp
//         inside that function is moved (or elided) into largeVector, not
//         deep-copied. "Size of largeVector: 10000000" prints, followed
//         by push_back(42) growing it to 10000001, and printing the first
//         element (11, unaffected by the later push_back).
// STEP 4  Two more createLargeVector().size() and createLargeVector()[0]
//         calls each build and immediately discard a fresh 10-million
//         temporary — each call independently moves/elides its own
//         internal buffer, prints "10000000" and "11" respectively.
// STEP 5  vec1={1,2,3,4,5}; vec2=move(vec1): same pattern as STEP 2 —
//         vec1 becomes empty (size 0), vec2 takes over (size 5).
// STEP 6  x=10 (an lvalue); rvalueRef binds to the literal 20 (an
//         rvalue) — "Lvalue x: 10", "Rvalue reference rvalueRef: 20".
//         rvalueRef=30 modifies the int rvalueRef is bound to; "New
//         Rvalue reference rvalueRef: 30" prints.
// STEP 7  "Elements in vec2 after move from vec1:" prints, followed by
//         vec2's 5 elements (1 2 3 4 5) — vec2 still holds exactly what
//         vec1 held before STEP 5's move.
// STEP 8  original(1000000, 99): a fresh, independent vector — "Original
//         size before move = 1000000". movedTo = std::move(original)
//         steals its buffer: "MovedTo size = 1000000", "Original size
//         after move = 0".
// STEP 9  main() returns 0.


