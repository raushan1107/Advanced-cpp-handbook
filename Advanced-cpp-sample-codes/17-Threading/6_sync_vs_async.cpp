// Synchronous vs Asynchronous execution — with only ONE worker.
//
// Every other file in this folder (1_thread1.cpp, 2_thread-mutex.cpp,
// 3_deadlockProg.cpp, 4_threadpool.cpp) is about std::thread: handing work
// to MULTIPLE OS threads so it can run truly in parallel, on multiple CPU
// cores at the same time.
//
// This file is about a DIFFERENT idea that people often confuse with
// threading: asynchronous / non-blocking execution on a SINGLE worker.
// There is only one thread in this whole program. No std::thread is created
// anywhere below. The "asynchronous" half still runs on exactly one worker —
// it just gets smart about NOT letting any one task hog that worker for too
// long, so several tasks can all make steady progress instead of one task
// finishing completely before the next one is even allowed to start.
//
// Why this matters in the real world (the "Not Responding" window):
// A Windows GUI application has one special thread that owns the window and
// runs a "message loop" — a loop that keeps asking Windows "anything for me
// to do? redraw? move? minimize?" and handling it. If your code performs a
// long BLOCKING operation directly on that thread (reading a huge file,
// waiting on a slow network call, a tight loop with no pauses), the message
// loop cannot run while that operation is in progress. Windows notices the
// window has stopped answering and marks it "(Not Responding)" — you can't
// drag it, minimize it, or close it cleanly until the blocking call returns.
// This is exactly the "hang state" you're thinking of.
//
// The fix is never "add more threads" by itself — it's "stop blocking the
// thread that has to stay responsive." Sometimes that means truly handing
// work to a background std::thread (see 1_thread1.cpp). But often — and this
// is the part this file demonstrates — it just means breaking one long task
// into small steps and interleaving those steps with everything else that
// also needs a turn, all on the SAME single thread. That is what
// "asynchronous" means here: not "on another core," but "not blocking."
//
// PART 1 and PART 2 below use NO async keyword or library facility at all -
// on purpose, to show the raw CONCEPT first. PART 3 and PART 4, added
// afterward, show C++'s two REAL async tools: std::async (a library
// function, works in C++17) and co_await/co_return (actual C++20 language
// keywords). See the comment above each part for what it demonstrates and
// why it's different from the hand-rolled version above it.
//
// Compile (parts 1-3 only, no coroutines): g++ -std=c++17 6_sync_vs_async.cpp -o sync_vs_async
// Compile (all four parts, incl. coroutines): g++ -std=c++20 6_sync_vs_async.cpp -o sync_vs_async
// Run:      sync_vs_async.exe   (Windows)   or   ./sync_vs_async   (Linux/macOS)
// (Also builds as a normal MSVC console app in Visual Studio — nothing here
// is compiler- or platform-specific. Compiled with -std=c++17, PART 4 is
// skipped automatically via #if __cplusplus >= 202002L below and the
// program still builds and runs PARTS 1-3 normally.)

#include <iostream>   // std::cout - prints text to the console
#include <chrono>     // std::chrono::milliseconds - a strongly-typed "duration" value
#include <thread>     // std::this_thread::sleep_for - pause the CURRENT thread (no new thread created)
#include <future>     // std::async, std::future, std::launch - PART 3's real async facility

using namespace std;

// ---------------------------------------------------------------------
// PART 1: SYNCHRONOUS (blocking) version
// ---------------------------------------------------------------------

