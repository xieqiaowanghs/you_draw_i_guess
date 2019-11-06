#ifndef GAMINGHANDLER_H
#define GAMINGHANDLER_H


/**
 * GamingHandler
 * 作者:骆正琛
 * 作用:房间游戏相关逻辑处理
 */
#include "ihandler.h"

#include <QJsonArray>
class GamingHandler : public IHandler
{
public:
    GamingHandler();

    void groupChat(const QString& roomName, const QString username, const QString message);
    void getQuestionIDFromServer(const QString &roomName, const QString username);
    void sendAnswer(const QString& roomName, const QString username, const QString message);
    void OneRoundOfGameTimingEnds(const QString& roomName);
    void gameOver(const QString &roomName);
public:
    virtual void handle(QTcpSocket *socket, const Protocol &protocol);
};

#endif // GAMINGHANDLER_H
