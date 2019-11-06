#ifndef SQLDAO_H
#define SQLDAO_H

#include "sqluser.h"

class SqlDao
{
public:
    SqlDao();
    virtual ~SqlDao();
    virtual bool insertUser(const SqlUser& user)=0;
    virtual bool selectUser(const QString& username, SqlUser& user)=0;
    virtual bool updateUserOnline(const QString& username, bool online)=0;
    virtual bool updateUserMoney(const QString& username,double money)=0;
};

#endif // SQLDAO_H
