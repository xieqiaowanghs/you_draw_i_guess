#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include <QSqlDatabase>

#include "sqldao.h"

class SqlManager
{
public:
    SqlManager();

    void init(const QString& sql);

    bool open();
    void close();

    SqlDao* dao();

    inline void setHostname(const QString& hostname){this->hostname = hostname;}
    inline void setUsername(const QString& username){this->username = username;}
    inline void setPassword(const QString& password){this->password = password;}
    inline void setPort(int port){this->port = port;}
    inline void setDatabaseName(const QString& databaseName){this->databaseName = databaseName;}
private:
    QSqlDatabase db;

    QString hostname;
    QString username;
    QString password;
    int port;

    QString databaseName;

    QString sql;
};

#endif // SQLMANAGER_H
