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
    //robot->setPos(-200, -40);
    //robot->setPos(-200, -300);


    robot->setPos(-200, 80);


    robot->update();
    scene->addItem(robot);

    robot->w=this;//for debug


    newWall = new Wall(-300,0,600,-50,0,0.4);
    //newWall = new Wall(-300,0,280,-50,30,0.4);
    Wall* newWall2 = new Wall(100,-150,500,-40,50,0.4);
    //newWall = new Wall(-300,0,600,-50,30,0.1);

    //QMessageBox ms;
    //ms.setText(QString::number( );
    //ms.exec();


    walls[0]=(newWall);
    walls[1]=(newWall2);
    scene->addItem(newWall);
    scene->addItem(newWall2);

    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QColor (170,170,170));
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Robots"));
    //view->resize(800, 600);
    view->resize(1024, 768);
    view->show();
    startTimer(10);
}

void world::timerEvent(QTimerEvent *)
{
    robot->nextStep(mDelta);

    robot->update();

    for (int i = 0; i < 2; i++) {
        //robot->checkCollision(*newWall);
        robot->checkCollision(*(walls[i]));
            robot->update();
    }

    robot->updateVelocity(mDelta);
    robot->updateWalls();
    robot->update();
}



