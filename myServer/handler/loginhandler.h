#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H

#include "ihandler.h"

class LoginHandler : public IHandler
{
public:
    LoginHandler();

    // IHandler interface
public:
    virtual void handle(QTcpSocket *socket, const Protocol &protocol);
};

#endif // LOGINHANDLER_H
