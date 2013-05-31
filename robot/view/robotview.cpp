#include "robotview.h"
#include "world.h"

#include <QMessageBox>

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

#include <math.h>

robotview::robotview()
    : angle(340), mass(100), size(40), V0(5), momentI(20),motorFactor(10)
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
}

void robotview::updateAngle()
{
    qreal tg = mV.ry()/mV.rx();
    angle = 180 * atan(tg)/M_PI;
    setRotation(angle);
}

void robotview::updateCoord()
{
    double x = pos().rx();
    double y = pos().ry();
    double nx = cos(angle * M_PI/180);
    double ny = sin(angle * M_PI/180);

    double nnx = nx*(size/2);
    double nny = ny*(size/2);

    mP[0] = QPointF(x + nnx + nny, y + nny - nnx);
    mP[1] = QPointF(x + nnx - nny, y + nny + nnx);
    mP[2] = QPointF(x - nnx - nny, y - nny + nnx);
    mP[3] = QPointF(x - nnx + nny, y - nny - nnx);
}

void robotview::nextStep(qreal dt)
{
    mV += mForce / mass * dt;
    setPos( pos() += mV*dt);
    angle += mAngularVelocity*dt;
    updateCoord();
}

void robotview::checkCollision(Wall& wall)
{
    if(collidesWithItem(&wall)) {
        for(int i = 0; i <4; i++)
        {
            QPointF new_p = wall.mapFromScene(mP[i]);
            if (wall.contains(new_p)) {
                if(mWalls[i]== NULL) {
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
                //if ((i == 0) || (i == 1)){
                    setWall(i, &wall);
                //}
            } else {
                    setWall(i, NULL);
            }
        }
    } else {
        for (int i = 0; i < 4; i++) {

            if (mWalls[i] == &wall) {
                mWalls[i] = NULL;
                mAngularVelocity = 0;
                qreal k = length(mV);
                mV.setX(cos(angle*M_PI/180)*k);
                mV.setY(sin(angle*M_PI/180)*k);
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


void robotview::updateVelocity(qreal dt) {
    mForce *= 0;
    mForseMoment = 0;
    QPointF napr (cos(angle * M_PI / 180), sin (angle * M_PI / 180));

    QPointF vec = mul(napr,scalarProduct(mV, napr));
    qreal tmp2 = ( V0 - length(vec)) * motorFactor;
    QPointF F_engine = mul (vec  ,tmp2);
    QPointF p0 = pos();
    mForce = F_engine;
    for (int i = 0; i < 2; i++){
        if (mWalls[i] != NULL){

            QLineF bord = nearRobotLine(*mWalls[i], mP[i]);
            qreal ang = bord.angle();
            QPointF vectorParalStene (cos(ang*M_PI/180),-sin(ang*M_PI/180));

            vectorParalStene = normalize(vectorParalStene);

            QPointF F_norm = mForce;

            double sc1 = scalarProduct(mForce, vectorParalStene);
            F_norm -= mul(vectorParalStene, sc1);

            F_norm *= -1;
            QPointF F_fr;

            vectorParalStene *= -1;

            F_fr = vectorParalStene;
            F_fr *= length(F_norm) * mWalls[i]->getFric();

            mForce += F_norm;
            mForce += F_fr;

            QPointF tmp(mP[i] - p0);
            qreal a = vectorProduct(F_fr, tmp);
            qreal b = vectorProduct(F_norm , tmp);

            mForseMoment += a;
            mForseMoment -= b;
        }
    }
    mV += mForce / mass * dt;
    mAngularVelocity += mForseMoment /  momentI * dt;
}


qreal robotview::vectorProduct(QPointF vector1, QPointF vector2)
{
    return  vector1.rx()*vector2.ry() - vector1.ry()*vector2.rx();
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
    if (collidesWithItem(&wall)){
        QPointF p = mP[index];
        QLineF border = nearRobotLine(wall, p);
        QPointF pntIntersect = normalPoint(border.x1(), border.y1(), border.x2(), border.y2(), p.rx(), p.ry());
        if (!((pntIntersect.rx() == NAN) || (pntIntersect.ry() == NAN))){
            QPointF k;
            k = pntIntersect -= p;
            QPointF poss = pos();
            k+=QPointF (0.0000001, 0.0000001);
            setPos(poss+=k);
            updateCoord();
        } else {
            QMessageBox n;
            n.setText("Error.");
            n.exec();
        }
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
    return wall.linesList.at(j);

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
