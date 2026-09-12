# 29-WrapUp-MiniProjects — how to build and run

This is the Module 10 (Day 6) sample-code path — see `module10.html` for the
full lesson these files support. Unlike `28-Qt-QML/`, everything here uses
the **plain g++ toolchain** already used all course long — no Qt SDK, no
CMake needed. Each file is fully independent of the other two.

## Build and run

```
g++ -std=c++17 1_banking_system.cpp -o banking_system
g++ -std=c++17 2_library_system.cpp -o library_system
g++ -std=c++17 3_performance_debugging.cpp -o performance_debugging
```

Then run whichever executable you just built:

```
banking_system.exe              (Windows)
./banking_system                 (Linux/macOS)
```

(same pattern for `library_system` and `performance_debugging`).

## What each file does

- **1_banking_system.cpp** — an `Account`/`SavingsAccount` hierarchy, a
  custom `InsufficientFundsError` exception, and a `transfer()` function
  that withdraws before it deposits so a failed transfer never leaves the
  destination account credited. No files or extra setup needed — just
  compile and run.

- **2_library_system.cpp** — this module's flagship: a `Library` class with
  `find_if`-based borrow/return and file persistence. Running it creates
  (or overwrites) a `catalog.txt` file **in whatever directory you run the
  executable from** — delete that file between runs if you want to see the
  catalog start empty again, or leave it and re-run to see the program pick
  up exactly where the last run left off.

- **3_performance_debugging.cpp** — no files, no arguments; just run it.
  Prints two millisecond timings comparing `vector::push_back` with and
  without `reserve()`. The numbers will differ every run and on every
  machine — that's expected, see the file's own header comment for the
  `gprof`/Visual Studio Profiler workflow if you want a deeper breakdown
  than two hand-placed timers.

Every file also carries its own header comment (purpose + exact compile/run
commands) and a "step-by-step execution trace" comment block near the
bottom, walking through what the program's variables actually do, line by
line, for the specific run whose output is captured at the very end of the
file.
