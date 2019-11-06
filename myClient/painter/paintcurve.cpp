#include "paintcurve.h"
#include <QDebug>
#include "singleton.h"

PaintCurve::PaintCurve()
{
    pen = SingleTon<QPen>::getInstance();
}

void PaintCurve::paint(QPaintDevice *frame)
{
    QPainter painter;
    painter.begin(frame);
    painter.setPen(*pen);
    painter.drawLine(line);
    painter.end();
}

void PaintCurve::release(const QPoint &pos)
{
    start = end;
    end = pos;
    type = releaseType;
    line = QLine(start, end);
}

void PaintCurve::press(const QPoint &pos)
{
    start = pos;
    end = pos;
    type = pressType;
    line = QLine(start, end);
}

void PaintCurve::move(const QPoint &pos)
{
     start = end;
     end = pos;
     type = moveType;
     line = QLine(start, end);
}
