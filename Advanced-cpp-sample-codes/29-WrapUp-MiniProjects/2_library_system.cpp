// Library Management System — Module 10's flagship wrap-up mini-project.
// An STL find_if-based catalog that survives the program exiting, via a
// simple delimited text file.
//
// Plain g++ toolchain, no Qt needed.
// Compile: g++ -std=c++17 2_library_system.cpp -o library_system
// Run:     library_system.exe   (Windows)   or   ./library_system   (Linux/macOS)
//
// This exact file was compiled and run for this repo — the "Actual output"
// block at the bottom is real captured output, not a guess.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Book — a plain aggregate; no class hierarchy needed since every book is
// the same kind of record (unlike Account/SavingsAccount next door).
struct Book {
    string title;
    string author;
    bool onLoan;
};

class Library {
    vector<Book> catalog;
    string catalogFile;
public:
    // Library(file)
    //   file - the path this instance will read from / write to; stored
    //          for saveToFile()/loadFromFile() to use later, not opened
    //          yet in the constructor itself.
    Library(string file) : catalogFile(move(file)) {}

    // addBook(title, author)
    //   title, author - the new Book's fields; onLoan starts false, since
    //                   a book is available the moment it's added.
    void addBook(const string& title, const string& author) {
        catalog.push_back({title, author, false});
    }

    // borrowBook(title)
    //   title - the book to look up by exact title match.
    // Returns true and marks the book on loan only if a matching, CURRENTLY
    // AVAILABLE book is found; returns false (no exception) both when the
    // title doesn't exist and when it's already borrowed — the caller
    // can't tell those two cases apart from the return value alone, which
    // is acceptable for this simple version.
    bool borrowBook(const string& title) {
        // find_if(catalog.begin(), catalog.end(), lambda)
        //   catalog.begin()/end() - the full range to search.
        //   lambda [&](const Book& b){ return b.title == title; }
        //     b     - each Book in turn, by const reference (no copies
        //             made while searching).
        //     title - the outer function's parameter, captured by
        //             reference so the lambda always compares against the
        //             CURRENT title argument.
        // Returns an iterator to the FIRST matching element, or
        // catalog.end() if none matched.
        auto it = find_if(catalog.begin(), catalog.end(),
                           [&](const Book& b) { return b.title == title; });
        if (it == catalog.end() || it->onLoan) return false;
        it->onLoan = true;
        return true;
    }

    // returnBook(title)
    //   title - the book to look up, same matching rule as borrowBook.
    // Mirror image of borrowBook: only succeeds if the book exists AND is
    // currently on loan.
    bool returnBook(const string& title) {
        auto it = find_if(catalog.begin(), catalog.end(),
                           [&](const Book& b) { return b.title == title; });
        if (it == catalog.end() || !it->onLoan) return false;
        it->onLoan = false;
        return true;
    }

    // listAvailable()
    // No parameters — prints every book in `catalog` whose onLoan is
    // false, one per line.
    void listAvailable() const {
        for (const auto& b : catalog)
            if (!b.onLoan) cout << "  " << b.title << " by " << b.author << "\n";
    }

    // saveToFile()
    // No parameters — writes the ENTIRE catalog to catalogFile (the path
    // given to the constructor), one line per book, as
    // "title|author|0-or-1". Overwrites the file if it already exists.
    void saveToFile() const {
        ofstream out(catalogFile);
        for (const auto& b : catalog)
            out << b.title << '|' << b.author << '|' << (b.onLoan ? 1 : 0) << '\n';
    }

