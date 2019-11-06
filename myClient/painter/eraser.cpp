#include "eraser.h"

Eraser::Eraser()
{
    pen = new QPen;
    pen->setColor(Qt::white);
    pen->setWidth(20);
}

Eraser::~Eraser()
{
    delete pen;
}

void Eraser::paint(QPaintDevice *frame)
{
    QPainter painter;
    painter.begin(frame);
    painter.setPen(*pen);
    painter.drawLine(line);
    painter.end();
}

void Eraser::release(const QPoint &pos)
{
    start = end;
    end = pos;
    type = releaseType;
    line = QLine(start, end);
}

void Eraser::press(const QPoint &pos)
{
    start = pos;
    end = pos;
    type = pressType;
    line = QLine(start, end);
}

void Eraser::move(const QPoint &pos)
{
    start = end;
    end = pos;
    type = moveType;
    line = QLine(start, end);
}
