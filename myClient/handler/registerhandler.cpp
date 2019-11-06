#include "registerhandler.h"
#include "singleton.h"

#include <QTcpSocket>
#include <QMessageBox>

RegisterHandler::RegisterHandler()
{

}

void RegisterHandler::regist(const QString &username, const QString &password)
{
    Protocol p(Protocol::regist);
    p["type"] = "regist";
    p["username"] = username;
    p["password"] = password;

    SingleTon<QTcpSocket>::getInstance()->write(p.pack());//发送个服务器
}


void RegisterHandler::handle(QTcpSocket *, const Protocol &protocol)
{
    QString result = protocol["result"].toString();
    QString info = protocol["info"].toString();

    if(result == "success"){
        QMessageBox::information(nullptr, "注册信息", info);
    }else if(result == "failed"){
        QMessageBox::warning(nullptr, "注册信息", info);
    }
}
