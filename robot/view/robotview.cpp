#include "robotview.h"
#include "world.h"

#include <QMessageBox>
#include <QTextItem>
#include <QFont>

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

#include <math.h>

robotview::robotview()
    : mAngle(330), mMass(100), mSize(40), mFullSpeed(10), mMomentI(200), mMotorFactor(70),mAngularVelocity(0)
{
    setRotation(mAngle);
    for (int i =0; i<4; i++){
        setWall (i, NULL);
    }
    for (int i =0; i<4; i++){
        setEdgeWall (i, NULL);
    }
}

QRectF robotview::boundingRect() const
{
    QRectF rect(-mSize*2, -mSize*2, mSize*4, mSize*4);
    return rect;
}

QPainterPath robotview::shape() const
{
    QPainterPath path;
    path.addRect(-mSize/2, -mSize/2, mSize, mSize);
    return path;
}


void robotview::setV(QVector2D& V)
{
    qreal V0 = getFullSpeed();
    if(V.length() > V0)
    {
        qreal x = V0/V.length();
        V *= x;
    }
    mV = V;
}

QVector2D robotview::getV()const
{
    return mV;
}

void robotview::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(QColor(0,0,0));
    setRotation(mAngle);
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

void robotview::updateCoord() // Обновляет координаты вершин
{
    double x = pos().rx();
    double y = pos().ry();
    double nx = cos(mAngle * M_PI/180);
    double ny = sin(mAngle * M_PI/180);

    double nnx = nx*(mSize/2);
    double nny = ny*(mSize/2);

    mP[0] = QPointF(x + nnx + nny, y + nny - nnx);
    mP[1] = QPointF(x + nnx - nny, y + nny + nnx);
    mP[2] = QPointF(x - nnx - nny, y - nny + nnx);
    mP[3] = QPointF(x - nnx + nny, y - nny - nnx);

    for (int i = 0; i < 3; i++) {
        mL[i] = QLineF(mP[i], mP[i+1]);
    }
    mL[3] = QLineF(mP[3], mP[0]);

}

void robotview::nextStep(qreal dt) // Делает шаг и меняет угол
{

    QVector2D curPos (pos());
    curPos += getV()*dt;
    setPos(curPos.x(), curPos.y());
    mAngle += mAngularVelocity*dt;
    updateCoord();
}

void robotview::checkCollision(Wall& wall) // Проверяет коллизии
{
    mEdP.clear();
    if(collidesWithItem(&wall)) {
        for(int i = 0; i <4; i++)
        {
            QPointF new_p = wall.mapFromScene(mP[i]);
            if (wall.contains(new_p)) {
                if(mWalls[i]== NULL) {
                    //Vnormal = 0
                    QLineF border = interRobotLine(wall);
                    QPointF normPoint = normalPoint(border.x1(), border.y1(), border.x2(), border.y2(), mP[i].rx(), mP[i].ry());

                    QVector2D n (-normPoint.rx() + mP[i].rx(), -normPoint.ry() + mP[i].ry());
                    n = n.normalized();
                    if (!(n.length() < 1.e-10)) {
                        QVector2D V = getV();
                        qreal k = scalarProduct(V, n);
                        QVector2D V1 (V - n * k);
                        setV(V1);
                    }
                }
                setWall(i, &wall);
            } else {
                if (mWalls[i] == &wall){
                    setWall(i, NULL);
                }
                QPointF p = mapFromScene(wall.getPoint(i));
                if (contains(p)) {
                    p = mapToScene(p);
                    QLineF border = interWallLine(wall);
                    QPointF normPoint = normalPoint(border.x1(), border.y1(), border.x2(), border.y2(), p.rx(), p.ry());
                    QVector2D n (-normPoint.rx() + p.rx(), -normPoint.ry() + p.ry());
                    n = n.normalized();
                    QVector2D V1 (0,0);
                    setV(V1);
                    mEdP.push_back(p);
                    mAngularVelocity=0;
                } else {
                    if (mEdgeWalls[i] == &wall){
                        setEdgeWall(i, NULL);
                    }
                }

            }
        }
    } else {
        for (int i = 0; i < 4; i++) {

            if (mWalls[i] == &wall) {
                mWalls[i] = NULL;
                mAngularVelocity = 0;
            }
        }
    }

}


