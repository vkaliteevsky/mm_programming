#include "world.h"
#include "view/wall.h"
#include <math.h>
#include <QTimer>
#include <QMessageBox>
#include <math.h>



world::world(QWidget *parent)
    :QWidget(parent), mColl(false)
{

    scene = new QGraphicsScene(-300, -300, 600, 600);
    view = new QGraphicsView(parent);
    view->setScene(scene);
    mDelta = 0.1;
    stop = false;
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    robot = new robotview;
    robot->setPos(-115, 200);
    scene->addItem(robot);

    newWall = new wall(-300,0,600,-50,-20,0.4);

    true_coord();
    line2 = new QGraphicsLineItem(pp1.rx(),pp1.ry(),pp2.rx(),pp2.ry());
    scene->addItem(line2);

    scene->addItem(newWall);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QColor (121,121,9));
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Robots"));
    view->resize(800, 600);
    view->show();
    startTimer(40);

}

void world::true_coord()
{
    qreal x = newWall->getX();
    qreal y = newWall->getY();
    qreal w = newWall->getWidth();
    qreal a = newWall->getAngle();

    pp1 = QPointF(x+ w/2 - (w/2)*cos(a*M_PI/180), y-(w/2)*sin(a*M_PI/180));
    pp2 = QPointF(-pp1.rx(), -pp1.ry());
}

void world::timerEvent(QTimerEvent *)
{
    if (!stop){

        qreal del = mDelta;

        if(!robot->collidesWithItem(newWall)){
            robot->setAngle(robot->angle);
            robot->setPos(robot->pos().rx() + robot->V0*del*cos(robot->angle * M_PI/180)
                          , robot->pos().ry() + robot->V0*del*sin(robot->angle* M_PI/180));
        } else {
            if (mColl == false){
                getRobotFromWall();
            } else {
                qreal originAngle = newWall->getAngle();
                qreal alpha = robot->angle - originAngle;
                qreal gamma = robot->angle_w;
                qreal I = robot->momentI;
                qreal m = robot->weight;
                qreal forseMoment;
                qreal K = 0.05;
                qreal Kv = 0.3;
                qreal F;
                qreal F_fr;
                qreal r = robot->r;
                qreal V = robot->V;

                F = (robot->V0 - V)*Kv;
                F_fr = F * sin(-1*alpha * M_PI/180)*K;
                forseMoment = F_fr * r * sin(-1*alpha * M_PI/180) - F * sin(-1*alpha * M_PI/180) * sin ((45 - (-1)*alpha)*M_PI/180) * r;

                qreal nAngle;
                qreal nAngle_w;
                qreal nV;

                nAngle_w = gamma + forseMoment*del/I;
                nAngle = (alpha + originAngle) - gamma * del;//?

                if ((alpha <= 1)&&(alpha >= -1)){
                    robot->setPos(robot->pos().rx() +robot->V0*del*cos(newWall->getAngle()*M_PI/180)
                                  , robot->pos().ry()+robot->V0*del*sin(newWall->getAngle()*M_PI/180));
                } else if (alpha <= -89){
                    robot->angle = -90 + originAngle;
                    stop = true;


                } else {
                    nV = V + (F * cos(alpha*M_PI/180) - F_fr)*del/m;

                    robot->setAngle(nAngle);
                    turnAndMoveRobot(nAngle_w, V);
                    robot->angle = nAngle;
                    robot->angle_w = nAngle_w;

                    QGraphicsRectItem * ss = new QGraphicsRectItem(0, 100, 300, 200);
                    ss->setBrush(QColor(121,121,9));
                    scene->addItem(ss);
                    QGraphicsTextItem *text = new QGraphicsTextItem(" F = " + QString::number(F)
                                                                    + "\n V = " + QString::number(V)
                                                                    + "\n Ftp = " + QString::number(F_fr)
                                                                    + "\n M = " + QString::number(forseMoment)
                                                                    + "\n angle = " + QString::number(alpha)
                                                                    + "\n momentI = " + QString::number(robot->momentI)
                                                                    + "\n angle_w = " + QString::number(gamma) );

                    text->setPos(0, 100);
                    text->setFont(QFont ("Courier", 14));
                    scene->addItem(text);

                    robot->V = nV;
                }
            }
        }

    }
}

