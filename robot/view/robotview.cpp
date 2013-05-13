#include "robotview.h"

#include <QMessageBox>

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

#include <math.h>

robotview::robotview()
    : angle(-56.0), weight(5.0), size(0.2), V0(4)
{
    setRotation(angle);
}

QRectF robotview::boundingRect() const
{
    QRectF rect(-20, -20,40, 40);
    return rect;
}

QPainterPath robotview::shape() const
{
    QPainterPath path;
    path.addRect(-20, -20, 40, 40);
    return path;
}

void robotview::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    setRotation(angle);
    painter->setBrush(QColor(121,121,121));
    painter->drawRect(-20,-20,40,40);

}

void robotview::setAngle(qreal nangle)
{
    angle = nangle;
}


