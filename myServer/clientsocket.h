#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>

class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(QTcpSocket* socket, QObject *parent = nullptr);

signals:

public slots:

private:
    QTcpSocket* socket;
};

#endif // CLIENTSOCKET_H
