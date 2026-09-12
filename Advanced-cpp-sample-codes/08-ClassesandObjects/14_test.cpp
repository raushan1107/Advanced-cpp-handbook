// Personal scratch/practice file. The commented-out block at the top is
// an EARLIER draft (a Employee/Manager/SeniorManager multi-level
// inheritance sketch, left in place for reference); the ACTIVE code below
// it is the same pure-virtual Payment/CreditCard/PayPal interface example
// as 9_purevirtual-interfaces.cpp — see that file for the fully commented
// version with parameter and step-by-step notes; this one is kept as a
// second, standalone practice copy.
//
// Compile: g++ -std=c++17 14_test.cpp -o test
// Run:     test.exe   (Windows)   or   ./test   (Linux/macOS)

// #include <iostream>

// using namespace std;

// class Employee {

// protected:

//     string name;

//     int id;

// public:

//     void setEmployee(string n, int i) {

//         name = n; id = i;

//     }

// };

// class Manager : public Employee {

// protected:

//     string department;

// public:

//     void setDepartment(string d) {

//         department = d;

//     }

// };

// class SeniorManager : public Manager {

// public:

//     void showDetails() {

//         cout << "Name: " << name << ", ID: " << id
// << ", Department: " << department << endl;

//     }

// };

// int main() {

//     SeniorManager sm;

//     sm.setEmployee("Ravi", 101);

//     sm.setDepartment("Finance");

//     sm.showDetails();

//     return 0;

// }

 #include <iostream>

using namespace std;

class Payment {

public:

    virtual void processPayment() = 0; // pure virtual

};

class CreditCard : public Payment {

public:

    void processPayment() override {

        cout << "Processing Credit Card Payment" << endl;

    }

};

class PayPal : public Payment {

public:

    void processPayment() override {

        cout << "Processing PayPal Payment" << endl;

    }

};

int main() {

    Payment* p1 = new CreditCard();

    Payment* p2 = new PayPal();

    p1->processPayment();

    p2->processPayment();

    delete p1;

    delete p2;

    return 0;

}

// --------------------------------------------------------------------------
// Step-by-step execution trace (identical program to
// 9_purevirtual-interfaces.cpp — see that file for the fully annotated
// version)
// --------------------------------------------------------------------------
// STEP 1  p1 = new CreditCard(), p2 = new PayPal(), both referenced
//         through Payment* pointers.
// STEP 2  p1->processPayment() resolves via virtual dispatch to
//         CreditCard's override -> prints "Processing Credit Card
//         Payment".
// STEP 3  p2->processPayment() resolves to PayPal's override -> prints
//         "Processing PayPal Payment".
// STEP 4  Both objects deleted; main() returns 0.
