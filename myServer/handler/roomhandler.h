#ifndef ROOMHANDLER_H
#define ROOMHANDLER_H

#include "ihandler.h"

class RoomHandler : public IHandler
{
public:
    RoomHandler();

    // IHandler interface
public:
    virtual void handle(QTcpSocket *socket, const Protocol &protocol);
};

#endif // ROOMHANDLER_H
