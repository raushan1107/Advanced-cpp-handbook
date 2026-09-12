// Pure virtual functions and interfaces — a base class that provides NO
// implementation at all, only a contract every derived class must fulfill.
//
// Compile: g++ -std=c++17 9_purevirtual-interfaces.cpp -o purevirtual-interfaces
// Run:     purevirtual-interfaces.exe   (Windows)   or   ./purevirtual-interfaces   (Linux/macOS)
#include <iostream>
using namespace std;

class Payment {
public:
    // virtual void processPayment() = 0
    //   = 0 - marks this a PURE virtual function: Payment provides no
    //         body for it at all. A class with even one pure virtual
    //         function becomes ABSTRACT — it can never be instantiated
    //         directly (`new Payment()` would be a compile error) — it
    //         only exists to define a required interface every derived
    //         class must implement.
    virtual void processPayment() = 0; // pure virtual
};

class CreditCard : public Payment {
public:
    // Must provide processPayment(), or CreditCard would ALSO remain
    // abstract and become impossible to instantiate.
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
    // Payment* p1 = new CreditCard()
    // Payment itself can never be `new`'d directly (it's abstract), but a
    // Payment* is perfectly valid pointing at any CONCRETE derived type.
    Payment* p1 = new CreditCard();
    Payment* p2 = new PayPal();

    // p1->processPayment()
    // Same virtual-dispatch idea as 8_polymorphismcls.cpp: even though
    // p1's declared type is Payment*, the call resolves to CreditCard's
    // implementation, since Payment itself never HAD an implementation to
    // fall back to.
    p1->processPayment();
    p2->processPayment();

    delete p1;
    delete p2;
    return 0;

}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  p1 = new CreditCard() — a CreditCard object, referenced through
//         a Payment* pointer.
// STEP 2  p2 = new PayPal() — likewise, a PayPal object through a
//         Payment* pointer.
// STEP 3  p1->processPayment() resolves to CreditCard's override (the
//         ONLY implementation that exists for this object, since Payment
//         never defined one) -> prints "Processing Credit Card Payment".
// STEP 4  p2->processPayment() resolves to PayPal's override -> prints
//         "Processing PayPal Payment".
// STEP 5  Both objects are deleted; main() returns 0.
//
// Try this: add `Payment p3;` anywhere in main() and attempt to compile —
// you'll get an error like "cannot declare variable 'p3' to be of
// abstract type 'Payment'", proving the `= 0` restriction is enforced at
// COMPILE time, not just a documentation convention.
