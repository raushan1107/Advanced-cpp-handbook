// QML + C++ backend — the Calculator from ../2-signals-slots-calculator/,
// this time driven by a QML front end instead of Qt Widgets.
//
// Build (from inside this folder, with CMakeLists.txt next to this file):
//   cmake -B build -S . -G Ninja
//   cmake --build build
// Run (from THIS folder, so main.qml is found next to the .exe):
//   build\qml_calculator.exe   (Windows)   ./build/qml_calculator   (Linux/macOS)
//
// Built and run successfully with Qt 6.10 for this repo — no runtime
// binding/QML errors.

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QUrl>
#include <QObject>

// Identical to ../2-signals-slots-calculator/main.cpp's Calculator class —
// see that file for a fully commented walkthrough of Q_OBJECT, signals, and
// slots. The only thing new in THIS file is how this same C++ class gets
// exposed to QML, below.
class Calculator : public QObject {
    Q_OBJECT
public:
    explicit Calculator(QObject *parent = nullptr) : QObject(parent) {}
public slots:
    void add(double a, double b) { emit resultChanged(a + b); }
signals:
    void resultChanged(double result);
};

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    // Calculator calc;
    // A single instance, created in C++ and about to be handed to QML by
    // reference — QML does not construct its own copy.
    Calculator calc;

    QQmlApplicationEngine engine;

    // engine.rootContext()->setContextProperty("calc", &calc)
    //   rootContext() - the top-level QML context every loaded .qml file's
    //                   expressions can see.
    //   "calc"        - the NAME this C++ object will be known by inside
    //                   QML — main.qml refers to it simply as `calc`.
    //   &calc         - the actual C++ object being exposed; QML gets a
    //                   reference to this exact instance, not a copy.
    // This one call is the entire bridge: after it, main.qml can call
    // calc.add(...) and listen for calc's resultChanged signal as if
    // Calculator were a native QML type.
    engine.rootContext()->setContextProperty("calc", &calc);

    engine.load(QUrl::fromLocalFile("main.qml"));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}

#include "main.moc"

// --------------------------------------------------------------------------
// Step-by-step execution trace (clicking "Calculate" once, defaults 2 and 3)
// --------------------------------------------------------------------------
// STEP 1  calc is constructed in C++. setContextProperty makes it visible
//         to QML under the name "calc" BEFORE engine.load() runs, so
//         main.qml can reference `calc` from the moment it's parsed.
// STEP 2  main.qml loads: aField.text == "2", bField.text == "3",
//         result == 0 (QML's own `property real result: 0`).
// STEP 3  User clicks "Calculate": QML's `onClicked:` handler runs
//         `calc.add(parseFloat(aField.text), parseFloat(bField.text))` —
//         parseFloat("2") -> 2.0, parseFloat("3") -> 3.0.
// STEP 4  Execution jumps into C++: Calculator::add(2.0, 3.0) runs,
//         a=2.0, b=3.0, and `emit resultChanged(5.0)` fires.
// STEP 5  Back in QML: the `Connections { target: calc;
//         function onResultChanged(value) { result = value } }` block
//         receives the signal with value == 5.0, and sets QML's `result`
//         property to 5.0.
// STEP 6  The bottom Text item's binding `text: "Result: " + result`
//         re-evaluates automatically, now showing "Result: 5".
// STEP 7  Changing bField to "10" and clicking "Calculate" again repeats
//         STEPS 3-6 with b=10.0, ending with "Result: 12" — proving the
//         same C++ object and the same signal/slot wiring works from a
//         QML caller exactly as it did from the Qt Widgets caller in
//         ../2-signals-slots-calculator/.
