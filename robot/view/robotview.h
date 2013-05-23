#ifndef ROBOTVIEW_H
#define ROBOTVIEW_H

//#include "view/world.h"
#include "view/wall.h"
#include <QtWidgets/QGraphicsItem>
#include <QVector2D>


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
    void setWall(int index, Wall* wall){mWalls[index] = wall;}
    void nextStep(qreal dt);
    void checkCollision(Wall &wall);
    void updateWalls();
    void updateVelocity(qreal dt);
    void updateAngle();
    QPointF mul(QPointF vector, qreal scalar);
    QString toString(QPointF point);

    void getRobotFromWall(Wall& wall, int index);
    QPointF interPoint(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal x4, qreal y4);
    QLineF interRobotLine(Wall& wall);
    QPointF normalPoint(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3);
    qreal length(QPointF vector);
    qreal scalarProduct(QPointF vector1, QPointF vector2);
    qreal vectorProduct(QPointF vector1, QPointF vector2);
    QPointF normalize(QPointF vector);
    void* w;

public:



    Wall* mWalls[4];

    void update();
    //private:





    qreal motorFactor;
    qreal angle;
    qreal mass;
    qreal size;

    qreal mAngularVelocity;
    QPointF mV;//vector

    qreal V0;
        const qreal momentI;
    QPointF mForce;//vector
    qreal mForseMoment;


    QPointF mP[4];


};
#endif // ROBOTVIEW_H
