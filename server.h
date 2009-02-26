#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Server : public QTcpServer
{
public:
    Server();
};

#endif // SERVER_H
