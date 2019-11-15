#ifndef PAINTER_H
#define PAINTER_H

#include <QPaintDevice>
#include "eraser.h"
#include "paintcircle.h"
#include "paintcurve.h"
#include "paintline.h"
#include "paintrectangle.h"

class Painter
{
public:
    Painter();
    virtual ~Painter();

    void paint(QPaintDevice* frame);
    void press(const QPoint& pos);
    void move(const QPoint& pos);
    void release(const QPoint& pos);
    void choosePaint(const QString& str);
    void setPenSize(int size);
    void setPenColor(QColor& color);
private:
    IPainter* curPainter;
    Eraser* eraser;
    PaintCircle* paintCircle;
    PaintRectangle* paintRectangle;
    PaintLine* paintLine;
    PaintCurve* paintCurve;
    QPen* pen;
};

#endif // PAINTER_H
