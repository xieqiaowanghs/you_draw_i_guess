#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

#include "handler/handler.h"
#include "loginwidget.h"
#include "hallwidget.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    void show();
signals:

public slots:

private:

};

#endif // CLIENT_H
