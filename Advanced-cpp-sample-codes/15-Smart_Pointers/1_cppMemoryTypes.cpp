// C++ memory types tour — stack, heap, static/global, and the code/text
// segment — plus common heap bugs (leak, double free) and their fix
// (smart pointers).
//
// Compile: g++ -std=c++17 1_cppMemoryTypes.cpp -o cppMemoryTypes
// Run:     cppMemoryTypes.exe   (Windows)   or   ./cppMemoryTypes   (Linux/macOS)
// Warning: this file DELIBERATELY leaks memory 10,000 times
// (leakMemoryExample, called in a loop in main) to demonstrate what a
// leak looks like — it will use a noticeable amount of memory while
// running, by design, and is not a bug to fix.

#include <iostream>
#include <memory> // For smart pointers
#include <vector>
#include <string>
using namespace std;

// global variable (static/global memory)
int globalVar = 50; // data segment (initialized global variable)
static int staticGlobalVar; // bss segment (uninitialized global variable)
// what is bss segment? BSS (Block Started by Symbol) segment is a 
// portion of memory that contains uninitialized global and static variables. 
// It is typically zero-initialized by the operating system when the program starts.

int global_var = 42;            // data segment (initialized)
static int static_var;          // BSS (uninitialized)
 
void showAddresses() {
    int local = 10;             // stack
    static int local_static = 20; // data segment (static local)
    int* heap = new int(99);    // heap
 
    string s = "literal";  // s (object on stack), internal buffer likely on heap
    const char* lit = "hello";  // string literal (read-only data)
 
    cout << "Code (func ptr)    : " << (void*)&showAddresses << '\n';
    cout << "Global var         : " << (void*)&global_var << '\n';
    cout << "Static var         : " << (void*)&static_var << '\n';
    cout << "Local static       : " << (void*)&local_static << '\n';
    cout << "Local (stack)      : " << (void*)&local << '\n';
    cout << "Heap pointer->     : " << (void*)heap << '\n';
    cout << "string object      : " << (void*)&s << '\n';
    cout << "string literal     : " << (const void*)lit << '\n';

    delete heap;
}

void heapAllocateDeallocateExample() {

    int * p = new int; // dynamically allocate an integer on the heap
    *p = 42; // assign a value to the allocated memory
    cout << "Dynamically allocated integer value: " << *p << endl;
    delete p; // deallocate the memory to prevent memory leak

    int * arr = new int[5]; // dynamically allocate an array of integers on the heap
    for (int i = 0; i < 5; ++i) {
        arr[i] = i * 10; // assign values to the array
    }
    cout << "Dynamically allocated array values: ";
    for (int i = 0; i < 5; ++i) {
        cout << arr[i] << " "; // print the array values
    }
    delete[] arr; // deallocate the array memory
}


void leakMemoryExample() {
    int * leak = new int[1000]; // allocate memory but never deallocate
    // Memory leak occurs here as we lose the reference to the allocated memory
    cout << "Leaked memory allocated." << endl;
    // Note: In a real application, you would want to avoid this situation.
    (void)leak; // to avoid unused variable warning

}

// doubefreeExample()
// No parameters. Demonstrates a DANGLING POINTER: `b` still holds a's old
// address after `a` is deleted — dereferencing `b` afterward reads freed
// memory (undefined behavior; it MAY still print the old value by
// coincidence, or may print garbage, depending on what the allocator does
// with freed memory).
void doubefreeExample() {
    int* ptr = new int(10);
    delete ptr; // First deletion
    //delete ptr; // Uncommenting this line would cause a double free error

    int * a = new int(5);
    int * b = a;
    cout << "b: " << *b << endl;
    cout << "a: " << *a << endl;
    delete a; // First deletion
    cout<< "b, after deleting a: " << *b << endl;
}

// safesingleallocExample()
// No parameters. Shows the FIX for the leaks/double-frees above: smart
// pointers that free themselves automatically.
void safesingleallocExample() {
    // make_unique<int>(10)
    //   10 - the initial value the managed int is constructed with;
    //        `p` (a unique_ptr<int>) owns it exclusively and frees it
    //        automatically when p goes out of scope — no delete needed.
    auto p = make_unique<int>(10); // Using unique_ptr for safe memory management
    cout << "Value managed by unique_ptr: " << *p << endl;

    // make_shared<int>(20)
    //   20 - the initial value; unlike unique_ptr, MULTIPLE shared_ptrs
    //        can own the same int at once, tracked by a reference count.
    auto q = make_shared<int>(20); // Using shared_ptr for shared ownership
    cout << "Value managed by shared_ptr: " << *q << endl;
    cout << "Reference count of shared_ptr: " << q.use_count() << endl;
    // shared_ptr<int> r = q
    //   q - copying a shared_ptr increments the SAME shared reference
    //       count; the underlying int is only freed once the LAST owner
    //       (whichever of q or r goes out of scope last) is destroyed.
    shared_ptr<int> r = q; // Sharing ownership
    cout << "Reference count after sharing ownership: " << q.use_count() << endl;

}

