#include "robotview.h"
#include "world.h"

#include <QMessageBox>

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

#include <math.h>

robotview::robotview()
    : angle(60), mass(5.0), size(40), V0(10), momentI(0.1),motorFactor(0.3)
{
    mV = QPointF(V0*cos(angle*M_PI/180), V0*sin(angle*M_PI/180));
    setRotation(angle);
    for (int i =0; i<4; i++){
        setWall (i, NULL);
    }
}

QRectF robotview::boundingRect() const
{
    QRectF rect(-size/2, -size/2, size, size);
    return rect;
}

QPainterPath robotview::shape() const
{
    QPainterPath path;
    path.addRect(-size/2, -size/2, size, size);
    return path;
}

void robotview::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    setRotation(angle);
    painter->setBrush(QColor(90,90,90));
    painter->drawRect(-20,-20,40,40);

                painter->save();

    qreal arrowWidth = 10;
    qreal arrowHeight = 10;
    QPolygon arrow;
            arrow << QPoint(0, -arrowWidth/2)
                  << QPoint(arrowHeight, 0)
                  << QPoint(0, arrowWidth/2);

            QPointF p0(0, 0);
            QPointF p1(60,0);
            double dx = p1.x() - p0.x();
            double dy = p1.y() - p0.y();
            double arangle = atan2(dy, dx);
            QPointF p2(p1.x() - arrowHeight * cos(arangle),
                       p1.y() - arrowHeight * sin(arangle));
            double lineLen = sqrt(dx*dx + dy*dy);

            if(lineLen >= arrowHeight){
                painter->drawLine(p0, p2);
            }
            painter->save();
            painter->translate(p2);
            painter->rotate(180/M_PI * arangle );
            painter->drawConvexPolygon(arrow);
            painter->restore();

}

void robotview::setAngle(qreal nangle)
{
    angle = nangle;
}

void robotview::updateAngle()
{
    qreal tg = mV.ry()/mV.rx();
    angle = 180 * atan(tg)/M_PI;
    setRotation(angle);
}

void robotview::update()
{

    //QPointF pos = pos();
    qreal x = pos().x();
    qreal y = pos().y();
    qreal nx = cos(angle * M_PI/180);
    qreal ny = sin(angle * M_PI/180);


    qreal nnx = nx*(size/2);
    qreal nny = ny*(size/2);

    mP[0] = QPointF(x + nnx + nny, y + nny - nnx);
    mP[1] = QPointF(x + nnx - nny, y + nny + nnx);
    mP[2] = QPointF(x - nnx - nny, y - nny + nnx);
    mP[3] = QPointF(x - nnx + nny, y - nny - nnx);

    QMessageBox ms;
    ms.setText(
"    mP[0].rx() = " + QString::number(   mP[0].rx()       ) +
"\n  mP[0].ry() = " + QString::number(   mP[0].ry()       ) +
"\n  mP[1].rx() = " + QString::number(   mP[1].rx()       ) +
"\n  mP[1].ry() = " + QString::number(   mP[1].ry()       ) +
"\n  mP[2].rx() = " + QString::number(   mP[2].rx()       ) +
"\n  mP[2].ry() = " + QString::number(   mP[2].ry()       ) +
"\n  mP[3].rx() = " + QString::number(   mP[3].rx()       ) +
"\n  mP[3].ry() = " + QString::number(   mP[3].ry()       ) +

"\n  pos().rx() = " + QString::number(   pos().rx()       ) +
"\n  pos().ry() = " + QString::number(   pos().ry()       )

               );
  //  ms.exec();

}

void robotview::nextStep(qreal dt)
{

    setPos( pos() += mV*dt);
    setAngle(angle + mAngularVelocity*dt);
    update();

}

