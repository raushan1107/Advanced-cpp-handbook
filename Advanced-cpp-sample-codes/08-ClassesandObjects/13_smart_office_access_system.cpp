// Capstone exercise sample -- combines inheritance, abstract classes, virtual
// dispatch, function overloading and operator overloading in one program.
// See capstone-work1.html for the full brief.
//
// Use case: a smart office building that has to grant or deny badge access to
// employees, contractors and visitors -- each under a different rule -- without
// giving each type its own reporting logic.
//
// Compile: g++ -std=c++17 13_smart_office_access_system.cpp -o smart_office_access
// Run:     smart_office_access.exe   (Windows)   or   ./smart_office_access   (Linux/macOS)
#include <iostream>
#include <string>
using namespace std;

// Every person who badges in is a Person first (inheritance).
class Person {
protected:
    string name;
    int id;

public:
    Person(const string& n, int i) : name(n), id(i) {}
    virtual ~Person() = default;

    // Pure virtual functions: every concrete role must define its own rule (abstract class).
    virtual bool canAccess() const = 0;
    virtual string statusLine() const = 0;

    virtual void display() const {
        cout << name << " | ID: " << id << " | " << statusLine();
    }

    // Operator overloading: two people share a badge record if their IDs match,
    // regardless of which derived type either one is.
    friend bool operator==(const Person& a, const Person& b) {
        return a.id == b.id;
    }
};

// One function, every role: virtual dispatch decides the rest at runtime.
void processAccess(const Person& person) {
    person.display();
    cout << " -> " << (person.canAccess() ? "GRANTED" : "DENIED") << "\n";
}

class Employee : public Person {
public:
    Employee(const string& n, int i) : Person(n, i) {}
    bool canAccess() const override { return true; }
    string statusLine() const override { return "Employee"; }
};

class Contractor : public Person {
    bool contractActive;
public:
    Contractor(const string& n, int i, bool active)
        : Person(n, i), contractActive(active) {}
    bool canAccess() const override { return contractActive; }
    string statusLine() const override {
        return contractActive ? "Contractor (active)" : "Contractor (expired)";
    }
};

class Visitor : public Person {
    bool approved;
public:
    Visitor(const string& n, int i, bool appr)
        : Person(n, i), approved(appr) {}
    bool canAccess() const override { return approved; }
    string statusLine() const override {
        return approved ? "Visitor (approved)" : "Visitor (not approved)";
    }
};

// Function overloading: two ways to price a desk booking.
double calculateCharge(int wholeHours) {
    return wholeHours * 50.0;
}
double calculateCharge(double hours, double ratePerHour) {
    return hours * ratePerHour;
}

int main() {
    Employee rahul("Rahul", 101);
    Contractor priya("Priya", 202, true);
    Contractor amit("Amit", 203, false);
    Visitor sarah("Sarah", 301, true);
    Visitor john("John", 302, false);

    cout << "SMART OFFICE ACCESS REPORT\n---\n";
    processAccess(rahul);
    processAccess(priya);
    processAccess(amit);
    processAccess(sarah);
    processAccess(john);

    cout << "\nDesk booking, 4 whole hours: Rs " << calculateCharge(4) << "\n";
    cout << "Desk booking, 2.5 hours @ Rs 60/hr: Rs " << calculateCharge(2.5, 60.0) << "\n";

    Visitor sarahAgain("Sarah Verma", 301, true);
    cout << "\nSame badge ID? sarah == sarahAgain -> " << (sarah == sarahAgain ? "true" : "false") << "\n";
    cout << "Same badge ID? priya == amit -> " << (priya == amit ? "true" : "false") << "\n";
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  Five Person-derived objects are constructed: rahul (Employee),
//         priya (Contractor, active=true), amit (Contractor,
//         active=false), sarah (Visitor, approved=true), john (Visitor,
//         approved=false).
// STEP 2  processAccess(rahul): calls rahul.display() (prints "Rahul |
//         ID: 101 | Employee"), then rahul.canAccess() (Employee's
//         override always returns true) -> " -> GRANTED".
// STEP 3  processAccess(priya): statusLine() returns "Contractor
//         (active)" since contractActive=true; canAccess() returns true
//         -> " -> GRANTED".
// STEP 4  processAccess(amit): statusLine() returns "Contractor
//         (expired)"; canAccess() returns false -> " -> DENIED".
// STEP 5  processAccess(sarah): "Visitor (approved)"; canAccess() true ->
//         " -> GRANTED". processAccess(john): "Visitor (not approved)";
//         canAccess() false -> " -> DENIED".
// STEP 6  calculateCharge(4) matches the ONE-int-parameter overload:
//         4 * 50.0 = 200.0 -> "Desk booking, 4 whole hours: Rs 200".
//         calculateCharge(2.5, 60.0) matches the (double,double)
//         overload: 2.5 * 60.0 = 150.0 -> "Desk booking, 2.5 hours @ Rs
//         60/hr: Rs 150".
// STEP 7  sarahAgain is a NEW Visitor with the same id (301) as sarah, but
//         a different name. sarah == sarahAgain calls the friend
//         operator==, which compares ONLY the id fields (a.id == b.id) ->
//         301 == 301 -> true -> "Same badge ID? sarah == sarahAgain ->
//         true" — proving the badge-match logic works across the SAME
//         derived type even with different names.
// STEP 8  priya == amit compares id 202 vs 203 -> false -> "Same badge ID?
//         priya == amit -> false".
// STEP 9  main() ends; every Person-derived object goes out of scope in
//         REVERSE construction order, each running Person's virtual
//         destructor (a no-op default here, so nothing prints).

