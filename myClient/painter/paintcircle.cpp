#include "paintcircle.h"

PaintCircle::PaintCircle()
{

}

void PaintCircle::paint(QPaintDevice *frame)
{
    QPainter painter;
    painter.begin(frame);

//    int i;
//    for(i = 0; i < circles.size(); i++){
//        painter.drawEllipse(circles[i]);
//    }

//    if(type == moveType) painter.drawEllipse(QRect(start, end));
    painter.drawEllipse(circle);

    painter.end();
}

void PaintCircle::release(const QPoint &pos)
{
    IPainter::release(pos);
    circle = QRect(start, end);
}


void PaintCircle::press(const QPoint &pos)
{
    IPainter::press(pos);
    circle = QRect(start, end);
}

void PaintCircle::move(const QPoint &pos)
{
    IPainter::move(pos);
    circle = QRect(start, end);
}
