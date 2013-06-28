#ifndef ROBOTVIEW_H
#define ROBOTVIEW_H

#include "view/wall.h"
#include <QtWidgets/QGraphicsItem>
#include <QVector2D>


class robotview : public QGraphicsRectItem
{
public:
    robotview();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void setAngle(qreal nangle);
    void setWall(int index, Wall* wall){mWalls[index] = wall;}
    void setEdgeWall(int index, Wall* wall){mEdgeWalls[index] = wall;}
    void nextStep(qreal dt);
    void checkCollision(Wall &wall);
    bool isCollision(Wall &wall, int i);
    bool isEdgeCollision(Wall &wall, int i);
    void updateWalls();
    void updateVelocity(qreal dt);
    void updateAngle();
    void updateCoord();
    QVector2D mul(QVector2D vector, qreal scalar);


    void getRobotFromWall(Wall& wall, int index);
    void getEdgeRobotFromWall(Wall& wall, int index);

    QLineF interRobotLine(Wall& wall);
    QLineF interWallLine(Wall& wall);
    QLineF nearRobotLine(Wall& wall, QPointF p);
    QPointF normalPoint(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3);
    qreal length(QPointF vector);
    qreal scalarProduct(QVector2D vector1, QVector2D vector2);
    qreal vectorProduct(QVector2D vector1, QVector2D vector2);
    bool isParallel(QLineF l1, QLineF l2);
    void setV(QVector2D &V);
    QVector2D getV() const;
    void update();


    Wall* mWalls[4]; // Массив вершин, хранящих указатели на стены
    Wall* mEdgeWalls[4]; // Массив ребер, хранящих указатели на стены

    qreal getAngle()
    {
        return mAngle;
    }
    qreal getMass()
    {
        return mMass;
    }
    qreal getSize()
    {
        return mSize;
    }
    qreal getFullSpeed()
    {
        return mFullSpeed;
    }
    qreal getInertiaMoment()
    {
        return mMomentI;
    }
    qreal getMotorFactor()
    {
        return mMotorFactor;
    }
    qreal getAngularVelocity()
    {
        return mAngularVelocity;
    }
    QVector2D getForce()
    {
        return mForce;
    }
    qreal getForceMoment()
    {
        return mForceMoment;
    }
    void setForce(QVector2D force)
    {
        mForce = force;
    }
    void setForceMoment(qreal forceMoment)
    {
        mForceMoment = forceMoment;
    }

    QList<QPointF> mEdP; // Массив вершин(стен), которые попали внутрь робота
    QPointF mP[4]; // Массив вершин робота
    QLineF mL[4]; // Массив ребер робота

private:
    QVector2D mForce;//vector
    qreal mForceMoment;
    QVector2D mV; //velocity vector
    qreal mAngle;
    qreal mMass;
    qreal mSize;
    qreal mFullSpeed;
    const qreal mMomentI;
    const qreal mMotorFactor;
    qreal mAngularVelocity;

};
#endif // ROBOTVIEW_H
