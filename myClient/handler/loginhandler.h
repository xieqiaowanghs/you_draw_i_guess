#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H

#include "ihandler.h"

class LoginHandler : public IHandler
{
public:
    LoginHandler();

    void login(const QString& username, const QString& password);
    void quit(const QString& username);

    // IHandler interface
public:
    virtual void handle(QTcpSocket *socket, const Protocol &protocol);
};

#endif // LOGINHANDLER_H
