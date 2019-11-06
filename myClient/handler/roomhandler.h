#ifndef ROOMHANDLER_H
#define ROOMHANDLER_H

#include "ihandler.h"

class RoomHandler : public IHandler
{
public:
    RoomHandler();

    void createRoom(const QString& username,const QString& roomName);
    void flushRoom();
    void joinRoom(const QString& roomName, const QString& username);
    void exitRoom(const QString& username,const QString& roomName,bool Masterflag);

    // IHandler interface
public:
    virtual void handle(QTcpSocket *socket, const Protocol &protocol);
};

#endif // ROOMHANDLER_H
