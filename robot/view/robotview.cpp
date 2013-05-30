#include "robotview.h"
#include "world.h"

#include <QMessageBox>

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

#include <math.h>

robotview::robotview()
    : angle(330), mass(50), size(40), V0(10), momentI(0.000000000000003),motorFactor(4)
    //13
{
    mV = QPointF(V0*cos(angle*M_PI/180), V0*sin(angle*M_PI/180));
    setRotation(angle);
    for (int i =0; i<4; i++){
        setWall (i, NULL);
    }
}

QRectF robotview::boundingRect() const
{
    QRectF rect(-size*2, -size*2, size*4, size*4);
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

    QPointF p00(0, 0);
    QPointF p11(60,0);
    double dx = p11.x() - p00.x();
    double dy = p11.y() - p00.y();
    double arangle = atan2(dy, dx);
    QPointF p22(p11.x() - arrowHeight * cos(arangle),
               p11.y() - arrowHeight * sin(arangle));
    double lineLen = sqrt(dx*dx + dy*dy);

    if(lineLen >= arrowHeight){
        painter->drawLine(p00, p22);
    }
    painter->save();
    painter->translate(p22);
    painter->rotate(180/M_PI * arangle );
    painter->drawConvexPolygon(arrow);
    painter->restore();

    //if (mWalls[0] == NULL) painter->drawRect();

}

void robotview::updateAngle()
{
    qreal tg = mV.ry()/mV.rx();
    angle = 180 * atan(tg)/M_PI;
    setRotation(angle);
}

void robotview::update()
{
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
}

void robotview::nextStep(qreal dt)
{
    //QPointF napr(cos(angle*M_PI/180), sin(angle*M_PI/180));


    //QPointF F_engine = napr * (V0 - length(mV)) * motorFactor;

    mV += mForce / mass * dt;
    setPos( pos() += mV*dt);
    angle += mAngularVelocity*dt;
    mForseMoment = 0;
    // setAngle(angle);
    update();

    QMessageBox mst;
    mst.setText("next");
    //mst.exec();


}

