#include "paintrectangle.h"

PaintRectangle::PaintRectangle()
{

}

void PaintRectangle::paint(QPaintDevice *frame)
{
    QPainter painter;
    painter.begin(frame);

    painter.drawRects(rectangles);

    if(type == moveType) painter.drawRect(QRect(start, end));

    painter.end();
}

void PaintRectangle::release(const QPoint &pos)
{
    IPainter::release(pos);
    rectangles.append(QRect(start, end));
}
