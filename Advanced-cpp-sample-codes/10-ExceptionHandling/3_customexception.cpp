// Custom exception classes — deriving from std::exception instead of
// throwing a plain string or int, so the exception carries structured data
// AND still works with any code that only knows how to catch
// std::exception.
//
// Compile: g++ -std=c++17 3_customexception.cpp -o customexception
// Run:     customexception.exe   (Windows)   or   ./customexception   (Linux/macOS)
// Interaction: enter an amount to withdraw (try more than 5000).
#include <iostream>
#include <exception>

using namespace std;

// Custom exception class for insufficient balance
// class InsufficientFundsException : public exception
// Inheriting from std::exception means this can be caught either
// specifically (catch (const InsufficientFundsException&)) or generically
// by any code that only knows about the base std::exception — the same
// polymorphism idea from Module 2, applied to error types.
class InsufficientFundsException : public exception {

    string message;

public:

    // InsufficientFundsException(balance, withdrawAmount)
    //   balance        - the account's current balance at the moment of
    //                    the failed withdrawal.
    //   withdrawAmount - the amount that was attempted and rejected.
    // Both values are folded into a human-readable message built ONCE,
    // here, and stored — so `what()` below has no work left to do but
    // hand that string back.
    InsufficientFundsException(double balance, double withdrawAmount) {

        message = "Error: Insufficient funds! Balance: " +

                  to_string(balance) + ", Tried to withdraw: " +

                  to_string(withdrawAmount);

    }

    // const char* what() const noexcept override
    // No parameters — OVERRIDES std::exception's own what(), which is
    // what every catch (const std::exception&) handler calls to get a
    // description. `noexcept` promises this function itself will never
    // throw (required to match std::exception's own signature exactly).
    const char* what() const noexcept override {

        return message.c_str();

    }

};

// withdraw(amount, balance)
//   amount  - how much the caller wants to withdraw.
//   balance - the account's current balance, checked against amount.
void withdraw(double amount, double balance) {

    if (amount > balance)

        throw InsufficientFundsException(balance, amount);

    cout << "Withdrawal successful. New balance: " << (balance - amount) << endl;

}

int main() {

    try {
                double balance = 5000.0; // Example balance

                cout << "Current balance: " << balance << endl;
        cout << "Enter amount to withdraw: ";
        double amount;
        cin >> amount;

        withdraw(amount, balance); // more than balance

    }

    // catch (const InsufficientFundsException &e)
    //   e - bound to the thrown exception object by const reference (no
    //       copy needed just to read it); e.what() calls the OVERRIDDEN
    //       what() above, returning the specific balance/amount message
    //       built in the constructor.
    catch (const InsufficientFundsException &e) {

        cout << e.what() << endl;

    }

    cout << "Transaction complete." << endl;

}

// --------------------------------------------------------------------------
// Step-by-step execution trace (example run: amount=7000)
// --------------------------------------------------------------------------
// STEP 1  balance = 5000.0. "Current balance: 5000" prints.
// STEP 2  User enters "7000" -> amount = 7000.0.
// STEP 3  withdraw(7000.0, 5000.0) checks amount > balance (7000 > 5000)
//         -> true -> throws InsufficientFundsException(5000.0, 7000.0).
//         The constructor builds message = "Error: Insufficient funds!
//         Balance: 5000.000000, Tried to withdraw: 7000.000000"
//         (to_string always shows 6 decimal digits for doubles).
// STEP 4  The catch clause matches; e.what() returns that exact message,
//         which prints.
// STEP 5  "Transaction complete." prints — the program continues normally
//         after handling the exception.
//
// If amount had been 3000 instead (<=balance), withdraw() would print
// "Withdrawal successful. New balance: 2000" and return normally — no
// throw, so the catch block would simply never execute.
