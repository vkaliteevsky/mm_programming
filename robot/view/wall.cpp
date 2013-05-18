#include <QPainter>

#include "wall.h"
#include <math.h>

wall::wall(qreal _x,qreal _y,qreal _width,qreal _height,qreal _angle,qreal _fric)
    : color(121,121,121)
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    angle = _angle;
    fric = _fric;
}

QRectF wall::boundingRect() const
{
    return QRectF(x-width, y-height, width*2, height*2);
}

QPainterPath wall::shape() const
{
    QPainterPath path;
    path.addRect(x, y, width, height);
    return path;
}

void wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    setRotation(angle);
    painter->setBrush(color);
    painter->drawRect(x, y, width, height);
}

void wall::setLines(QPointF p1, QPointF p2, QPointF p3, QPointF p4)
{
    linesList.push_back(QLineF(p1,p2));
    linesList.push_back(QLineF(p2,p3));
    linesList.push_back(QLineF(p3,p4));
    linesList.push_back(QLineF(p4,p1));
}
