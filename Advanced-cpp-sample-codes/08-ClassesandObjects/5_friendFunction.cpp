// Friend Function in C++ — a non-member function granted access to a
// class's private data.
//
// Compile: g++ -std=c++17 5_friendFunction.cpp -o friendFunction
// Run:     friendFunction.exe   (Windows)   or   ./friendFunction   (Linux/macOS)
#include <iostream>
using namespace std;

class Box {
private:
    double width;
public:
    // Box(w)
    //   w - the box's width, stored directly via the member-initializer
    //       list `: width(w)`.
    Box(double w) : width(w) {}

    // Function declaration
    // printW(b)
    //   b - a Box passed BY VALUE (a full copy); as a MEMBER function of
    //       Box, this can read `b.width` even though width is private,
    //       because member functions always have access to every OTHER
    //       object of their own class, not just `this`.
    void printW(Box b)
    {
        cout << "Width of box: " << b.width << endl;
    }

    // Declare friend function
    // friend void printWidth(box)
    //   box - a Box passed by value. `friend` here means printWidth is
    //         declared INSIDE the class but is NOT a member of it (it
    //         can't be called as `someBox.printWidth()`) — it's a
    //         completely ordinary free function that the class has
    //         specifically granted permission to see its private members.
    friend void printWidth(Box box)
    {
        // Access private member
        cout << "Width of box: " << box.width << endl;
        // Purpose of friend function is to access private members of the class.
        // It is not a member of the class but has access to its private and protected members.
        // It is useful when two or more classes need to work closely together and share data.
        // Analogy: Think of a friend function like a trusted friend who is allowed to enter your house (class) and see things that others cannot (private members).
    }

};

int main() {
    Box box(10.0);
    // printWidth(box)
    // Called as a plain FREE function — no `box.` prefix — even though it
    // reads box's private `width`, because it was declared `friend`
    // inside Box.
    printWidth(box); // Call friend function
    box.printW(box); // Call member function
    return 0;
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  box is constructed with width = 10.0.
// STEP 2  printWidth(box) is called: since it's a friend, it can read
//         box.width directly. Prints "Width of box: 10".
// STEP 3  box.printW(box) is called: a MEMBER function, called through an
//         object (box.), that ALSO happens to take a Box by value as its
//         parameter; it reads the passed-in copy's .width. Prints "Width
//         of box: 10" again — the same result reached two different ways
//         (friend function vs. a member function that takes another Box
//         as a parameter).
// STEP 4  main() returns 0.
