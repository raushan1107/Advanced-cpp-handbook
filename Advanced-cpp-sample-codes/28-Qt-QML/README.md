# 28-Qt-QML — how to build and run every demo in this folder

This is the Module 9 (Day 6) sample-code path — see `module9.html` for the
full lesson these files support. Every subfolder here is a **separate,
self-contained project**: its own `main.cpp` (and, for the QML demos, its
own `main.qml`), plus its own `CMakeLists.txt`. None of them share a build —
you build and run each one independently, inside its own folder.

## 1. Install the Qt 6 SDK (one-time setup)

Everywhere else in this course, plain `g++ -std=c++17 file.cpp -o file` is
enough. Qt is different — it needs its own SDK (widgets, QML engine,
networking classes, and the `moc` code generator), not just a compiler.

**If you're on this repo's MSYS2/MinGW (UCRT64) toolchain**, open the
"MSYS2 UCRT64" shell and run:

```
pacman -S mingw-w64-ucrt-x86_64-qt6-base mingw-w64-ucrt-x86_64-qt6-declarative mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
```

This installs roughly 300 MB: `qt6-base` (Widgets, Gui, Core, Network),
`qt6-declarative` (QML/Qt Quick, including Qt Quick Controls), `cmake`, and
`ninja` (a fast build-file generator; CMake can also target plain
`"MinGW Makefiles"` if you'd rather skip Ninja).

**Otherwise**, the [Qt Online Installer](https://www.qt.io/download-qt-installer)
gives you the same SDK bundled with Qt Creator, if you prefer a full IDE
instead of the command line.

Every file in this folder was actually built (and, where it doesn't need a
click to prove it works, actually run) against Qt 6.10 installed exactly
this way, using CMake + Ninja, before being committed to this repo.

## 2. The build pattern every subfolder follows

From **inside** the specific subfolder you want to build (each one has its
own `CMakeLists.txt` sitting next to its `.cpp` file):

```
cmake -B build -S . -G Ninja
cmake --build build
```

(Drop `-G Ninja` — or swap it for `-G "MinGW Makefiles"` — if you didn't
install Ninja; CMake will pick a default generator for your platform.)

This produces the executable inside that subfolder's own `build/` directory.
Run it from there:

```
build\<name>.exe        (Windows)
./build/<name>           (Linux/macOS)
```

For the two QML subfolders (`3-qml-counter/`, `4-qml-calculator/`), run the
executable **from the subfolder itself** (or copy `main.qml` next to the
`.exe`) — the program loads its `.qml` file from disk by a relative path at
startup, it is not compiled into the binary.

## 3. What CMakeLists.txt is actually doing

Every `CMakeLists.txt` in this folder follows the same four lines, changing
only the target name and which Qt module(s) it needs:

```cmake
cmake_minimum_required(VERSION 3.16)
project(<name>)
set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS <Widgets|Quick QuickControls2|Network|...>)
add_executable(<name> <source files>.cpp)
target_link_libraries(<name> Qt6::<the same component(s)>)
```

- `CMAKE_AUTOMOC ON` — automatically runs Qt's `moc` (Meta-Object Compiler)
  on any class that declares `Q_OBJECT`, generating the plumbing `connect()`
  and `emit` need. You never invoke `moc` by hand.
- `find_package(Qt6 REQUIRED COMPONENTS ...)` — the component list tells
  CMake which piece of the Qt SDK this specific demo needs: `Widgets` for
  the widget-based demos, `Quick` + `QuickControls2` for the QML demos,
  `Network` for the networking demos (some demos, like the flagship
  Nimbus Fleet Console, need more than one at once).

## 4. Per-subfolder quick reference

| Subfolder | Needs | What you'll see |
|---|---|---|
| `1-widgets-click-counter/` | Widgets | A window with a label + button; clicking increments the label. |
| `2-signals-slots-calculator/` | Widgets | Two number fields, a "+" button, a result label. |
| `3-qml-counter/` | Quick, QuickControls2 | Same idea as folder 1, in pure QML (no C++ UI code). |
| `4-qml-calculator/` | Quick, QuickControls2 | Same idea as folder 2, QML front end calling a C++ `Calculator`. |
| `5-tcp-chat/` | Network | Two executables — `chat_server` and `chat_client` — build both from the one `CMakeLists.txt`, run the server first. |
| `6-udp-heartbeat/` | Network | A console app that broadcasts + prints one "agent-alive" line per second; run two copies to see them hear each other. |
| `7-shape-canvas/` | Widgets | Module 2's Shape hierarchy, rendered as a cyan circle + yellow rectangle instead of printed. |
| `8-nimbus-fleet-console/` | Widgets, Network | The flagship combined demo — a chat-style window; needs `5-tcp-chat/chat_server.exe` running first. |

Every `.cpp`/`.qml` file also carries its own header comment with the exact
build/run commands for that specific demo, plus a "step-by-step execution
trace" comment block at the bottom walking through what happens, in order,
when you actually run it.