// simulateLongTask_blocking(taskName, totalSteps, msPerStep)
//   taskName    - text printed before each progress line, so the console
//                 output makes clear which task is running.
//   totalSteps  - how many chunks the "work" is divided into, purely for
//                 printing a percentage; the function does not return until
//                 EVERY step is done.
//   msPerStep   - how many milliseconds to sleep per step. sleep_for is a
//                 stand-in for any slow operation — reading a big file,
//                 waiting on a database, waiting on a network reply. The
//                 real operation would block the calling thread the exact
//                 same way this sleep does.
//
// Because this function contains its own loop and does not return control
// to main() until it is completely finished, the calling thread can do
// NOTHING else — including printing a "heartbeat" message — while this
// function is running. That blocked-until-fully-done behaviour is exactly
// what "synchronous" means.
void simulateLongTask_blocking(const string& taskName, int totalSteps, int msPerStep) {
    for (int step = 1; step <= totalSteps; ++step) {
        // --- Added explanation: this_thread::sleep_for(duration) ----------------
        // Generic syntax:  std::this_thread::sleep_for( <chrono duration> )
        //   duration - parameter #1 (only parameter): a std::chrono duration
        //              value. Here it is chrono::milliseconds(msPerStep),
        //              built from the msPerStep parameter above, meaning
        //              "pause THIS thread for msPerStep milliseconds."
        this_thread::sleep_for(chrono::milliseconds(msPerStep));
        int percent = step * 100 / totalSteps;
        cout << "  [" << taskName << "] " << percent << "% complete\n";
    }
}

void runSynchronousDemo() {
    cout << "\n=== SYNCHRONOUS DEMO (one task must finish before ANYTHING else happens) ===\n";
    cout << "  [Heartbeat] Program just started. Everything is responsive so far...\n";

    // This call does not return for ~3 seconds. During those 3 seconds the
    // single thread this program has is entirely inside this function - it
    // is physically impossible for any other line of code (a heartbeat
    // print, a keypress check, a window repaint) to run in the meantime.
    // --- Added explanation: simulateLongTask_blocking(taskName, totalSteps, msPerStep)
    // Generic syntax:  simulateLongTask_blocking( string taskName, int totalSteps, int msPerStep )
    //   taskName ("Download") - parameter #1: label printed on every
    //                           progress line.
    //   totalSteps (6)         - parameter #2: how many sleep+print steps
    //                           the loop above performs before returning.
    //   msPerStep (500)        - parameter #3: milliseconds slept per step,
    //                           so total blocking time here is 6 * 500ms =
    //                           3000ms (~3 seconds).
    simulateLongTask_blocking("Download", /*totalSteps=*/6, /*msPerStep=*/500);

    cout << "  [Heartbeat] Task finished - only NOW can the program do anything else.\n";
    cout << "=== end of synchronous demo ===\n";
}

// ---------------------------------------------------------------------
// PART 2: ASYNCHRONOUS (cooperative, single-worker) version
// ---------------------------------------------------------------------

// A "cooperative task" does not run to completion in one call. Instead it
// exposes a step() method that does one SMALL slice of work and then
// returns immediately, reporting whether it still has more work left.
// Something else (the loop in runAsynchronousDemo, below) decides when each
// task gets its next turn. This is the same core idea behind JavaScript's
// async/await and C++20 coroutines, built here with nothing but a loop and
// a counter so it works in plain C++17 on any compiler.
struct CooperativeTask {
    string name;          // printed before each progress line
    int stepsRemaining;   // how many more step() calls this task needs
    int totalSteps;       // stepsRemaining's starting value, kept to compute %
    int msPerStep;        // how long ONE slice of work takes to simulate

