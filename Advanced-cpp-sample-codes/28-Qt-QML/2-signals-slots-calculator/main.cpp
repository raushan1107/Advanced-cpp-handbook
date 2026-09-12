// Signals & Slots — a custom QObject with its own signal, driving two widgets.
//
// Builds on 1-widgets-click-counter/: instead of only reacting to a widget's
// BUILT-IN signal (QPushButton::clicked), this file declares its OWN
// QObject subclass with its OWN signal, and connects it into the UI the
// same way. This is the pattern every non-trivial Qt program uses to keep
// business logic (Calculator) separate from the UI that displays it.
//
// Build (from inside this folder, with CMakeLists.txt next to this file):
//   cmake -B build -S . -G Ninja
//   cmake --build build
// Run:
//   build\calc_signals.exe   (Windows)      ./build/calc_signals   (Linux/macOS)
//
// Built and linked successfully with Qt 6.10 (CMake + Ninja) before being
// placed in this repo.

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

// Q_OBJECT
// A macro that must appear as the first line inside any class that declares
// its own signals or slots. It marks this class for Qt's moc (Meta-Object
// Compiler) — a code generator that runs BEFORE the real C++ compiler and
// writes the plumbing connect()/emit need. CMAKE_AUTOMOC (set in
// CMakeLists.txt) runs moc automatically; the #include "main.moc" line at
// the very bottom of this file is what pulls that generated code into this
// translation unit, since Calculator is defined here rather than in its own
// header.
class Calculator : public QObject {
    Q_OBJECT
public:
    // explicit Calculator(QObject *parent = nullptr)
    //   parent - the QObject that owns this one, in Qt's parent/child
    //            ownership tree (separate from the vtable-based C++
    //            inheritance above). nullptr (the default used below, via
    //            Calculator calc;) means "no owner — this object manages
    //            its own lifetime," which is correct for a stack-allocated
    //            object like the one main() creates.
    explicit Calculator(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    // add(a, b)
    //   a, b - the two operands to sum. Any regular member function CAN be
    //          a slot in modern Qt; the `public slots:` label is kept here
    //          for readability, marking this specifically as something
    //          meant to be connect()-ed to, not just called directly.
    void add(double a, double b) {
        // emit resultChanged(a + b)
        //   a + b - the computed sum, passed as the ONE argument
        //           resultChanged's signature declares below. `emit` is
        //           only a readability marker in modern Qt (it expands to
        //           nothing) — the real work is calling the signal like a
        //           function, which Qt intercepts and fans out to every
        //           connected slot.
        emit resultChanged(a + b);
    }

signals:
    // resultChanged(result)
    //   result - declared with no function body, since a signal is never
    //            implemented by hand; moc generates the implementation that
    //            calls every connected slot with this same argument.
    void resultChanged(double result);
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Nimbus Calculator");
    auto *outer = new QVBoxLayout(&window);

    auto *row = new QHBoxLayout();
    // new QLineEdit("2") / new QLineEdit("3")
    //   the string argument - each QLineEdit's initial, editable text.
    auto *inputA = new QLineEdit("2");
    auto *inputB = new QLineEdit("3");
    auto *addButton = new QPushButton("+");
    row->addWidget(inputA);
    row->addWidget(addButton);
    row->addWidget(inputB);
    outer->addLayout(row);

    auto *resultLabel = new QLabel("Result: (not calculated yet)");
    outer->addWidget(resultLabel);

    // Calculator calc;
    // Stack-allocated, parent == nullptr (see the constructor comment
    // above) — its lifetime is tied to main()'s scope, which is fine since
    // main() doesn't return until the whole app closes.
    Calculator calc;

    // connect(&calc, &Calculator::resultChanged, lambda)
    //   &calc                     - sender: this specific Calculator
    //                               instance.
    //   &Calculator::resultChanged - the custom signal from above.
    //   [&](double result){...}    - the slot: captures resultLabel by
    //                               reference and updates its text using
    //                               the value the signal carried.
    QObject::connect(&calc, &Calculator::resultChanged, [&](double result) {
        resultLabel->setText(QString("Result: %1").arg(result));
    });

    // connect(addButton, &QPushButton::clicked, lambda)
    // This lambda is the bridge between the UI and the Calculator: it reads
    // both text fields, converts them, and calls calc.add(...) — which is
    // what triggers the resultChanged signal connected just above.
    QObject::connect(addButton, &QPushButton::clicked, [&]() {
        // inputA->text().toDouble()
        //   text()     - the QLineEdit's current contents as a QString.
        //   toDouble() - parses that QString as a floating-point number
        //                (returns 0.0 if the text isn't a valid number —
        //                no exception is thrown).
        calc.add(inputA->text().toDouble(), inputB->text().toDouble());
    });

    window.show();
    return app.exec();
}

#include "main.moc"

// --------------------------------------------------------------------------
// Step-by-step execution trace (clicking "+" once, with the default 2 and 3)
// --------------------------------------------------------------------------
// STEP 1  Window opens. inputA->text() == "2", inputB->text() == "3".
//         resultLabel reads "Result: (not calculated yet)".
// STEP 2  User clicks "+": the clicked lambda runs.
//         inputA->text().toDouble() -> 2.0
//         inputB->text().toDouble() -> 3.0
// STEP 3  calc.add(2.0, 3.0) runs: inside it, a=2.0, b=3.0, so
//         emit resultChanged(5.0) fires.
// STEP 4  Qt looks up every slot connected to calc's resultChanged signal
//         and calls each one with result == 5.0. There is exactly one here:
//         the lambda that does resultLabel->setText("Result: 5").
// STEP 5  resultLabel now reads "Result: 5" on screen.
// STEP 6  User changes inputB to "10" and clicks "+" again:
//         inputA->text().toDouble() -> 2.0, inputB->text().toDouble() -> 10.0
//         calc.add(2.0, 10.0) -> emit resultChanged(12.0) -> label becomes
//         "Result: 12". Each click re-runs STEPS 2-5 independently; nothing
//         from the previous click is reused except the widgets themselves.
