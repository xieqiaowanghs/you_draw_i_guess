#include "paintline.h"

PaintLine::PaintLine()
{

}

void PaintLine::paint(QPaintDevice *frame)
{
    QPainter painter;
    painter.begin(frame);

    painter.drawLines(lines);

    if(type == moveType) painter.drawLine(start, end);

    painter.end();
}

void PaintLine::release(const QPoint &pos)
{
    IPainter::release(pos);
    lines.append(QLine(start, end));
}
