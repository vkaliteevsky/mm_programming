#include "robotview.h"
#include "world.h"

#include <QMessageBox>

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

#include <math.h>

robotview::robotview()
    : angle(15), mass(100), size(40), V0(10), momentI(0.00000000000003),motorFactor(5)
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

    setPos( pos() += mV*dt);
    angle += mAngularVelocity*dt;
   // setAngle(angle);
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
                    QPointF n (-normPoint + mP[i]);

                    if (!(length(n) < 1.e-10)){
                        qreal k = n.rx()*mV.rx() +  n.ry()*mV.ry();
                        qreal n2 = n.rx()*n.rx() +  n.ry()*n.ry();
                        mV -= n*(k/n2);
                    }
                }
                setWall(i, &wall);
            } else {
                if (mWalls[i] == &wall) {
                    QMessageBox ms;
                    ms.setText("setNull");
                    ms.exec();
                    setWall(i, NULL);
                }
            }
        }
    }
}

void robotview::updateWalls()
{
    for (int i = 0; i < 4; i++){
        if (mWalls[i] != NULL){
            getRobotFromWall(*(mWalls[i]),i);
        }
    }
}


void robotview::updateVelocity(qreal dt){

    mForce *= 0;//vector
    mForseMoment = 0;
    QPointF F_engine = mul (mV  , ( V0 - length(mV)) * motorFactor);
    QPointF p0 = pos();
    mForce = F_engine;
    for (int i = 0; i < 4; i++){
        if (mWalls[i] != NULL){

            QLineF bord = interRobotLine(*mWalls[i]);
            QPointF vectorParalStene (-bord.x2() + bord.x1(), -bord.y2() + bord.y1());

            QPointF F_norm = mForce;
            qreal sc = scalarProduct(vectorParalStene,vectorParalStene);
            if (sc > 1.e-20)
                F_norm -= scalarProduct(mForce, vectorParalStene)*vectorParalStene/scalarProduct(vectorParalStene,vectorParalStene);
            F_norm *=-1;
            QPointF F_fr = mV;
            sc = scalarProduct(F_norm,F_norm);
            if (sc > 1.e-20)
                   F_fr -= scalarProduct(F_fr,F_norm)/scalarProduct(F_norm,F_norm)*F_norm;
            F_fr *= -1;
            F_fr = normalize(F_fr);
            F_fr *= length(F_norm) * mWalls[i]->getFric();
            //F_fr = Force * sin(wallRobotAngle * M_PI/180)*K;
            (mForce += F_norm ) += F_fr;
            QPointF tmp(mP[i] - p0);
            qreal a = vectorProduct(F_fr, tmp);
            qreal b = vectorProduct(F_norm , tmp);
            mForseMoment += a += b;


            // //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            QGraphicsRectItem * ss = new QGraphicsRectItem(0, 150, 300, 200);
            ss->setBrush(QColor(121,121,9));
            ( (world*)w)->scene->addItem(ss);
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
            ( (world*)w)->scene->addItem(text);

            // //////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        }
    }
    //qreal mAngularVelocity;




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
    QPointF pntIntersect = interPoint(border.x1(), border.y1(), border.x2(), border.y2(), revDirection.x1(), revDirection.y1(), revDirection.x2(), revDirection.y2());

    if (!((pntIntersect.rx() == NAN) || (pntIntersect.ry()==NAN))){
   //     setPos(this->pos().rx()+ pntIntersect.rx() - p.rx()
     //           , this->pos().ry() + pntIntersect.ry() - p.ry());

        setPos(pos() += pntIntersect -= p);
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
    return ( QString::number(point.rx()) + ", " + QString::number(point.ry()));
}
