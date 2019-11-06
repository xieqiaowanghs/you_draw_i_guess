#include "room.h"
#include <qrandom.h>
#include <QTime>

#include <QTcpSocket>
#include "protocol.h"

Room::Room(const QString &roomName)
    : roomName(roomName)
{

}

void Room::appendUser(const User &user)
{
    int i;
    for(i = 0; i < users.size(); i++){
        if(!(users[i] < user || user < users[i]))    return;
    }

    users.append(user);
}

void Room::removeUser(const User &user)
{
    QVector<User>::iterator it;
    for(it = users.begin(); it != users.end(); ++it){
        if(!(*it < user || user < *it)){
            users.erase(it);
            return;
        }
    }
}

void Room::removeUser(const QString &username)
{
    QVector<User>::iterator it;
    for(it = users.begin(); it != users.end(); ++it){
        if(username == it->getUsername()){
            users.erase(it);
            return;
        }
    }
}

/** new*/
/** 添加本轮游戏已用题目id*/
void Room::appendID(int value)
{
    playedID.append(value);
}
/** 获得新id*/
int Room::getNewID(QString &username)
{
    int count = 0; //防止死循环
    int id = randomID();
    while(isTitlePlayed(id) && count <100)
    {
        id = randomID();
        playedID.append(id);
        count++;
    }
    if(count >= 100)
    {
        qDebug()<<"题库空了";

        return -1;
    }
    appendID(id);
    return id;
}

int Room::randomID()
{
    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
    int num = qrand()%20;

    qDebug()<<"随机数 :"<<num;

    return num;
}

/** 更新画手*/
void Room::setPainter()
{
    for(int i = 0; i < users.size(); i++)
    {
        QString nowName = users[i].getUsername();
        if(nowName == painter)
        {
            painter = users[i + 1].getUsername();

            qDebug()<<"当前画手:"<<painter;

            return ;
        }
    }
}

void Room::newCount()
{
     setPainter();
     qDebug()<<"newCount";

     //给所有玩家发消息
     Protocol p(Protocol::gaming);
     p["type"] = "setPainter";
     p["painter"] = painter;
     for (int i = 0; i < users.size(); i++) {
         users[i].setisAnswer(false);
         users[i].getSocket()->write(p.pack());
     }
}



/**
 * 作用判断本题是否玩过
 * */
bool Room::isTitlePlayed(int id)
{
    QVector<int>::iterator it = playedID.begin();
    for(; it < playedID.end(); it++)
    {
        if(*it == id)
        {
            return true;
        }
    }
    return false;
}

void Room::gameStartInit()
{
    painter = users[0].getUsername();
    playedID.clear();
    qDebug()<<"playerid: "<<playedID.size();
    setGameCount(users.size());

    //给所有玩家发消息
    Protocol p(Protocol::gaming);
    p["type"] = "setPainter";
    p["painter"] = painter;


    for(int i = 0; i < users.size(); i++)
    {
       users[i].setScore(0);
       users[i].setisAnswer(false);
       users[i].getSocket()->write(p.pack());
    }

    qDebug()<<"当前画手："<<painter;
}

bool Room::isNewCount()
{
    // 所有人答对

    qDebug()<<"isNewCount";

    for (int i = 0; i < users.size(); i++) {
        if(users[i].getUsername() != painter)
        {
            if(users[i].getIsAnswer() == false)
            {
                return false;
            }
        }
    }
    return true;
}

void Room::addScore(QString username)
{
    int metex = 2; //等于0时退出
    for(int i = 0; i < users.size(); i++)
    {
        if(users[i].getUsername() == username)
        {
            users[i].setScore(users[i].getScore() + 3);
            users[i].setisAnswer(true);
            metex--;
        }else if (users[i].getUsername() == painter) {
            users[i].setScore(users[i].getScore() + 1);
            metex--;
        }

        qDebug()<<"username:"<<users[i].getUsername()<<"  score:"<<users[i].getScore();     

        if(metex == 0)
        {
            break;
        }
    }
    qDebug()<<endl;
}

bool Room::NextOrEnd()
{
    // true:next      false:end
    if(getGameCount() == 1)
    {
        qDebug()<<"本轮游戏结束，战绩。。。";

        return false;
    }
    setGameCount(gameCount - 1);
    qDebug()<<"当前剩余回合: " <<gameCount;
    return true;
}




