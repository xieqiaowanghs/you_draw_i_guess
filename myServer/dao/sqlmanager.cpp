#include "sqlmanager.h"
#include "sqldaomysql.h"

SqlManager::SqlManager()
{

}

void SqlManager::init(const QString &sql)
{
    this->sql = sql;

    if(sql == "MYSQL"){
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setUserName(username);
        db.setPassword(password);
        db.setHostName(hostname);
        db.setPort(port);

        db.setDatabaseName(databaseName);
    }
}

bool SqlManager::open()
{
    if(db.isOpen()) return true;
    return db.open();
}

void SqlManager::close()
{
    db.close();
}

SqlDao *SqlManager::dao()
{
    if(sql == "MYSQL"){
        return new SqlDaoMysql;
    }

    return nullptr;
}
