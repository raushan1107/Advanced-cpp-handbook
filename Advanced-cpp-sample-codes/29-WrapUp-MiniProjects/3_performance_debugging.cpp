// Performance Debugging — Module 10's timing mini-project: measures the
// real, concrete cost of building a vector WITHOUT reserve() vs. WITH it.
//
// Plain g++ toolchain, no Qt needed.
// Compile: g++ -std=c++17 3_performance_debugging.cpp -o performance_debugging
// Run:     performance_debugging.exe   (Windows)   or   ./performance_debugging   (Linux/macOS)
//
// For a deeper, per-function breakdown instead of hand-timing two blocks:
//   gprof workflow -  g++ -std=c++17 -pg 3_performance_debugging.cpp -o performance_debugging
//                      then run it once (writes gmon.out), then
//                      gprof performance_debugging.exe gmon.out
//   MSVC / Visual Studio - Debug -> Performance Profiler -> CPU Usage.
//
// This exact file was compiled (no optimization flag, matching every other
// compile command in this course) and run for this repo — see the "Actual
// output" block at the bottom. Timings are inherently machine- and
// run-specific; yours will differ.

#include <iostream>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;

// buildWithoutReserve(n)
//   n - how many ints to push into the vector, one at a time, with NO
//       advance warning to the vector about how large it will eventually
//       need to be.
vector<int> buildWithoutReserve(int n) {
    vector<int> v;
    for (int i = 0; i < n; i++) v.push_back(i);
    return v;
}

// buildWithReserve(n)
//   n - same total element count as buildWithoutReserve, for a fair
//       comparison; the only difference is the v.reserve(n) call below.
vector<int> buildWithReserve(int n) {
    vector<int> v;
    // v.reserve(n)
    //   n - tells the vector "you will eventually hold at least n
    //       elements," letting it allocate that much capacity ONCE, up
    //       front, instead of guessing and reallocating (copying every
    //       existing element into new, larger memory) repeatedly as
    //       push_back calls arrive.
    v.reserve(n);
    for (int i = 0; i < n; i++) v.push_back(i);
    return v;
}

int main() {
    const int N = 2000000;

    // high_resolution_clock::now()
    // Takes no parameters — returns a time_point representing "right now,"
    // at whatever precision this platform's clock actually offers (often
    // nanoseconds). Two of these subtracted give a duration.
    auto t1 = high_resolution_clock::now();
    auto v1 = buildWithoutReserve(N);
    auto t2 = high_resolution_clock::now();
    auto v2 = buildWithReserve(N);
    auto t3 = high_resolution_clock::now();

    // duration<double, milli>
    //   double - the numeric type the elapsed time is stored as (so
    //            fractional milliseconds print, not just whole ticks).
    //   milli  - the unit: this duration is expressed in MILLISECONDS.
    // withoutReserve = t2 - t1
    //   Subtracting two time_points gives a duration; assigning it into a
    //   duration<double, milli> converts it into a plain double count of
    //   milliseconds, ready to print with .count().
    duration<double, milli> withoutReserve = t2 - t1;
    duration<double, milli> withReserve = t3 - t2;

    cout << "Without reserve(): " << withoutReserve.count() << " ms\n";
    cout << "With reserve():    " << withReserve.count() << " ms\n";
    cout << "Both vectors have size " << v1.size() << " and " << v2.size() << "\n";
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  t1 is captured, immediately before buildWithoutReserve(2000000)
//         starts.
// STEP 2  buildWithoutReserve runs its loop 2,000,000 times. Every time the
//         vector's internal capacity is exceeded, push_back triggers a
//         REALLOCATION: allocate a bigger buffer (typically ~1.5-2x the
//         old capacity), copy every existing element into it, free the old
//         buffer — this happens roughly log2(2000000) ≈ 21 times over the
//         whole loop, each one copying everything accumulated so far.
// STEP 3  t2 is captured right after v1 is fully built; t2 - t1 is the real
//         wall-clock cost of those ~21 reallocations plus 2,000,000
//         push_back calls.
// STEP 4  buildWithReserve(2000000) runs: v.reserve(2000000) allocates
//         enough capacity for all 2,000,000 elements in ONE allocation, up
//         front. The loop's 2,000,000 push_back calls now never trigger a
//         reallocation at all, since the capacity was already sufficient
//         from the start.
// STEP 5  t3 is captured; t3 - t2 measures only the cost of 2,000,000
//         push_back calls with zero reallocations — consistently smaller
//         than STEP 3's duration, since the expensive repeated-copying
//         work from STEP 2 simply never happens here.
// STEP 6  Both v1.size() and v2.size() print as 2000000 — the TWO vectors
//         hold identical final contents; only the cost of BUILDING them
//         differed, which is exactly the point being measured.
//
// --------------------------------------------------------------------------
// Actual output (your numbers will vary by machine and by run — timing is
// never perfectly repeatable; this is one real captured run, not a guess)
// --------------------------------------------------------------------------
// Without reserve(): 23.3903 ms
// With reserve():    9.0513 ms
// Both vectors have size 2000000 and 2000000
