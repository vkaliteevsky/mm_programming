#include "world.h"
#include "view/wall.h"
#include "boomdetector.h"
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
    startTimer(20);

}

void world::true_coord()
{
    qreal x = newWall->getX();
    qreal y = newWall->getY();
    qreal h = newWall->getHeight();
    qreal w = newWall->getWidth();
    qreal a = newWall->getAngle();

    pp1 = QPointF(x+ w/2 - (w/2)*cos(a*M_PI/180), y-(w/2)*sin(a*M_PI/180));
    pp2 = QPointF(-pp1.rx(), -pp1.ry());
}

void world::timerEvent(QTimerEvent *)
{
    qreal del = 0.1;
    QPointF pos = robot->pos();
    qreal x = pos.x();
    qreal y = pos.y();
    qreal nx = robot->V0*del*cos(robot->angle * M_PI/180);
    qreal ny = robot->V0*del*sin(robot->angle * M_PI/180);

    QMessageBox msgBox;
    msgBox.setText(QString::number(nx) + " " + QString::number(ny));
    //msgBox.exec();
    msgBox.close();



    qreal gip = sqrt(nx*nx + ny*ny);

    qreal nnx = nx*20/gip;
    qreal nny = ny*20/gip;

    qreal n_x = -nny;
    qreal n_y = -nnx;

    //qreal ang;
    //ang = atan(ny/nx);


    QPointF p1 = QPoint(x + nnx + nny, y + nny - nnx);
    QPointF p2 = QPoint(x + nnx - nny, y + nny + nnx);
    QPointF p3 = QPoint(x - nnx - nny, y - nny + nnx);
    QPointF p4 = QPoint(x - nnx + nny, y - nny - nnx);
  QPointF new_p1 = newWall->mapFromScene(p1);
  QPointF new_p2 = newWall->mapFromScene(p2);
  QPointF new_p3 = newWall->mapFromScene(p3);
  QPointF new_p4 = newWall->mapFromScene(p4);
    //QPointF new_p1 = p1;
    //QPointF new_p2 = p2;
    //QPointF new_p3 = p3;
    //QPointF new_p4 = p4;

    QGraphicsLineItem *line11 = new QGraphicsLineItem(x + nnx + nny, y + nny - nnx,x + nnx - nny, y + nny + nnx);
    QGraphicsLineItem *line22 = new QGraphicsLineItem(x + nnx - nny, y + nny + nnx,x - nnx - nny, y - nny + nnx);
    QGraphicsLineItem *line33 = new QGraphicsLineItem(x - nnx - nny, y - nny + nnx,x - nnx + nny, y - nny - nnx);
    QGraphicsLineItem *line44 = new QGraphicsLineItem(x - nnx + nny, y - nny - nnx,x + nnx + nny, y + nny - nnx);
   // scene->addItem(line11);
   // scene->addItem(line22);
   // scene->addItem(line33);
   // scene->addItem(line44);
   // QGraphicsRectItem *rect = new QGraphicsRectItem(0,0,1,1);
   // scene->addItem(rect);




  if(!robot->collidesWithItem(newWall))
    {


        robot->setAngle(robot->angle);
        robot->setPos(robot->pos().rx() + robot->V0*del*cos(robot->angle * M_PI/180),robot->pos().ry() + robot->V0*del*sin(robot->angle* M_PI/180));
       // robot->setAngle(ang*180/M_PI);
       // robot->setPos(x+nx,y+ny);


    }
    else
    {
      if (mColl == false){
            QGraphicsRectItem *rect2 = new QGraphicsRectItem(60,60,3,3);

            QMessageBox msgBox2;


            if (newWall->contains(new_p1))
            {

                   rect2 = new QGraphicsRectItem(p1.rx(),p1.ry(),1,1);
                   curPoint.setX(p1.rx());
                   curPoint.setY(p1.ry());
            }
            else if (newWall->contains(new_p2))
            {

                    rect2 = new QGraphicsRectItem(p2.rx(),p2.ry(),1,1);
                    curPoint.setX(p2.rx());
                    curPoint.setY(p2.ry());
            }
             else   if (newWall->contains(new_p3))
            {

                    rect2 = new QGraphicsRectItem(p3.rx(),p3.ry(),1,1);
                    curPoint.setX(p3.rx());
                    curPoint.setY(p3.ry());
            }
              else  if (newWall->contains(new_p4))
            {

                    rect2 = new QGraphicsRectItem(p4.rx(),p4.ry(),1,1);
                    curPoint.setX(p4.rx());
                    curPoint.setY(p4.ry());
            }
                scene->addItem(rect2);

                QGraphicsRectItem *rectc = new QGraphicsRectItem(curPoint.rx(),curPoint.ry(),1,1);
    //            QGraphicsRectItem *rectp1 = new QGraphicsRectItem(p1.rx(),p1.ry(),1,1);
    //            QGraphicsRectItem *rectp2 = new QGraphicsRectItem(p2.rx(),p2.ry(),1,1);
    //            QGraphicsRectItem *rectp3 = new QGraphicsRectItem(p3.rx(),p3.ry(),1,1);
    //            QGraphicsRectItem *rectp4 = new QGraphicsRectItem(p4.rx(),p4.ry(),1,1);
              //  scene->addItem(rectc);
               // scene->addItem(rectp1);
               // scene->addItem(rectp2);
                //scene->addItem(rectp3);
               // scene->addItem(rectp4);




            QLineF line1 = QLineF(line2->line());
          //  line1.intersect()

                    QLineF line3(curPoint, QPointF(curPoint.x() -nnx*3,curPoint.ry()-nny*3));

                    QLineF line7(curPoint, QPointF(curPoint.rx()+nnx*3,curPoint.ry()+nny*3));
                   // QLineF line7(curPoint, QPoint(curPoint.rx()+nnx*3,curPoint.ry()+nny*3));
                    QGraphicsLineItem *line5 = new QGraphicsLineItem(line3);
                   // scene->addItem(line5);

                    QGraphicsLineItem *line6 = new QGraphicsLineItem(line7);
                 //   scene->addItem(line6);

                    QPointF pntIntersect = interPoint(line1.x1(), line1.y1(), line1.x2(), line1.y2(), line3.x1(), line3.y1(), line3.x2(), line3.y2());

                    if (line2->contains(pntIntersect))
                    {
                        QMessageBox msgBox;
                        msgBox.setText("Hello Here");
                //        msgBox.exec();
               //         msgBox.close();
                    }


                    QGraphicsRectItem *rectc2 = new QGraphicsRectItem(pntIntersect.rx(),pntIntersect.ry(),1,1);
                    //scene->addItem(rectc2);

                    QGraphicsLineItem *line4 = new QGraphicsLineItem(curPoint.rx(),curPoint.ry(),pntIntersect.rx(),pntIntersect.ry());
                   // scene->addItem(line4);
                    robot->translate(pntIntersect.rx()-curPoint.rx(),pntIntersect.ry()-curPoint.ry());
                    curPoint.setX(pntIntersect.rx()-curPoint.rx());
                    curPoint.setY(pntIntersect.ry()-curPoint.ry());
                    mColl = true;

                    vector.setP1(curPoint);
                    vector.setP2(QPoint(pp2.rx(), pp2.ry()));

                  //  robot->angle=ang*180/M_PI;




                    robot->momentI = robot->weight * robot->size * robot->size / 6; //    1/6*m*a^2


                    robot->r=robot->size/sqrt(2);
                    robot->V = robot->V0/2;

        } else {
            qreal cof = newWall->getAngle();
            qreal alpha = robot->angle - cof;
            qreal gamma = robot->angle_w;
            qreal I = robot->momentI;
            qreal m = robot->weight;
            qreal M;
            qreal K = 0.05;
            qreal Kv = 0.3;
            qreal F;
            qreal F_fr;
            qreal r = robot->r;
            qreal V = robot->V;

            F = (robot->V0 - V)*Kv;
            F_fr = F * sin(alpha * M_PI/180)*K;
            //F_fr = 0;
            M = F_fr * r * sin(alpha * M_PI/180) - F * sin(alpha * M_PI/180) * sin ((45 - alpha)*M_PI/180) * r;



            qreal nAngle;
            qreal nAngle_w;
            qreal nV;

            nAngle_w = gamma + M*del/I;
            nAngle = (alpha + cof) + gamma * del;




            if ((alpha <= 1)&&(alpha >= -1)){
                robot->setPos(robot->pos().rx() +robot->V0*del*cos(newWall->getAngle()*M_PI/180),robot->pos().ry()+robot->V0*del*sin(newWall->getAngle()*M_PI/180));
            } else if (alpha <= -90){
                robot->angle = -90;
            } else {
                nV = V + (F * cos(alpha*M_PI/180) - F_fr)*del/m;





                robot->setAngle(nAngle);

                qreal newX = curPoint.rx()*cos(nAngle_w *M_PI/180) + curPoint.ry()*sin(nAngle_w *M_PI/180);
                qreal newY = -1*curPoint.rx()*sin(nAngle_w *M_PI/180) + curPoint.ry()*cos(nAngle_w*M_PI/180);
                robot->setPos(robot->pos().rx() + curPoint.rx() - newX, robot->pos().ry() + curPoint.ry() - newY);
                robot->setPos(robot->pos().rx() + V * del*cos(newWall->getAngle()*M_PI/180), robot->pos().ry() + V * del*sin(newWall->getAngle()*M_PI/180));
                robot->angle = nAngle;
                robot->angle_w = nAngle_w;
                robot->V = nV;


                QGraphicsRectItem * ss = new QGraphicsRectItem(0, 100, 300, 200);
                ss->setBrush(QColor(121,121,9));
                scene->addItem(ss);
                QGraphicsTextItem *text = new QGraphicsTextItem(" F = " + QString::number(F)
                                                               + "\n V = " + QString::number(V)
                                                               + "\n Ftp = " + QString::number(F_fr)
                                                               + "\n M = " + QString::number(M)
                                                               + "\n angle = " + QString::number(alpha)
                                                               + "\n angle_w = " + QString::number(gamma) );



                text->setPos(0, 100);
                text->setFont(QFont ("Courier", 14));
                scene->addItem(text);
                QMessageBox msgBox;
                msgBox.setText("Hello Here");
        //        msgBox.exec();
                msgBox.close();
            }
        }

    }

    // Add Boom Detecor
    // BoomDetector* detector = new BoomDetector(robot, newWall);
    // QTimer timer2;
    // QObject::connect(&timer2, SIGNAL(timeout()), detector, SLOT(ToDetect()));

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
