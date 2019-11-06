#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include "ihandler.h"
#include "room/roommanager.h"
#include "singleton.h"


class ImageHandler : public IHandler
{
public:
    ImageHandler();

    // IHandler interface
public:


    // IHandler interface
public:
    void handle(QTcpSocket *socket, const Protocol &protocol);
};

#endif // IMAGEHANDLER_H
