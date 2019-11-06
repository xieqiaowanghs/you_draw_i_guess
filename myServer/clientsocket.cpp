#include "clientsocket.h"
#include "protocol.h"
#include "handler/handler.h"

ClientSocket::ClientSocket(QTcpSocket *socket, QObject *parent)
    : QObject(parent),
      socket(socket)
{

    //    QObject::connect(socket, &QTcpSocket::disconnected, [=](){
    //        this->socket->deleteLater();
    //        this->deleteLater();
    //    });
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