    // --- Added explanation: CooperativeTask(taskName, steps, msPerStepIn) constructor
    // Generic syntax:  CooperativeTask variableName( string taskName, int steps, int msPerStepIn )
    //   taskName    - parameter #1: label printed on this task's progress
    //                 lines (stored into member `name`).
    //   steps       - parameter #2: total number of step() calls this task
    //                 needs to finish (stored into BOTH `stepsRemaining`,
    //                 which counts down, and `totalSteps`, which stays fixed
    //                 so percentages can be computed later).
    //   msPerStepIn - parameter #3: how many milliseconds ONE step() call
    //                 sleeps for (stored into member `msPerStep`).
    CooperativeTask(string taskName, int steps, int msPerStepIn)
        : name(std::move(taskName)), stepsRemaining(steps),
          totalSteps(steps), msPerStep(msPerStepIn) {}
    // can we write above code without move semantics like below?
    //
    // CooperativeTask(string taskName, int steps, int msPerStepIn)
    //     : name(taskName), stepsRemaining(steps),
    //       totalSteps(steps), msPerStep(msPerStepIn) {}
    // step() - do ONE small slice of this task's work, then return.
    // Return value: true  -> this task still has more steps left (give it
    //                        another turn later).
    //               false -> this task is completely finished.
    // --- Added explanation: step() ---------------------------------------------
    // Generic syntax:  taskObj.step()
    //   (no parameters) - runs ONE small slice of work (one sleep +
    //   progress print), then returns whether more slices remain.
    bool step() {
        if (stepsRemaining <= 0) return false;

        // Same sleep_for(duration) pattern explained above: pauses this
        // (single, shared) thread for msPerStep milliseconds - just a much
        // SHORTER pause per call than the blocking version's single big
        // sleep, which is what lets control return to the caller quickly.
        this_thread::sleep_for(chrono::milliseconds(msPerStep));
        --stepsRemaining;
        int percent = (totalSteps - stepsRemaining) * 100 / totalSteps;
        cout << "  [" << name << "] " << percent << "% complete\n";

        return stepsRemaining > 0;
    }
};

void runAsynchronousDemo() {
    cout << "\n=== ASYNCHRONOUS DEMO (one worker, but it keeps switching between tasks) ===\n";

    // Same total amount of "work" as the synchronous demo (6 slow steps),
    // PLUS a second task representing "the rest of the program staying
    // responsive" - a heartbeat that also needs regular turns.
    // --- Added explanation: CooperativeTask(taskName, steps, msPerStep) --------
    // Same generic constructor syntax explained above the struct definition:
    // parameter #1 = display name, parameter #2 = total steps, parameter #3 =
    // milliseconds per step. Both tasks here get 6 steps of 80ms each (total
    // "work" of 480ms per task, same 6-step shape as the blocking demo, just
    // sliced into smaller pieces and interleaved below instead of run whole).
    CooperativeTask download("Download",  /*steps=*/6, /*msPerStep=*/80);
    CooperativeTask heartbeat("Heartbeat", /*steps=*/6, /*msPerStep=*/80);

    bool downloadActive  = true;
    bool heartbeatActive = true;

    // The cooperative scheduler: a plain while loop, still just ONE thread.
    // Each pass gives Download a small turn, then gives Heartbeat a small
    // turn, then loops back. Neither task is allowed to run for long enough
    // at once to make the program look frozen - control keeps coming back
    // to this loop, which is free to hand the next slice to whichever task
    // still needs one. This is "context switching" done entirely by
    // ordinary function calls, with no operating system thread involved.
    // --- Added explanation: download.step() / heartbeat.step() -----------------
    // Generic syntax:  taskObj.step()  (no parameters - see struct above)
    //   Each call runs exactly one 80ms slice of that task and returns
    //   true/false for whether it still has steps left. Re-assigning
    //   downloadActive/heartbeatActive to that return value is what lets the
    //   `while` condition eventually become false for a task that's done,
    //   so it stops being called while the other one keeps going.
    while (downloadActive || heartbeatActive) {
        if (downloadActive)  downloadActive  = download.step();
        if (heartbeatActive) heartbeatActive = heartbeat.step();
    }

    cout << "  Both tasks finished - and notice the two names were interleaved\n";
    cout << "  the whole time above, instead of Download finishing completely first.\n";
    cout << "=== end of asynchronous demo ===\n";
}

