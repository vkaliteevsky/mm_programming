#ifndef WALL_H
#define WALL_H

#include <QtWidgets/QGraphicsItem>
#include <QPoint>


class Wall : public QGraphicsRectItem
{
public:
    Wall(qreal x,qreal y,qreal width,qreal heidth,qreal angle,qreal fric);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    bool contain(QPointF point);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void* r;

public:
    bool isNotNear(QPointF point);
    void setLines(QPointF p1, QPointF p2, QPointF p3, QPointF p4);
    void true_coord2();
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
    qreal getFric()
    {
        return fric;
    }
    QList<QLineF> linesList;
    QPointF mP[4];


private:
    qreal x;
    qreal y;
    qreal width;
    qreal height;
    qreal angle;
    qreal fric;//friction coefficient
    QColor color;
        void* w;



};

#endif // WALL_H
