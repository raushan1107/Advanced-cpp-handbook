// Floating-point types — float / double / long double, and how many
// decimal digits of precision each one can actually display faithfully.
//
// Compile: g++ -std=c++17 2_modifiersdouble.cpp -o modifiersdouble
// Run:     modifiersdouble.exe   (Windows)   or   ./modifiersdouble   (Linux/macOS)

#include <iostream>

#include <iomanip> // for setprecision

using namespace std;

int main() {

    float f = 3.14159f;

    double d = 3.1415926535;

    long double ld = 3.141592653589793238L;

    cout << "float: " << f << endl;
    // cout << fixed << setprecision(10)
    //   fixed        - an I/O manipulator switching cout to always show a
    //                  fixed number of digits AFTER the decimal point
    //                  (rather than switching to scientific notation for
    //                  very large/small numbers).
    //   setprecision(10) - how many digits after the decimal point to
    //                  show for every floating-point value printed from
    //                  this line onward, until changed again.
    // Both manipulators are STICKY — they affect every subsequent cout
    // line in this program, not just the next one.
    cout << fixed << setprecision(10); // show 15 digits

    cout << "double: " << d << endl;
    cout << fixed << setprecision(15); // show 15 digits

    cout << "long double: " << ld << endl;

    return 0;

}


// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  f, d, ld are initialized. Note: f is declared as a float storing
//         a `double`-typed literal expression truncated by the `f` suffix
//         at the end of 3.14159f — without that suffix, 3.14159 defaults
//         to a double literal.
// STEP 2  "float: " << f prints using cout's DEFAULT precision (6
//         significant digits) since setprecision hasn't been called yet:
//         "float: 3.14159".
// STEP 3  fixed + setprecision(10) is applied; every float/double printed
//         AFTER this line shows exactly 10 digits after the decimal point.
// STEP 4  "double: " << d prints "double: 3.1415926535" — this double
//         actually stores that many meaningful digits, so nothing is lost.
// STEP 5  setprecision is changed again to 15 (fixed is already active and
//         doesn't need re-applying, though the code does so anyway,
//         harmlessly).
// STEP 6  "long double: " << ld prints "long double: 3.141592653589793"
//         — long double can hold MORE precision than double, which is why
//         this line uses a wider setprecision than STEP 3's double line.
//
// Try this: print `f` again AFTER the fixed/setprecision(10) line runs —
// you'll see float can't actually deliver 10 meaningful digits; it prints
// trailing digits that aren't part of the original value, since float's
// precision (~7 significant digits) is exhausted well before digit 10.
