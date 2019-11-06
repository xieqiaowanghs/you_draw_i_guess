#include "roommanager.h"

RoomManager::RoomManager()
{

}

Room* RoomManager::createRoom(const QString &roomName)
{
    int i = 0;
    for(i = 0; i < rooms.size(); i++){
        if(rooms[i].getRoomName() == roomName)  return nullptr;
    }

    rooms.append(Room(roomName));
    return &(rooms.last());
}

void RoomManager::removeRoom(const QString &roomName)
{
    QVector<Room>::iterator it;
    for(it = rooms.begin(); it != rooms.end(); ++it){
        if(it->getRoomName() == roomName){
            rooms.erase(it);
            return;
        }
    }
}

Room* RoomManager::selectRoom(const QString &roomName)
{
    int i = 0;
    for(i = 0; i < rooms.size(); i++){
        if(rooms[i].getRoomName() == roomName)  return &rooms[i];
    }

    return nullptr;
}
