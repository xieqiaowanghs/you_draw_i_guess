#ifndef IHANDLER_H
#define IHANDLER_H

#include <QTcpSocket>
#include "protocol.h"

class IHandler
{
public:
    IHandler();
    virtual ~IHandler();

    virtual void handle(QTcpSocket* socket, const Protocol& protocol)=0;
};

#endif // IHANDLER_H
