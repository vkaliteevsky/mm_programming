#include <QPainter>

#include "wall.h"
#include "Robotview.h"
#include <math.h>
#include "world.h"


Wall::Wall(qreal x, qreal y, qreal width, qreal height, qreal angle, qreal fric)
    : mColor(150,20,20), r(0)
{
    mX = x;
    mY = y;
    mWidth = width;
    mHeight = height;
    mAngle = angle;
    mFric = fric;
    trueCoord();
}

QRectF Wall::boundingRect() const
{
    return QRectF(mX - mWidth*2, mY - mHeight*2, mWidth*3, mHeight*3);
}

QPainterPath Wall::shape() const
{
    QPainterPath path;
    path.addRect(mX, mY, mWidth, mHeight);
    return path;
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    setRotation(mAngle);
    painter->setBrush(mColor);
    painter->drawRect(mX, mY, mWidth, mHeight);
}

void Wall::setLines(QPointF p1, QPointF p2, QPointF p3, QPointF p4)
{
    linesList.push_back(QLineF(p1,p2));
    linesList.push_back(QLineF(p2,p3));
    linesList.push_back(QLineF(p3,p4));
    linesList.push_back(QLineF(p4,p1));
}

void Wall::trueCoord( )
{

    mP[0] = QPointF(getX()              ,getY());
    mP[1] = QPointF(getX() + getWidth() ,getY());
    mP[2] = QPointF(getX() + getWidth() ,getY() + getHeight());
    mP[3] = QPointF(getX()              ,getY() + getHeight());

    qreal angRad = getAngle()*M_PI/180;

    mP[0] = QPointF(mP[0].rx()*cos(angRad) - mP[0].ry()*sin(angRad), mP[0].rx()*sin(angRad) + mP[0].ry()*cos(angRad));
    mP[1] = QPointF(mP[1].rx()*cos(angRad) - mP[1].ry()*sin(angRad), mP[1].rx()*sin(angRad) + mP[1].ry()*cos(angRad));
    mP[2] = QPointF(mP[2].rx()*cos(angRad) - mP[2].ry()*sin(angRad), mP[2].rx()*sin(angRad) + mP[2].ry()*cos(angRad));
    mP[3] = QPointF(mP[3].rx()*cos(angRad) - mP[3].ry()*sin(angRad), mP[3].rx()*sin(angRad) + mP[3].ry()*cos(angRad));

    setLines(mP[0], mP[1], mP[2], mP[3]);
}


