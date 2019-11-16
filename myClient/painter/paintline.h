#ifndef PAINTLINE_H
#define PAINTLINE_H

#include "ipainter.h"
#include <QVector>
#include <QLine>

class PaintLine : public IPainter
{
public:
    PaintLine();
    virtual void paint(QPaintDevice *frame);
    virtual void release(const QPoint &pos);
private:
    QVector<QLine> lines;

};

#endif // PAINTLINE_H