void robotview::checkCollision(Wall& wall)
{




    if(collidesWithItem(&wall)) {
        for(int i = 0; i <4; i++)
        {

            QLineF bord = nearRobotLine(wall, mP[i]);
            QPointF normPoint = normalPoint(bord.x1(), bord.y1(), bord.x2(), bord.y2(), mP[i].rx(), mP[i].ry());
            QLineF line(normPoint.rx(), normPoint.ry(),mP[i].rx(), mP[i].ry());

            QPointF new_p = wall.mapFromScene(mP[i]);

            QMessageBox ms;
            ms.setText(toString(new_p) + " _____ " + toString(mP[i]));
            //ms.exec();

            if (wall.contains(new_p)) {
                QMessageBox mst;
                mst.setText("toString(new_p) +  + toString(mP[i])");
                 mst.exec();
            }

            //( (world*)w)->scene->addRect(new_p.rx(),new_p.ry(),3,3 );
            if (wall.contains(new_p)) {



                ( (world*)w)->scene->addRect(mP[i].rx(),mP[i].ry(),2,2 );


                //if (wall.contains(new_p)) {
                //if (line.length() < 1) {
                if(mWalls[i]== NULL) {

                    QMessageBox ms;
                    ms.setText("lol");
                   // ms.exec();

                    //Vnormal = 0
                    QLineF border = interRobotLine(wall);

                    //QLineF border = nearRobotLine(wall, mP[i]);

                    QPointF normPoint = normalPoint(border.x1(), border.y1(), border.x2(), border.y2(), mP[i].rx(), mP[i].ry());
                    QPointF n (-normPoint + mP[i]);


                    if (!(length(n) < 1.e-10)){
                        qreal k = n.rx()*mV.rx() +  n.ry()*mV.ry();
                        qreal n2 = n.rx()*n.rx() +  n.ry()*n.ry();
                        mV -= n*(k/n2);
                    }

                }
                setWall(i, &wall);
            } else {
                /* if (mWalls[i] == &wall) {
                    getRobotFromWall(wall, i);
                    update();
                    //QMessageBox ms;
                    //ms.setText("setNull");
                    //ms.exec();
                    QMessageBox ms;
                   // ms.setText("setNeNull");
                   // ms.exec();                    //( (world*)w)->scene->addRect(mP[i].rx(), mP[i].ry(), 3,3);

                    //mAngularVelocity = 0;
                    //setWall(i, NULL);
                } else {
                    QMessageBox ms;
                    //ms.setText("setNull");
                   // ms.exec();
                    mAngularVelocity = 0;
                    setWall(i, NULL);
                }*/

                QLineF bord = nearRobotLine(wall, mP[i]);
                QPointF normPoint = normalPoint(bord.x1(), bord.y1(), bord.x2(), bord.y2(), mP[i].rx(), mP[i].ry());
                QLineF line(normPoint.rx(), normPoint.ry(),mP[i].rx(), mP[i].ry());





                QPointF normPoint2 = normalPoint(bord.x1(), bord.y1(), bord.x2(), bord.y2(), mP[i].rx() - 40*cos(angle*M_PI/180) , mP[i].ry() - 40*sin(angle*M_PI/180));
                QLineF line2(normPoint2.rx(), normPoint2.ry(),mP[i].rx() - 40*cos(angle*M_PI/180) , mP[i].ry() - 40*sin(angle*M_PI/180) );

                QMessageBox ms;
                ms.setText(QString::number(-line.length() +line2.length()));
                //  ms.exec();

                if (fabs(-line.length() +line2.length())<1) {


                    QLineF deltaLine (line2.x1() - line.x1(), line2.y1() - line.y1(), line2.x2() - line.x2(), line2.y2() - line.y2());



                    ( (world*)w)->scene->addLine(deltaLine);


                    setPos(pos().rx() + (deltaLine.x2() - deltaLine.x1())/2, pos().ry()+ (deltaLine.y2() - deltaLine.y1())/2);

                    qreal len = length(mV);
                    qreal borddx, borddy;
                    if (mV.rx() > 0) { borddx = fabs(bord.dx());} else { borddx = - fabs(bord.dx());}
                    if (mV.ry() > 0) { borddy = fabs(bord.dy());} else { borddy = - fabs(bord.dy());}
                    mV.setX((borddx/bord.length())*len);
                    mV.setY((borddy/bord.length())*len);



                    mAngularVelocity = 0;
                    setWall(i, NULL);
                }
            }
        }
    } else {

        for (int i = 0; i < 4; i++) {


            if ((mWalls[i] != NULL)){//&&(!wall.isNotNear(mP[i]) )){
                    QMessageBox ms;
                    ms.setText("There are no collision");
                    ms.exec();
                    for (int i = 0; i < 4; i++) {
                            mWalls[i] = NULL;
                    }
                    mAngularVelocity = 0;
                    mV.setX(cos(angle*M_PI/180)*V0);
                    mV.setY(sin(angle*M_PI/180)*V0);
                }
        }






        /*
        for (int i = 0; i < 4; i++) {
            if (mWalls[i] != NULL) {


                QLineF bord = nearRobotLine(wall, mP[i]);
                QPointF normPoint = normalPoint(bord.x1(), bord.y1(), bord.x2(), bord.y2(), mP[i].rx(), mP[i].ry());
                QLineF line(normPoint.rx(), normPoint.ry(),mP[i].rx(), mP[i].ry());





                QPointF normPoint2 = normalPoint(bord.x1(), bord.y1(), bord.x2(), bord.y2(), mP[i].rx() - 40*cos(angle*M_PI/180) , mP[i].ry() - 40*sin(angle*M_PI/180));
                QLineF line2(normPoint2.rx(), normPoint2.ry(),mP[i].rx() - 40*cos(angle*M_PI/180) , mP[i].ry() - 40*sin(angle*M_PI/180) );

                QMessageBox ms;
                ms.setText(QString::number(-line.length() +line2.length()));
                //  ms.exec();

                if (fabs(-line.length() +line2.length())<1) {


                    QLineF deltaLine (line2.x1() - line.x1(), line2.y1() - line.y1(), line2.x2() - line.x2(), line2.y2() - line.y2());



                    //( (world*)w)->scene->addLine(deltaLine);


                    setPos(pos().rx() + (deltaLine.x2() - deltaLine.x1()), pos().ry()+ (deltaLine.y2() - deltaLine.y1()));

                    qreal len = length(mV);
                    qreal borddx, borddy;
                    if (mV.rx() > 0) { borddx = fabs(bord.dx());} else { borddx = - fabs(bord.dx());}
                    if (mV.ry() > 0) { borddy = fabs(bord.dy());} else { borddy = - fabs(bord.dy());}
                    mV.setX((borddx/bord.length())*len);
                    mV.setY((borddy/bord.length())*len);

                    angle = atan(mV.ry()/mV.rx())/M_PI*180;

                    mAngularVelocity = 0;
                    setWall(i, NULL);
                }
            }

        }
        */
    }
}

