// A variant of 2_memoryprog2.cpp with the placement-new block ACTIVE
// (it's commented out in that file) — constructing an S object directly
// inside a pre-allocated stack buffer instead of letting `new` allocate
// heap memory. See 2_memoryprog2.cpp for the fully commented unique_ptr/
// shared_ptr/weak_ptr walkthrough this file shares.
//
// Compile: g++ -std=c++17 4_memoryprog2_extended.cpp -o memoryprog2_extended
// Run:     memoryprog2_extended.exe   (Windows)   or   ./memoryprog2_extended   (Linux/macOS)

#include <iostream>
#include <new> // placement new
#include <cstring>
#include <memory> // for smart pointers

struct S {
    int x;
    S(int v) : x(v) { std::cout << "S constructed\n"; }
    ~S() { std::cout << "S destructed\n"; }
};


struct Node
{
    int v;
    Node(int val) : v(val) { std::cout << "Node constructed\n"; }
    ~Node() { std::cout << "Node destructed\n"; }
};

// int x=0 vs thread_local int x=0
// thread_local storage duration means that each thread has its own instance of the variable.   
// and it is initialized when the thread is created and destroyed when the thread exits.
// In contrast, a regular global variable has a single instance shared across all threads in the program.
// Example:
// thread_local int threadVar = 0; // each thread has its own copy
// int globalVar = 0; // shared across all threads
// In a multi-threaded program, modifying threadVar in one thread does not affect its value in another thread,
// whereas modifying globalVar affects all threads.
 
int main() {

    // unique pointer example
    {
        std::unique_ptr<Node> ptr1 = std::make_unique<Node>(10);
        std::cout << "Node value: " << ptr1->v << '\n';
    } // ptr1 goes out of scope here, and Node is automatically deleted

    // shared pointer example
    {
        std::shared_ptr<Node> ptr2 = std::make_shared<Node>(20);
        {
            std::shared_ptr<Node> ptr3 = ptr2; // shared ownership
            std::cout << "Node value from ptr3: " << ptr3->v << '\n';
            std::cout << "Reference count: " << ptr2.use_count() << '\n';
        } // ptr3 goes out of scope here
        std::cout << "Reference count after ptr3 goes out of scope: " << ptr2.use_count() << '\n';
    } // ptr2 goes out of scope here, and Node is automatically deleted

    // weak pointer example
    {
        std::shared_ptr<Node> ptr4 = std::make_shared<Node>(30);
        std::weak_ptr<Node> weakPtr = ptr4; // weak reference
        std::cout << "Reference count: " << ptr4.use_count() << '\n';
        if (auto sharedPtr = weakPtr.lock()) { // try to get shared_ptr
            std::cout << "Node value from weakPtr: " << sharedPtr->v << '\n';
        } else {
            std::cout << "Node has been deleted\n";
        }
    } // ptr4 goes out of scope here, and Node is automatically deleted

    // Placement new example: It allows constructing an object in a pre-allocated memory buffer rather than allocating new memory on the heap.
    // char buffer[sizeof(S)]
    //   sizeof(S) - exactly enough bytes for one S object; this array is
    //               ordinary STACK memory, not heap.
    char buffer[sizeof(S)];
    // new (buffer) S(42)
    //   buffer - the pre-allocated memory PLACEMENT NEW constructs into,
    //            instead of asking the heap for new space.
    //   S(42)  - the constructor call, run AT that address.
    S* s = new (buffer) S(42); // placement-new constructs in buffer (stack memory)
    // Means instead of allocating new memory on heap, it uses the provided buffer to construct the object.
    // Note: We must ensure that the buffer is large enough and properly aligned for the object type.
    // Real world use cases of placement new?
    // Placement new is often used in performance-critical applications where memory allocation overhead needs to be minimized
    // It is also used in custom memory management systems, such as memory pools or arenas,
    // where objects are constructed in pre-allocated memory blocks.
    std::cout << "s->x = " << s->x << '\n';
    // s->~S()
    // No parameters — placement new has NO matching "placement delete";
    // since the memory itself is just a stack array (already reclaimed
    // automatically when it goes out of scope), only the OBJECT'S
    // destructor needs to be called manually — this is the one case in
    // this course where you call a destructor directly by name instead of
    // relying on `delete` or scope-exit.
    s->~S(); // must manually call destructor
    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace (continuing after the unique_ptr/
// shared_ptr/weak_ptr blocks, which behave identically to
// 2_memoryprog2.cpp's trace)
// --------------------------------------------------------------------------
// STEP 1  buffer is a 4-ish-byte (sizeof(S)) stack array. new (buffer)
//         S(42) runs S's constructor AT that address -> "S constructed"
//         prints; s->x is set to 42. No heap allocation happened at all.
// STEP 2  "s->x = 42" prints.
// STEP 3  s->~S() manually invokes S's destructor -> "S destructed"
//         prints — done explicitly here because placement new has no
//         corresponding `delete` to call automatically.
// STEP 4  main() returns 0. buffer itself (the raw stack memory) is
//         reclaimed automatically when main() returns, same as any other
//         local array — but that's just freeing BYTES; STEP 3 already
//         handled cleaning up the OBJECT that lived in those bytes.

 