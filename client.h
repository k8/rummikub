#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

class Client : public QTcpSocket
{
public:
    Client();
};

#endif // CLIENT_H