// ---------------------------------------------------------------------
// PART 3: std::async / std::future - C++'s REAL library-level async tool
// ---------------------------------------------------------------------
//
// PART 2 above faked "asynchronous" using nothing but a struct, a counter,
// and a while loop - deliberately zero library help, to show the concept
// bare. C++ has no "async"/"await" language KEYWORDS the way JavaScript or
// C# do, but the standard library gives you std::async, declared in
// <future> (included above). Calling async(policy, fn, args...) starts
// running fn - with std::launch::async, on a NEW background std::thread,
// which is a real difference from PART 2's "only one thread total" claim
// - and immediately hands back a future<ReturnType>: a handle to a result
// that may not exist yet. You keep doing other work, and later call
// .get() on that handle to block until the result is ready and collect
// it. That "start it, do something else, then collect the answer" shape
// is the closest real C++ cousin of `await`.
//
// --- Added explanation: downloadFile_computesTotalBytes(totalSteps, msPerStep)
// Generic syntax:  int downloadFile_computesTotalBytes( int totalSteps, int msPerStep )
//   totalSteps - parameter #1: how many sleep+print steps to run before
//                returning, same idea as PART 1/2's totalSteps.
//   msPerStep  - parameter #2: milliseconds slept per step.
//   Return value: a fabricated "bytes downloaded" total, standing in for
//   any real result a background task might compute and hand back.
int downloadFile_computesTotalBytes(int totalSteps, int msPerStep) {
    int totalBytes = 0;
    for (int step = 1; step <= totalSteps; ++step) {
        this_thread::sleep_for(chrono::milliseconds(msPerStep));
        totalBytes += 1024;
        cout << "  [std::async Download] step " << step << " complete\n";
    }
    return totalBytes;
}

