#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "view/robotview.h"
#include "view/wall.h"

class world : public QWidget
{
    Q_OBJECT
public:
    world(QWidget *parent = 0);
   // void run();

protected:
    void timerEvent(QTimerEvent *event);
    QPointF interPoint(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal x4, qreal y4);

private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    wall* newWall;
    robotview* robot;
    QGraphicsLineItem* line2;

    bool mColl;

    //QPoint direction;
    void true_coord();
    QPointF pp1;
    QPointF pp2;
    QPointF curPoint;

    QLineF vector;


};

#endif // WORLD_H
