// Qt TCP client — pairs with chat_server.cpp in this same folder.
// See chat_server.cpp's header comment for the shared build/run commands
// (both targets come from one CMakeLists.txt). Start chat_server.exe
// FIRST, in its own terminal, then this one in a second terminal.

#include <QCoreApplication>
#include <QTcpSocket>
#include <QTextStream>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QTextStream out(stdout);

    QTcpSocket socket;

    // connect(&socket, &QTcpSocket::connected, lambda)
    // `connected` fires once, the moment the TCP handshake with the server
    // finishes successfully — the Qt equivalent of raw connect() RETURNING
    // 0, but delivered as an event instead of a blocking call's result.
    QObject::connect(&socket, &QTcpSocket::connected, [&]() {
        out << "[Client] Connected to server.\n";
        out.flush();
        // socket.write("Rack-A temperature nominal.")
        // Sends this literal message the moment the connection is up —
        // safe to call here specifically because `connected` guarantees
        // the socket is actually ready to send.
        socket.write("Rack-A temperature nominal.");
    });

    // connect(&socket, &QTcpSocket::readyRead, lambda)
    // Fires when the server's reply bytes arrive.
    QObject::connect(&socket, &QTcpSocket::readyRead, [&]() {
        out << "[Client] Server replied: " << socket.readAll() << "\n";
        out.flush();
        // app.quit()
        // Stops the event loop (causing app.exec() below to return), since
        // this one-shot demo has nothing left to do once it has the reply.
        app.quit();
    });

    // socket.connectToHost("127.0.0.1", 9091)
    //   "127.0.0.1" - the loopback address: "this same machine." Matches
    //                 chat_server.cpp's QHostAddress::Any, which accepts
    //                 connections on every local interface including this
    //                 one.
    //   9091        - must match the port chat_server.cpp is listening on.
    // Unlike raw connect(), this call does NOT block waiting for the
    // handshake to finish — it returns immediately, and the `connected`
    // signal above is how the code finds out the handshake succeeded.
    socket.connectToHost("127.0.0.1", 9091);
    return app.exec();
}

// --------------------------------------------------------------------------
// Step-by-step execution trace
// --------------------------------------------------------------------------
// STEP 1  connectToHost("127.0.0.1", 9091) is called; it returns
//         immediately, before the handshake is known to have succeeded.
// STEP 2  app.exec() starts the event loop and blocks.
// STEP 3  The TCP handshake with chat_server.exe completes -> `connected`
//         fires -> "[Client] Connected to server." prints -> socket.write()
//         queues "Rack-A temperature nominal." to be sent.
// STEP 4  The server's reply ("Message received, over.") arrives ->
//         `readyRead` fires -> "[Client] Server replied: Message received,
//         over." prints -> app.quit() stops the event loop.
// STEP 5  app.exec() returns; main() returns; the process exits.
//
// --------------------------------------------------------------------------
// Actual output — both processes really run together for this repo
// --------------------------------------------------------------------------
// Server terminal:
//   [Server] Listening on port 9091...
//   [Server] Client connected.
//   [Server] Received: Rack-A temperature nominal.
//
// Client terminal:
//   [Client] Connected to server.
//   [Client] Server replied: Message received, over.
