#include "world.h"
#include "view/wall.h"
#include <math.h>
#include <QTimer>
#include <QMessageBox>
#include <math.h>



world::world(QWidget *parent)
    :QWidget(parent)
{
    scene = new QGraphicsScene(-300, -300, 600, 600);
    view = new QGraphicsView(parent);
    view->setScene(scene);
    mDelta = 0.05;
    robot = new robotview;
    robot->setPos(-200, -40);
    robot->update();
    scene->addItem(robot);

    robot->w=this;//for debug

    newWall = new Wall(-300,0,600,-50,30,0.4);
    scene->addItem(newWall);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QColor (170,170,170));
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Robots"));
    view->resize(800, 600);
    view->show();
    startTimer(10);
}

void world::timerEvent(QTimerEvent *)
{
    robot->nextStep(mDelta);
    robot->checkCollision(*newWall);
    robot->updateWalls();
    robot->update();
    robot->updateVelocity(mDelta);
}



