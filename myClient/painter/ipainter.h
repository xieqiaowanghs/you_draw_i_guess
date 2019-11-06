#ifndef IPAINTER_H
#define IPAINTER_H

#include <QPaintDevice>
#include <QPainter>

class IPainter
{
public:
    enum Type{
        none = 0,
        pressType,
        moveType,
        releaseType
    };

public:
    IPainter();
    virtual ~IPainter();

    virtual void press(const QPoint& pos);
    virtual void move(const QPoint& pos);
    virtual void release(const QPoint& pos);
    virtual void paint(QPaintDevice* frame)=0;

protected:
    Type type;
    QPoint start;
    QPoint end;
    QPen* pen;
};

#endif // IPAINTER_H