void robotview::checkCollision(Wall& wall)
{
    if(collidesWithItem(&wall))
    {
        for(int i = 0; i <4; i++)
        {
            QPointF new_p = wall.mapFromScene(mP[i]);
            if (wall.contains(new_p))
            {
                if(mWalls[i]== NULL)
                {
                    //Vnormal = 0
                    QLineF border = interRobotLine(wall);
                    QPointF normPoint = normalPoint(border.x1(), border.y1(), border.x2(), border.y2(), mP[i].rx(), mP[i].ry());

                    ( (world*)w)->scene->addRect(     normPoint.rx()  , normPoint.ry() , 2,2);
                    ( (world*)w)->scene->addRect(     normPoint.rx()  , normPoint.ry() , 3,3);



                    QPointF pos( this->pos());
                    QPointF n (-normPoint + mP[i]);


                    if (!(length(n) < 1.e-10)){


                        qreal k = n.rx()*mV.rx() +  n.ry()*mV.ry();
                        qreal n2 = n.rx()*n.rx() +  n.ry()*n.ry();

                        QMessageBox ms2;
                        ms2.setText(" normalPoint x = " + QString::number(normPoint.rx()) +
                                    "\n normalPoint y = " + QString::number(normPoint.ry()) +
                                    "\n  N x = " + QString::number(normPoint.rx() - pos.rx()) +
                                    "\n N y = " + QString::number(normPoint.ry() - pos.ry())


                                    );
                       // ms2.exec();


                            ( (world*)w)->scene->addRect(     mP[i].rx()  , mP[i].ry() , 2,2);
                            ( (world*)w)->scene->addRect(     mP[i].rx()  , mP[i].ry() , 3,3);



                        mV -= n*(k/n2);
                        //updateAngle();

                   //     ( (world*)w)->scene->addLine(new_p.rx(), new_p.ry(),new_p.rx() + n.rx(), new_p.ry() + n.ry() );
                   //     ( (world*)w)->scene->addLine(new_p.rx(), new_p.ry(),new_p.rx() + n.rx(), new_p.ry() + n.ry() );
                        ( (world*)w)->scene->addLine(mP[i].rx(), mP[i].ry(), mP[i].rx() + n.rx(), mP[i].ry() + n.ry() );








                        QMessageBox ms;
                        ms.setText("collision x = " + QString::number(normPoint.rx()) +
                                   "\n collision y = " + QString::number(normPoint.ry()) +
                                    "\n border x = " + QString::number(border.x2() - border.x1()) +
                                    "\n border y = " + QString::number(border.y2() - border.y1()) +
                                   // "\nborder x2 = " + QString::number(border.x2()) +
                                  //  "\nborder y2 = " + QString::number(border.y2()) +
                                    "\n  n x = " + QString::number(n.rx()) +
                                    "\n  n y = " + QString::number(n.ry()) +
                                   "\n  Vx = " + QString::number(mV.rx()) +
                                   "\n  Vy = " + QString::number(mV.ry())+

                                   "\n  posx = " + QString::number(pos.rx()) +
                                   "\n  posy = " + QString::number(pos.ry())+

                                   "\n new_p x = " + QString::number(new_p.rx()) +
                                  "\n  new_p y = " + QString::number(new_p.ry()) +
                                   "\n mP[i] x = " + QString::number(mP[i].rx()) +
                                   "\n mP[i] y = " + QString::number(mP[i].ry())
                                   );
                      // ms.exec();
                    }
                }
                setWall(i, &wall);
            }
        }
    }
}

void robotview::updateWalls()
{
    for (int i = 0; i < 4; i++){
        if (mWalls[i] != NULL){
           // getRobotFromWall(*(mWalls[i]),i);
        }
    }
}


