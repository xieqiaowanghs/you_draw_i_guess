#include "loginhandler.h"
#include "dao/sqlmanager.h"
#include "singleton.h"

LoginHandler::LoginHandler()
{

}


void LoginHandler::handle(QTcpSocket *socket, const Protocol &protocol)
{
    QString type = protocol["type"].toString();
    if(type == "login"){
        QString username = protocol["username"].toString();
        QString password = protocol["password"].toString();

        Protocol p(Protocol::login);
        p["type"] = "login";

        /** 1. 是否注册 **/
        SqlDao* sd = SingleTon<SqlManager>::getInstance()->dao();
        SqlUser user;
        if(sd->selectUser(username, user) == false){
            //没有注册
            p["result"] = "failed";
            p["info"] = "无此用户";
            socket->write(p.pack());
            delete sd;
            return;
        }
        /** 2. 是否重复登录 **/
        if(user.getOnline() == true){
            //重复
            p["result"] = "failed";
            p["info"] = "重复登录";
            socket->write(p.pack());
            delete sd;
            return;
        }

        /** 3. 密码正确 **/
        if(user.getPassword() != password){
            //密码错误
            p["result"] = "failed";
            p["info"] = "密码错误";
            socket->write(p.pack());
            delete sd;
            return;
        }

        p["result"] = "success";
        p["info"] = "登录成功";

        sd->updateUserOnline(username, true);//在线状态

        socket->write(p.pack());
        return;

    }else if(type == "quit"){
        QString username = protocol["username"].toString();

        /** 1. 修改在线状态为离线 **/
        SqlDao* sd = SingleTon<SqlManager>::getInstance()->dao();
        sd->updateUserOnline(username, false);
        delete sd;
    }
}
