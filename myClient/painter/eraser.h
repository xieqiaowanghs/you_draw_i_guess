#ifndef ERASER_H
#define ERASER_H

#include "ipainter.h"
#include <QLine>

class Eraser : public IPainter
{
private:
    QLine line;
public:
    Eraser();
    ~Eraser();

    virtual void paint(QPaintDevice *frame);
    virtual void release(const QPoint &pos);
    virtual void press(const QPoint &pos);
    virtual void move(const QPoint &pos);
};

#endif // ERASER_H
