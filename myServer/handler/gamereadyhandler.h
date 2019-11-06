#ifndef GAMEREADYHANDLER_H
#define GAMEREADYHANDLER_H

#include "ihandler.h"
#include "room/roommanager.h"
#include "singleton.h"

#include <QJsonArray>
#include <QDebug>

class GameReadyHandler : public IHandler
{
public:
    GameReadyHandler();

    // IHandler interface
public:
    void handle(QTcpSocket *socket, const Protocol &protocol);
};

#endif // GAMEREADYHANDLER_H
