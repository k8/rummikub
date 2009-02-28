#include "server.h"

#include <QDebug>
#include <QMessageBox>


Server::Server()
        : QThread(), tcpServer(NULL)
{}

void Server::run() {
    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any, 7890);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));

    exec();
}

void Server::acceptConnection() {
    if(sockets.count() < 4) {
        QTcpSocket * socket = tcpServer->nextPendingConnection();
        emit error(QString("setting up new connection: %1").arg((int)socket));
        sockets << socket;
        connect(socket, SIGNAL(readyRead()), this, SLOT(processRead()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(deleteConnection()));
        connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));

        socket->write(QString("ACCEPT\n").toAscii());
    } else {
        QTcpSocket * socket = tcpServer->nextPendingConnection();
        emit error("To much connections");
        socket->write(QString("GET LOST\n").toAscii());
        connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
        //socket->disconnectFromHost();
    }
}

void Server::processRead() {
    // gets sender of signal
    QTcpSocket * sock = qobject_cast<QTcpSocket * >(this->sender());
    emit error(QString("from: %1 :: %2").arg((int)sock).arg(QString(sock->readAll())));
}

void Server::deleteConnection() {
    QTcpSocket * sock = qobject_cast<QTcpSocket * >(this->sender());
    sockets.removeAll(sock);
    emit error(QString("%1 is disconnecting.").arg((int)sock));
    //if(sock) delete sock;
}
