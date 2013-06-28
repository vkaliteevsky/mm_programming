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
    QPointF mul(QPointF vector, qreal scalar);
    QString toString(QPointF point);

    void getRobotFromWall(Wall& wall, int index);
    void getEdgeRobotFromWall(Wall& wall, int index);

    QPointF interPoint(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal x4, qreal y4);
    QLineF interRobotLine(Wall& wall);
    QLineF interWallLine(Wall& wall);
    QLineF nearRobotLine(Wall& wall, QPointF p);
    QPointF normalPoint(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3);
    qreal length(QPointF vector);
    qreal scalarProduct(QPointF vector1, QPointF vector2);
    qreal vectorProduct(QPointF vector1, QPointF vector2);
    QPointF normalize(QPointF vector);
    bool isParallel(QLineF l1, QLineF l2);
    void setV(QPointF& V);
    QPointF getV()const;
    void update();
    QPointF mPos;

    Wall* mWalls[4];
    Wall* mEdgeWalls[4];

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
    QPointF getForce()
    {
        return mForce;
    }
    qreal getForceMoment()
    {
        return mForceMoment;
    }
    void setForce(QPointF force)
    {
        mForce = force;
    }
    void setForceMoment(qreal forceMoment)
    {
        mForceMoment = forceMoment;
    }

    QList<QPointF> mEdP;
    QPointF mP[4];
    QLineF mL[4];

private:
    QPointF mForce;//vector
    qreal mForceMoment;
    QPointF mV; //velocity vector
    qreal mAngle;
    qreal mMass;
    qreal mSize;
    qreal mFullSpeed;
    const qreal mMomentI;
    const qreal mMotorFactor;
    qreal mAngularVelocity;

};
#endif // ROBOTVIEW_H
