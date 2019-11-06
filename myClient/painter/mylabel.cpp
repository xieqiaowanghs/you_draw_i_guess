#include "mylabel.h"
#include <QMouseEvent>
#include <QDebug>
#include "protocol.h"
#include <QTcpSocket>
#include "singleton.h"
#include "handler/imagehandler.h"
#include "gamereadywidget.h"

MyLabel::MyLabel(QWidget *parent)
    : QLabel (parent),count(0)
{
    painter = new Painter;
}

MyLabel::~MyLabel()
{
    delete painter;
}

void MyLabel::init()
{
    image = QImage(this->size(), QImage::Format_RGB32);
    image.fill(Qt::white);
    this->setPixmap(QPixmap::fromImage(image));
}

void MyLabel::choosePaint(const QString &str)
{
    painter->choosePaint(str);
}

void MyLabel::setSize(int size)
{
    painter->setPenSize(size);
}

void MyLabel::setPenColor(QColor &color)
{
    painter->setPenColor(color);
}

QImage MyLabel::getImage() const
{
    return image;
}

void MyLabel::mousePressEvent(QMouseEvent *event)
{
    painter->press(event->pos());
    painter->paint(&image);
    this->setPixmap(QPixmap::fromImage(image));
    //图片压缩
    QBuffer buffer;
    image.save(&buffer, "jpg");
    //图片发送
    ImageHandler ih;
    QString username = SingleTon<GameReadyWidget>::getInstance()->getUsername();
    QString roomName = SingleTon<GameReadyWidget>::getInstance()->getRoomName();
    ih.sendPicture(username,roomName,buffer.data());
}

void MyLabel::mouseReleaseEvent(QMouseEvent *event)
{
    painter->release(event->pos());
    painter->paint(&image);
    this->setPixmap(QPixmap::fromImage(image));
    //图片压缩
    QBuffer buffer;
    image.save(&buffer, "jpg");
    //图片发送
    ImageHandler ih;
    QString username = SingleTon<GameReadyWidget>::getInstance()->getUsername();
    QString roomName = SingleTon<GameReadyWidget>::getInstance()->getRoomName();
    ih.sendPicture(username,roomName,buffer.data());
}

void MyLabel::mouseMoveEvent(QMouseEvent *event)
{
    painter->move(event->pos());
    painter->paint(&image);
    this->setPixmap(QPixmap::fromImage(image));   
    //图片压缩
    QBuffer buffer;
    image.save(&buffer, "jpg");
    //图片发送
    ImageHandler ih;
    QString username = SingleTon<GameReadyWidget>::getInstance()->getUsername();
    QString roomName = SingleTon<GameReadyWidget>::getInstance()->getRoomName();
    ih.sendPicture(username,roomName,buffer.data());
}
