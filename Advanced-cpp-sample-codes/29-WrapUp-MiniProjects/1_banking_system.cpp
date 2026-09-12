// Banking System — Module 10's first wrap-up mini-project. Combines
// inheritance (Account/SavingsAccount), a custom exception
// (InsufficientFundsError), and smart-pointer ownership
// (vector<unique_ptr<Account>>) into one small, realistic system.
//
// Plain g++ toolchain, no Qt needed.
// Compile: g++ -std=c++17 1_banking_system.cpp -o banking_system
// Run:     banking_system.exe   (Windows)   or   ./banking_system   (Linux/macOS)
//
// This exact file was compiled and run for this repo — the "Actual output"
// block at the bottom is real captured output, not a guess.

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <iomanip>
using namespace std;

// InsufficientFundsError : public runtime_error
// A custom exception carrying a specific, catchable meaning instead of a
// generic runtime_error every caller would have to inspect the message of.
class InsufficientFundsError : public runtime_error {
public:
    // InsufficientFundsError(msg)
    //   msg - the human-readable explanation, forwarded straight to
    //         runtime_error's own constructor, which is what e.what()
    //         later returns.
    InsufficientFundsError(const string& msg) : runtime_error(msg) {}
};

class Account {
protected:
    string owner;
    double balance;
public:
    // Account(owner_, opening)
    //   owner_  - the account holder's name; moved into the member `owner`
    //             rather than copied, since the caller's own string isn't
    //             needed after this call.
    //   opening - the starting balance.
    Account(string owner_, double opening) : owner(move(owner_)), balance(opening) {}
    virtual ~Account() {}

    // deposit(amt)
    //   amt - the amount to add to the balance; must be strictly positive.
    virtual void deposit(double amt) {
        if (amt <= 0) throw invalid_argument("Deposit amount must be positive");
        balance += amt;
    }

    // withdraw(amt)
    //   amt - the amount to remove from the balance; must be positive AND
    //         no larger than the current balance, or this throws instead
    //         of ever letting the balance go negative.
    virtual void withdraw(double amt) {
        if (amt <= 0) throw invalid_argument("Withdrawal amount must be positive");
        if (amt > balance) throw InsufficientFundsError(owner + " has insufficient funds");
        balance -= amt;
    }

    double getBalance() const { return balance; }

    virtual string describe() const {
        ostringstream oss;
        // fixed << setprecision(2)
        // Forces exactly two digits after the decimal point (so $500
        // prints as "$500.00", not "$500"), matching how currency is
        // normally displayed.
        oss << owner << ": $" << fixed << setprecision(2) << balance;
        return oss.str();
    }
};

class SavingsAccount : public Account {
    double rate;
public:
    // SavingsAccount(owner_, opening, rate_)
    //   owner_, opening - forwarded straight to the base Account
    //                     constructor.
    //   rate_           - the annual interest rate as a fraction (0.04
    //                     means 4%), stored for applyInterest() to use
    //                     later.
    SavingsAccount(string owner_, double opening, double rate_) : Account(move(owner_), opening), rate(rate_) {}

    // applyInterest()
    // Takes no parameters — it operates purely on this object's own
    // `balance` and `rate`, adding balance*rate to the balance.
    void applyInterest() { balance += balance * rate; }

    string describe() const override {
        ostringstream oss;
        oss << owner << " (Savings, " << int(rate * 100) << "% APR): $" << fixed << setprecision(2) << balance;
        return oss.str();
    }
};

// transfer(from, to, amt)
//   from - the account money leaves; withdraw() is called on this FIRST.
//   to   - the account money arrives in; deposit() is only reached if
//          `from`'s withdrawal didn't throw.
//   amt  - the amount to move between them.
// This ordering is the whole point of the function: if `from.withdraw(amt)`
// throws (insufficient funds), execution never reaches `to.deposit(amt)`,
// so a failed transfer can never leave `to` credited without `from` having
// actually paid for it.
void transfer(Account& from, Account& to, double amt) {
    from.withdraw(amt); // if this throws, `to` is untouched
    to.deposit(amt);
}

