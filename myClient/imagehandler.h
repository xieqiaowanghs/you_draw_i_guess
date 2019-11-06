#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include "ihandler.h"
#include "protocol.h"
#include "singleton.h"
#include "gamingwidget.h"
#include <QTcpSocket>
#include <QTextCodec>
#include <QBuffer>
class ImageHandler : public IHandler
{
public:
    ImageHandler();
    void sendPicture(const QString& username,const QString& roomName,
                     const QByteArray& bytes);
    void handle(QTcpSocket *socket,const Protocol &protocol);
};

#endif // IMAGEHANDLER_H
