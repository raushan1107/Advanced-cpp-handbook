// Structs — grouping related fields into one named type, plus a member
// function that can read them.
//
// Compile: g++ -std=c++17 1_Program1.cpp -o Program1
// Run:     Program1.exe   (Windows)   or   ./Program1   (Linux/macOS)
// Interaction: the program asks for first name, last name, age, and salary
// on the console — type each value and press Enter.

#include <iostream>

using namespace std;

// struct Person
// A struct groups several DIFFERENT pieces of data (a name, an age, a
// salary — not all the same type) under one name, so they can be passed
// around and referred to as a single unit (`p1` below) instead of four
// separate loose variables.
struct Person
{
    string first_name;
    string last_name;
    int age;
    float salary;

    // introduce()
    // No parameters — a member function reads this SAME object's own
    // fields directly (first_name, age) without needing them passed in,
    // since every call happens through a specific Person instance (p1.introduce()
    // below), which member functions can always see.
    void introduce() {
        cout << "Hi, my name is " << first_name << " and I am " << age << " years old." << endl;
    }

};

int main()

{
    // Person p1;
    // Declares one Person variable. Its string fields default to empty,
    // and age/salary are left uninitialized until the cin lines below fill
    // them in.
    Person p1;
    cout << "Enter first name: ";
    // cin >> p1.first_name
    //   p1.first_name - the member field being filled; cin reads one
    //                   whitespace-delimited token from the console into it
    //                   (so a first name containing a space would only
    //                   capture the first word — a limitation of >> with
    //                   strings, contrasted with getline() elsewhere in
    //                   this course).
    cin >> p1.first_name;

    cout << "Enter last name: ";
    cin >> p1.last_name;

    cout << "Enter age: ";
    // cin >> p1.age
    // Reads one token and parses it as an int; typing non-numeric text
    // here would leave p1.age unset and put cin into a fail state (not
    // handled in this simple version — see Module 4's exception handling
    // sample folder for input validation).
    cin >> p1.age;

    cout << "Enter salary: ";
    cin >> p1.salary;

    cout << "\nDisplaying Information." << endl;
    cout << "First Name: " << p1.first_name << endl;
    cout << "Last Name: " << p1.last_name << endl;
    cout << "Age: " << p1.age << endl;
    cout << "Salary: " << p1.salary << endl;

    // p1.introduce()
    // Calls the member function defined above, through THIS specific
    // Person object — introduce() reads p1's first_name and age because
    // it's being called ON p1, not because those names are global.
    p1.introduce();
    return 0;

}

// --------------------------------------------------------------------------
// Step-by-step execution trace (example run: "Ravi", "Kumar", 29, 55000.5)
// --------------------------------------------------------------------------
// STEP 1  Person p1 is declared; its fields are not yet meaningfully set.
// STEP 2  User types "Ravi" -> p1.first_name becomes "Ravi".
// STEP 3  User types "Kumar" -> p1.last_name becomes "Kumar".
// STEP 4  User types "29" -> p1.age becomes 29 (parsed as int).
// STEP 5  User types "55000.5" -> p1.salary becomes 55000.5 (parsed as
//         float).
// STEP 6  The four cout lines print each field back exactly as stored:
//         "First Name: Ravi", "Last Name: Kumar", "Age: 29",
//         "Salary: 55000.5".
// STEP 7  p1.introduce() runs, reading p1.first_name ("Ravi") and p1.age
//         (29) to print "Hi, my name is Ravi and I am 29 years old."
// STEP 8  main() returns 0; the program exits.
