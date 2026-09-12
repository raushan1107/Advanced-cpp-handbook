// Constructor overloading and the copy constructor — three DIFFERENT ways
// a Student object can come into existence.
//
// Compile: g++ -std=c++17 2_c2withconstructor.cpp -o c2withconstructor
// Run:     c2withconstructor.exe   (Windows)   or   ./c2withconstructor   (Linux/macOS)

#include <iostream>

using namespace std;

class Student {

private:
    string name;
    int rollNo;

public:
    // Constructor
    // Student()
    // No parameters — the DEFAULT constructor, called when a Student is
    // created with no arguments at all (`Student s1;` below).
    Student() {
        this->name = "Test User";
        this->rollNo = 0;
        cout << "Constructor called!" << endl;
    }

    // Constructor overloading with parameters
    // Student(n, r)
    //   n - the name to store.
    //   r - the roll number to store.
    // A SECOND constructor, same class, different parameter list — the
    // compiler picks whichever constructor matches the arguments given at
    // the object's creation site (`Student s2("Raushan", 11);` picks this
    // one; `Student s1;` picks the one above).
    Student(string n, int r) {
        this->name = n;
        this->rollNo = r;
        cout << "Constructor called!" << endl;
    }

    // Copy Constructor (optional)
    /*
    Copy constructor is used to create a new object as a copy of an existing object. It is called when an object is passed by value, returned from a function, or explicitly copied.
    It is defined with a single parameter that is a reference to an object of the same class.
    In real-world scenarios, if you don't define a copy constructor, the compiler provides a default one that performs a shallow copy. However, if your class manages resources like dynamic memory, file handles, etc., you should define your own copy constructor to ensure a deep copy and proper resource management.
    Analogy: Think of a copy constructor like making a photocopy of a document. The photocopy is a separate entity that contains the same information as the original document, but changes made to the photocopy do not affect the original document.
    */
    // Student(const Student &s)
    //   s - the EXISTING object being copied FROM, taken by const
    //       reference (so the source is neither modified nor
    //       expensively copied just to pass it in). This constructor
    //       runs automatically for `Student s3 = s2;` below — it is a
    //       THIRD distinct way to create a Student, separate from the two
    //       constructors above.
    Student(const Student &s) {
        this->name = s.name;
        this->rollNo = s.rollNo;
        cout << "Copy Constructor called!" << endl;
    }

    void display() {
        cout << "Name: " << name << ", Roll: " << rollNo << endl;
    }

};

int main() {

    // Student s1
    // No arguments -> matches the DEFAULT constructor.
    Student s1;   // Constructor is called automatically
    // Student s2("Raushan", 11)
    //   "Raushan", 11 -> matches the (string, int) constructor.
    Student s2("Raushan", 11); // Parameterized constructor is called automatically
    s1.display();
    s2.display();

    // Student s3 = s2
    // This is COPY-INITIALIZATION: s3 is a brand-new object, and its
    // value is initialized FROM s2 — this calls the copy constructor
    // above, NOT the assignment operator (assignment only applies to an
    // object that ALREADY exists; s3 doesn't exist yet at this line).
    Student s3 = s2; // Copy constructor is called automatically
    s3.display();
    return 0;

}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  Student s1; -> default constructor runs: name="Test User",
//         rollNo=0. Prints "Constructor called!".
// STEP 2  Student s2("Raushan", 11); -> the (string, int) constructor
//         runs: name="Raushan", rollNo=11. Prints "Constructor called!"
//         again (a DIFFERENT constructor, same printed message).
// STEP 3  s1.display() prints "Name: Test User, Roll: 0".
// STEP 4  s2.display() prints "Name: Raushan, Roll: 11".
// STEP 5  Student s3 = s2; -> the copy constructor runs, copying s2's
//         CURRENT field values (name="Raushan", rollNo=11) into a brand
//         new s3. Prints "Copy Constructor called!" — a third, distinct
//         message from the other two constructors' output.
// STEP 6  s3.display() prints "Name: Raushan, Roll: 11" — identical to
//         s2's own fields, since s3 is an independent copy of s2's values
//         at the moment of copying, not a reference to s2 itself.
// STEP 7  main() returns 0.
