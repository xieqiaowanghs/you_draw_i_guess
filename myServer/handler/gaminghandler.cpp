#include "gaminghandler.h"
#include <QDateTime>
#include "singleton.h"
#include "room/roommanager.h"
GamingHandler::GamingHandler()
{

}
void GamingHandler::handle(QTcpSocket *, const Protocol &protocol)
{

    QString type = protocol["type"].toString();

    if(type == "getQuestionIDFromServer"){
        Protocol p(Protocol::gaming);
        QString roomName = protocol["roomName"].toString();
        QString username = protocol["username"].toString();
        Room* room = SingleTon<RoomManager>::getInstance()->selectRoom(roomName);
        if(room == nullptr)
        {
            return;
        }

        if(username != room->getPainter())
        {
            return;
        }
        int id = room->getNewID(username);
        p["type"] = "getQuestionIDFromServer";
        p["id"] = id;
        p["painter"] = room->getPainter();
        const QVector<User>& users = room->allUsers();
        int i = 0;
        for(i = 0; i < users.size(); i++){
            users[i].getSocket()->write(p.pack());
        }
    }
    else if(type == "sendAnswer"){

        Protocol p(Protocol::gaming);
        QString roomName = protocol["roomName"].toString();
        QString username = protocol["username"].toString();
        QString judge = protocol["true"].toString();
        qDebug()<<"judge:"<<judge;
        p["type"] = "sendAnswer";
        Room* room = SingleTon<RoomManager>::getInstance()->selectRoom(roomName);
        if(room == nullptr)
        {
            return;
        }
        QVector<User>& users = room->allUsers();

        if(judge == "F")
        {
            p["judge"] = "F";
            QString message = username + " : " + protocol["message"].toString();
            p["message"] = message;
        }else {
            //回答正确后对服务端操作和判定

                if(username != room->getPainter())
                {
                    //修改答题状态
                    room->addScore(username);
                    //判断是否全部答完
                    qDebug()<<"修改答题状态后";
                    bool flag = room->isNewCount();
                    qDebug()<<"flag = "<<flag;
                    if(flag)
                    {
                    //判断回合结束还是游戏结束
                        bool ret = room->NextOrEnd();
                        qDebug()<<"ret = "<<ret;
                        if(ret)
                        {
                            //下回合
                            qDebug()<<"下回合";
                            p["state"] = "nextCount";
                            room->newCount();
                            p["painter"] = room->getPainter();
                        }else {
                        //结束游戏
                            p["state"] = "gameOver";
                        }
                    }
                    else
                    {
                        p["state"] = "continue";
                    }
                }

            //数据包
            p["judge"] = "T";
            QString message = username + " : " + "回答正确";
            p["message"] = message;

            QString Painter = room->getPainter();
            QJsonArray userArray;
            for (int i = 0;i < users.size();i++) {
                QString userInfo = "";
                QString isPainter = "";
                if(Painter == users[i].getUsername()) isPainter = "画手";
                userInfo = users[i].getUsername() + "    " + QString::number(users[i].getScore()) + "    " + isPainter;
                userArray.append(userInfo);
            }
            p["userList"] = userArray;

        }

        int i = 0;
        for(i = 0; i < users.size(); i++){
            users[i].getSocket()->write(p.pack());
        }
    }else if (type == "OneRoundOfGameTimingEnds") {
        QString roomName = protocol["roomName"].toString();
        Protocol p(Protocol::gaming);

        Room* room = SingleTon<RoomManager>::getInstance()->selectRoom(roomName);
        if(room == nullptr)
        {
            return;
        }
        QVector<User>& users = room->allUsers();

        bool ret = room->NextOrEnd();
        qDebug()<<"ret = "<<ret;
        if(ret)
        {
            //下回合
            qDebug()<<"下回合";
            p["state"] = "nextCount";
            room->newCount();
            p["painter"] = room->getPainter();
        }else {
        //结束游戏
            p["state"] = "gameOver";
        }
qDebug()<<"write";
        QString Painter = room->getPainter();
        QJsonArray userArray;
        for (int i = 0;i < users.size();i++) {
            QString userInfo = "";
            QString isPainter = "";
            if(Painter == users[i].getUsername()) isPainter = "画手";
            userInfo = users[i].getUsername() + "    " + QString::number(users[i].getScore()) + "    " + isPainter;
            userArray.append(userInfo);
        }

        p["type"] = "OneRoundOfGameTimingEnds";
        p["userList"] = userArray;
        int i = 0;
        for(i = 0; i < users.size(); i++){
            users[i].getSocket()->write(p.pack());
        }
    }
}
