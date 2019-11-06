#ifndef SQLUSER_H
#define SQLUSER_H

#include <QString>

class SqlUser
{
private:
    QString username;
    QString password;
    bool online;
    double money;

public:
    SqlUser();
    SqlUser(const QString& username, const QString& password, bool online);

    inline QString getUsername()const{return this->username;}
    inline QString getPassword()const{return this->password;}
    inline bool getOnline()const{return this->online;}
    inline double getMoney()const{return this->money;}

    inline void setUsername(const QString& username){this->username = username;}
    inline void setPassword(const QString& password){this->password = password;}
    inline void setOnline(bool online){this->online = online;}
    inline void setMoney(double money){this->money = money;}
};

#endif // SQLUSER_H
