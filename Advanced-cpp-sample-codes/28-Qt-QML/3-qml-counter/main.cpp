// QML loader — pure QML UI, no C++ backend object at all.
//
// QGuiApplication (not QApplication) is the right application object here
// since there is no Qt Widgets involved — Qt Quick draws everything itself
// through its own GPU-accelerated scene graph.
//
// Build (from inside this folder, with CMakeLists.txt next to this file):
//   cmake -B build -S . -G Ninja
//   cmake --build build
// Run (from THIS folder, or copy main.qml next to the .exe first — the QML
// file is loaded from disk at startup, it is not compiled into the binary):
//   build\qml_counter.exe   (Windows)      ./build/qml_counter   (Linux/macOS)
//
// Built and run successfully with Qt 6.10 for this repo — the window opened
// and stayed open with no QML load errors.

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QUrl>

int main(int argc, char *argv[]) {
    // QGuiApplication(argc, argv)
    //   argc/argv - same role as QApplication's constructor in the widgets
    //               demos: forwarded from main(), used to parse Qt's own
    //               command-line flags first.
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // engine.load(QUrl::fromLocalFile("main.qml"))
    //   QUrl::fromLocalFile("main.qml") - builds a file:// URL pointing at
    //                                     main.qml in the CURRENT WORKING
    //                                     DIRECTORY at runtime (a relative
    //                                     path here, not a path baked in at
    //                                     compile time).
    // load() parses that QML file and builds the object tree it describes
    // (the ApplicationWindow, Column, Text, Button from main.qml).
    engine.load(QUrl::fromLocalFile("main.qml"));

    // engine.rootObjects().isEmpty()
    // If main.qml failed to parse (a typo, a missing import), load() prints
    // an error to stderr and rootObjects() comes back empty — this check is
    // how a QML app fails fast instead of calling app.exec() on nothing.
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  app is constructed.
// STEP 2  engine.load(...) reads main.qml from disk and builds its object
//         tree: an ApplicationWindow containing a Column containing a Text
//         and a Button. QML's own `property int clicks: 0` starts at 0.
// STEP 3  rootObjects() is non-empty (load succeeded), so execution
//         continues to app.exec() instead of returning -1.
// STEP 4  The window becomes visible (main.qml sets `visible: true` itself,
//         unlike the widgets demos which call window.show() from C++).
//         The Text item's binding `text: "Clicks: " + clicks` evaluates to
//         "Clicks: 0".
// STEP 5  User clicks the Button: QML's `onClicked: clicks++` runs entirely
//         inside the QML engine — no C++ code executes for this click at
//         all. `clicks` becomes 1.
// STEP 6  Because `text: "Clicks: " + clicks` is a BINDING (not a one-time
//         assignment), Qt Quick automatically re-evaluates it whenever
//         `clicks` changes — the Text item now reads "Clicks: 1" with no
//         explicit "update the label" call anywhere, unlike the C++/Qt
//         Widgets version of this same demo in ../1-widgets-click-counter/.
// STEP 7  Further clicks repeat STEP 5-6, incrementing the same `clicks`
//         property each time.