QPointF world::interPoint(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal x4, qreal y4)
{
    qreal a1 = (y2-y1)/(x2-x1);
    qreal b1 = y1 - x1*a1;

    qreal a2 = (y4-y3)/(x4-x3);
    qreal b2 = y3 - x3*a2;

    qreal cx = (b2-b1)/(a1-a2);
    qreal cy = a1 * cx + b1;
    return QPointF(cx, cy);
}

void world::turnAndMoveRobot(qreal nAngle_w, qreal V)
{

    qreal newX = curPoint.rx()*cos(nAngle_w *M_PI/180) + curPoint.ry()*sin(nAngle_w *M_PI/180);
    qreal newY = -1*curPoint.rx()*sin(nAngle_w *M_PI/180) + curPoint.ry()*cos(nAngle_w*M_PI/180);

    robot->setPos(robot->pos().rx() + curPoint.rx() - newX
                  , robot->pos().ry() + curPoint.ry() - newY);

    robot->setPos(robot->pos().rx() + V * mDelta*cos(newWall->getAngle()*M_PI/180)
                  , robot->pos().ry() + V * mDelta*sin(newWall->getAngle()*M_PI/180));

}

void world::getRobotFromWall()
{
    qreal del = mDelta;
    QPointF pos = robot->pos();
    qreal x = pos.x();
    qreal y = pos.y();
    qreal nx = robot->V0*del*cos(robot->angle * M_PI/180);
    qreal ny = robot->V0*del*sin(robot->angle * M_PI/180);

    qreal gip = sqrt(nx*nx + ny*ny);

    qreal nnx = nx*20/gip;
    qreal nny = ny*20/gip;

    QPointF p1 = QPoint(x + nnx + nny, y + nny - nnx);
    QPointF p2 = QPoint(x + nnx - nny, y + nny + nnx);
    QPointF p3 = QPoint(x - nnx - nny, y - nny + nnx);
    QPointF p4 = QPoint(x - nnx + nny, y - nny - nnx);
    QPointF new_p1 = newWall->mapFromScene(p1);
    QPointF new_p2 = newWall->mapFromScene(p2);
    QPointF new_p3 = newWall->mapFromScene(p3);
    QPointF new_p4 = newWall->mapFromScene(p4);
    if (newWall->contains(new_p1))
    {
        curPoint.setX(p1.rx());
        curPoint.setY(p1.ry());
    }
    else if (newWall->contains(new_p2))
    {
        curPoint.setX(p2.rx());
        curPoint.setY(p2.ry());
    }
    else   if (newWall->contains(new_p3))
    {
        curPoint.setX(p3.rx());
        curPoint.setY(p3.ry());
    }
    else  if (newWall->contains(new_p4))
    {
        curPoint.setX(p4.rx());
        curPoint.setY(p4.ry());
    }
    QLineF line1 = QLineF(line2->line());
    QLineF line3(curPoint, QPointF(curPoint.x() -nnx*3,curPoint.ry()-nny*3));
    QPointF pntIntersect = interPoint(line1.x1(), line1.y1(), line1.x2(), line1.y2(), line3.x1(), line3.y1(), line3.x2(), line3.y2());
    robot->pos().rx()=pntIntersect.rx()-curPoint.rx();
    robot->pos().ry()=pntIntersect.ry()-curPoint.ry();
    curPoint.setX(pntIntersect.rx()-curPoint.rx());
    curPoint.setY(pntIntersect.ry()-curPoint.ry());

    mColl = true;

    robot->momentI = robot->weight * robot->size * robot->size / 6; //    1/6*m*a^2
    robot->r=2;
    //robot->r=robot->size/sqrt(2);
    robot->V = robot->V0/2;
}
