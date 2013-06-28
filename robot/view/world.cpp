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
    robot->setPos(-200, 50);


    robot->updateCoord();
    scene->addItem(robot);

    robot->w=this;//for debug

    //newWall = new Wall(-300,0,800,-50,0,0.2);
    //Wall* newWall2 = new Wall(-200,-0,800,-40,10,0.06);
    //Wall* newWall3 = new Wall(-400,-300,800,-50,100,0.6);
    newWall = new Wall(-300,0,800,-50,0,0.2);
    Wall* newWall2 = new Wall(-200,-0,800,-40,10,0.06);
    Wall* newWall3 = new Wall(-80,-50,600,-50,20,0.6);
    Wall* newWall4 = new Wall(-500,-100,100,-50,180,0.6);
    //Wall* newWall4 = new Wall(-180,20,100,-50,0,0.6);

    walls[0]=(newWall);
    walls[1]=(newWall2);
    walls[2]=(newWall3);
        walls[0]->r = robot;
    walls[3]=(newWall4);
    scene->addItem(newWall);
    scene->addItem(newWall2);
    scene->addItem(newWall3);
    scene->addItem(newWall4);

    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QColor (170,170,170));
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Robots"));
    view->resize(1024, 768);
    view->show();
    startTimer(10);
}

void world::timerEvent(QTimerEvent *)
{
    robot->mCounter++;
    for (int i = 0; i < 4; i++)
    {
        robot->setWall(i, NULL);
    }


    robot->updateCoord();



    for (int i = 0; i < 4; i++) {//po stenam
        robot->checkCollision(*(walls[i]));
            robot->updateCoord();
    }
    robot->updateVelocity(mDelta);





    robot->updateCoord();

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {//po stenam
            if (robot->isCollision(*(walls[j]), i)) {

            //if (robot->mWalls[i] != NULL) {
                robot->getRobotFromWall(*(walls[j]), i);

            }
            if (robot->isEdgeCollision(*(walls[j]), i)) {


                if (robot->mEdgeWalls[i] != NULL)
                robot->getEdgeRobotFromWall(*(walls[j]), i);
            }
            //}
        }
    }
    robot->nextStep(mDelta);
    robot->updateCoord();



    //robot->updateWalls();


}



