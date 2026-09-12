// QUdpSocket heartbeat — broadcasts one "agent-alive" datagram per second
// and prints any heartbeat it receives (including its own, since the port
// is shared). This is UDP's connectionless send/receive pattern, contrasted
// with ../5-tcp-chat/'s connection-oriented QTcpSocket pair.
//
// Build (from inside this folder, with CMakeLists.txt next to this file):
//   cmake -B build -S . -G Ninja
//   cmake --build build
// Run:
//   build\heartbeat.exe   (Windows)      ./build/heartbeat   (Linux/macOS)
// Run two copies at once (two terminals) to see each one print the other's
// (and its own) broadcast heartbeats.
//
// Built successfully with Qt 6.10 for this repo.

#include <QCoreApplication>
#include <QUdpSocket>
#include <QTimer>
#include <QTextStream>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QTextStream out(stdout);

    QUdpSocket udp;

    // udp.bind(QHostAddress::Any, 9092, QUdpSocket::ShareAddress)
    //   QHostAddress::Any    - listen for datagrams on every local
    //                          interface.
    //   9092                 - the UDP port.
    //   QUdpSocket::ShareAddress - allows MULTIPLE processes on this
    //                          machine to bind the same port at once (so
    //                          running two copies of this program to test
    //                          it doesn't fail on the second one).
    // Unlike TCP's listen()+accept() pair, UDP has no connection to
    // establish — bind() alone is enough to start receiving.
    udp.bind(QHostAddress::Any, 9092, QUdpSocket::ShareAddress);

    // connect(&udp, &QUdpSocket::readyRead, lambda)
    // Fires whenever at least one datagram is waiting — the SAME signal
    // name as QTcpSocket's readyRead, but UDP delivers whole, distinct
    // datagrams rather than a continuous byte stream.
    QObject::connect(&udp, &QUdpSocket::readyRead, [&]() {
        // while (udp.hasPendingDatagrams())
        // More than one datagram can arrive before this slot gets a
        // chance to run, so draining them in a loop (rather than reading
        // just one per readyRead) avoids falling behind.
        while (udp.hasPendingDatagrams()) {
            QByteArray datagram;
            // datagram.resize(udp.pendingDatagramSize())
            //   pendingDatagramSize() - the exact byte size of the NEXT
            //                           queued datagram, read in advance
            //                           so the buffer is sized correctly
            //                           (UDP datagrams keep their message
            //                           boundaries — there's no "read
            //                           whatever's available" ambiguity
            //                           like a TCP stream has).
            datagram.resize((int)udp.pendingDatagramSize());
            // udp.readDatagram(datagram.data(), datagram.size())
            //   datagram.data() - a raw pointer to write the incoming
            //                     bytes into.
            //   datagram.size() - how many bytes the buffer can hold
            //                     (matches the exact datagram size from
            //                     the resize() call above).
            udp.readDatagram(datagram.data(), datagram.size());
            out << "[Heartbeat] " << datagram << "\n";
            out.flush();
        }
    });

    QTimer timer;
    // connect(&timer, &QTimer::timeout, lambda)
    // `timeout` fires once per interval set by timer.start() below —
    // Qt's non-blocking replacement for a manual sleep-then-send loop,
    // which would block the whole event loop like a raw recv() would.
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        // udp.writeDatagram("agent-alive", QHostAddress::Broadcast, 9092)
        //   "agent-alive"            - the datagram's payload.
        //   QHostAddress::Broadcast  - send to every host on the local
        //                              network segment, not one specific
        //                              address (UDP's connectionless
        //                              send/receive: no connectToHost()
        //                              call anywhere in this file).
        //   9092                     - the destination port.
        udp.writeDatagram("agent-alive", QHostAddress::Broadcast, 9092);
    });
    // timer.start(1000)
    //   1000 - milliseconds between timeouts: once per second.
    timer.start(1000);

    return app.exec();
}

// --------------------------------------------------------------------------
// Step-by-step execution trace (one second of running)
// --------------------------------------------------------------------------
// STEP 1  udp.bind(...) succeeds; the readyRead connection and the 1000ms
//         QTimer are both armed, but nothing has fired yet.
// STEP 2  app.exec() starts the event loop.
// STEP 3  At t=1000ms, the QTimer's timeout fires -> writeDatagram(...)
//         broadcasts "agent-alive" on port 9092.
// STEP 4  Because ShareAddress lets this same process (and any other copy
//         of it) also be bound to port 9092, the broadcast is received by
//         this program's OWN socket almost immediately -> readyRead fires
//         -> "[Heartbeat] agent-alive" prints.
// STEP 5  At t=2000ms, STEP 3-4 repeat: a second "agent-alive" is sent and
//         received, printing a second "[Heartbeat] agent-alive" line.
// STEP 6  If a SECOND copy of this program is running on the same machine,
//         its broadcasts arrive here too (and vice versa) — each running
//         copy prints one "[Heartbeat] agent-alive" line per second, per
//         copy currently running, since every copy both sends and listens.
