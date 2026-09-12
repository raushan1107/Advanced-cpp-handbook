// Qt Widgets 101 — a window with a label and a button that updates it.
//
// This is the smallest possible Qt Widgets program that still shows the
// three things every widget-based Qt app needs: an application object that
// owns the event loop, a window built out of child widgets arranged by a
// layout, and one signal->slot connection reacting to a click.
//
// This file needs the Qt 6 SDK (Qt6::Widgets), not just plain g++ — see the
// "Before you start — install Qt" callout at the top of module9.html for the
// exact `pacman` package list if you're on this repo's MSYS2/UCRT64 setup.
//
// Build (from inside this folder, with CMakeLists.txt next to this file):
//   cmake -B build -S . -G Ninja        (or -G "MinGW Makefiles" without Ninja)
//   cmake --build build
// Run:
//   build\calc_window.exe   (Windows)      ./build/calc_window   (Linux/macOS)
//
// This exact file was built with Qt 6.10 (CMake + Ninja) before being placed
// in this repo — the window opened and the counter updated correctly.

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

int main(int argc, char *argv[]) {
    // QApplication(argc, argv)
    //   argc/argv - forwarded straight from main(); QApplication looks for
    //               its OWN command-line flags in here (e.g. -style) before
    //               your program ever sees the rest. Exactly one
    //               QApplication must exist per program, constructed before
    //               any widget.
    QApplication app(argc, argv);

    // A plain QWidget with no parent is a top-level window. It starts
    // invisible — nothing appears until window.show() runs near the bottom.
    QWidget window;
    window.setWindowTitle("Nimbus Click Counter");

    // new QVBoxLayout(&window)
    //   &window - the widget this layout will arrange children INSIDE of.
    //             Passing it to the constructor both creates the layout and
    //             immediately installs it as `window`'s layout in one call.
    // Every widget added below with layout->addWidget(...) gets stacked
    // vertically, top to bottom, and resized automatically if the window
    // is resized.
    auto *layout = new QVBoxLayout(&window);

    // new QLabel("Clicks: 0") / new QPushButton("Click me")
    //   the string argument - each widget's constructor takes its OWN kind
    //   of initial content: a QLabel's is the text it displays, a
    //   QPushButton's is the text drawn on the button face.
    // Both are heap-allocated with `new` and deliberately never `delete`d
    // by this code — see the ownership note below.
    auto *countLabel = new QLabel("Clicks: 0");
    auto *button = new QPushButton("Click me");

    // layout->addWidget(widget)
    //   widget - the child widget to place next in the layout's stacking
    //            order (here: label first, button second, so the label
    //            ends up above the button).
    // Ownership note: addWidget() doesn't just position the widget — it
    // reparents it to `window` (the widget the layout itself belongs to).
    // That means `window` is now responsible for destroying `countLabel`
    // and `button` when it is destroyed; this code never calls `delete` on
    // either pointer, and that is correct, not a leak.
    layout->addWidget(countLabel);
    layout->addWidget(button);

    int clicks = 0;

    // QObject::connect(sender, signal, slot)
    //   button                - the SENDER: the QObject that will emit the
    //                           signal below.
    //   &QPushButton::clicked - the SIGNAL being listened for: QPushButton
    //                           emits this automatically whenever the user
    //                           clicks it (press + release inside the
    //                           button's bounds).
    //   [&](){ ... }           - the SLOT: a lambda capturing `clicks` and
    //                           `countLabel` by reference, run every time
    //                           `clicked` fires. No explicit receiver
    //                           QObject is passed here since the lambda
    //                           doesn't need its lifetime tied to one.
    QObject::connect(button, &QPushButton::clicked, [&]() {
        clicks++;
        // QString("Clicks: %1").arg(clicks)
        //   "%1"   - a placeholder in the format string, filled in by the
        //            next .arg(...) call in the chain (Qt's version of
        //            sprintf-style formatting, but type-safe).
        //   clicks - the int substituted in place of %1.
        countLabel->setText(QString("Clicks: %1").arg(clicks));
    });

    // window.show()
    // Makes the window (and everything inside it) actually visible. Before
    // this line, `window` exists in memory but nothing has been drawn.
    window.show();

    // app.exec()
    // Starts the Qt event loop and BLOCKS here until the user closes the
    // window (or the app calls QApplication::quit()). Every click, resize,
    // and repaint from this point on is handled by callbacks — like the
    // lambda above — not by any code running top-to-bottom after this line.
    return app.exec();
}

// --------------------------------------------------------------------------
// Step-by-step execution trace (what actually happens, in order)
// --------------------------------------------------------------------------
// STEP 1  app is constructed; the event loop exists but has not started yet.
// STEP 2  window, layout, countLabel, button are constructed. clicks == 0.
//         countLabel's text is "Clicks: 0" (its constructor argument).
// STEP 3  addWidget() twice: layout now contains [countLabel, button], and
//         both widgets are reparented under `window`.
// STEP 4  connect() registers the lambda against button's clicked signal.
//         Nothing has fired yet — this just wires the connection.
// STEP 5  window.show() makes the window visible: "Clicks: 0" and a
//         "Click me" button are now on screen.
// STEP 6  app.exec() starts the event loop and blocks.
// STEP 7  User clicks the button once:
//           - Qt emits QPushButton::clicked.
//           - The connected lambda runs: clicks goes from 0 to 1.
//           - countLabel->setText(...) changes the label to "Clicks: 1".
//           - Qt schedules a repaint; the new text appears on screen.
// STEP 8  User clicks two more times: clicks becomes 2, then 3; the label
//         reads "Clicks: 2", then "Clicks: 3" — one lambda invocation per
//         click, each seeing (and incrementing) the SAME captured `clicks`
//         variable from STEP 2, since the lambda captured it by reference.
// STEP 9  User closes the window: app.exec() returns, main() returns, the
//         program exits. window's destructor runs, which also destroys
//         layout, countLabel, and button (see the ownership note above).