void robotview::updateWalls() // Вытаскивает из стен
{
    for (int i = 0; i < 4; i++){
        if (mWalls[i] != NULL){
            getRobotFromWall(*(mWalls[i]),i);
        }
        if (mEdgeWalls[i] != NULL){
            getEdgeRobotFromWall(*(mEdgeWalls[i]),i);
        }
    }
}


bool robotview::isCollision(Wall& wall, int i) // Проверяет коллизию поиском вершины робота в стене
{
    QPointF new_p = wall.mapFromScene(mP[i]);
    return (wall.contains(new_p));
}

bool robotview::isEdgeCollision(Wall& wall, int i) // Проверяет наличие пересечения ребра робота со стеной
{
    QPainterPath path (mL[i].p1() );
    path.lineTo(mL[i].p2());
    return (wall.collidesWithPath(path));
}

void robotview::updateVelocity(qreal dt) { // Высчитывает изменение скорости и угла

    setForce(QVector2D(0,0));
    setForceMoment(0);

    qreal rotationalFricFactor = getV().length()*150;
    qreal angularVelocityFricFactor = fabs(mAngularVelocity*100);

    QVector2D napr (cos(mAngle * M_PI / 180), sin (mAngle * M_PI / 180));
    qreal scalProd = scalarProduct(getV(), napr);
    qreal V0 = getFullSpeed();
    qreal tmp2 = ( V0 - scalProd) * mMotorFactor;
    QVector2D F_engine = mul(napr,tmp2);
    QPointF p0 = pos();
    mForce = F_engine;

    for (int i = 0; i < 4; i++) { // Если врезались в угол стены
        if (mEdgeWalls[i] != NULL){
            for (int j = 0; j < mEdP.length(); j++) {
                QVector2D tmp(mEdP.at(j) - p0);
                QVector2D F_norm = mForce;
                F_norm *= -1;
                qreal a = vectorProduct(F_norm, tmp);
                mForceMoment -= a;
            }
        }
    }



    for (int i = 0; i < 4; i++) { // Если врезались в ребро стены
        if (mWalls[i] != NULL){

            QVector2D tmp(mP[i] - p0);

            QLineF bord = nearRobotLine(*mWalls[i], mP[i]);
            qreal ang = bord.angle();
            QVector2D vectorParalStene (cos(ang*M_PI/180),-sin(ang*M_PI/180));

            if (scalarProduct(vectorParalStene, napr) < 0) {
                vectorParalStene *= (-1);
            }
            vectorParalStene = vectorParalStene.normalized();

            QVector2D F_norm = mForce;

            double sc1 = scalarProduct(mForce, vectorParalStene);
            F_norm -= mul(vectorParalStene, sc1);

            F_norm *= -1;
            QVector2D F_fr_wall;

            vectorParalStene *= -1;

            F_fr_wall = vectorParalStene;
            F_fr_wall *= F_norm.length() * mWalls[i]->getFric();

            mForce += F_norm;
            mForce += F_fr_wall;

            qreal a = vectorProduct(F_fr_wall, tmp);
            qreal b = vectorProduct(F_norm , tmp);

            mForceMoment -= a;
            mForceMoment -= b;


        }
    }

    QVector2D V = getV();
    QVector2D V1 = V + mForce / mMass * dt;
    setV(V1);

    qreal momentI = getInertiaMoment();
    mAngularVelocity += mForceMoment /  momentI * dt;

        // Далее анализируем трение поворота и момент трения поворота
    qreal tmpAngVel = mAngularVelocity;
    if (mAngularVelocity > 0) {
        mAngularVelocity -= angularVelocityFricFactor / momentI * dt;
    } else {
        mAngularVelocity += angularVelocityFricFactor / momentI * dt;
    }
    if (tmpAngVel * mAngularVelocity <= 0) {
        mAngularVelocity = 0;
    }


    QVector2D rotationalFrictionF (-napr.y(), napr.x());

    rotationalFrictionF = rotationalFrictionF.normalized();

    QVector2D tmpV = getV();
    if (tmpV.length() != 0) {
        tmpV = tmpV.normalized();
    }
    qreal sinus = vectorProduct(tmpV, rotationalFrictionF);

    rotationalFrictionF = mul(rotationalFrictionF ,sinus * rotationalFricFactor);

    V = getV();
    if (scalarProduct(rotationalFrictionF, V) > 0) {
        rotationalFrictionF = -rotationalFrictionF;
    }

    QVector2D newV = V + rotationalFrictionF / mMass * dt;
    qreal sc_1 = scalarProduct(newV, rotationalFrictionF);
    if (sc_1 > 0) {
        qreal sc_2 = -scalarProduct(V, rotationalFrictionF);
        if(sc_2 < 0) {
            QMessageBox msb;
            msb.setText("error");
            msb.exec();
        }
        qreal dt_tmp = dt *sc_2/(sc_2 + sc_1);
        QVector2D V1 = V + rotationalFrictionF / mMass * dt_tmp;
        setV(V1);

    }  else {
        setV(newV);
    }
    V = getV();
    if ( V.length() > V0){
        newV = V.normalized() * V0;
        setV(newV);
    }
}


