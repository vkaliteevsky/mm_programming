#ifndef ROBOTVIEW_H
#define ROBOTVIEW_H

#include <QGraphicsItem>

class robotview : public QGraphicsRectItem
{
   // Q_OBJECT
public:
    robotview();

    QRectF boundingRect() const;
        QPainterPath shape() const;
//    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void setAngle(qreal nangle);




public:
    qreal vX;
    qreal vY;

//private:
    QColor color;

    qreal momentI;
    qreal weight;
    qreal size;
    qreal angle;
    qreal angle_w;
    qreal V;
    qreal V0;
    qreal r;

};
#endif // ROBOTVIEW_H
