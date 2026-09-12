// main.qml — QML front end for the C++ Calculator exposed as `calc` by
// main.cpp in this same folder (via setContextProperty). See main.cpp's
// header comment for build/run commands.

import QtQuick
import QtQuick.Controls

ApplicationWindow {
    visible: true
    width: 320
    height: 220
    title: "Nimbus QML Calculator"

    // property real result: 0
    // A QML-side property, separate from the C++ Calculator's internal
    // state — it exists purely to hold the last value QML received from
    // the resultChanged signal, so the Text item below has something to
    // bind to.
    property real result: 0

    // Connections { target: calc; function onResultChanged(value) {...} }
    //   target: calc          - which QObject's signals this block is
    //                           listening to; `calc` is the exact name
    //                           given to setContextProperty in main.cpp.
    //   function onResultChanged(value) { ... }
    //   value                  - the argument carried by Calculator's
    //                           resultChanged(double result) signal; QML's
    //                           handler function names its own parameter
    //                           `value` here (it does not have to match the
    //                           C++ signal's parameter name `result`).
    // This is Qt 6's syntax for handling a signal from an EXTERNAL object
    // inside QML — Button's built-in onClicked below doesn't need a
    // Connections block because it's a property already defined on Button
    // itself.
    Connections {
        target: calc
        function onResultChanged(value) { result = value }
    }

    Column {
        anchors.centerIn: parent
        spacing: 10

        Row {
            spacing: 8
            // id: aField / id: bField
            //   id - a QML-only identifier letting OTHER items in this file
            //        refer back to this one by name (aField.text below) —
            //        unrelated to a C++ variable name or a signal.
            TextField { id: aField; text: "2"; width: 60 }
            Text { text: "+"; font.pixelSize: 18 }
            TextField { id: bField; text: "3"; width: 60 }
        }

        Button {
            text: "Calculate"
            // onClicked: calc.add(parseFloat(aField.text), parseFloat(bField.text))
            //   aField.text / bField.text - the two TextFields' current
            //                               text, read by id.
            //   parseFloat(...)            - JavaScript's string-to-number
            //                               conversion (QML's expressions
            //                               are JavaScript); returns NaN
            //                               for unparsable text rather than
            //                               throwing.
            //   calc.add(a, b)              - calls straight into the C++
            //                               Calculator::add slot exposed by
            //                               main.cpp, as if it were a
            //                               native QML method.
            onClicked: calc.add(parseFloat(aField.text), parseFloat(bField.text))
        }

        Text { text: "Result: " + result; font.pixelSize: 18 }
    }
}