void robotview::updateVelocity(qreal dt){

    mForce *= 0;//vector





    mForseMoment = 0;
   // QPointF F_engine = V *= (|V|-V0)*k;



    QPointF F_engine = mul (mV  , ( V0 - length(mV)) * motorFactor);



    QMessageBox ms4;
    ms4.setText(" F_engine x = " + QString::number(F_engine.rx()) +
                "\n F_engine y = " + QString::number(F_engine.ry()) +
               "\n  V x = " + QString::number(mV.rx()) +
               "\n V y = " + QString::number(mV.ry())
                );
 //   ms4.exec();
    QPointF p0 = pos();
    mForce = F_engine;
    for (int i = 0; i < 4; i++){
        if (mWalls[i] != NULL){

            QLineF bord = interRobotLine(*mWalls[i]);
            QPointF vectorParalStene (-bord.x2() + bord.x1(), -bord.y2() + bord.y1());



            QPointF F_norm = mForce;
            F_norm -= scalarProduct(mForce, vectorParalStene)*vectorParalStene/scalarProduct(vectorParalStene,vectorParalStene);
            F_norm *=-1;
            QPointF F_fr = mV;
            F_fr -= scalarProduct(F_fr,F_norm)/scalarProduct(F_norm,F_norm)*F_norm;
            F_fr *= -1;
            F_fr = normalize(F_fr);
            F_fr *= length(F_norm) * mWalls[i]->getFric();
            //F_fr = Force * sin(wallRobotAngle * M_PI/180)*K;
            (mForce += F_norm ) += F_fr;

            QPointF tmp(mP[i] - p0);



            qreal a = vectorProduct(F_fr, tmp);
            qreal b = vectorProduct(F_norm , tmp);


 /*           // /////////////////////////----------------------------------------------------

            QGraphicsRectItem * ss = new QGraphicsRectItem(-400, 100, 400, 200);
            ss->setBrush(QColor(121,121,9));
            ( (world*)w)->scene->addItem(ss);
            QGraphicsTextItem *text = new QGraphicsTextItem(  " Force engine   = " +               QString::number( F_engine.rx() ) + "," + QString::number( F_engine.ry() )

                                                            + "\n mV = " +             QString::number(         mV.rx()       )+ ","  + QString::number(  mV.ry())

                                                            + "\n F_norm = " +           QString::number(         F_norm.rx()   )+ ","  +  QString::number( F_norm.ry() )

                                                            + "\n F_fr = " + QString::number(         F_fr.rx()     )+ ","  +  QString::number( F_fr.ry())

                                                              );

            text->setPos(-400, 100);
            text->setFont(QFont ("Courier", 10));
            ( (world*)w)->scene->addItem(text);
*/
            // /////////////////////////-----------------------------------------------------

            mForseMoment += a += b;
        }
    }
    //qreal mAngularVelocity;



    QMessageBox ms2;
    ms2.setText(" mForce x = " + QString::number(mForce.rx()) +
                "\n mForce y = " + QString::number(mForce.ry())
          //      "\n  N x = " + QString::number(normPoint.rx() - pos.rx()) +
            //    "\n N y = " + QString::number(normPoint.ry() - pos.ry())
                );
   // ms2.exec();




    mV += mForce / mass * dt;

    mAngularVelocity += mForseMoment /  momentI * dt;


}


qreal robotview::vectorProduct(QPointF vector1, QPointF vector2)
{
    return vector1.rx()*vector2.ry() - vector1.ry()*vector2.rx();
}

QPointF robotview::normalize(QPointF vector)
{
    return QPointF(vector.rx()/length(vector) , vector.ry()/length(vector));
}

qreal robotview::length(QPointF vector)
{
    return sqrt(vector.rx()*vector.rx() + vector.ry()*vector.ry());
}

qreal robotview::scalarProduct(QPointF vector1, QPointF vector2)
{
    return vector1.rx()*vector2.rx() + vector1.ry()*vector2.ry();
}

