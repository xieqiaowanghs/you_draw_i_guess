#include "roomhandler.h"
#include "room/roommanager.h"
#include "singleton.h"

#include <QJsonArray>
#include <QTime>

RoomHandler::RoomHandler()
{

}


void RoomHandler::handle(QTcpSocket *socket, const Protocol &protocol)
{
    QString type = protocol["type"].toString();
    QString roomName = protocol["roomName"].toString();

    Protocol p(Protocol::room);
    Protocol pAll(Protocol::room);

    if(type == "createRoom"){
        p["type"] = "createRoom";
        QString username = protocol["username"].toString();
        Room* room = SingleTon<RoomManager>::getInstance()->createRoom(roomName);
        if(room != nullptr){
            room->setGameStart(false);
            room->setRoomName(roomName);

            User user;
            user.setUsername(username);
            user.setSocket(socket);
            user.setReadyFlag(false);
            user.setMasterFlag(true);
            room->appendUser(user);

            p["result"] = "success";
            p["roomName"] = roomName;
            p["username"] = username;

        }else{
            p["result"] = "failed";
        }

        socket->write(p.pack());
    }else if(type == "flushRoom"){
        p["type"] = "flushRoom";
        QJsonArray roomArray;

        const QVector<Room>& rooms = SingleTon<RoomManager>::getInstance()->allRooms();
        int i;
        for(i = 0; i < rooms.size(); i++){
            QString roomName = rooms[i].getRoomName();
            int gamerInRoom = rooms[i].getUserNumber();
            QString gameStartState = "";
            if(rooms[i].getGameStart()){
                gameStartState = "正在游戏中";
            }else{
                gameStartState = "";
            }
            QString roomInfo = roomName + "    " + QString::number(gamerInRoom) +
                    "    " + gameStartState;
            roomArray.append(roomInfo);
        }
        p["roomList"] = roomArray;

        socket->write(p.pack());
    }else if(type == "joinRoom"){

        QString username = protocol["username"].toString();

        Room* room = SingleTon<RoomManager>::getInstance()->selectRoom(roomName);
        if(room == nullptr){
            return;
        }else{
            User user;
            user.setUsername(username);
            user.setSocket(socket);
            user.setReadyFlag(false);
            user.setMasterFlag(false);
            room->appendUser(user);
        }

        QJsonArray userArray;
        QVector<User> users = room->allUsers();
        for (int i = 0;i < users.size();i++) {
            QString userInfo = "";
            QString isReady = "";
            QString isMaster = "";
            if(users[i].getReadyFlag()){
                isReady = "已准备";
            }else {
                isReady = "未准备";
            }
            if(users[i].getMasterFlag()) isMaster = "房主";
            userInfo = users[i].getUsername() + "    " + isReady + "    " + isMaster;
            userArray.append(userInfo);
        }

        pAll["type"] = "otherOneJoinRoom";
        pAll["userList"] = userArray;
        pAll["username"] = username;
        for (int i = 0;i < users.size();i++) {
            users[i].getSocket()->write(pAll.pack());
        }


        p["type"] = "joinRoom";
        p["roomName"] = roomName;
        p["username"] = username;
        socket->write(p.pack());
    }else if(type == "MasterExitRoom"){
        /** 房主退出房间先判定是否为最后一个人退出房间*/
        Room* room = SingleTon<RoomManager>::getInstance()->selectRoom(roomName);
        if(room == nullptr) return;
        QString username = protocol["username"].toString();

        /** 房间此时只剩下房主一个人*/
        if(room->getUserNumber() == 1){
            SingleTon<RoomManager>::getInstance()->removeRoom(roomName);
            return;
        }

        /** 房间不只房主一个人,房主退出房间则从room的users中删掉房主*/
        room->removeUser(username);

        /** 随机指定房间中任一用户为房主*/
        QVector<User>& users = room->allUsers();
        QTime time;
        time= QTime::currentTime();
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        int n = qrand() % room->getUserNumber();
        for (int i = 0;i < users.size();i++) {
            if(i == n) users[i].setMasterFlag(true);
        }

        /** 指定房主之后,将users中的信息发给客户端更新*/
        QJsonArray userArray;
        for (int i = 0;i < users.size();i++) {
            QString userInfo = "";
            QString isReady = "";
            QString isMaster = "";
            if(users[i].getReadyFlag()) isReady = "已准备";
            else isReady = "未准备";
            if(users[i].getMasterFlag()) isMaster = "房主";
            userInfo = users[i].getUsername() + "    " + isReady + "    " + isMaster;
            userArray.append(userInfo);
        }

        pAll["type"] = "otherOneExitRoom";
        pAll["userList"] = userArray;
        pAll["username"] = username;
        for (int i = 0;i < users.size();i++) {
            users[i].getSocket()->write(pAll.pack());
        }
    } else if (type == "memberExitRoom") {
        /** 房间其他普通成员退出房间*/
        Room* room = SingleTon<RoomManager>::getInstance()->selectRoom(roomName);
        if(room == nullptr) return;
        QString username = protocol["username"].toString();

        /** 将该成员从房间users中移除*/
        room->removeUser(username);

        QJsonArray userArray;
        for (int i = 0;i < room->allUsers().size();i++) {
            QString userInfo = "";
            QString isReady = "";
            QString isMaster = "";
            if(room->allUsers()[i].getReadyFlag()) isReady = "已准备";
            else isReady = "未准备";
            if(room->allUsers()[i].getMasterFlag()) isMaster = "房主";
            userInfo = room->allUsers()[i].getUsername() + "    " + isReady + "    " + isMaster;
            userArray.append(userInfo);
        }
        pAll["type"] = "otherOneExitRoom";
        pAll["userList"] = userArray;
        pAll["username"] = username;
        const QVector<User>& users = room->allUsers();
        for (int i = 0;i < users.size();i++) {
            users[i].getSocket()->write(pAll.pack());
        }
    }

}
