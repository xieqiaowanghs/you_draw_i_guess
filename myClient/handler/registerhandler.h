#ifndef REGISTERHANDER_H
#define REGISTERHANDER_H

#include "ihandler.h"
class RegisterHandler : public IHandler
{
public:
    RegisterHandler();
    void regist(const QString& username, const QString& password);

    // IHandler interface
public:
    virtual void handle(QTcpSocket *socket, const Protocol &protocol);

};

#endif // REGISTERHANDER_H
