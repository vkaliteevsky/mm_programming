#ifndef WALL_H
#define WALL_H

#include <QtWidgets/QGraphicsItem>
#include <QPoint>

class wall : public QGraphicsRectItem
{
public:
    wall(qreal x,qreal y,qreal width,qreal heidth,qreal angle,qreal fric);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    void setLines(QPointF p1, QPointF p2, QPointF p3, QPointF p4);
    qreal getX()
    {
        return x;
    }
    qreal getY()
    {
        return y;
    }
    qreal getWidth()
    {
        return width;
    }
    qreal getHeight()
    {
        return height;
    }
    qreal getAngle()
    {
        return angle;
    }

private:
    qreal x;
    qreal y;
    qreal width;
    qreal height;
    qreal angle;
    qreal fric;//friction coefficient
    QColor color;

    QList<QLineF> linesList;

};

#endif // WALL_H
