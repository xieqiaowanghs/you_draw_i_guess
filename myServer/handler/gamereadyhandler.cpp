#include "gamereadyhandler.h"

GameReadyHandler::GameReadyHandler()
{

}


void GameReadyHandler::handle(QTcpSocket *socket, const Protocol &protocol)
{
    QString type = protocol["type"].toString();
    QString username = protocol["username"].toString();
    QString roomName = protocol["roomName"].toString();
    Protocol pAll(Protocol::readyGame);

    if(type == "readyGame"){
        Room* room = SingleTon<RoomManager>::getInstance()->selectRoom(roomName);
        if(room == nullptr) return;

        QVector<User>& users = room->allUsers();
        for (int i = 0;i < users.size();i++) {
            if(users[i].getUsername() == username){
                users[i].setReadyFlag(true);
                break;
            }
        }

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

        pAll["type"] = "updateUserIsReady";
        pAll["userList"] = userArray;
        for (int i = 0;i < users.size();i++) {
            users[i].getSocket()->write(pAll.pack());
        }
    }else if (type == "readyGameCancel") {
        Room* room = SingleTon<RoomManager>::getInstance()->selectRoom(roomName);
        if(room == nullptr) return;

        QVector<User>& users = room->allUsers();
        for (int i = 0;i < users.size();i++) {
            if(users[i].getUsername() == username){
                users[i].setReadyFlag(false);
                break;
            }
        }

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

        pAll["type"] = "updateUserIsReady";
        pAll["userList"] = userArray;
        for (int i = 0;i < users.size();i++) {
            users[i].getSocket()->write(pAll.pack());
        }
    }else if (type == "chat") {
        Room* room = SingleTon<RoomManager>::getInstance()->selectRoom(roomName);
        if(room == nullptr) return;

        QString message = protocol["message"].toString();
        message = username + " : " + message;

        pAll["type"] = "chat";
        pAll["message"] = message;

        QVector<User>& users = room->allUsers();
        for (int i = 0;i < users.size();i++) {
            users[i].getSocket()->write(pAll.pack());
        }
    }else if (type == "gameStart") {
        Room* room = SingleTon<RoomManager>::getInstance()->selectRoom(roomName);
        if(room == nullptr) return;

        bool isAllReady = true;

        QVector<User>& users = room->allUsers();
        for (int i = 0;i < users.size();i++) {
            if(users[i].getReadyFlag() == false){
                isAllReady = false;
                break;
            }
        }

        if(isAllReady){
            room->setGameStart(true);
            room->gameStartInit();
            QString Painter = room->getPainter();

            QJsonArray userArray;
            for (int i = 0;i < users.size();i++) {
                QString userInfo = "";
                QString isPainter = "";
                if(Painter == users[i].getUsername()) isPainter = "画手";
                userInfo = users[i].getUsername() + "    " + QString::number(users[i].getScore()) + "    " + isPainter;
                userArray.append(userInfo);
            }

            pAll["type"] = "gameStart";
            pAll["userList"] = userArray;

            for (int i = 0;i < users.size();i++) {
                users[i].getSocket()->write(pAll.pack());
                users[i].setReadyFlag(false);
            }
        }else {
            Protocol p(Protocol::readyGame);
            p["type"] = "gameStartFailed";
            socket->write(p.pack());
        }
    }else if (type == "kickOutGamer") {
        Room* room = SingleTon<RoomManager>::getInstance()->selectRoom(roomName);
        if(room == nullptr) return;

        Protocol p(Protocol::readyGame);
        p["type"] = "KickedOut";
        QVector<User>& users = room->allUsers();
        for (int i = 0;i < users.size();i++) {
            if(users[i].getUsername() == username){
                users[i].getSocket()->write(p.pack());
                break;
            }
        }

        room->removeUser(username);

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

        pAll["type"] = "otherOneKickedOut";
        pAll["userList"] = userArray;
        pAll["username"] = username;
        for (int i = 0;i < users.size();i++) {
            users[i].getSocket()->write(pAll.pack());
        }
    }

}
