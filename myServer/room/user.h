#ifndef USER_H
#define USER_H

#include <QString>
#include <QTcpSocket>

class User
{
public:
    User();

    bool operator<(const User& rhs)const;
    bool operator==(const User& rhs)const;

    inline QString getUsername()const{return this->username;}
    inline void setUsername(const QString& username){this->username = username;}

    inline QTcpSocket* getSocket()const{return this->socket;}
    inline void setSocket(QTcpSocket* socket){this->socket = socket;}

    inline bool getReadyFlag()const {return this->readyFlag;}
    inline void setReadyFlag(bool readyFlag) {this->readyFlag = readyFlag;}

    inline bool getMasterFlag()const {return this->MasterFlag;}
    inline void setMasterFlag(bool MasterFlag) {this->MasterFlag = MasterFlag;}

    inline bool getIsAnswer()const {return this->isAnswer;}
    inline void setisAnswer(bool value){isAnswer = value;}
    inline int getScore()const {return this->score;}
    inline void setScore(int value){score = value;}

private:
    QString username;
    bool readyFlag;
    bool MasterFlag;
    QTcpSocket* socket;

    int score;
    /**
     * 答对玩家+3分，画家+1分
     * */
    bool isAnswer;
};

#endif // USER_H
