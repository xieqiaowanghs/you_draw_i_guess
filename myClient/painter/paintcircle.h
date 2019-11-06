#ifndef PAINTCIRCLE_H
#define PAINTCIRCLE_H
#include "ipainter.h"
#include <QVector>

class PaintCircle : public IPainter
{
public:
    PaintCircle();

    virtual void paint(QPaintDevice *frame);
    virtual void release(const QPoint &pos);
    virtual void press(const QPoint &pos);
    virtual void move(const QPoint &pos);
private:
    QRect circle;
    QVector<QRect> circles;
};

#endif // PAINTCIRCLE_H
