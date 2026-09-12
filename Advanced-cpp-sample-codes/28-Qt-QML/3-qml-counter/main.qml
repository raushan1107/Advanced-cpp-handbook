// main.qml — pure declarative UI, loaded by main.cpp in this same folder.
// Run alongside main.cpp; see main.cpp's header comment for build/run
// commands. QML has no separate compile step of its own — it is parsed at
// program startup by QQmlApplicationEngine.

import QtQuick
import QtQuick.Controls

// ApplicationWindow { ... }
// QML's top-level window item — the Qt Quick equivalent of a C++ QWidget
// used as a top-level window. Its properties below (visible, width, height,
// title) are set with `name: value` syntax instead of C++ setter calls.
ApplicationWindow {
    visible: true      // shown immediately once loaded (no engine.show() needed)
    width: 300
    height: 200
    title: "Nimbus QML Counter"

    // property int clicks: 0
    // Declares a NEW property named `clicks`, of type int, on this window,
    // initialized to 0. Any item below can read or write it by name, and
    // any expression that references it (see the Text item's `text:` below)
    // automatically re-evaluates whenever it changes — that automatic
    // re-evaluation is called a BINDING.
    property int clicks: 0

    Column {
        // anchors.centerIn: parent
        //   parent - QML's implicit reference to the item this one is
        //            nested inside (here, the ApplicationWindow itself).
        // Centers this Column inside its parent, both horizontally and
        // vertically — no manual x/y pixel math.
        anchors.centerIn: parent
        spacing: 12

        Text {
            // text: "Clicks: " + clicks
            // A BINDING, not a one-time assignment: this expression is
            // re-evaluated by the QML engine every time `clicks` changes,
            // so the displayed text always reflects the current count with
            // no explicit "update the label" code anywhere.
            text: "Clicks: " + clicks
            font.pixelSize: 20
        }

        Button {
            text: "Click me"
            // onClicked: clicks++
            // A SIGNAL HANDLER — QML's inline way of writing a slot right
            // where the signal is used, instead of a separate connect()
            // call. Every time this Button's built-in `clicked` signal
            // fires, this one-line handler runs: `clicks` increments by 1,
            // which in turn re-triggers the Text item's binding above.
            onClicked: clicks++
        }
    }
}