qreal robotview::vectorProduct(QVector2D vector1, QVector2D vector2)
{
    return  vector1.x()*vector2.y() - vector1.y()*vector2.x();
}

qreal robotview::scalarProduct(QVector2D vector1, QVector2D vector2)
{
    return vector1.x()*vector2.x() + vector1.y()*vector2.y();
}

void robotview::getRobotFromWall(Wall& wall, int index) // Вытаскивает из стены по заданной вершине робота
{
    if ((collidesWithItem(&wall))){
        QPointF p = mP[index];
        QLineF border = nearRobotLine(wall, p);
        QPointF pntIntersect = normalPoint(border.x1(), border.y1(), border.x2(), border.y2(), p.rx(), p.ry());
        QPointF k;
        k = pntIntersect -= p;
        QPointF curPos = pos();
        setPos(curPos+=k);
        updateCoord();
    }
}

void robotview::getEdgeRobotFromWall(Wall& wall, int index) // Вытаскивает из стены по заданному ребру робота
{    
    if ((collidesWithItem(&wall))){
        QLineF l = mL[index];
        for (int i = 0; i<4; i++)
        {
            QPointF p = mapFromScene(wall.getPoint(i));
            if (contains(p)){
                p = mapToScene(p);
                QPointF pntIntersect = normalPoint(l.x1(), l.y1(), l.x2(), l.y2(), p.rx(), p.ry());
                QPointF k (p.rx() - pntIntersect.rx(),p.ry() - pntIntersect.ry());
                QPointF curPos = pos();
                setPos(curPos+=k);
                updateCoord();
            }
        }
    }
}

QLineF robotview::interRobotLine(Wall& wall) // Возвращает ребро стены, в которое въехал робот
{
    QLineF tmpLine;
    QGraphicsLineItem *l = new QGraphicsLineItem(0,0,0,0);
    for(int i = 0; i<4; i++)
    {
        l->setLine(wall.getLine(i));
        if (collidesWithItem(l)){
            tmpLine = l->line();
        }
    }
    return tmpLine;
}

QLineF robotview::interWallLine(Wall& wall) // Возвращает ребро робота, которым робот въехал в стену
{
    QLineF tmpLine;
    QGraphicsLineItem *l = new QGraphicsLineItem(0,0,0,0);
    for(int i = 0; i<4; i++)
    {
        l->setLine(mL[i]);
        if (wall.collidesWithItem(l)){
            tmpLine = l->line();
            setEdgeWall(i, &wall);
        }
    }
    return tmpLine;
}

QLineF robotview::nearRobotLine(Wall& wall, QPointF p) // Возвращает наименьший из перпендикуляров от точки до ребер стены
{
    QList<qreal> len;
    qreal min=0;
    for(int i = 0; i<4; i++)
    {
        QLineF l;
        l= wall.getLine(i);
        QPointF normPoint = normalPoint(l.x1(), l.y1(), l.x2(), l.y2(), p.rx(),p.ry());
        QLineF k (p.rx(), p.ry(), normPoint.rx(),normPoint.ry());
        len.push_back( k.length());
        if (min == 0){
            min = k.length();
        }
        if (k.length() < min){
            min = k.length();
        }
    }
    int j = len.indexOf(min);
    return wall.getLine(j);
}

QPointF robotview::normalPoint(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3) // Возвращает точку прямой, в которую опустится перпендикуляр из заданной точки
{
    if (x1 == x2) return QPointF(x2, y3);
    qreal x0 = (x1*(y2-y1)*(y2-y1) + x3*(x2-x1)*(x2-x1) + (x2-x1)*(y2-y1)*(y3-y1))/((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
    qreal y0 = ((y2-y1)*(x0-x1)/(x2-x1))+y1;
    return QPointF(x0, y0);
}

QVector2D robotview::mul(QVector2D vector, qreal scalar)
{
    return QVector2D(vector.x()*scalar, vector.y()*scalar);
}


