#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include "view/robotview.h"
#include "view/wall.h"

class world : public QWidget
{
    Q_OBJECT
public:
    world(QWidget *parent = 0);
    // void run();

        QGraphicsScene* scene;


protected:
    void timerEvent(QTimerEvent *event);
    QPointF interPoint(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal x4, qreal y4);

private:
    QPointF getRobotFromWall();
    QLineF interRobotLine();
    void normalRobot(QPointF point, QLineF line);
    qreal trueAngle(qreal angle);
    QPointF normalPoint(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3);
    void turnAndMoveRobot(qreal nAngle_w, qreal V);

    QGraphicsView* view;
    Wall* newWall;
    robotview* robot;
    QGraphicsLineItem* line2;

    bool isRobotContact;
    bool stop;

    void true_coord();
    void true_coord2(Wall &w);
    QPointF pp1;
    QPointF pp2;
    QPointF curPoint;
    qreal mDelta;

    QLineF intLine;
    QPointF intPoint;

};

#endif // WORLD_H
