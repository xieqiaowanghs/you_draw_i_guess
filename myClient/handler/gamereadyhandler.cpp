#include "gamereadyhandler.h"
/**
 * 聂尊航
 * gamereadyhandler类
*/

GameReadyHandler::GameReadyHandler()
{

}


void GameReadyHandler::readyGameStart(const QString &username, const QString &roomName)
{
    Protocol p(Protocol::readyGame);
    p["type"] = "readyGame";
    p["username"] = username;
    p["roomName"] = roomName;

    SingleTon<QTcpSocket>::getInstance()->write(p.pack());
}

void GameReadyHandler::readyGameStartCancel(const QString &username, const QString &roomName)
{
    Protocol p(Protocol::readyGame);
    p["type"] = "readyGameCancel";
    p["username"] = username;
    p["roomName"] = roomName;

    SingleTon<QTcpSocket>::getInstance()->write(p.pack());
}

void GameReadyHandler::Chat(const QString &username, const QString &roomName, const QString &message)
{
    Protocol p(Protocol::readyGame);
    p["type"] = "chat";
    p["username"] = username;
    p["roomName"] = roomName;
    p["message"] = message;

    SingleTon<QTcpSocket>::getInstance()->write(p.pack());
}

void GameReadyHandler::gameStart(const QString& username,const QString &roomName)
{
    Protocol p(Protocol::readyGame);
    p["type"] = "gameStart";
    p["roomName"] = roomName;
    p["username"] = username;

    SingleTon<QTcpSocket>::getInstance()->write(p.pack());
}

void GameReadyHandler::KickOutGamer(const QString &username, const QString &roomName)
{
    Protocol p(Protocol::readyGame);
    p["type"] = "kickOutGamer";
    p["username"] = username;
    p["roomName"] = roomName;

    SingleTon<QTcpSocket>::getInstance()->write(p.pack());
}


void GameReadyHandler::handle(QTcpSocket *, const Protocol &protocol)
{
    QString type = protocol["type"].toString();
    if(type == "updateUserIsReady"){
        QJsonArray userArray = protocol["userList"].toArray();
        for (int i = 0;i < userArray.size();i++) {
            SingleTon<GameReadyWidget>::getInstance()->setLbGamerInfo(userArray[i].toString(),i+1);
        }
    }else if (type == "chat") {
        QString message = protocol["message"].toString();
        SingleTon<GameReadyWidget>::getInstance()->appendText(message);
    }else if (type == "gameStart") {
        QJsonArray userArray = protocol["userList"].toArray();

        for (int i = 0;i < userArray.size();i++) {
            SingleTon<GamingWidget>::getInstance()->setLbGamerInfo(userArray[i].toString(),i+1);
        }
        SingleTon<GameReadyWidget>::getInstance()->readyRoomInit();
        SingleTon<GamingWidget>::getInstance()->countDown();
        SingleTon<GamingWidget>::getInstance()->appendText("第一轮游戏开始\n\n");

        SingleTon<GameReadyWidget>::getInstance()->hide();
        SingleTon<GamingWidget>::getInstance()->initGame();
        SingleTon<GamingWidget>::getInstance()->show();
        SingleTon<GameReadyWidget>::getInstance()->setLbGamerNotReady();
    }else if(type == "gameStartFailed"){
        QMessageBox::warning(nullptr,"开始游戏结果","有人未准备,不能开始游戏");
    }else if (type == "KickedOut") {
        QMessageBox::warning(nullptr,"warning","你已被踢出房间");
        SingleTon<GameReadyWidget>::getInstance()->close();
    }else if (type == "otherOneKickedOut") {
        QString username = protocol["username"].toString();
        QJsonArray userArray = protocol["userList"].toArray();

        SingleTon<GameReadyWidget>::getInstance()->clearAllLBGamer();

        for (int i = 0;i < userArray.size();i++) {
            SingleTon<GameReadyWidget>::getInstance()->setLbGamerInfo(userArray[i].toString(),i+1);
        }
        SingleTon<GameReadyWidget>::getInstance()->btnKickGamerHideOrShow();
        SingleTon<GameReadyWidget>::getInstance()->appendText(username + "被踢出了房间");
    }
}
