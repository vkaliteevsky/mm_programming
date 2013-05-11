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
    return QRectF(x, y, width*2, height*2);
}

QPainterPath wall::shape() const
{
  //  QPointF pp1 = QPointF(fcoord+ fcoord2/2 - (fcoord2/2)*cos(angle*3.14159265359/180), scoord-(fcoord2/2)*sin(angle*3.14159265359/180));
  //  QPointF pp2 = QPointF(-pp1.rx(), -pp1.ry());
  //  QPointF  pp3 = QPointF (pp1.rx() - scoord2*sin(angle*3.14159265359/180), pp1.ry()- scoord2*cos(angle*3.14159265359/180));
  //  QPointF  pp4 = QPointF (pp3.rx() + 2*pp2.rx(),pp3.ry()+2*pp2.ry());

  //  QPolygonF polygon;
  //  polygon << pp1 << pp2 << pp4 << pp3 << pp1;

    QPainterPath path;
    path.addRect(x, y, width, height);
//    path.addPolygon(polygon);
    return path;
}

void wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    setRotation(angle);
    painter->setBrush(color);
    painter->drawRect(x, y, width, height);





}

