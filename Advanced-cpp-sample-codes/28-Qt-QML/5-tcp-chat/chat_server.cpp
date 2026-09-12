// Qt TCP server — the console (no widgets) rewrite of Module 8's raw
// Winsock relay server, using Qt's signal-based QTcpServer/QTcpSocket
// instead of blocking bind()/listen()/accept()/recv() calls.
//
// QCoreApplication (not QApplication/QGuiApplication) is the right
// application object here — there is no UI at all, just an event loop
// servicing network events.
//
// Pairs with chat_client.cpp in this same folder. Build both from one
// CMakeLists.txt:
//   cmake -B build -S . -G Ninja
//   cmake --build build
// Run the SERVER first, in its own terminal:
//   build\chat_server.exe   (Windows)      ./build/chat_server   (Linux/macOS)
// then chat_client.exe in a second terminal.
//
// This exact server/client pair was run together for this repo — real
// captured output is in chat_client.cpp's trailing comment.

#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextStream>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QTextStream out(stdout);

    QTcpServer server;

    // server.listen(QHostAddress::Any, 9091)
    //   QHostAddress::Any - listen on every local network interface (the
    //                       Qt equivalent of raw sockets' INADDR_ANY).
    //   9091              - the TCP port to listen on.
    // Returns false if the port is already in use or otherwise
    // unavailable — unlike raw bind()+listen(), this one call does both.
    if (!server.listen(QHostAddress::Any, 9091)) {
        out << "Failed to start server: " << server.errorString() << "\n";
        return 1;
    }
    out << "[Server] Listening on port 9091...\n";
    out.flush();

    // connect(&server, &QTcpServer::newConnection, lambda)
    // newConnection fires once per INCOMING client, any time after
    // listen() succeeds — there is no separate accept() call to make; the
    // pending connection is already waiting inside `server` when this
    // slot runs.
    QObject::connect(&server, &QTcpServer::newConnection, [&]() {
        // server.nextPendingConnection()
        // Returns the QTcpSocket* for the client that just triggered
        // newConnection. Ownership: this socket is NOT automatically
        // deleted; the disconnected->deleteLater connection a few lines
        // down is what cleans it up later.
        QTcpSocket *client = server.nextPendingConnection();
        out << "[Server] Client connected.\n";
        out.flush();

        // connect(client, &QTcpSocket::readyRead, lambda)
        //   client - captured by value (a raw pointer, cheap to copy) so
        //            each connected client gets its own independent lambda
        //            instance with its OWN `client` pointer.
        //   &out   - captured by reference so every client's lambda shares
        //            the one QTextStream writing to stdout.
        // readyRead fires whenever THIS socket has bytes waiting — never
        // blocks, unlike raw recv().
        QObject::connect(client, &QTcpSocket::readyRead, [client, &out]() {
            // client->readAll()
            // Reads every byte currently buffered for this socket as a
            // QByteArray — the Qt equivalent of recv() into a buffer, but
            // with no fixed buffer size to manage.
            QByteArray data = client->readAll();
            out << "[Server] Received: " << data << "\n";
            out.flush();
            // client->write("Message received, over.")
            // Queues this literal C-string's bytes to be sent back;
            // write() never blocks the caller waiting for the network.
            client->write("Message received, over.");
        });

        // connect(client, &QTcpSocket::disconnected, client, &QTcpSocket::deleteLater)
        //   client (2nd arg)     - the RECEIVER QObject; tying the
        //                          connection's lifetime to `client` itself
        //                          means it's automatically disconnected if
        //                          `client` is destroyed some other way.
        //   &QTcpSocket::deleteLater - the slot: schedules `client` for
        //                          deletion once control returns to the
        //                          event loop, instead of deleting it
        //                          immediately (which would be unsafe while
        //                          still inside a signal it emitted).
        QObject::connect(client, &QTcpSocket::disconnected, client, &QTcpSocket::deleteLater);
    });

    return app.exec();
}

// --------------------------------------------------------------------------
// Step-by-step execution trace (one client connects, sends one message)
// --------------------------------------------------------------------------
// STEP 1  server.listen(...) succeeds; "Listening on port 9091..." prints.
// STEP 2  app.exec() starts the event loop and blocks, waiting for events.
// STEP 3  A client calls connectToHost("127.0.0.1", 9091) (see
//         chat_client.cpp) -> the OS completes the TCP handshake ->
//         QTcpServer emits newConnection.
// STEP 4  The newConnection lambda runs: client = that new QTcpSocket*;
//         "[Server] Client connected." prints; the readyRead and
//         disconnected connections are wired for THIS client.
// STEP 5  The client sends "Rack-A temperature nominal." -> bytes arrive ->
//         QTcpSocket buffers them -> readyRead fires for `client`.
// STEP 6  The readyRead lambda runs: data = "Rack-A temperature nominal.";
//         "[Server] Received: Rack-A temperature nominal." prints; then
//         client->write("Message received, over.") queues the reply.
// STEP 7  The client's own readyRead fires with that reply (see
//         chat_client.cpp step 4) and the client calls app.quit(), closing
//         its side of the connection.
// STEP 8  The server's `client` socket emits disconnected -> deleteLater
//         schedules it for cleanup -> the event loop keeps running,
//         ready to accept the NEXT client's newConnection.
