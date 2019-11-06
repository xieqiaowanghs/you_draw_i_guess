#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include "room.h"

#include <QVector>

class RoomManager
{
public:
    RoomManager();

    Room* createRoom(const QString& roomName);
    void removeRoom(const QString& roomName);
    Room* selectRoom(const QString& roomName);

    inline const QVector<Room>& allRooms()const {return this->rooms;}
private:
    QVector<Room> rooms;
};

#endif // ROOMMANAGER_H
