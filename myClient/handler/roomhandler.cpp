#include "roomhandler.h"
#include "singleton.h"
#include "hallwidget.h"
#include "gamereadywidget.h"

#include <QTcpSocket>
#include <QMessageBox>
#include <QJsonArray>
#include <QStringList>

RoomHandler::RoomHandler()
{

}

void RoomHandler::createRoom(const QString& username,const QString &roomName)
{
    Protocol protocol(Protocol::room);
    protocol["type"] = "createRoom";
    protocol["roomName"] = roomName;
    protocol["username"] = username;

    SingleTon<QTcpSocket>::getInstance()->write(protocol.pack());
}

void RoomHandler::flushRoom()
{
    Protocol protocol(Protocol::room);
    protocol["type"] = "flushRoom";

    SingleTon<QTcpSocket>::getInstance()->write(protocol.pack());
}

void RoomHandler::joinRoom(const QString &roomName, const QString &username)
{
    Protocol protocol(Protocol::room);
    protocol["type"] = "joinRoom";
    protocol["roomName"] = roomName;
    protocol["username"] = username;

    SingleTon<QTcpSocket>::getInstance()->write(protocol.pack());
}

void RoomHandler::exitRoom(const QString &username, const QString &roomName,bool Masterflag)
{
    Protocol protocol(Protocol::room);
    if(Masterflag){
        protocol["type"] = "MasterExitRoom";
    }else {
        protocol["type"] = "memberExitRoom";
    }

    protocol["username"] = username;
    protocol["roomName"] = roomName;

    SingleTon<QTcpSocket>::getInstance()->write(protocol.pack());
}

void RoomHandler::handle(QTcpSocket *, const Protocol &protocol)
{
    QString type = protocol["type"].toString();
    QString result = protocol["result"].toString();

    if(type == "createRoom"){
        QString roomName = protocol["roomName"].toString();
        if(result == "success"){
            //房间创建成功，切换到对应房间里
            QString username = protocol["username"].toString();
            QString GamerInfo = username + "    " + "未准备" + "    " + "房主";
            SingleTon<GameReadyWidget>::getInstance()->setWindowTitle("你画我猜   房间名:"+roomName);
            SingleTon<GameReadyWidget>::getInstance()->setRoomName(roomName);
            SingleTon<GameReadyWidget>::getInstance()->setUsername(username);
            SingleTon<GameReadyWidget>::getInstance()->setActiveUser(username);
            SingleTon<GameReadyWidget>::getInstance()->setMasterFlag(true);
            SingleTon<GameReadyWidget>::getInstance()->setLbGamerInfo(GamerInfo,1);
            SingleTon<GameReadyWidget>::getInstance()->btnStartGameHideOrShow();
            SingleTon<GameReadyWidget>::getInstance()->btnKickGamerHideOrShow();

            SingleTon<HallWidget>::getInstance()->hide();
            SingleTon<GameReadyWidget>::getInstance()->show();
        }else if(result == "failed"){
            QMessageBox::warning(nullptr, "创建房间信息", "创建房间失败");
        }
    }else if(type == "flushRoom"){
        QJsonArray roomArray = protocol["roomList"].toArray();
        QStringList rooms;

        int i;
        for(i = 0; i < roomArray.size(); ++i){
            rooms.append(roomArray[i].toString());
        }

        SingleTon<HallWidget>::getInstance()->flushRoom(rooms);
    }else if(type == "joinRoom"){
        //房间创建成功，切换到对应房间里
        QString roomName = protocol["roomName"].toString();
        QString username = protocol["username"].toString();

        SingleTon<GameReadyWidget>::getInstance()->setActiveUser(username);
        SingleTon<GameReadyWidget>::getInstance()->setWindowTitle("你画我猜   房间名:"+roomName);
        SingleTon<GameReadyWidget>::getInstance()->setRoomName(roomName);
        SingleTon<GameReadyWidget>::getInstance()->setUsername(username);//为了准备游戏界面中username的方便取用
        SingleTon<GameReadyWidget>::getInstance()->setMasterFlag(false);
        SingleTon<GameReadyWidget>::getInstance()->btnStartGameHideOrShow();
        SingleTon<GameReadyWidget>::getInstance()->btnKickGamerHideOrShow();

        SingleTon<HallWidget>::getInstance()->hide();
        SingleTon<GameReadyWidget>::getInstance()->show();
    }else if (type == "otherOneJoinRoom") {
        QString username = protocol["username"].toString();
        QJsonArray userArray = protocol["userList"].toArray();
        for (int i = 0;i < userArray.size();i++) {
            SingleTon<GameReadyWidget>::getInstance()->setLbGamerInfo(userArray[i].toString(),i+1);
        }
        SingleTon<GameReadyWidget>::getInstance()->btnKickGamerHideOrShow();
        SingleTon<GameReadyWidget>::getInstance()->appendText(username + "进入了房间");
    }else if (type == "otherOneExitRoom") {
        QString username = protocol["username"].toString();
        QJsonArray userArray = protocol["userList"].toArray();

        SingleTon<GameReadyWidget>::getInstance()->clearAllLBGamer();
        for (int i = 0;i < userArray.size();i++) {
            SingleTon<GameReadyWidget>::getInstance()->setLbGamerInfo(userArray[i].toString(),i+1);
            QStringList list = userArray[i].toString().split(" ",QString::SkipEmptyParts);
            if(list.size() == 3 && list[0] == SingleTon<GameReadyWidget>::getInstance()->getUsername()){
                /** 等于3说明是房主*/
                SingleTon<GameReadyWidget>::getInstance()->setMasterFlag(true);
                SingleTon<GameReadyWidget>::getInstance()->btnStartGameHideOrShow();
            }
        }
        SingleTon<GameReadyWidget>::getInstance()->btnKickGamerHideOrShow();
        SingleTon<GameReadyWidget>::getInstance()->appendText(username + "离开了房间");
    }
}
