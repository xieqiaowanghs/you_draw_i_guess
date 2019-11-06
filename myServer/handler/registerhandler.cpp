#include "registerhandler.h"
#include "dao/sqlmanager.h"
#include "singleton.h"

RegisterHandler::RegisterHandler()
{

}


void RegisterHandler::handle(QTcpSocket *socket, const Protocol &protocol)
{
    QString username = protocol["username"].toString();
    QString password = protocol["password"].toString();

    Protocol p(Protocol::regist);
    p["type"] = "regist";

    /** 1. 判断是否注册 **/
    SqlDao* sd = SingleTon<SqlManager>::getInstance()->dao();
    SqlUser user(username, password, false);

    if(sd->insertUser(user) == false){//已经注册/

        p["result"] = "failed";
        p["info"] = "注册失败";
    }else{//没有注册过
        /** 2. 注册 **/

        p["result"] = "success";
        p["info"] = "注册成功";
    }

    socket->write(p.pack());
    delete sd;
}
