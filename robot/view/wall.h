#ifndef WALL_H
#define WALL_H

#include <QtWidgets/QGraphicsItem>
#include <QPoint>


class Wall : public QGraphicsRectItem
{
public:
    Wall(qreal x, qreal y, qreal width, qreal height, qreal angle, qreal fric);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    bool contain(QPointF point);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void* r;

public:
    void setLines(QPointF p1, QPointF p2, QPointF p3, QPointF p4);
    void trueCoord();
    qreal getX()
    {
        return mX;
    }
    qreal getY()
    {
        return mY;
    }
    qreal getWidth()
    {
        return mWidth;
    }
    qreal getHeight()
    {
        return mHeight;
    }
    qreal getAngle()
    {
        return mAngle;
    }
    qreal getFric()
    {
        return mFric;
    }
    QPointF getPoint(int i)
    {
        return mP[i];
    }
    QLineF getLine(int i)
    {
        return linesList.at(i);
    }


private:
    QList<QLineF> linesList;
    QPointF mP[4];
    qreal mX;
    qreal mY;
    qreal mWidth;
    qreal mHeight;
    qreal mAngle;
    qreal mFric;//friction coefficient
    QColor mColor;
};

#endif // WALL_H
