// Shape Drawing (Qt GUI) — Module 2's Shape/Circle/Rectangle hierarchy,
// given a draw(QPainter&) method and actually rendered instead of only
// having its area() printed to a console.
//
// This is Module 10's "Shape Drawing" mini-project. Build (from inside this
// folder, with CMakeLists.txt next to this file):
//   cmake -B build -S . -G Ninja
//   cmake --build build
// Run:
//   build\shape_canvas.exe   (Windows)      ./build/shape_canvas   (Linux/macOS)
//
// Built successfully with Qt 6.10 for this repo; the window opened showing
// both shapes with no runtime error.

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <memory>
#include <vector>
using namespace std;

// Shape / Circle / RectangleShape
// The exact same polymorphic pattern as Module 2's and Module 8's Shape
// hierarchies: a pure-virtual base, two concrete subclasses, called through
// a base-class pointer. What's new here is the SECOND pure-virtual method,
// draw(), sitting right next to the familiar area().
struct Shape {
    virtual ~Shape() {}
    virtual double area() const = 0;
    // draw(QPainter&)
    //   painter - the SAME QPainter instance every shape in the canvas
    //             draws with (see ShapeCanvas::paintEvent below); passed
    //             by reference so no shape ever owns or copies it.
    virtual void draw(QPainter &painter) const = 0;
};

struct Circle : Shape {
    // x, y, radius - center position and radius, in the widget's own pixel
    //                coordinate space (0,0 is the widget's top-left).
    int x, y, radius;
    Circle(int x_, int y_, int r) : x(x_), y(y_), radius(r) {}
    double area() const override { return 3.14159 * radius * radius; }
    void draw(QPainter &painter) const override {
        // painter.setBrush(Qt::cyan)
        //   Qt::cyan - one of Qt's predefined QColor constants; sets the
        //              FILL color used by the next draw* call.
        painter.setBrush(Qt::cyan);
        // painter.drawEllipse(QPoint(x, y), radius, radius)
        //   QPoint(x, y) - the ellipse's center.
        //   radius, radius - the horizontal and vertical radii; passing
        //              the same value for both draws a perfect circle
        //              (an ellipse with different values would draw an
        //              oval).
        painter.drawEllipse(QPoint(x, y), radius, radius);
    }
};

struct RectangleShape : Shape {
    // x, y - top-left corner; w, h - width and height, all in pixels.
    int x, y, w, h;
    RectangleShape(int x_, int y_, int w_, int h_) : x(x_), y(y_), w(w_), h(h_) {}
    double area() const override { return w * h; }
    void draw(QPainter &painter) const override {
        painter.setBrush(Qt::yellow);
        // painter.drawRect(x, y, w, h)
        //   x, y - top-left corner (matches the constructor arguments
        //          exactly — no coordinate conversion needed).
        //   w, h - width and height.
        painter.drawRect(x, y, w, h);
    }
};

class ShapeCanvas : public QWidget {
public:
    ShapeCanvas() {
        // make_unique<Circle>(80, 80, 50)
        //   80, 80 - center at pixel (80, 80).
        //   50     - radius 50 pixels.
        shapes.push_back(make_unique<Circle>(80, 80, 50));
        // make_unique<RectangleShape>(180, 40, 100, 80)
        //   180, 40  - top-left corner at pixel (180, 40) — placed to the
        //              right of the circle so the two shapes don't overlap.
        //   100, 80  - 100 pixels wide, 80 pixels tall.
        shapes.push_back(make_unique<RectangleShape>(180, 40, 100, 80));
        setWindowTitle("Nimbus Shape Canvas");
        resize(320, 200);
    }
protected:
    // paintEvent(QPaintEvent*) override
    // Qt calls this automatically whenever the widget needs to (re)draw —
    // first shown, resized, or uncovered by another window. This code
    // never calls paintEvent() itself.
    void paintEvent(QPaintEvent *) override {
        // QPainter painter(this)
        //   this - constructing a QPainter "on" a widget, inside its OWN
        //          paintEvent, is what makes every subsequent draw* call
        //          land on THIS widget's on-screen surface.
        QPainter painter(this);
        // painter.setRenderHint(QPainter::Antialiasing)
        //   QPainter::Antialiasing - smooths curved/diagonal edges (most
        //                            visible on the circle) instead of
        //                            leaving them jagged.
        painter.setRenderHint(QPainter::Antialiasing);
        // for (const auto &s : shapes) s->draw(painter);
        // The same polymorphic loop pattern as Module 2/8: iterating over
        // base-class pointers and calling one virtual method per element —
        // ShapeCanvas never needs to know it's drawing one Circle and one
        // RectangleShape specifically.
        for (const auto &s : shapes) s->draw(painter);
    }
private:
    vector<unique_ptr<Shape>> shapes;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ShapeCanvas canvas;
    canvas.show();
    return app.exec();
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  ShapeCanvas's constructor runs: shapes ends up holding exactly
//         two elements — a Circle at (80,80) r=50, then a RectangleShape
//         at (180,40) 100x80. Neither has been drawn yet.
// STEP 2  canvas.show() makes the window visible; Qt immediately schedules
//         a first paintEvent since the widget has never been painted.
// STEP 3  paintEvent runs: a QPainter is constructed on `this` (the
//         canvas), antialiasing is turned on, then the for loop calls
//         shapes[0]->draw(painter) followed by shapes[1]->draw(painter).
// STEP 4  shapes[0]->draw(painter) is a virtual call that resolves to
//         Circle::draw: brush set to cyan, a filled circle is drawn
//         centered at (80,80) with radius 50.
// STEP 5  shapes[1]->draw(painter) resolves to RectangleShape::draw: brush
//         set to yellow, a filled rectangle is drawn from (180,40) sized
//         100x80.
// STEP 6  paintEvent returns; the finished frame (cyan circle + yellow
//         rectangle) is now on screen. If the window is later resized or
//         uncovered, Qt calls paintEvent again and STEPS 3-5 repeat
//         exactly, since `shapes` itself never changes after STEP 1.
