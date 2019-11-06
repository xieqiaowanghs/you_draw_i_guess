#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include "painter.h"

class MyLabel:public QLabel
{
    Q_OBJECT
public:
    MyLabel(QWidget* parent = nullptr);
    ~MyLabel();

    void init();

    inline Painter* getPainter()const{return painter;}
    void choosePaint(const QString &str);
    void setSize(int size);
    void setPenColor(QColor& color);
    QImage getImage() const;

private:
    Painter* painter;
    QImage image;
    int count;
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
};

#endif // MYLABEL_H
