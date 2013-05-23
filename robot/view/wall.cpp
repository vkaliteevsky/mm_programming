#include <QPainter>

#include "wall.h"
#include <math.h>

Wall::Wall(qreal _x,qreal _y,qreal _width,qreal _height,qreal _angle,qreal _fric)
    : color(150,20,20)
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    angle = _angle;
    fric = _fric;
    true_coord2();
}

QRectF Wall::boundingRect() const
{
    return QRectF(x-width*1.5, y-height*1.5, width*3, height*3);
}

QPainterPath Wall::shape() const
{
    QPainterPath path;
    path.addRect(x, y, width, height);
    return path;
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    setRotation(angle);
    painter->setBrush(color);
    painter->drawRect(x, y, width, height);
   // painter->drawLine();






}

void Wall::setLines(QPointF p1, QPointF p2, QPointF p3, QPointF p4)
{
    linesList.push_back(QLineF(p1,p2));
    linesList.push_back(QLineF(p2,p3));
    linesList.push_back(QLineF(p3,p4));
    linesList.push_back(QLineF(p4,p1));
}

void Wall::true_coord2( )
{
    QPoint p1 = QPoint(getX()                      ,getY());
    QPoint p2 = QPoint(getX() + getWidth() ,getY());
    QPoint p3 = QPoint(getX() + getWidth() ,getY() + getHeight());
    QPoint p4 = QPoint(getX()                      ,getY() + getHeight());

    qreal angRad = getAngle()*M_PI/180;

    p1 = QPoint(p1.rx()*cos(angRad) - p1.ry()*sin(angRad), p1.rx()*sin(angRad) + p1.ry()*cos(angRad));
    p2 = QPoint(p2.rx()*cos(angRad) - p2.ry()*sin(angRad), p2.rx()*sin(angRad) + p2.ry()*cos(angRad));
    p3 = QPoint(p3.rx()*cos(angRad) - p3.ry()*sin(angRad), p3.rx()*sin(angRad) + p3.ry()*cos(angRad));
    p4 = QPoint(p4.rx()*cos(angRad) - p4.ry()*sin(angRad), p4.rx()*sin(angRad) + p4.ry()*cos(angRad));

    setLines(p1, p2, p3, p4);
}
