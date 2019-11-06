#include "ipainter.h"
#include "singleton.h"

IPainter::IPainter()
    :type(none)
{

}

IPainter::~IPainter()
{

}

void IPainter::press(const QPoint &pos)
{
    start = pos;
    type = pressType;
}

void IPainter::move(const QPoint &pos)
{
    end = pos;
    type = moveType;
}

void IPainter::release(const QPoint &pos)
{
    end = pos;
    type = releaseType;
}
