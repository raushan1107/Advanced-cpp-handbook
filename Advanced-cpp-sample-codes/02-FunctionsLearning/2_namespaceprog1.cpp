// Namespaces — grouping related names so two different pieces of code can
// both define something called `display()` without colliding.
//
// Compile: g++ -std=c++17 2_namespaceprog1.cpp -o namespaceprog1
// Run:     namespaceprog1.exe   (Windows)   or   ./namespaceprog1   (Linux/macOS)

#include <iostream>
using namespace std;
//using namespace MyNamespace; // importing our custom namespace

// namespace FirstNamespace { ... }
// Everything declared inside these braces is scoped under the name
// "FirstNamespace" — a function called display() in here is a COMPLETELY
// different function from any display() declared in another namespace,
// even though both are spelled the same way.
namespace FirstNamespace {
    void display() {
        std::cout << "Inside FirstNamespace" << std::endl;
    }
}

namespace SecondNamespace {
    // class Test — nested inside SecondNamespace, so its full name from
    // outside this namespace is SecondNamespace::Test.
    class Test {
    public:
        // show()
        // No parameters — just prints which namespace/class this method
        // belongs to.
        void show() {
            std::cout << "Inside Test class of SecondNamespace" << std::endl;
        }
    };
    // display() — a SECOND function named "display", but scoped under
    // SecondNamespace instead of FirstNamespace; the two never collide
    // because their full, qualified names differ
    // (FirstNamespace::display vs SecondNamespace::display).
    void display() {
        std::cout << "Inside SecondNamespace" << std::endl;
    }
}
int main() {
    // SecondNamespace::Test obj;
    //   SecondNamespace:: - the scope-resolution qualifier, telling the
    //                       compiler to look for `Test` specifically
    //                       inside SecondNamespace, not some other Test
    //                       class that might exist elsewhere.
    SecondNamespace::Test obj;
    obj.show();  // Calls show from Test class
    // FirstNamespace::display()
    // Explicitly qualified so there's no ambiguity about WHICH display()
    // is meant — necessary here because TWO different display() functions
    // exist (one per namespace) and neither namespace has been brought in
    // with a blanket `using namespace`.
    FirstNamespace::display();  // Calls display from FirstNamespace
    SecondNamespace::display(); // Calls display from SecondNamespace
    return 0;
}

// can we use using namespace here?
// Yes, we can use 'using namespace' to avoid prefixing the namespace each time.
// How i can use this namespace in different files?
// To use namespaces across different files, you can define the namespace in a header file
// and include that header file in other source files where you want to use the namespace.
// Example:
// In MyNamespace.h

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  obj is constructed as a SecondNamespace::Test.
// STEP 2  obj.show() runs, printing "Inside Test class of SecondNamespace".
// STEP 3  FirstNamespace::display() runs — the compiler resolves this to
//         the display() defined INSIDE the `namespace FirstNamespace {...}`
//         block, printing "Inside FirstNamespace".
// STEP 4  SecondNamespace::display() runs — a DIFFERENT function despite
//         the identical name, printing "Inside SecondNamespace".
// STEP 5  main() returns 0. Final console output, in order:
//           Inside Test class of SecondNamespace
//           Inside FirstNamespace
//           Inside SecondNamespace
