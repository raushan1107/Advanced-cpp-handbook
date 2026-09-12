// Custom exception classes — an earlier/duplicate draft of
// 3_customexception.cpp (identical logic, near-identical formatting). See
// that file for the fully commented, currently-taught version of this
// InsufficientFundsException pattern; this copy is kept as a second,
// standalone practice run of the same idea.
//
// Compile: g++ -std=c++17 4_customexceptionProgram.cpp -o customexceptionProgram
// Run:     customexceptionProgram.exe   (Windows)   or   ./customexceptionProgram   (Linux/macOS)
// Interaction: enter an amount to withdraw (try more than 5000).
#include <iostream>

#include <exception>

using namespace std;

// Custom exception class for insufficient balance

class InsufficientFundsException : public exception {

    string message;

public:

    InsufficientFundsException(double balance, double withdrawAmount) {

        message = "Error: Insufficient funds! Balance: " +

                  to_string(balance) + ", Tried to withdraw: " +

                  to_string(withdrawAmount);

    }

    const char* what() const noexcept override {

        return message.c_str();

    }

};

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

    catch (const InsufficientFundsException &e) {

        cout << e.what() << endl;

    }

    cout << "Transaction complete." << endl;

}

// --------------------------------------------------------------------------
// Step-by-step execution trace — identical program to
// 3_customexception.cpp; see that file for the fully worked example
// (amount=7000 against a 5000 balance)
// --------------------------------------------------------------------------
// STEP 1  balance=5000.0 prints as "Current balance: 5000".
// STEP 2  User enters an amount greater than 5000 -> withdraw() throws
//         InsufficientFundsException(balance, amount).
// STEP 3  The catch clause runs e.what(), printing the built message.
// STEP 4  "Transaction complete." prints; main() ends.
