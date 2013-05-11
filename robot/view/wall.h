#ifndef WALL_H
#define WALL_H

#include <QGraphicsItem>
#include <QPoint>

class wall : public QGraphicsRectItem
{
public:
    wall(qreal x,qreal y,qreal width,qreal heidth,qreal angle,qreal fric);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
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

};

#endif // WALL_H