int main() {
    vector<unique_ptr<Account>> bank;
    // make_unique<Account>("Meera", 500.0)
    //   "Meera", 500.0 - forwarded straight to Account's constructor as
    //                    owner_ and opening.
    bank.push_back(make_unique<Account>("Meera", 500.0));
    // make_unique<SavingsAccount>("Aakash", 1000.0, 0.04)
    //   "Aakash", 1000.0, 0.04 - owner_, opening, and a 4% annual rate.
    bank.push_back(make_unique<SavingsAccount>("Aakash", 1000.0, 0.04));

    cout << "Opening balances:\n";
    for (auto& acc : bank) cout << "  " << acc->describe() << "\n";

    // transfer(*bank[1], *bank[0], 200.0)
    //   *bank[1] - dereferences the unique_ptr to get the actual
    //              SavingsAccount object (Aakash) — this is the `from`.
    //   *bank[0] - the Account object (Meera) — the `to`.
    //   200.0    - the amount moved.
    transfer(*bank[1], *bank[0], 200.0);
    cout << "\nAfter transferring 200 from Aakash to Meera:\n";
    for (auto& acc : bank) cout << "  " << acc->describe() << "\n";

    // dynamic_cast<SavingsAccount*>(bank[1].get())
    //   bank[1].get() - the raw Account* stored inside the unique_ptr,
    //                   without giving up ownership (get() never releases
    //                   or transfers the pointer).
    // dynamic_cast returns a valid SavingsAccount* only because bank[1]
    // really does point at a SavingsAccount; it would be nullptr for
    // bank[0], which is a plain Account.
    if (auto* savings = dynamic_cast<SavingsAccount*>(bank[1].get())) {
        savings->applyInterest();
    }
    cout << "\nAfter Aakash's savings account applies interest:\n";
    for (auto& acc : bank) cout << "  " << acc->describe() << "\n";

    cout << "\nAttempting to withdraw 10000 from Meera's account:\n";
    try {
        // bank[0]->withdraw(10000.0)
        //   10000.0 - far more than Meera's balance, deliberately, to
        //             trigger InsufficientFundsError below.
        bank[0]->withdraw(10000.0);
    } catch (const InsufficientFundsError& e) {
        cout << "  Caught: " << e.what() << "\n";
    }
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  bank[0] = Account("Meera", balance=500.00).
//         bank[1] = SavingsAccount("Aakash", balance=1000.00, rate=0.04).
// STEP 2  transfer(*bank[1], *bank[0], 200.0):
//           bank[1].withdraw(200) -> 200 <= 1000, so it succeeds:
//             Aakash's balance becomes 1000.00 - 200 = 800.00.
//           bank[0].deposit(200)  -> Meera's balance becomes
//             500.00 + 200 = 700.00.
// STEP 3  dynamic_cast succeeds for bank[1] (it IS a SavingsAccount) ->
//         savings->applyInterest() runs: interest = 800.00 * 0.04 = 32.00,
//         so Aakash's balance becomes 800.00 + 32.00 = 832.00.
// STEP 4  bank[0]->withdraw(10000.0): 10000 > Meera's current balance
//         (700.00), so the `amt > balance` check throws
//         InsufficientFundsError("Meera has insufficient funds") instead
//         of ever changing `balance`. Meera's balance is STILL 700.00
//         after this line, not some negative number.
// STEP 5  The catch block runs, printing the exception's message; program
//         ends with Meera at 700.00 and Aakash at 832.00.
//
// --------------------------------------------------------------------------
// Actual output
// --------------------------------------------------------------------------
// Opening balances:
//   Meera: $500.00
//   Aakash (Savings, 4% APR): $1000.00
//
// After transferring 200 from Aakash to Meera:
//   Meera: $700.00
//   Aakash (Savings, 4% APR): $800.00
//
// After Aakash's savings account applies interest:
//   Meera: $700.00
//   Aakash (Savings, 4% APR): $832.00
//
// Attempting to withdraw 10000 from Meera's account:
//   Caught: Meera has insufficient funds
