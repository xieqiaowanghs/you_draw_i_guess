#ifndef ROOM_H
#define ROOM_H

#include <QString>
#include <QVector>

#include "user.h"

class Room
{
public:
    Room(const QString& roomName = "");

    inline QString getRoomName()const{return this->roomName;}
    inline void setRoomName(const QString& roomName){this->roomName = roomName;}

    void appendUser(const User& user);
    void removeUser(const User& user);
    void removeUser(const QString& username);
    inline const QVector<User>& allUsers()const{return users;}
    inline QVector<User>& allUsers() {return users;}

    inline int getUserNumber()const {return users.size();}

    inline void setGameStart(bool value) {this->GameStart = value;}
    inline bool getGameStart()const {return this->GameStart;}


    /** new*/
    void appendID(int value);
    int getNewID(QString &username);
    //void cleanID(int value);
    int randomID();
    bool isTitlePlayed(int id);

    inline QString getPainter(){return painter;}
    void setPainter(); //改变画手
    void gameStartInit();  //新一轮游戏开始 初始化
    inline int getGameCount(){return gameCount;}
    inline void setGameCount(int value){gameCount = value;}

    bool isNewCount(); //判断是否回合结束
    void newCount(); //新一回合，另一画家开始作画
    void addScore(QString username); //答对后玩家和画家加分，改变玩家状态
    bool NextOrEnd(); //判断回合结束还是游戏结束

private:
    QString roomName;//房间名
    QVector<User> users;
    bool GameStart;//表明房间是否已经开始游戏

    int gameCount; //游戏回合剩余数
    QVector<int> playedID; //new
    QString painter;

};

#endif // ROOM_H
