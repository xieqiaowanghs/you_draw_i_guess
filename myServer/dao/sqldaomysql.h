#ifndef SQLDAOMYSQL_H
#define SQLDAOMYSQL_H

#include "sqldao.h"

class SqlDaoMysql : public SqlDao
{
public:
    SqlDaoMysql();

    // SqlDao interface
public:
    virtual bool insertUser(const SqlUser &user);
    virtual bool selectUser(const QString &username, SqlUser &user);
    virtual bool updateUserOnline(const QString &username, bool online);
    virtual bool updateUserMoney(const QString &username, double money);
};

#endif // SQLDAOMYSQL_H
