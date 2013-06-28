#include "world.h"
#include "view/wall.h"
#include <math.h>
#include <QTimer>
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

    Wall* newWall = new Wall(-300,0,800,-50,0,0.2);
    Wall* newWall2 = new Wall(-200,-0,800,-40,10,0.06);
    Wall* newWall3 = new Wall(-80,-50,600,-50,20,0.6);
    Wall* newWall4 = new Wall(-500,-100,100,-50,180,0.6);

    walls.push_back( newWall);
    walls.push_back( newWall2);
    walls.push_back( newWall3);
    walls.push_back( newWall4);

    for (int i = 0; i < walls.length(); i++) {
        scene->addItem(walls.at(i));
    }

    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QColor (170,170,170));
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Robots"));
    view->resize(1024, 768);
    view->show();
    startTimer(10);
}

void world::timerEvent(QTimerEvent *)
{
    for (int i = 0; i < 4; i++)
    {
        robot->setWall(i, NULL);
    }

    for (int i = 0; i < walls.length(); i++) { // Ищет коллизии
        robot->checkCollision(*(walls[i]));
            robot->updateCoord();
    }
    robot->updateVelocity(mDelta); // Считаем изменение скорости и угла

    for (int i = 0; i < 4; i++){ // Вытаскиваем из стен
        for (int j = 0; j < walls.length(); j++) {
            if (robot->isCollision(*(walls[j]), i)) {
                robot->getRobotFromWall(*(walls[j]), i);
            }
            if (robot->isEdgeCollision(*(walls[j]), i)) {
                if (robot->mEdgeWalls[i] != NULL) {
                    robot->getEdgeRobotFromWall(*(walls[j]), i);
                }
            }
        }
    }
    robot->nextStep(mDelta); //Сдвигаем и поварачиваем
}