void recurseiveFunction(int count) {
    if (count == 0) return;
    volatile int arr[1000]; // Large array on stack to demonstrate stack usage 
    if(count%100 == 0) cout << "Recursion depth: " << count << endl;
    recurseiveFunction(count - 1);
}

struct Big {
    string s;
    Big(const char* t) : s(t) {}
    Big(const Big& o) : s(o.s) { cout << "Copy ctor\n"; }
    Big(Big&& o) noexcept : s(move(o.s)) { cout << "Move ctor\n"; }
};

int main() {

    // Demonstrate move semantics with Big struct
    vector<Big> v;
    v.reserve(2);
    v.emplace_back("A"); // construct in-place, no move/copy
    v.emplace_back("B");
    cout << "Pushing third element (will reallocate if capacity insufficient)\n";
    v.emplace_back("C"); // if reallocation needed, move ctor used if available
    v.emplace_back("D"); // if reallocation needed, move ctor used if available
    
    // why now move constructor is called twice?
    // Because when the vector needs to reallocate its internal storage to accommodate new elements,
    // it moves existing elements to the new storage using the move constructor (if available) to avoid expensive copies.
   cout << "Done\n";

    // Demonstrate safe memory management using smart pointers
    safesingleallocExample();
    try
    {
        // Demonstrate recursive function to show stack memory usage
        recurseiveFunction(1000); // Adjust the depth as needed
    }
    catch(const std::exception& e)
    {
        cerr << "Exception occurred: " << e.what() << endl;
    }

    // Demonstrate double free error
    doubefreeExample(); // undefined behavior

    // // Demonstrate memory leak
    for(int i = 0; i < 10000; ++i) {
        leakMemoryExample();
        // In a real application, we would monitor memory usage here to see the leak effect
        // how even it is possible to monitor memory leak in C++?
        // We can use tools like Valgrind (on Linux) or Visual Studio's built-in diagnostic tools (on Windows) to monitor memory usage and detect leaks.
        // These tools can help identify memory that was allocated but not properly deallocated.

    }

    // // Demonstrate heap allocation and deallocation
    heapAllocateDeallocateExample();

    // // Show memory addresses
    showAddresses();

    cout << "C++ Memory Types and Management" << endl;

    // Stack Memory Example
    int stackVar = 10; // Allocated on stack
    cout << "Stack Variable: " << stackVar << endl;

    // Heap Memory Example
    int* heapVar = new int(20); // Allocated on heap
    cout << "Heap Variable: " << *heapVar << endl;
    delete heapVar; // Deallocate heap memory

    // Static/Global Memory Example
    static int staticVar = 30; // Allocated in static memory
    cout << "Static Variable: " << staticVar << endl;

    // Code/Text Segment is not directly accessible in code, but we can mention it.
    cout << "Code/Text Segment contains the compiled program code." << endl;
    const char* str = "Hello, World!"; // string literal stored in code/text segment
    cout << str << endl;
    cout << "Global Variable: " << globalVar << endl;

    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace (the overall flow of main(), top to bottom)
// --------------------------------------------------------------------------
// STEP 1  v.emplace_back("A") and ("B") construct two Big objects directly
//         inside the already-reserved vector capacity — no move/copy
//         needed since there's room. emplace_back("C") exceeds the
//         reserved capacity of 2, forcing a REALLOCATION: the vector's
//         existing elements ("A","B") are relocated into new, larger
//         storage using Big's MOVE constructor (cheaper than copying),
//         printing "Move ctor" once per relocated element. emplace_back
//         ("D") constructs in place again if there's now room, or
//         triggers another reallocation (more "Move ctor" lines) if not.
// STEP 2  safesingleallocExample() runs (see its own comments above):
//         prints unique_ptr's managed value (10), then shared_ptr's (20)
//         along with reference counts 1, then 2 after sharing.
// STEP 3  recurseiveFunction(1000) recurses 1000 levels deep, printing
//         "Recursion depth: 1000", "900", ... "100" every 100th level —
//         each level allocates a 1000-int array ON THE STACK, which is
//         why deep, unbounded recursion can exhaust stack space (a stack
//         overflow) in ways a heap allocation never would.
// STEP 4  doubefreeExample() runs: prints "b: 5" and "a: 5" (both read the
//         same freshly-allocated int), then deletes `a`. The final
//         "b, after deleting a: ..." line reads THROUGH a dangling
//         pointer — undefined behavior, so its printed value is not
//         reliable (it may still show 5 by coincidence).
// STEP 5  leakMemoryExample() runs 10,000 times in a loop, each call
//         allocating a 1000-int array and never freeing it — this is a
//         DELIBERATE, large memory leak, included specifically so you can
//         watch this program's memory usage climb in a task manager while
//         it runs.
// STEP 6  heapAllocateDeallocateExample() allocates one int and one
//         5-element array, prints their values (42, then "0 10 20 30
//         40"), and correctly frees both.
// STEP 7  showAddresses() prints a table of memory addresses — one per
//         memory TYPE (code, global, static, local-static, stack, heap,
//         string object, string literal) — the exact numbers differ every
//         run (see 07-Pointers/1_Checkmemoryaddress.cpp for why), but
//         their RELATIVE grouping (stack addresses near each other, heap
//         addresses elsewhere) is the point being illustrated.
// STEP 8  The remaining lines in main() repeat smaller, standalone
//         examples of each memory type (stack, heap, static, code/text,
//         global) with one line of output each, ending with "Global
//         Variable: 50". main() returns 0.
// What is memory leaks: Memory leaks occur when a program allocates
//memory but fails to release it back to the system after it's no longer needed. 
//This can lead to increased memory usage over time and may eventually cause the 
//program to run out of memory.

// How to verify memory types?
    // We can use tools like Valgrind (on Linux) or Visual Studio's built
    // in diagnostic tools (on Windows) to monitor memory usage and detect leaks.
    // These tools can help identify memory that was allocated but not properly deallocated.

    // When to use which memory type?
    // - Use stack memory for local variables with a short lifetime.
    // - Use heap memory for objects that need to persist beyond the scope of a function or have a large size.
    // - Use static/global memory for variables that need to maintain state across function calls or throughout
    // the program's lifetime.
    // - Code/Text segment is managed by the operating system and is not directly controlled by the programmer.
    // Proper memory management is crucial for efficient and reliable C++ programs.


    // Language terms:
    // 1. Memory Allocation: The process of reserving a block of memory for use by a program.
    // 2. Memory Deallocation: The process of releasing previously allocated memory back to the
    // system.
    // 3. Dangling Pointer: A pointer that points to a memory location that has
    // already been deallocated.
    // 4. Fragmentation: The condition where free memory is divided into small,
    // non-contiguous blocks, making it difficult to allocate large contiguous memory blocks.
    // 5. Garbage Collection: An automatic memory management technique where the system
    // periodically identifies and frees memory that is no longer in use by the program.
    // C++ does not have built-in garbage collection, but smart pointers can help manage memory automatically.
    // 6. RAII (Resource Acquisition Is Initialization): A programming idiom where resource allocation
    // is tied to the lifetime of objects. Resources are acquired during object creation and released during
    // object destruction.

    // what is storage duration in C++?
    // Storage duration determines the lifetime of a variable and when its memory is allocated and deallocated.
    // There are four types of storage duration in C++:
    // 1. Automatic Storage Duration: Variables are automatically allocated and deallocated when they go out of scope.
    // 2. Static Storage Duration: Variables are allocated when the program starts and deallocated when it ends.
    // 3. Dynamic Storage Duration: Variables are allocated and deallocated manually using new and delete.
    // 4. Thread Storage Duration: Variables are allocated for the lifetime of a thread.

    // Safety and Common bugs:
    // 1. Memory Leaks: Failing to deallocate memory can lead to increased
    // memory usage over time.
    // 2. Dangling Pointers: Accessing memory that has already been deallocated
    // can lead to undefined behavior.
    // 3. Buffer Overflows: Writing beyond the allocated memory can corrupt data
    // and lead to security vulnerabilities.
    // 4. Double Free: Deallocating the same memory block more than once can
    // lead to undefined behavior. But how it happens?
    // It happens when a program calls delete or free on the same memory address multiple times.
    // or shared pointers going out of scope together.
    // This can corrupt the memory management data structures, leading to crashes or unpredictable behavior.
    // 5. Use After Free: Accessing memory after it has been deallocated can
    // lead to undefined behavior.
    // To avoid these issues, use smart pointers, follow RAII principles, and utilize
    // memory profiling tools to monitor and manage memory effectively.

// Memory types:
// 1. Stack Memory: Used for static memory allocation. Variables are automatically allocated and deallocated when they go out of scope.
// 2. Heap Memory: Used for dynamic memory allocation. Memory is manually allocated and de
// allocated using new and delete keywords.
// 3. Static/Global Memory: Used for global and static variables. Memory is allocated
// when the program starts and deallocated when the program ends.
// 4. Code/Text Segment: Contains the compiled program code. This memory is read-only and shared among processes.
// How to manage memory effectively in C++:
// 1. Use smart pointers (unique_ptr, shared_ptr) to manage dynamic memory automatically
// 2. Avoid memory leaks by ensuring every new has a corresponding delete
// 3. Use RAII (Resource Acquisition Is Initialization) principles to tie resource management to
// object lifetime
// 4. Regularly profile and monitor memory usage to identify potential leaks or inefficiencies


//& vs && in C++
// & is the address-of operator, used to get the memory address of a variable.
// && is the rvalue reference operator, used to bind to temporary objects (rvalues) for move semantics.