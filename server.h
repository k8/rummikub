#ifndef SERVER_H
#define SERVER_H

#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

class Server : public QThread
{
    Q_OBJECT
public:
    Server();

    void run();

public slots:
    void acceptConnection();
    void processRead();

protected slots:
    void deleteConnection();

signals:
    // emitted when error occures, should be catched by UI to show message
    void error(const QString &);

private:
    QTcpServer * tcpServer;
    QList<QTcpSocket * > sockets;
};

#endif // SERVER_H