void robotview::updateWalls()
{
    for (int i = 0; i < 4; i++){
        if (mWalls[i] != NULL){
            QMessageBox ms;
            ms.setText(QString::number(i));
             //ms.exec();

            getRobotFromWall(*(mWalls[i]),i);
        }
    }
}


void robotview::updateVelocity(qreal dt){

    mForce *= 0;//vector
    mForseMoment += mForseMoment;
    QPointF F_engine = mul (mV  , ( V0 - length(mV)) * motorFactor);
    QPointF p0 = pos();
    mForce = F_engine;
    for (int i = 0; i < 4; i++){
        if (mWalls[i] != NULL){

            //QLineF bord = interRobotLine(*mWalls[i]);
            QLineF bord = nearRobotLine(*mWalls[i], mP[i]);
            qreal ang = bord.angle();
            QPointF vectorParalStene (100*cos(ang*M_PI/180),-100*sin(ang*M_PI/180));


            vectorParalStene = normalize(vectorParalStene);

            QPointF F_norm = mForce;
            qreal sc = scalarProduct(vectorParalStene,vectorParalStene);
            //if (sc > 1.e-10)
            if (sc > 1.e-20)
                F_norm -= mul(vectorParalStene,(scalarProduct(mForce, vectorParalStene)))/scalarProduct(vectorParalStene,vectorParalStene);


            F_norm *=-1;
            QPointF F_fr;
            //sc = scalarProduct(F_norm,F_norm);
            //if (sc > 1.e-10)
            //if (sc > 1.e-20)
            //F_fr -= scalarProduct(F_fr,F_norm)/scalarProduct(F_norm,F_norm)*F_norm;


            QMessageBox mse2;
            mse2.setText(toString(vectorParalStene));
            //mse2.exec();

            vectorParalStene *= -1;


            QMessageBox mse;
            mse.setText(toString(vectorParalStene));
            //mse.exec();

            F_fr = vectorParalStene;
            F_fr *= length(F_norm) * mWalls[i]->getFric();
            //F_fr = Force * sin(wallRobotAngle * M_PI/180)*K;

            QMessageBox ms;
            ms.setText(toString(F_fr));
            //ms.exec();

            (mForce += F_norm ) += F_fr;
            QPointF tmp(mP[i] - p0);
            qreal a = vectorProduct(F_fr, tmp);
            qreal b = vectorProduct(F_norm , tmp);





            QMessageBox ms4;
            ms4.setText(QString::number(a));
           // ms4.exec();

            QMessageBox ms5;
            ms5.setText(QString::number(b));
            // ms5.exec();


            mForseMoment += a += b;


            // //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // output indicators

            QGraphicsRectItem * ss = new QGraphicsRectItem(0, 150, 300, 200);
            ss->setBrush(QColor(121,121,9));
            // ( (world*)w)->scene->addItem(ss);
            QGraphicsTextItem *text = new QGraphicsTextItem( "F_norm = " + toString(F_norm) + "\n" +
                                                             "F_fr = " + toString(F_fr) + "\n" +
                                                             "F_engine = " + toString(F_engine) + "\n" +
                                                             "mForce = " + toString(mForce) + "\n" +
                                                             "mForseMoment = " + QString::number(mForseMoment) + "\n" +
                                                             "mAngularVelocity = " + QString::number(mAngularVelocity) + "\n" +
                                                             "mAngle = " + QString::number(angle) + "\n"
                                                             "mV = " + toString(mV) + "\n"
                                                             );

            text->setPos(0, 150);
            text->setFont(QFont ("Courier", 10));
            // ( (world*)w)->scene->addItem(text);

            // //////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        }
    }
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
    //QLineF border = interRobotLine(wall);
    QLineF border = nearRobotLine(wall, p);

    QLineF revDirection(p, QPointF(p.rx() - 5*cos(angle*M_PI/180), p.ry()-5*sin(angle*M_PI/180)));
    //QPointF pntIntersect = interPoint(border.x1(), border.y1(), border.x2(), border.y2(), revDirection.x1(), revDirection.y1(), revDirection.x2(), revDirection.y2());
    QPointF pntIntersect = normalPoint(border.x1(), border.y1(), border.x2(), border.y2(), p.rx(), p.ry());
    if (!((pntIntersect.rx() == NAN) || (pntIntersect.ry() == NAN))){

        QPointF k; k = pntIntersect -= p;

        ( (world*)w)->scene->addLine(mP[index].rx(),mP[index].ry(),mP[index].rx()+k.rx(),mP[index].ry()+k.ry() );

        QMessageBox n;

        if (k.rx()>0){
            n.setText(QString::number(length(k) ));
        } else {
            n.setText("-" + QString::number(length(k) ));
        }
        //n.exec();

        setPos(pos() += k);
        QMessageBox n2;
        n2.setText("vutashili");
       // n2.exec();
    } else {
        QMessageBox n;
        n.exec();
    }
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

QLineF robotview::nearRobotLine(Wall& wall, QPointF p)
{
    QList<qreal> len;


    qreal min=0;
    for(int i = 0; i<4; i++)
    {
        QLineF l;
        l= wall.linesList.at(i);

        QPointF normPoint = normalPoint(l.x1(), l.y1(), l.x2(), l.y2(), p.rx(),p.ry());
        QLineF k (p.rx(), p.ry(), normPoint.rx(),normPoint.ry());
        len.push_back( k.length());

        QMessageBox d2;
        d2.setText(QString::number(k.length()));
        // d2.exec();

        if (min == 0){
            min = k.length();
        }
        if (k.length() < min){
            min = k.length();
        }
    }
    int j = len.indexOf(min);
    QMessageBox d;
    d.setText(QString::number(j));
    // d.exec();
    return wall.linesList.at(j);

}

/*bool robotview::isParallel(QLineF l1, QLineF l2)
{
    if ( -((l1.y2()-l1.y1())/(l1.x2()-l1.x1())) + ((l2.y2()-l2.y1())/(l2.x2()-l2.x1())) < 1.e-13){
        return true;
    } else {
        return false;
    }
}*/

QPointF robotview::interPoint(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal x4, qreal y4)
{


    if (fabs(x3-x4) < 1.e-10){
        QMessageBox d;
        d.setText("x3 == x4");
        d.exec();
    }
    if (fabs(x2-x1)<1.e-10){
        QMessageBox d;
        d.setText("x1 == x2");
        d.exec();
    }

    qreal a1 = (y2-y1)/(x2-x1);
    qreal b1 = y1 - x1*a1;

    qreal a2 = (y4-y3)/(x4-x3);
    qreal b2 = y3 - x3*a2;

    qreal cx = (b2-b1)/(a1-a2);
    qreal cy = a1 * cx + b1;



    if (fabs(a1-a2)<1.e-10){
        QMessageBox d;
        d.setText("a");
        d.exec();
    }

    return QPointF(cx, cy);
}

QPointF robotview::normalPoint(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3)
{
    qreal x0 = (x1*(y2-y1)*(y2-y1) + x3*(x2-x1)*(x2-x1) + (x2-x1)*(y2-y1)*(y3-y1))/((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
    qreal y0 = ((y2-y1)*(x0-x1)/(x2-x1))+y1;
    return QPointF(x0, y0);
}

QPointF robotview::mul(QPointF vector, qreal scalar)
{
    return QPointF(vector.rx()*scalar, vector.ry()*scalar);
}

QString robotview::toString(QPointF point)
{
    return ( QString::number (point.rx(), 'g',20) + ", " + QString::number(point.ry(), 'g',20));
}
