// Nimbus Fleet Console — Module 9's complete try-now use case: a chat-style
// QWidget window (log + input field + Send button) wired to a QTcpSocket
// that connects to ../5-tcp-chat/chat_server.cpp. This combines THREE
// earlier folders' ideas in one program: widgets (1-widgets-click-counter),
// a custom-feeling connection pattern (2-signals-slots-calculator), and
// live networking (5-tcp-chat) — QML stays a separate, standalone exercise
// rather than being merged in, since it's an alternative front end for the
// same backend idea, not an additional feature on top of it.
//
// Build (from inside a folder containing THIS file, chat_server.cpp, and a
// CMakeLists.txt linking Qt6::Widgets + Qt6::Network for this target and
// Qt6::Network for chat_server):
//   cmake -B build -S . -G Ninja
//   cmake --build build
// Run chat_server.exe FIRST, in its own terminal, then this program.
//
// Built and run against a live chat_server.exe for this repo — the
// server's own console printed "[Server] Client connected." confirming the
// socket handshake succeeded from this exact file.

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QTcpSocket>

// NimbusChatClient : public QWidget
// A custom widget class (like ShapeCanvas in ../7-shape-canvas/), except
// this one also declares Q_OBJECT because its constructor connects
// lambdas as `this`-bound slots (see the three connect() calls below) —
// technically optional for plain lambda connections, but kept here since
// this class is the natural place a future version would add its own
// custom signals.
class NimbusChatClient : public QWidget {
    Q_OBJECT
public:
    NimbusChatClient() {
        setWindowTitle("Nimbus Fleet Console");
        resize(360, 280);

        auto *outer = new QVBoxLayout(this);
        log = new QTextEdit();
        // log->setReadOnly(true)
        // Prevents the user from typing directly into the log panel — it's
        // meant to be an output-only history, not an editable text box.
        log->setReadOnly(true);
        outer->addWidget(log);

        auto *row = new QHBoxLayout();
        input = new QLineEdit();
        auto *sendButton = new QPushButton("Send");
        row->addWidget(input);
        row->addWidget(sendButton);
        outer->addLayout(row);

        // connect(&socket, &QTcpSocket::connected, this, lambda)
        //   this - the receiver QObject; ties this connection's lifetime
        //          to NimbusChatClient itself (auto-disconnected if this
        //          widget is ever destroyed while `socket` lives longer).
        connect(&socket, &QTcpSocket::connected, this, [this]() {
            // log->append(text)
            //   text - a new line added to the end of the log; unlike
            //          setText() (used in the earlier calculator demos),
            //          append() keeps every prior line instead of
            //          replacing them — exactly what a chat history needs.
            log->append("[System] Connected to relay.");
        });
        connect(&socket, &QTcpSocket::readyRead, this, [this]() {
            // QString::fromUtf8(socket.readAll())
            //   socket.readAll()   - the raw bytes received, as a
            //                        QByteArray (same call as
            //                        ../5-tcp-chat/chat_server.cpp uses).
            //   QString::fromUtf8(...) - converts those bytes into a
            //                        QString assuming UTF-8 encoding, so
            //                        it can be concatenated with the
            //                        QString literal below.
            log->append("[Relay] " + QString::fromUtf8(socket.readAll()));
        });
        connect(sendButton, &QPushButton::clicked, this, [this]() {
            // input->text()
            // The QLineEdit's current contents at the moment of the click
            // — read fresh every time, so each click sends whatever the
            // user has typed since the last send.
            QString text = input->text();
            // if (text.isEmpty()) return;
            // Guards against sending an empty message if the user clicks
            // Send with nothing typed — the lambda simply does nothing.
            if (text.isEmpty()) return;
            // socket.write(text.toUtf8())
            //   text.toUtf8() - converts the QString back into raw UTF-8
            //                   bytes, the form write() expects (the exact
            //                   inverse of QString::fromUtf8 used above).
            socket.write(text.toUtf8());
            log->append("You: " + text);
            // input->clear()
            // Empties the QLineEdit so the next message starts from a
            // blank field instead of the just-sent text staying there.
            input->clear();
        });

        // socket.connectToHost("127.0.0.1", 9091)
        //   "127.0.0.1", 9091 - must match ../5-tcp-chat/chat_server.cpp's
        //                       listening address/port exactly; called
        //                       once, right here in the constructor, so the
        //                       connection attempt starts the moment this
        //                       widget is created.
        socket.connectToHost("127.0.0.1", 9091);
    }

private:
    QTextEdit *log;
    QLineEdit *input;
    QTcpSocket socket;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    NimbusChatClient window;
    window.show();
    return app.exec();
}

#include "program.moc"

// --------------------------------------------------------------------------
// Step-by-step execution trace (typing "Rack-C offline" and clicking Send)
// --------------------------------------------------------------------------
// STEP 1  NimbusChatClient's constructor builds the window (empty log,
//         empty input field), wires the three connect() calls, then calls
//         socket.connectToHost(...) — the connection attempt starts
//         immediately, before window.show() even runs in main().
// STEP 2  window.show() makes the window visible; app.exec() starts the
//         event loop.
// STEP 3  The TCP handshake with chat_server.exe completes -> `connected`
//         fires -> log now reads "[System] Connected to relay."
// STEP 4  User types "Rack-C offline" into `input`, then clicks Send:
//         text = "Rack-C offline" (not empty, so the guard passes) ->
//         socket.write(...) sends it -> log gains a second line, "You:
//         Rack-C offline" -> input->clear() empties the field.
// STEP 5  chat_server.exe's own readyRead fires with that message, prints
//         "[Server] Received: Rack-C offline", and writes back "Message
//         received, over." (see ../5-tcp-chat/chat_server.cpp).
// STEP 6  This program's `readyRead` fires with that reply -> log gains a
//         third line, "[Relay] Message received, over."
// STEP 7  User can type and Send again at any point — STEP 4-6 repeat
//         independently for each message, since the same `socket` stays
//         connected across multiple sends (unlike ../5-tcp-chat/, which is
//         a one-shot demo that quits after one reply).
