#include "world.h"
#include "view/wall.h"
#include <math.h>
#include <QTimer>
#include <QMessageBox>
#include <math.h>



world::world(QWidget *parent)
    :QWidget(parent), isRobotContact(false)
{


    scene = new QGraphicsScene(-300, -300, 600, 600);
    view = new QGraphicsView(parent);
    view->setScene(scene);
    mDelta = 0.05;
    stop = false;
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    robot = new robotview;
    robot->setPos(-270, -120);
    robot->update();
    scene->addItem(robot);


    //scene->addLine(robot->pos().rx(), robot->pos().ry(), robot->pos().rx() + cos(robot->angle*M_PI/180)*800   , robot->pos().ry() + sin(robot->angle*M_PI/180)*800      );
    robot->w=this;

    newWall = new Wall(-300,0,600,-50,30,0.4);
   // newWall->true_coord2();

    true_coord();
    line2 = new QGraphicsLineItem(pp1.rx(),pp1.ry(),pp2.rx(),pp2.ry());
   // scene->addItem(line2);

    scene->addItem(newWall);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QColor (170,170,170));
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Robots"));
    view->resize(800, 600);
    view->show();
    startTimer(20);

}

void world::true_coord2(Wall& newWall)
{
    QPoint p1 = QPoint(newWall.getX()                      ,newWall.getY());
    QPoint p2 = QPoint(newWall.getX() + newWall.getWidth() ,newWall.getY());
    QPoint p3 = QPoint(newWall.getX() + newWall.getWidth() ,newWall.getY() + newWall.getHeight());
    QPoint p4 = QPoint(newWall.getX()                      ,newWall.getY() + newWall.getHeight());

    qreal angRad = newWall.getAngle()*M_PI/180;

    p1 = QPoint(p1.rx()*cos(angRad) - p1.ry()*sin(angRad), p1.rx()*sin(angRad) + p1.ry()*cos(angRad));
    p2 = QPoint(p2.rx()*cos(angRad) - p2.ry()*sin(angRad), p2.rx()*sin(angRad) + p2.ry()*cos(angRad));
    p3 = QPoint(p3.rx()*cos(angRad) - p3.ry()*sin(angRad), p3.rx()*sin(angRad) + p3.ry()*cos(angRad));
    p4 = QPoint(p4.rx()*cos(angRad) - p4.ry()*sin(angRad), p4.rx()*sin(angRad) + p4.ry()*cos(angRad));

    newWall.setLines(p1, p2, p3, p4);
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
    robot->nextStep(mDelta);
   // robot->updateAngle();

    robot->checkCollision(*newWall);
    robot->updateWalls();
    robot->update();
    //robot->updateVelocity();
    robot->updateVelocity(mDelta);



/*

    QGraphicsRectItem * ss = new QGraphicsRectItem(0, 200, 300, 200);
    ss->setBrush(QColor(121,121,9));
    scene->addItem(ss);
    QGraphicsTextItem *text = new QGraphicsTextItem(" mV x= " + QString::number(robot->mV.rx())
                                                    + "\n mV y= " + QString::number(robot->mV.ry())
                                                      + "\n x = " + QString::number(robot->pos().rx())
                                                + "\n y = " + QString::number(robot->pos().ry())
                                                    );

    text->setPos(0, 200);
    text->setFont(QFont ("Courier", 10));
    scene->addItem(text);


*/


    /*

    if (!stop){




        if(!robot->collidesWithItem(newWall)){ //?????? ????????
            robot->setAngle(robot->angle);
            robot->setPos(robot->pos().rx() + robot->V0*mDelta*cos(robot->angle * M_PI/180)
                          , robot->pos().ry() + robot->V0*mDelta*sin(robot->angle* M_PI/180));
        } else {
            if (isRobotContact == false){ //??????? ? ????? ??? ?????? "??????"
                point = getRobotFromWall();

            } else { //??????? ??????







                qreal originAngle = newWall->getAngle();
                qreal tempAngle = robot->angle - originAngle;
                //qreal wallRobotAngle = trueAngle(robot->angle - originAngle);
                qreal wallRobotAngle = originAngle - robot->angle;
                qreal angularVelocity = robot->mAngularVelocity;
                qreal I = robot->momentI;
                qreal m = robot->weight;
                qreal forseMoment;
                qreal K = 4000;
                qreal tractionCoefficient = 0.1;
                qreal F;
                qreal F_fr;
                qreal r = robot->r;
                qreal V = robot->V;

                F = (robot->V0 - V)*tractionCoefficient;
                F_fr = F * sin(wallRobotAngle * M_PI/180)*K;
                forseMoment = F_fr * r * sin(wallRobotAngle * M_PI/180) - F * sin(wallRobotAngle * M_PI/180) * sin ((45 - wallRobotAngle)*M_PI/180) * r;

                qreal nAngle;
                qreal nAngle_w;
                qreal nV;

                nAngle_w = angularVelocity + forseMoment*mDelta/I;
                nAngle = originAngle - wallRobotAngle + angularVelocity * mDelta;//?



            //    QGraphicsRectItem * ss = new QGraphicsRectItem(0, 100, 300, 200);
          //      ss->setBrush(QColor(121,121,9));
        //        scene->addItem(ss);
      //          QGraphicsTextItem *text = new QGraphicsTextItem(" wallRobotAngle = " + QString::number(wallRobotAngle)
                                                               + "\n nAngle = " + QString::number(nAngle) );

    //            text->setPos(0, 100);
  //              text->setFont(QFont ("Courier", 14));
//                scene->addItem(text);

                if (wallRobotAngle <= 1){
                    robot->setPos(robot->pos().rx() +robot->V0*mDelta*cos(newWall->getAngle()*M_PI/180)
                                  , robot->pos().ry()+robot->V0*mDelta*sin(newWall->getAngle()*M_PI/180));
                } else if (wallRobotAngle >= 89){
                    robot->angle = wallRobotAngle + originAngle;
                    stop = true;
                } else {

                    nV = V + (F * cos(wallRobotAngle*M_PI/180) - F_fr)*mDelta/m;




                    //robot->setAngle(nAngle);



                    turnAndMoveRobot(nAngle_w * mDelta, V);



                    robot->angle = nAngle;
                    robot->mAngularVelocity = nAngle_w;

                    QGraphicsRectItem * ss = new QGraphicsRectItem(0, 100, 300, 200);
                    ss->setBrush(QColor(121,121,9));
                    scene->addItem(ss);
                    QGraphicsTextItem *text = new QGraphicsTextItem(" F = " + QString::number(F)
                                                                    + "\n V = " + QString::number(V)
                                                                    + "\n Ftp = " + QString::number(F_fr)
                                                                    + "\n M = " + QString::number(forseMoment)
                                                                    + "\n angle = " + QString::number(wallRobotAngle)
                                                                    + "\n momentI = " + QString::number(robot->momentI)
                                                                    + "\n angularVelocity = " + QString::number(angularVelocity) );

                    text->setPos(0, 100);
                    text->setFont(QFont ("Courier", 14));
                    scene->addItem(text);

                    robot->V = nV;
                }
            }
        }

    }
*/
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

QPointF world::normalPoint(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3)
{
    qreal x0 = (x1*(y2-y1)*(y2-y1) + x3*(x2-x1)*(x2-x1) + (x2-x1)*(y2-y1)*(y3-y1))/((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
    qreal y0 = (x2-x1)*(x3-x0)/(y2-y1) + y3;

    return QPointF(x0, y0);
}

void world::turnAndMoveRobot(qreal nAngle_w, qreal V)
{
////





    qreal xlocal = curPoint.rx() - robot->pos().rx();
    qreal ylocal = curPoint.ry() - robot->pos().ry();
    //qreal ylocal = robot->pos().ry() - curPoint.ry();

    qreal nxlocal = xlocal*cos(nAngle_w *M_PI/180) - ylocal*sin(nAngle_w *M_PI/180);
    qreal nylocal = xlocal*sin(nAngle_w *M_PI/180) + ylocal*cos(nAngle_w *M_PI/180);



    robot->setPos(robot->pos().rx() + V * mDelta*cos(newWall->getAngle()*M_PI/180)
                  , robot->pos().ry() + V * mDelta*sin(newWall->getAngle()*M_PI/180));

    robot->setAngle(robot->angle);
    // ///////


/*
    QRectF r3(intPoint.rx(), intPoint.ry(), 3,3);
    scene->addRect(r3);
*/

    //QLineF l = interRobotLine();
    //QPointF point = normalPoint(l.x1(), l.y1(), l.x2(),l.y2(),pointN.rx(), pointN.ry());



    //QRectF r2(l.x1(), l.y1(), l.dx(),l.dy());
    //scene->addRect(r2);

  //  QRectF r1(point.rx(), point.ry(),3,3);
 //   scene->addRect(r1);



    //QLineF lene(robot->pos().rx(), robot->pos().ry(),robot->pos().rx() + point.rx() - nxlocal,robot->pos().ry() + point.ry() - nylocal );
    //scene->addLine(lene.x1(),lene.y1(),lene.x2(),lene.y2());


    //normalRobot(intPoint, intLine);


    //robot->setPos(robot->pos().rx() + point.rx() - nxlocal
      //                  , robot->pos().ry() + point.ry() - nylocal);

/*
    qreal newX = curPoint.rx()*cos(nAngle_w *M_PI/180) - curPoint.ry()*sin(nAngle_w *M_PI/180);//?????
    qreal newY = curPoint.rx()*sin(nAngle_w *M_PI/180) + curPoint.ry()*cos(nAngle_w *M_PI/180);//?????

    robot->setPos(robot->pos().rx() + curPoint.rx() - newX
                  , robot->pos().ry() + curPoint.ry() - newY);

    robot->setPos(robot->pos().rx() + V * mDelta*cos(newWall->getAngle()*M_PI/180)
                  , robot->pos().ry() + V * mDelta*sin(newWall->getAngle()*M_PI/180));

    */

}


void world::normalRobot(QPointF point, QLineF line)
{







    QMessageBox boxa;
    boxa.setText("aaaaa");
    boxa.exec();
    boxa.close();

    QPointF pointK = normalPoint(line.x1(), line.y1(), line.x2(),line.y2(),point.rx(), point.ry());

    scene->addLine(pointK.rx(), pointK.ry(), point.rx(), point.ry());

    QMessageBox box;
    box.setText(  " pointK x  = " + QString::number(pointK.rx()) +
                  " pointK y  = " + QString::number(pointK.ry()) +
                  " point x  = " + QString::number(point.rx()) +
                  " point x  = " + QString::number(point.ry())
                                                  );
    box.exec();
    box.close();
    robot->setPos(robot->pos().rx() + pointK.rx() - point.rx()
                , robot->pos().ry() + pointK.ry() - point.ry());

    QMessageBox boxb;
    boxb.setText("bbbbb");
    boxb.exec();
    boxb.close();
}

QPointF world::getRobotFromWall()
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

    QLineF linne = interRobotLine();



    /*
    QGraphicsLineItem *line = new QGraphicsLineItem(0,0,0,0);
    QLineF l;
    QPointF *p = new QPointF(0,0);
    foreach (l, newWall->linesList) {

        QPointF point = interPoint(l.x1(), l.y1(), l.x2(), l.y2(), curPoint.rx(), curPoint.ry(), curPoint.x() -nnx*3, curPoint.ry()-nny*3 );
        point = robot->mapFromScene(point);


        QMessageBox box;
        box.setText(" point x  = " + QString::number(point.rx()) +
                    " point y  = " + QString::number(point.ry())
                //    + " x2 = " + QString::number(line1.x2()) +
                   // " y2 = " + QString::number(line1.y2())
                    );
        box.exec();
        box.close();

        if(robot->contains(point)){

            line2->setLine(l.x1(), l.y1(), l.x2(), l.y2());


            QMessageBox box;
            box.setText("lol");
            box.exec();
            box.close();
        } else {
            QMessageBox box;
            box.setText("dsfsdfl");
            box.exec();
            box.close();
        }
    }
*/

    QLineF line1 = QLineF(line2->line());
    line1 = linne;

    QLineF line3(curPoint, QPointF(curPoint.x() -nnx,curPoint.ry()-nny));
    QPointF pntIntersect = interPoint(line1.x1(), line1.y1(), line1.x2(), line1.y2(), line3.x1(), line3.y1(), line3.x2(), line3.y2());
    robot->pos().rx()=  pntIntersect.rx()-curPoint.rx();
    robot->pos().ry()=  pntIntersect.ry()-curPoint.ry();

    QPointF returnPoint (curPoint.rx(),curPoint.ry());

    curPoint.setX(pntIntersect.rx()-curPoint.rx());
    curPoint.setY(pntIntersect.ry()-curPoint.ry());

    isRobotContact = true;





    //robot->r=robot->size/sqrt(2);
    //robot->V = robot->V0/2;


    QRectF rrr(returnPoint.rx(), returnPoint.ry(),3,3);
    scene->addRect(rrr);

    intPoint = returnPoint;
    return QPointF(returnPoint.rx(), returnPoint.ry());
}

QLineF world::interRobotLine()
{
    QLineF linne;
    QGraphicsLineItem *l = new QGraphicsLineItem(0,0,0,0);
    l->setLine(newWall->linesList.at(0));
    if (robot->collidesWithItem(l)){
        QMessageBox box;
       // box.setText("lol1");
       // box.exec();
        box.close();
        linne = l->line();

    }
    l->setLine(newWall->linesList.at(1));
    if (robot->collidesWithItem(l)){
        QMessageBox box;
        box.setText("lol2");
        box.exec();
        box.close();
                linne = l->line();
    }
    l->setLine(newWall->linesList.at(2));
    if (robot->collidesWithItem(l)){
        QMessageBox box;
        box.setText("lol3");
        box.exec();
        box.close();
                linne = l->line();
    }
    l->setLine(newWall->linesList.at(3));
    if (robot->collidesWithItem(l)){
        QMessageBox box;
        box.setText("lol4");
        box.exec();
        box.close();
                linne = l->line();
    }
    intLine = linne;
    return linne;
}

qreal world::trueAngle(qreal angle)
{
    if (angle > 90){
        while (angle >= 90){
            angle -= 90;
        }
        return angle;
    }
    if (angle < 0){
        while (angle <= 0){
            angle += 90;
        }
        return angle;
    }
    return angle;
}


