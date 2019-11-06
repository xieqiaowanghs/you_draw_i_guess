#include "gameoverhandler.h"

GameoverHandler::GameoverHandler()
{

}

bool cmpScore(User& u1,User& u2)//积分比较大小
{
    return u1.getScore() > u2.getScore();
}


void GameoverHandler::handle(QTcpSocket *socket, const Protocol &protocol)
{
    QString type = protocol["type"].toString();
    if(type == "gameover")
    {
        QString roomName = protocol["roomName"].toString();
        Protocol pAll(Protocol::gameover);

        Room* room = SingleTon<RoomManager>::getInstance()->selectRoom(roomName);
        if(room == nullptr) return;

        room->setGameStart(false);
        QVector<User>& users = room->allUsers();
        std::sort(users.begin(),users.end(),cmpScore);//积分排序

        QJsonArray userArray;
        for(int i = 0;i < users.size();i++){
            QString userInfo = "";
            userInfo = QString::number(users[i].getScore()) + "                     "
                    + users[i].getUsername();
            userArray.append(userInfo);

        }
        pAll["type"] = "ranking";//排名类型包
        pAll["rankList"] = userArray;

        for (int i = 0;i < users.size();i++) {
            users[i].getSocket()->write(pAll.pack());
        }

    }
}
