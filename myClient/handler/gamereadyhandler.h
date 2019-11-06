#ifndef GAMEREADYHANDLER_H
#define GAMEREADYHANDLER_H

#include "ihandler.h"
#include "protocol.h"
#include "singleton.h"
#include "gamereadywidget.h"
#include "gamingwidget.h"

#include <QTcpSocket>
#include <QJsonArray>
#include <QMessageBox>

class GameReadyHandler : public IHandler
{
public:
    GameReadyHandler();
    void readyGameStart(const QString& username,const QString& roomName);
    void readyGameStartCancel(const QString& username,const QString& roomName);
    void Chat(const QString& username,const QString& roomName,const QString& message);
    void gameStart(const QString& username,const QString& roomName);
    void KickOutGamer(const QString& username,const QString& roomName);


    // IHandler interface
public:
    void handle(QTcpSocket *socket, const Protocol &protocol);
};

#endif // GAMEREADYHANDLER_H
