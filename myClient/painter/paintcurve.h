#ifndef PAINTCURVE_H
#define PAINTCURVE_H

#include "ipainter.h"
#include <QVector>
#include <QLine>

class PaintCurve : public IPainter
{
private:
    QLine line;
public:
    PaintCurve();

    virtual void paint(QPaintDevice *frame);
    virtual void release(const QPoint &pos);
    virtual void press(const QPoint &pos);
    virtual void move(const QPoint &pos);
};

#endif // PAINTCURVE_H
