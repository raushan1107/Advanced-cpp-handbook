// Smart pointer lifetimes — unique_ptr, shared_ptr with reference
// counting, weak_ptr, and placement new (constructing an object into a
// pre-allocated buffer instead of letting `new` allocate heap memory).
//
// Compile: g++ -std=c++17 2_memoryprog2.cpp -o memoryprog2
// Run:     memoryprog2.exe   (Windows)   or   ./memoryprog2   (Linux/macOS)

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

int main() {

    // {
    //     Node* p = new Node(11);
    //     std::cout << "Node::" << p->v<< '\n';
    // }
    // unique pointer example
    {
        // make_unique<Node>(10)
        //   10 - forwarded straight to Node's constructor as `val`; ptr1
        //        is the SOLE owner of this Node.
        std::unique_ptr<Node> ptr1 = std::make_unique<Node>(10);
        std::cout << "Node value: " << ptr1->v << '\n';
    } // ptr1 goes out of scope here, and Node is automatically deleted

    // shared pointer example
    {
        std::shared_ptr<Node> ptr2 = std::make_shared<Node>(20);
        {
            // shared_ptr<Node> ptr3 = ptr2
            //   ptr2 - copying a shared_ptr adds a SECOND owner of the
            //          SAME Node object (no new Node is constructed) and
            //          increments the shared reference count by one.
            std::shared_ptr<Node> ptr3 = ptr2; // shared ownership
            std::cout << "Node value from ptr3: " << ptr3->v << '\n';
            // ptr2.use_count()
            // No parameters — returns how many shared_ptr instances
            // currently share ownership of this Node (2, right now: ptr2
            // and ptr3).
            std::cout << "Reference count: " << ptr2.use_count() << '\n';
        } // ptr3 goes out of scope here
        std::cout << "Reference count after ptr3 goes out of scope: " << ptr2.use_count() << '\n';
    } // ptr2 goes out of scope here, and Node is automatically deleted

    // weak pointer example
    {
        std::shared_ptr<Node> ptr4 = std::make_shared<Node>(30);
        // weak_ptr<Node> weakPtr = ptr4
        //   ptr4 - a weak_ptr OBSERVES the same Node ptr4 owns, but does
        //          NOT count as an owner — creating it does NOT increment
        //          use_count(), and it can never keep the Node alive by
        //          itself.
        std::weak_ptr<Node> weakPtr = ptr4; // weak reference
        std::cout << "Reference count: " << ptr4.use_count() << '\n';
        // weakPtr.lock()
        // No parameters — returns a TEMPORARY shared_ptr if the observed
        // Node is still alive (bumping the count briefly while that
        // temporary exists), or an empty/null shared_ptr if it has
        // already been destroyed. Calling ->v directly on the result here
        // is safe ONLY because we know ptr4 is still in scope; a real
        // program should check the result before dereferencing (as the
        // `if (auto sharedPtr = ...)` line right below correctly does).
        std::cout << "Node value using weakPtr: " << weakPtr.lock()->v << '\n'; // lock() returns shared_ptr if Node is still alive
        if (auto sharedPtr = weakPtr.lock()) { // try to get shared_ptr
            std::cout << "Node value from weakPtr: " << sharedPtr->v << '\n';
        } else {
            std::cout << "Node has been deleted\n";
        }
    } // ptr4 goes out of scope here, and Node is automatically deleted

    // Placement new example: It allows constructing an object in a pre-allocated memory buffer rather than allocating new memory on the heap.
    // char buffer[sizeof(S)];
    // S* s = new (buffer) S(42); // placement-new constructs in buffer (stack memory)
    //   buffer - a raw, already-allocated block of memory, sized exactly
    //            for one S (sizeof(S)) — no bytes are allocated by this
    //            `new` call; it only runs S's CONSTRUCTOR, targeting the
    //            memory already sitting at `buffer`'s address.
    //   S(42)  - the constructor call, same as any other `new S(42)`,
    //            just pointed at pre-existing memory instead of the heap.

    // Means instead of allocating new memory on heap, it uses the provided buffer to construct the object.
    // Note: We must ensure that the buffer is large enough and properly aligned for the object type.
    // Real world use cases of placement new?
    // Placement new is often used in performance-critical applications where memory allocation overhead needs to be minimized
    // It is also used in custom memory management systems, such as memory pools or arenas,
    // where objects are constructed in pre-allocated memory blocks.
    // std::cout << "s->x = " << s->x << '\n';
    // s->~S(); // must manually call destructor
    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace (the ACTIVE code — the placement-new block
// at the end of main() is commented out and never runs)
// --------------------------------------------------------------------------
// STEP 1  ptr1 = make_unique<Node>(10): "Node constructed" prints, then
//         "Node value: 10". At the closing brace of this block, ptr1 goes
//         out of scope -> "Node destructed" prints automatically.
// STEP 2  ptr2 = make_shared<Node>(20): "Node constructed" prints;
//         use_count is 1 (only ptr2 owns it). Inside the nested block,
//         ptr3 = ptr2 makes a SECOND owner: use_count becomes 2 ("Node
//         value from ptr3: 20", "Reference count: 2"). When ptr3's block
//         ends, use_count drops back to 1 ("Reference count after ptr3
//         goes out of scope: 1"). When ptr2's own block ends, use_count
//         hits 0 and "Node destructed" prints.
// STEP 3  ptr4 = make_shared<Node>(30): "Node constructed" prints;
//         use_count is 1. weakPtr observes ptr4 WITHOUT incrementing that
//         count — "Reference count: 1" (not 2). weakPtr.lock() succeeds
//         (ptr4 is still alive) -> "Node value using weakPtr: 30" prints,
//         then the if-check ALSO succeeds -> "Node value from weakPtr:
//         30" prints again. When ptr4's block ends, "Node destructed"
//         prints (weakPtr never kept it alive).
// STEP 4  main() returns 0.

// int x=0 vs thread_local int x=0
// thread_local storage duration means that each thread has its own instance of the variable.   
// and it is initialized when the thread is created and destroyed when the thread exits.
// In contrast, a regular global variable has a single instance shared across all threads in the program.
// Example:
// thread_local int threadVar = 0; // each thread has its own copy
// int globalVar = 0; // shared across all threads
// In a multi-threaded program, modifying threadVar in one thread does not affect its value in another thread,
// whereas modifying globalVar affects all threads.
 
 