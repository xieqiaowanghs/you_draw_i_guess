#ifndef PAINTRECTANGLE_H
#define PAINTRECTANGLE_H

#include "ipainter.h"
#include <QVector>
#include <QRect>

class PaintRectangle : public IPainter
{
public:
    PaintRectangle();

    virtual void paint(QPaintDevice *frame);
    virtual void release(const QPoint &pos);
private:
    QVector<QRect> rectangles;
};

#endif // PAINTRECTANGLE_H
