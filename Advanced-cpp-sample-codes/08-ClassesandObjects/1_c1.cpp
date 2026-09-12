// Classes — bundling data (rollNo, name) with the functions that operate
// on it (setDetails, display) into one type, plus the `this` pointer.
//
// Compile: g++ -std=c++17 1_c1.cpp -o c1
// Run:     c1.exe   (Windows)   or   ./c1   (Linux/macOS)

#include <iostream>
using namespace std;

class Student {
private:
    int rollNo;
    string name;

public:
    // Student(roll, n)
    //   roll - the roll number to store.
    //   n    - the name to store; a CONSTRUCTOR runs automatically the
    //          moment a Student object is created (see `Student s1(11,
    //          "Raushan");` in main), unlike setDetails() below, which
    //          must be called explicitly, later, if you want to change
    //          those fields again.
    Student(int roll, string n) {
        rollNo = roll;
        name = n;
    }
    // setDetails(rollNo, name)
    //   rollNo, name - NEW values to overwrite this object's fields with.
    //                  These parameter names deliberately match the
    //                  member field names (rollNo, name), which is
    //                  exactly why `this->` is needed below.
    void setDetails(int rollNo, string name) {
        // this->rollNo = rollNo
        //   this->rollNo - the MEMBER field (disambiguated with `this->`)
        //   rollNo (right side) - the PARAMETER of the same name; without
        //                         `this->`, `rollNo = rollNo;` would just
        //                         assign the parameter to itself and leave
        //                         the member field untouched, since the
        //                         parameter name SHADOWS the member name
        //                         inside this function's body.
        this->rollNo = rollNo;
        this->name = name;
    }

    void display() {
        cout << "Roll: " << rollNo << ", Name: " << name << endl;
    }

};

int main() {
    // Student s1(11,"Raushan")
    //   11, "Raushan" - forwarded straight to the constructor above,
    //                   which runs immediately as s1 is created.
    Student s1(11,"Raushan");
    s1.display();
    // Student s1;  // Static allocation -> Stack memory
    // Student* s2 = new Student(); // Dynamic allocation -> Heap memory

    // s2->setDetails(102, "Anita");
    // s2->display();

    // s1.setDetails(101, "Ravi");
    // s1.display();

    // delete s2; // Free dynamically allocated memory -> Heap memory

    return 0;
}


// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  Student s1(11, "Raushan") runs the constructor: rollNo = 11,
//         name = "Raushan" (no `this->` needed here since the
//         constructor's parameters are named `roll`/`n`, not `rollNo`/
//         `name`, so there's no shadowing to resolve).
// STEP 2  s1.display() prints "Roll: 11, Name: Raushan".
// STEP 3  main() returns 0. Every line after this is commented out and
//         never runs — it's a sketch of static (stack) vs. dynamic (heap)
//         allocation using a second Student, `s2`, created with `new` and
//         released with `delete`; uncomment it to see setDetails()
//         actually overwrite s1's fields via the `this->` disambiguation
//         explained above.