void robotview::getRobotFromWall(Wall& wall, int index)
{
    QPointF p = mP[index];
    QLineF border = interRobotLine(wall);

    QLineF revDirection(p, QPointF(p.rx() - 5*cos(angle*M_PI/180), p.ry()-5*sin(angle*M_PI/180)));

( (world*)w)->scene->addLine(p.rx(), p.ry(),p.rx() - 40*cos(angle*M_PI/180), p.ry()-40*sin(angle*M_PI/180) );

    QPointF pntIntersect = interPoint(border.x1(), border.y1(), border.x2(), border.y2(), revDirection.x1(), revDirection.y1(), revDirection.x2(), revDirection.y2());

    if (!((pntIntersect.rx() = NAN) && (pntIntersect.ry()=NAN))){






//( (world*)w)->scene->addLine(     revDirection.x1(), revDirection.y1(), revDirection.x2(), revDirection.y2()        );
//( (world*)w)->scene->addLine(    border.x1(), border.y1(), border.x2(), border.y2()        );


/*
    QMessageBox ms2;
    ms2.setText("x = " + QString::number(            this->pos().rx()   ) +
               "\y 2 = " + QString::number(         this->pos().ry()  )
               );
    ms2.exec();

*/
    QMessageBox ms;
    ms.setText("x = " + QString::number(             pntIntersect.rx()                              ) +
               "\n y = " + QString::number(         pntIntersect.ry()                                                    )

               );
   ms.exec();


   // /////////////////////////----------------------------------------------------
/*
   QGraphicsRectItem * ss = new QGraphicsRectItem(-400, 100, 400, 200);
   ss->setBrush(QColor(121,121,9));
   ( (world*)w)->scene->addItem(ss);
   QGraphicsTextItem *text = new QGraphicsTextItem(  " Force engine   = " +               QString::number( p.rx() ) + "," + QString::number( p.ry() )

                                                   + "\n mV = " +             QString::number(         pntIntersect.rx()       )+ ","  + QString::number(  pntIntersect.ry())


                                                     );

   text->setPos(-400, 100);
   text->setFont(QFont ("Courier", 10));
   ( (world*)w)->scene->addItem(text);
*/
   // /////////////////////////-----------------------------------------------------


    setPos(this->pos().rx()+ pntIntersect.rx() - p.rx()
           ,this->pos().ry() + pntIntersect.ry() - p.ry());




//( (world*)w)->scene->addLine(     p.rx()      ,    p.ry()       ,    pntIntersect.rx()    ,   pntIntersect.ry()         );




 //   ( (world*)w)->scene->addRect(     border.x1()  , border.y1() , 3,3);
 //   ( (world*)w)->scene->addRect(     border.x2()  , border.y2() , 3,3);
 //   ( (world*)w)->scene->addRect(     revDirection.x1()  , revDirection.y1() , 3,3);
 //   ( (world*)w)->scene->addRect(     revDirection.x2()  , revDirection.y2() , 3,3);

//( (world*)w)->scene->addLine(this->pos().rx(), this->pos().ry(),(this->pos().rx()+ pntIntersect.rx() - p.rx()), (this->pos().ry() + pntIntersect.ry() - p.ry()) );


    QMessageBox ms2;

   // ms2.exec();
}

    //isRobotContact = true;
}

QLineF robotview::interRobotLine(Wall& wall)
{
    QLineF linne;
    QGraphicsLineItem *l = new QGraphicsLineItem(0,0,0,0);
    for(int i = 0; i<4; i++)
    {
        l->setLine(wall.linesList.at(i));
        if (collidesWithItem(l)){
            linne = l->line();
        }
    }

    return linne;
}

QPointF robotview::interPoint(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal x4, qreal y4)
{
    qreal a1 = (y2-y1)/(x2-x1);
    qreal b1 = y1 - x1*a1;

    qreal a2 = (y4-y3)/(x4-x3);
    qreal b2 = y3 - x3*a2;

    qreal cx = (b2-b1)/(a1-a2);
    qreal cy = a1 * cx + b1;
    return QPointF(cx, cy);
}

QPointF robotview::normalPoint(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3)
{
    qreal x0 = (x1*(y2-y1)*(y2-y1) + x3*(x2-x1)*(x2-x1) + (x2-x1)*(y2-y1)*(y3-y1))/((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
   // qreal y0 = ((x2-x1)*(x3-x0))/((y2-y1)) + y3;
    qreal y0 = ((y2-y1)*(x0-x1)/(x2-x1))+y1;
    return QPointF(x0, y0);
}

QPointF robotview::mul(QPointF vector, qreal scalar)
{
    return QPointF(vector.rx()*scalar, vector.ry()*scalar);
}

QString robotview::toString(QPointF point)
{
    return ( QString::number(point.rx()) + ", " + QString::number(point.ry()));
}