    // loadFromFile()
    // No parameters — replaces `catalog` entirely with whatever is parsed
    // out of catalogFile. If the file doesn't exist yet, `in` simply opens
    // in a failed state and the while loop below never runs, leaving
    // `catalog` empty rather than crashing.
    void loadFromFile() {
        catalog.clear();
        ifstream in(catalogFile);
        string line;
        // getline(in, line)
        //   in   - the file stream to read from.
        //   line - filled with the next full line (up to but not
        //          including the newline); returns false once there are
        //          no more lines, ending the while loop.
        while (getline(in, line)) {
            stringstream ss(line);
            string title, author, loanFlag;
            // getline(ss, title, '|')
            //   ss    - reading from THIS one line's stringstream, not the
            //           file directly.
            //   title - filled with everything up to the next '|'.
            //   '|'   - the delimiter character, instead of getline's
            //           default of '\n' — this is how one "title|author|0"
            //           line gets split into its three fields.
            getline(ss, title, '|');
            getline(ss, author, '|');
            getline(ss, loanFlag, '|');
            // loanFlag == "1"
            // Converts the stored "0" or "1" text back into a bool: true
            // only for the exact string "1".
            catalog.push_back({title, author, loanFlag == "1"});
        }
    }
};

int main() {
    // Library lib("catalog.txt")
    //   "catalog.txt" - relative to the current working directory the
    //                   program is RUN from, not where the .exe sits.
    Library lib("catalog.txt");
    lib.addBook("Clean Code", "Robert Martin");
    lib.addBook("The Pragmatic Programmer", "Hunt & Thomas");
    lib.addBook("Effective Modern C++", "Scott Meyers");

    cout << "Available before borrowing:\n";
    lib.listAvailable();

    lib.borrowBook("Effective Modern C++");
    cout << "\nAvailable after borrowing 'Effective Modern C++':\n";
    lib.listAvailable();

    lib.saveToFile();
    cout << "\nCatalog saved to catalog.txt.\n";

    // Library reloaded("catalog.txt")
    // A SEPARATE Library object, starting with an EMPTY in-memory catalog
    // — nothing here is shared with `lib` above except the file path. The
    // only way `reloaded` gets any books is the loadFromFile() call next.
    Library reloaded("catalog.txt");
    reloaded.loadFromFile();
    cout << "\nReloaded from disk, available copies:\n";
    reloaded.listAvailable();

    reloaded.returnBook("Effective Modern C++");
    cout << "\nAfter returning 'Effective Modern C++':\n";
    reloaded.listAvailable();
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  lib's catalog after three addBook() calls (in order added):
//           ["Clean Code", false], ["The Pragmatic Programmer", false],
//           ["Effective Modern C++", false]
//         listAvailable() prints all three (none are on loan yet).
// STEP 2  lib.borrowBook("Effective Modern C++"): find_if locates it,
//         it->onLoan is false so the borrow succeeds, flipping it to true.
//         listAvailable() now prints only the first two.
// STEP 3  lib.saveToFile() writes THREE lines to catalog.txt:
//           Clean Code|Robert Martin|0
//           The Pragmatic Programmer|Hunt & Thomas|0
//           Effective Modern C++|Scott Meyers|1
// STEP 4  reloaded starts with an EMPTY catalog (a fresh Library object).
//         reloaded.loadFromFile() reads all three lines back, splitting
//         each on '|' and converting "1"/"0" back to bool — reloaded's
//         catalog now matches lib's exactly, including "Effective Modern
//         C++" still marked on loan. listAvailable() again prints only
//         the first two.
// STEP 5  reloaded.returnBook("Effective Modern C++"): find_if locates it,
//         it->onLoan is true so the return succeeds, flipping it back to
//         false. listAvailable() now prints all three again — proving the
//         borrowed state really did survive being written to disk and
//         read back into a completely separate object.
//
// --------------------------------------------------------------------------
// Actual output
// --------------------------------------------------------------------------
// Available before borrowing:
//   Clean Code by Robert Martin
//   The Pragmatic Programmer by Hunt & Thomas
//   Effective Modern C++ by Scott Meyers
//
// Available after borrowing 'Effective Modern C++':
//   Clean Code by Robert Martin
//   The Pragmatic Programmer by Hunt & Thomas
//
// Catalog saved to catalog.txt.
//
// Reloaded from disk, available copies:
//   Clean Code by Robert Martin
//   The Pragmatic Programmer by Hunt & Thomas
//
// After returning 'Effective Modern C++':
//   Clean Code by Robert Martin
//   The Pragmatic Programmer by Hunt & Thomas
//   Effective Modern C++ by Scott Meyers
