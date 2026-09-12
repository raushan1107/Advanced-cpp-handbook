// goto, continue, and break — three ways to jump control flow around
// inside a loop (or out of one) instead of letting it run top-to-bottom.
//
// Compile: g++ -std=c++17 6_for-jump-continue-break.cpp -o for-jump-continue-break
// Run:     for-jump-continue-break.exe   (Windows)   or   ./for-jump-continue-break   (Linux/macOS)
// Interaction: enter how many numbers you'll provide, then that many
// numbers (or one negative number to stop early).

#include <iostream>

using namespace std;

int main() {
    float num, average, sum = 0.0;
    int i, n;

    cout << "Maximum number of inputs: ";
    cin >> n;

    // for(i = 1; i <= n; ++i)
    //   i - declared OUTSIDE the for loop (not `for(int i = 1; ...)`) so
    //       its final value is still readable after the loop ends, at the
    //       `average = sum / (i - 1);` line below.
    for(i = 1; i <= n; ++i)
    {
        cout << "Enter n" << i << ": ";
        cin >> num;
        if(num < 0.0)
        {
           // Control of the program move to jump:
            // goto jump
            // Immediately jumps execution to the `jump:` LABEL below,
            // skipping the rest of THIS iteration, all remaining
            // iterations, and the loop's own exit check entirely — a much
            // blunter tool than `break` (which only exits the innermost
            // loop) since goto can jump to any labeled point in the same
            // function. Used sparingly in modern C++; shown here mainly
            // to contrast with the safer continue/break below.
            goto jump;
        }
        sum += num;
    }
jump:
    // average = sum / (i - 1)
    //   i - 1 - if the loop ran to completion, i is n+1 when the loop
    //           condition finally fails, so i-1 = n (the count of numbers
    //           actually summed). If `goto jump` fired early instead, i
    //           still holds whichever iteration it jumped OUT of, so i-1
    //           correctly counts only the numbers summed BEFORE the
    //           negative one that triggered the jump.
    average = sum / (i - 1);
    cout << "\nAverage = " << average;
    cout << "\nsum = " << sum;

    cout << "\nDemonstration of continue and break statements:\n";

    for (int i = 1; i <= 5; i++) {
        // condition to continue
        if (i == 2) {
            // continue
            // Skips the REST of this one iteration's body (the
            // `cout << i` below never runs for i==2) and jumps straight
            // to the loop's increment (`i++`) and condition check — the
            // loop itself keeps going, unlike break.
            continue;
        }
        // break condition

        if (i == 4) {

            // break
            // Exits the loop ENTIRELY right here — i never reaches 5 in
            // this run, and the loop's increment/condition are never
            // evaluated again.
            break;

        }

        cout << i << endl;

    }

return 0;

}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// Part 1 (goto) — example run: n=4, entering 10, 20, -5:
// STEP 1  i=1: user enters 10 (not negative) -> sum becomes 10.
// STEP 2  i=2: user enters 20 -> sum becomes 30.
// STEP 3  i=3: user enters -5 -> `num < 0.0` is true -> `goto jump` fires
//         immediately, skipping `sum += num` for this -5, and skipping
//         i=4 entirely.
// STEP 4  Execution resumes at the `jump:` label with i still equal to 3
//         (the value it held when goto fired). average = sum/(i-1) =
//         30/(3-1) = 30/2 = 15. Prints "Average = 15", "sum = 30".
//
// Part 2 (continue/break) — this part always runs the same way regardless
// of Part 1's input, since it's a fresh, independent loop with its own i:
// STEP 5  i=1: not 2, not 4 -> prints "1".
// STEP 6  i=2: `i==2` is true -> `continue` skips the print and the i==4
//         check, jumping straight to i++.
// STEP 7  i=3: not 2, not 4 -> prints "3".
// STEP 8  i=4: `i==2` is false, `i==4` is true -> `break` exits the loop
//         immediately; i never reaches 5.
// STEP 9  Final printed sequence for this part: 1, 3 (2 was skipped by
//         continue, 4 and 5 never printed because break exited first).
