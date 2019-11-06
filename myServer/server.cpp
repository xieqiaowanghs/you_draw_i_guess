#include "server.h"
#include "clientsocket.h"
#include "dao/sqlmanager.h"
#include "singleton.h"

Server::Server(QObject *parent)
    : QObject(parent),
      server(nullptr), port(0)
{
    SqlManager* manager = SingleTon<SqlManager>::getInstance();
    manager->setHostname("localhost");
    manager->setUsername("root");
    manager->setPassword("123456");
    manager->setPort(3306);
    manager->setDatabaseName("account");

    manager->init("MYSQL");
    manager->open();
//    qDebug()<<"打一个啊";
}

void Server::initServer()
{
    server = new QTcpServer(this);
    server->listen(QHostAddress(ip), port);

    QObject::connect(server, &QTcpServer::newConnection, [=](){
        while(server->hasPendingConnections()){
            QTcpSocket* socket = server->nextPendingConnection();
            if(socket){
                new ClientSocket(socket, this);
            }
        }
    });
}

void Server::initServer(const QString &ip, int port)
{
    this->setIp(ip);
    this->setPort(port);
    this->initServer();
}
