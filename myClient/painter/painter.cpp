#include "painter.h"
#include "singleton.h"

Painter::Painter()
    :curPainter(nullptr),
    eraser(new Eraser),
    paintCircle(new PaintCircle),
    paintRectangle(new PaintRectangle),
    paintLine(new PaintLine),
    paintCurve(new PaintCurve)
{
    pen = SingleTon<QPen>::getInstance();
}

Painter::~Painter()
{
    delete paintCircle;
    delete paintRectangle;
    delete paintLine;
    delete paintCurve;
}

void Painter::paint(QPaintDevice *frame)
{
    if(curPainter)  curPainter->paint(frame);
}

void Painter::press(const QPoint &pos)
{
     if(curPainter)  curPainter->press(pos);
}

void Painter::move(const QPoint &pos)
{
     if(curPainter)  curPainter->move(pos);
}

void Painter::release(const QPoint &pos)
{
    if(curPainter)  curPainter->release(pos);
}

void Painter::choosePaint(const QString &str)
{
    if(str == "圆"){
        curPainter = paintCircle;
    }else if(str == "矩形"){
        curPainter = paintRectangle;
    }else if(str == "线"){
        curPainter = paintLine;
    }else if(str == "曲线"){
        curPainter = paintCurve;
    }else if(str == "橡皮"){
        curPainter = eraser;
    }else{
        curPainter = nullptr;
    }
}

void Painter::setPenSize(int size)
{
    pen->setWidth(size);
}

void Painter::setPenColor(QColor& color)
{
    pen->setColor(color);
}
