#include <QPainter>

#include "wall.h"
#include "Robotview.h"
#include <math.h>
#include "world.h"


Wall::Wall(qreal _x,qreal _y,qreal _width,qreal _height,qreal _angle,qreal _fric)
    : color(150,20,20), r(0)
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    angle = _angle;
    fric = _fric;
    true_coord2();
}

QRectF Wall::boundingRect() const
{
    return QRectF(x-width*1.5, y-height*1.5, width*3, height*3);
}

QPainterPath Wall::shape() const
{
    QPainterPath path;
    path.addRect(x, y, width, height);
    return path;
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    setRotation(angle);
    painter->setBrush(color);
    painter->drawRect(x, y, width, height);
    if (r){
        robotview* rr = (robotview*)r;

      //  painter->drawText(QRect(-300,-300,2000,2000),"скорость " + QString::number(rr->mV.rx()) + "   " + QString::number(rr->mV.ry()));
      //  painter->drawText(QRect(-300,-290,2000,2000),"угловая скорость " + QString::number(rr->mAngularVelocity));
      //  painter->drawText(QRect(-300,-280,2000,2000),"сила " + QString::number(rr->mForce.rx()) + "   " + QString::number(rr->mForce.ry()));
      //  painter->drawText(QRect(-300,-270,2000,2000),"момент силы " + QString::number(rr->mForseMoment));

    }
}

bool Wall::isNotNear(QPointF point)
{
    //( (world*)w)->scene->addRect(point.rx(),point.ry(),3,3 );
    //return true;

    qreal diag = 1;
    QLineF l1(point.rx(), point.ry(), mP[0].rx(), mP[0].ry());
    QLineF l2(point.rx(), point.ry(), mP[1].rx(), mP[1].ry());
    QLineF l3(point.rx(), point.ry(), mP[2].rx(), mP[2].ry());
    QLineF l4(point.rx(), point.ry(), mP[3].rx(), mP[3].ry());
    if ((l1.length() > diag)&&((l2.length())>diag)&&((l3.length())>diag)&&((l4.length())>diag)){
        return true;
    } else {
        return false;
    }

}



void Wall::setLines(QPointF p1, QPointF p2, QPointF p3, QPointF p4)
{
    linesList.push_back(QLineF(p1,p2));
    linesList.push_back(QLineF(p2,p3));
    linesList.push_back(QLineF(p3,p4));
    linesList.push_back(QLineF(p4,p1));
}

void Wall::true_coord2( )
{

    mP[0] = QPointF(getX()                      ,getY());
    mP[1] = QPointF(getX() + getWidth() ,getY());
    mP[2] = QPointF(getX() + getWidth() ,getY() + getHeight());
    mP[3] = QPointF(getX()                      ,getY() + getHeight());

    qreal angRad = getAngle()*M_PI/180;

    mP[0] = QPointF(mP[0].rx()*cos(angRad) - mP[0].ry()*sin(angRad), mP[0].rx()*sin(angRad) + mP[0].ry()*cos(angRad));
    mP[1] = QPointF(mP[1].rx()*cos(angRad) - mP[1].ry()*sin(angRad), mP[1].rx()*sin(angRad) + mP[1].ry()*cos(angRad));
    mP[2] = QPointF(mP[2].rx()*cos(angRad) - mP[2].ry()*sin(angRad), mP[2].rx()*sin(angRad) + mP[2].ry()*cos(angRad));
    mP[3] = QPointF(mP[3].rx()*cos(angRad) - mP[3].ry()*sin(angRad), mP[3].rx()*sin(angRad) + mP[3].ry()*cos(angRad));

    setLines(mP[0], mP[1], mP[2], mP[3]);
}