void runStdAsyncDemo() {
    cout << "\n=== PART 3: std::async DEMO (real library async - runs on a helper thread) ===\n";

    // --- Added explanation: async(policy, fn, args...) --------------------
    // Generic syntax:  std::async( std::launch policy, Function fn, Args... args )
    //   launch::async (policy)     - forces fn to start running immediately
    //                                on its own new thread. (The other
    //                                option, launch::deferred, would NOT
    //                                start fn now - it would wait until
    //                                .get()/.wait() is called and then run
    //                                fn on the CALLING thread, which is
    //                                lazy, not concurrent.)
    //   downloadFile_computesTotalBytes (fn) - the function to run.
    //   4, 150 (args...)           - forwarded through as fn's own
    //                                totalSteps/msPerStep parameters.
    // Return value: future<int> - a handle to an int that may not exist
    // yet. This line returns almost instantly; it does NOT wait for the
    // 4 steps below to finish.
    future<int> downloadFuture = async(launch::async, downloadFile_computesTotalBytes, /*totalSteps=*/4, /*msPerStep=*/150);

    // Meanwhile the CALLING thread (main) is free to keep working - this
    // is the entire point of async: the async(...) call above did not
    // block, so this loop and the background download genuinely overlap.
    for (int i = 1; i <= 3; ++i) {
        cout << "  [Main thread] still doing other work... (" << i << ")\n";
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    // --- Added explanation: downloadFuture.get() ---------------------------
    // Generic syntax:  futureObj.get()
    //   (no parameters) - this is the moment we finally choose to WAIT for
    //   the result. If the background work isn't done yet, THIS call
    //   blocks until it is; if it already finished, it returns right away.
    //   A given future can only be get() once.
    int bytes = downloadFuture.get();
    cout << "  [Main thread] download finished, got " << bytes << " bytes back via future.get()\n";
    cout << "=== end of std::async demo ===\n";
}

#if __cplusplus >= 202002L
#include <coroutine>

// ---------------------------------------------------------------------
// PART 4: C++20 coroutines - co_await / co_return are REAL keywords
// ---------------------------------------------------------------------
//
// This is the only part of this whole file with an actual async KEYWORD
// in the language sense: co_await and co_return (co_yield exists too but
// isn't used here). A coroutine is a function whose body can be paused at
// a co_await point and resumed later while keeping all of its local state
// alive in between - exactly what CooperativeTask::step() in PART 2 faked
// by hand, using a `stepsRemaining` struct field as a stand-in for "where
// was I." Here the compiler generates that bookkeeping for you.
//
// A minimal coroutine still needs a small piece of required plumbing: a
// nested `promise_type` that tells the compiler how to build the
// coroutine's return object and what to do when it starts, finishes, or
// throws. There is no scheduler/event-loop here - a real async framework
// (a networking library, Boost.Asio, etc.) would add one. This is
// deliberately the smallest possible co_await example: just enough to show
// suspend/resume mechanics, driven by the same kind of while-loop scheduler
// PART 2 already used.
struct Task {
    struct promise_type {
        Task get_return_object() { return Task{ coroutine_handle<promise_type>::from_promise(*this) }; }
        suspend_always initial_suspend() { return {}; }
        suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    coroutine_handle<promise_type> handle;

    explicit Task(coroutine_handle<promise_type> h) : handle(h) {}
    ~Task() { if (handle) handle.destroy(); }

    // resume() steps the coroutine forward to its next co_await (or to
    // co_return if there isn't one) - the same job CooperativeTask::step()
    // did in PART 2, except the compiler tracks "which step am I on," not us.
    // Return value: true if the coroutine has more work left, false if done.
    bool resume() {
        if (!handle.done()) handle.resume();
        return !handle.done();
    }
};

// A trivial awaiter: always suspends, does nothing special on resume -
// just enough to make `co_await SimpleAwaiter{}` legal. A real awaiter
// (e.g. "awaiting a network read") would use await_suspend to register a
// callback and only let the coroutine resume once data is actually ready.
struct SimpleAwaiter {
    bool await_ready() { return false; }
    void await_suspend(coroutine_handle<>) {}
    void await_resume() {}
};

// --- Added explanation: downloadCoroutine(taskName, totalSteps, msPerStep)
// Generic syntax:  Task downloadCoroutine( string taskName, int totalSteps, int msPerStep )
//   taskName   - parameter #1: label printed on this task's progress lines.
//   totalSteps - parameter #2: how many sleep+print+co_await cycles to run.
//   msPerStep  - parameter #3: milliseconds slept per step.
// This LOOKS like an ordinary function, but the co_await inside its body
// makes it a coroutine: calling it does NOT execute this code top-to-bottom
// immediately. It returns a Task, already suspended (initial_suspend), and
// each call to Task::resume() runs it forward to the next co_await.
Task downloadCoroutine(string taskName, int totalSteps, int msPerStep) {
    for (int step = 1; step <= totalSteps; ++step) {
        this_thread::sleep_for(chrono::milliseconds(msPerStep));
        int percent = step * 100 / totalSteps;
        cout << "  [" << taskName << "] " << percent << "% complete\n";
        co_await SimpleAwaiter{};   // <-- suspend point: control returns to whoever called resume()
    }
}

void runCoroutineDemo() {
    cout << "\n=== PART 4: C++20 coroutine DEMO (co_await is a real language keyword) ===\n";

    Task download  = downloadCoroutine("Download",  /*totalSteps=*/6, /*msPerStep=*/80);
    Task heartbeat = downloadCoroutine("Heartbeat", /*totalSteps=*/6, /*msPerStep=*/80);

    bool downloadMore  = true;
    bool heartbeatMore = true;

    // Same shape as PART 2's scheduler loop, on purpose: give each
    // coroutine one small turn, then loop back. The difference is that
    // "one turn" here means "run until the next co_await," which the
    // compiler tracks, instead of "run one step() call," which PART 2's
    // hand-written struct tracked.
    while (downloadMore || heartbeatMore) {
        if (downloadMore)  downloadMore  = download.resume();
        if (heartbeatMore) heartbeatMore = heartbeat.resume();
    }

    cout << "  Notice this driving while-loop is nearly identical to PART 2's -\n";
    cout << "  coroutines give you that same cooperative-switching pattern with\n";
    cout << "  compiler-generated state instead of a hand-written struct.\n";
    cout << "=== end of coroutine demo ===\n";
}
#endif // __cplusplus >= 202002L

int main() {
    // --- Added explanation: runSynchronousDemo() / runAsynchronousDemo() -------
    // Generic syntax:  runSynchronousDemo()  and  runAsynchronousDemo()
    //   (no parameters, either function) - each runs its whole demo to
    //   completion on the single thread this program has, one after the
    //   other (runAsynchronousDemo does not start until
    //   runSynchronousDemo has fully returned).
    runSynchronousDemo();
    runAsynchronousDemo();
    // runStdAsyncDemo();
// #if __cplusplus >= 202002L
//     runCoroutineDemo();
// #else
//     cout << "\n(Skipping PART 4 - coroutine demo needs -std=c++20 or later.)\n";
// #endif

//     cout << "\nCompare the console blocks above:\n";
//     cout << "  PART 1 (blocking)    : all [Download] lines print together, then [Heartbeat] runs once at the end.\n";
//     cout << "  PART 2 (cooperative) : [Download] and [Heartbeat] interleave - one thread, hand-rolled scheduling, no keyword.\n";
//     cout << "  PART 3 (std::async)  : [Main thread] work overlaps a REAL background thread; .get() is where we finally wait.\n";
// #if __cplusplus >= 202002L
//     cout << "  PART 4 (coroutine)   : same interleaving as PART 2, but co_await/co_return are actual C++20 keywords.\n";
// #endif
//     cout << "  Takeaway: \"asynchronous\" is about NOT blocking while waiting, not about how many\n";
//     cout << "  threads are used - PART 2 and PART 4 use one thread, PART 3 uses two.\n";
}

// ============================================================================
// Added: STEP-BY-STEP EXECUTION FLOW (workflow) for this file
// ============================================================================
// #1  main() calls runSynchronousDemo() first.
// #2  Inside runSynchronousDemo():
//       #2a  prints the "=== SYNCHRONOUS DEMO ===" header and the first
//            "[Heartbeat] Program just started..." line.
//       #2b  calls simulateLongTask_blocking("Download", 6, 500). This ONE
//            call does not return until it has looped 6 times, sleeping
//            500ms and printing a "[Download] N% complete" line each time -
//            a full 3 seconds pass with NOTHING ELSE able to run, because
//            there is only one thread and it is stuck inside this call.
//       #2c  only after all 6 [Download] lines have printed does control
//            return to runSynchronousDemo(), which prints the second
//            "[Heartbeat]" line and the "end of synchronous demo" line.
// #3  main() calls runAsynchronousDemo() next (runSynchronousDemo has fully
//     finished and returned by now).
// #4  Inside runAsynchronousDemo():
//       #4a  prints the "=== ASYNCHRONOUS DEMO ===" header.
//       #4b  constructs `download` (6 steps, 80ms each) and `heartbeat`
//            (6 steps, 80ms each); both start with stepsRemaining = 6.
//       #4c  downloadActive and heartbeatActive both start true.
//       #4d  enters the while loop. Pass 1: download.step() runs (sleeps
//            80ms, prints "[Download] 17% complete", stepsRemaining -> 5,
//            returns true so downloadActive stays true); then
//            heartbeat.step() runs the same way for Heartbeat
//            ("[Heartbeat] 17% complete", stepsRemaining -> 5).
//       #4e  pass 2 through 6 repeat #4d, each time the OTHER task's step()
//            is called right after the first, so the printed lines
//            physically interleave: [Download] then [Heartbeat], pass after
//            pass, instead of one task's 6 lines all together.
//       #4f  after pass 6, both stepsRemaining reach 0, so both step() calls
//            return false, downloadActive and heartbeatActive both become
//            false, and the `while (downloadActive || heartbeatActive)`
//            condition becomes false, ending the loop.
//       #4g  prints the two "Both tasks finished..." lines and
//            "end of asynchronous demo".
// #5  Control returns to main(), which prints the final "Compare the two
//     console blocks above" summary lines and the program ends (falls off
//     the end of main(), which is equivalent to `return 0;`).
// #6  The key takeaway visible in the OUTPUT ORDER itself: in step #2 all 6
//     [Download] lines appear together, THEN [Heartbeat] runs; in step #4
//     [Download] and [Heartbeat] lines alternate the whole time - yet BOTH
//     demos used exactly one thread throughout. The difference is entirely
//     in how the work was divided (one huge blocking call vs. many small
//     step() calls interleaved by a scheduling loop), not in how many
//     threads did the work.
// ============================================================================



