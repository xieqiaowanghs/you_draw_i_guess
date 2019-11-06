#include "client.h"
#include "singleton.h"
#include "protocol.h"

#include <QTcpSocket>
#include <QHostAddress>

Client::Client(QObject *parent)
    : QObject(parent)
{
    QTcpSocket* socket = SingleTon<QTcpSocket>::getInstance();
    socket->connectToHost(QHostAddress("192.168.1.227"), 7000);

    QObject::connect(socket, &QTcpSocket::readyRead, [=](){
        QByteArray array = socket->readAll();
        Protocol p;
        int len;
        while((len = p.unpack(array)) > 0){
            array = array.mid(len);

            //根据Type，进行不同处理，策略
            Handler::Handle(socket, p);
        }
    });
}

Client::~Client()
{

}

void Client::show()
{
    SingleTon<LoginWidget>::getReference().show();
}
