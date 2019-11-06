#ifndef GAMINGHANDLER_H
#define GAMINGHANDLER_H

#include "ihandler.h"
#include <QJsonArray>
class GamingHandler : public IHandler
{
public:
    GamingHandler();
public:
    virtual void handle(QTcpSocket *socket, const Protocol &protocol);

};

#endif // GAMINGHANDLER_H
