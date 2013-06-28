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
    : angle(330), mass(100), size(40), V0(10), momentI(200), motorFactor(70),mAngularVelocity(0)
{
    QPointF q (0.01*V0*cos(angle*M_PI/180), 0.01*V0*sin(angle*M_PI/180));
    (q);
    setRotation(angle);
    for (int i =0; i<4; i++){
        setWall (i, NULL);
    }
    for (int i =0; i<4; i++){
        setEdgeWall (i, NULL);
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


void robotview::setV(QPointF& V)
{
    if(length(V) > V0)
    {
        qreal x = V0/length(V);
        V *= x;
        mV += 0. * mV;
    }

    if(V.ry() > 0.)
    {
        mV += 0. * mV;
    }
    mV = V;
}

QPointF robotview::getV()const
{
    return mV;
}

void robotview::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(QColor(0,0,0));



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

    QFont font;

    painter->setFont(font);
    if (!(this->mWalls[0] == NULL)){
            painter->drawText(QRect(10,-25,20,20),"+");
    } else {
            painter->drawText(QRect(15,-25,20,20),"-");
    }
    if (!(this->mWalls[1] == NULL)){
            painter->drawText(QRect(10,5,20,20),"+");
    } else {
            painter->drawText(QRect(15,5,20,20),"-");
    }
    if (!(this->mWalls[2] == NULL)){
            painter->drawText(QRect(-20,5,20,20),"+");
    } else {
            painter->drawText(QRect(-20,5,20,20),"-");
    }
    if (!(this->mWalls[3] == NULL)){
            painter->drawText(QRect(-20,-25,20,20),"+");
    } else {
            painter->drawText(QRect(-20,-25,20,20),"-");
    }
    font.setPointSize(8);






   painter->drawText(QRect(0,0,25,25),QString::number(length(mV)));



}

void robotview::updateAngle()
{
    QPointF V = getV();
    angle = 180 * atan2(V.ry(), V.rx())/M_PI;
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

    for (int i = 0; i < 3; i++) {
        mL[i] = QLineF(mP[i], mP[i+1]);
    }
    mL[3] = QLineF(mP[3], mP[0]);

}

void robotview::nextStep(qreal dt)
{
    //QPointF V = getV();
    //QPointF V1 = V + mForce / mass * dt;
    //setV(V1);
    mPos = pos();
    setPos( mPos += getV()*dt);
    QPointF pos1 = pos();
    mPos = pos();
    angle += mAngularVelocity*dt;
    updateCoord();
}

void robotview::checkCollision(Wall& wall)
{


    mEdP.clear();
    if(collidesWithItem(&wall)) {
        for(int i = 0; i <4; i++)
        {
            QPointF new_p = wall.mapFromScene(mP[i]);
            if (wall.contains(new_p)) {



                if (i == 1) {
                    mV += 0. * mV;
                }

                if(mWalls[i]== NULL) {
                    //Vnormal = 0
                    QLineF border = interRobotLine(wall);
                    QPointF normPoint = normalPoint(border.x1(), border.y1(), border.x2(), border.y2(), mP[i].rx(), mP[i].ry());
                    QPointF n (-normPoint + mP[i]);
                    n = normalize(n);
                    if (!(length(n) < 1.e-10)){
                        QPointF V = getV();
                        qreal k = scalarProduct(V, n);
                        QPointF V1 (V - n * k);
                        setV(V1);
                    }
                }
                //

                    if (i == 1) {
                        mV += 0. * mV;
                    }
                    setWall(i, &wall);
                //}
            } else {
                //if ((i == 2) || (i == 3)){
                //     setWall(i, NULL);
                //}
                if (mWalls[i] == &wall){
                    setWall(i, NULL);
                }
            }




           // QPointF p = mapFromScene(wall.mP[i]);
            // //QPointF p = (mP[i]);
             //p = ((wall.mP[i]));

            //if (contains(p)){
                //p = mapToScene(p);



            QPointF p = mapFromScene(wall.mP[i]);
            if (contains(p)) {
                p = mapToScene(p);
                QLineF border = interWallLine(wall);
                QPointF normPoint = normalPoint(border.x1(), border.y1(), border.x2(), border.y2(), p.rx(), p.ry());
                QPointF n (-normPoint + p);
                n = normalize(n);
                QPointF V1 (0,0);
                setV(V1);
                mEdP.push_back(p);
                mEdgeP = p;
                mAngularVelocity=0;
                //setEdgeWall(i, &wall);
            } else {
                if (mEdgeWalls[i] == &wall){
                    setEdgeWall(i, NULL);
                }
            }


        }
    } else {
        for (int i = 0; i < 4; i++) {

            if (mWalls[i] == &wall) {
                mWalls[i] = NULL;
                mAngularVelocity = 0;
                qreal k = length( getV() );
                //setV(QPointF(cos(angle*M_PI/180)*k, sin(angle*M_PI/180)*k));
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
        if (mEdgeWalls[i] != NULL){
            getEdgeRobotFromWall(*(mEdgeWalls[i]),i);
        }
        //for (int j = 0; j < 3; j++) {
        //    if (isCollision(mWalls[i], j)) {
        //        getRobotFromWall(*(mWalls[i]),j);
        //    }
        //}
    }
}


bool robotview::isCollision(Wall& wall, int i)
{
    QPointF new_p = wall.mapFromScene(mP[i]);
    return (wall.contains(new_p));
}

bool robotview::isEdgeCollision(Wall& wall, int i)
{
    QPainterPath path (mL[i].p1() );
    path.lineTo(mL[i].p2());
    return (wall.collidesWithPath(path));
}

void robotview::updateVelocity(qreal dt) {
    //qreal kk = 700;
    mForce *= 0;
    mForseMoment = 0;

    qreal kk = length(getV())*150;
    qreal angularVelocityFric = fabs(mAngularVelocity*100);

    //qreal angularVelocityFric = 250;

    QPointF napr (cos(angle * M_PI / 180), sin (angle * M_PI / 180));


    qreal scalProd = scalarProduct(getV(), napr);
    QPointF vec = mul(napr, fabs(scalProd));


    qreal tmp2 = ( V0 - scalProd) * motorFactor;
    QPointF F_engine = mul (napr  ,tmp2);
    QPointF p0 = pos();
    mForce = F_engine;


    if (mCounter == 1434) {
        mV += 0. * mV;
    }
    for (int i = 0; i < 4; i++){
        if (mEdgeWalls[i] != NULL){
            for (int j = 0; j < mEdP.length(); j++) {
                QPointF tmp(mEdP.at(j) - p0);
                QPointF F_norm = mForce;
                F_norm *= -1;
                qreal a = vectorProduct(F_norm, tmp);
                mForseMoment -= a;
            }
        }
    }



    for (int i = 0; i < 4; i++){
        if (mWalls[i] != NULL){

            QPointF tmp(mP[i] - p0);
            //QPointF tmp2(mP[i].rx() - napr.rx(), mP[i].ry() - napr.ry());

            QLineF bord = nearRobotLine(*mWalls[i], mP[i]);
            qreal ang = bord.angle();
            QPointF vectorParalStene (cos(ang*M_PI/180),-sin(ang*M_PI/180));//знаки
            //QPointF vectorParalStene (sin(ang*M_PI/180), -cos(ang*M_PI/180));//знаки

            if (scalarProduct(vectorParalStene, napr) < 0) vectorParalStene *= (-1);


            vectorParalStene = normalize(vectorParalStene);

            QPointF F_norm = mForce;

            double sc1 = scalarProduct(mForce, vectorParalStene);
            F_norm -= mul(vectorParalStene, sc1);

            F_norm *= -1;
            QPointF F_fr_wall;

            vectorParalStene *= -1;

            F_fr_wall = vectorParalStene;
            F_fr_wall *= length(F_norm) * mWalls[i]->getFric();





            mForce += F_norm;
            mForce += F_fr_wall;





            qreal a = vectorProduct(F_fr_wall, tmp);
            qreal b = vectorProduct(F_norm , tmp);

            mForseMoment -= a;
            mForseMoment -= b;


        }
    }


    if (mForseMoment != 0) {
        QMessageBox msb;
        msb.setText("error");



    }
    QPointF V = getV();
    QPointF V1 = V + mForce / mass * dt;
    setV(V1);

   /* qreal tmp3 = scalarProduct(mV, F_fric);
    if (tmp3 > 0){
        QPointF vec = normalize(mV);
        vec = mul(vec, tmp3);

        mV -= vec;
    }*/

    mAngularVelocity += mForseMoment /  momentI * dt;

    qreal tmp = mAngularVelocity;
    if (mAngularVelocity > 0) {
        mAngularVelocity -= angularVelocityFric / momentI * dt;
    } else {
        mAngularVelocity += angularVelocityFric / momentI * dt;
    }
    if (tmp * mAngularVelocity <= 0) {
        mAngularVelocity = 0;
    }

    QPointF F_fric = QPointF(-napr.ry(), napr.rx());

    F_fric = normalize(F_fric);

    QPointF tmp_mV = getV();
    if (length(tmp_mV) != 0) {
        tmp_mV = normalize(tmp_mV);
    }
    qreal sinus = vectorProduct(tmp_mV, F_fric);

    F_fric = mul(F_fric ,sinus*kk);

    V = getV();
    if (scalarProduct(F_fric, V) > 0) {
        F_fric = -F_fric;
    }

    QPointF mVtmp = V + F_fric / mass * dt;
    qreal sc_1 = scalarProduct(mVtmp, F_fric);
    if (sc_1 > 0) {
        qreal sc_2 = -scalarProduct(V, F_fric);
        if(sc_2 < 0) {
            QMessageBox msb;
            msb.setText("error");
            msb.exec();
        }
        qreal dt_tmp = dt *sc_2/(sc_2 + sc_1);
        QPointF V1 = V + F_fric / mass * dt_tmp;
        setV(V1);

    }  else {
        setV(mVtmp);
    }
     V = getV();
    if ( length(V) > V0){
        V1 = normalize(V) * V0;
        setV(V1);
    }
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
    if ((collidesWithItem(&wall))){
        QPointF p = mP[index];
        QLineF border = nearRobotLine(wall, p);
        QPointF pntIntersect = normalPoint(border.x1(), border.y1(), border.x2(), border.y2(), p.rx(), p.ry());
        if (!((pntIntersect.rx() == NAN) || (pntIntersect.ry() == NAN))){
            QPointF k;
            k = pntIntersect -= p;
            QPointF poss = pos();
            setPos(poss+=k);
            mPos = pos();
            updateCoord();
        } else {
            QMessageBox n;
            n.setText("Error.");
            n.exec();
        }
    }
}

void robotview::getEdgeRobotFromWall(Wall& wall, int index)
{

   // QPointF new_p = wall.mapFromScene(mP[i]);
   // if (wall.contains(new_p)) {}


    if ((collidesWithItem(&wall))){
        QLineF l = mL[index];

        wall.mP[0];
        for (int i = 0; i<4; i++)
        {
            QPointF p = mapFromScene(wall.mP[i]);
            //QPointF p = (mP[i]);
             //p = ((wall.mP[i]));

            if (contains(p)){
                p = mapToScene(p);
                QPointF pntIntersect = normalPoint(l.x1(), l.y1(), l.x2(), l.y2(), p.rx(), p.ry());
                QPointF k (p.rx() - pntIntersect.rx(),p.ry() - pntIntersect.ry());
                qreal op = length(k);
                QPointF poss = pos();
                setPos(poss+=k);
                mPos = pos();
                updateCoord();

            }


        }



    }
       /* QPointF p = mP[index];
        QLineF border = nearRobotLine(wall, p);
        QPointF pntIntersect = normalPoint(border.x1(), border.y1(), border.x2(), border.y2(), p.rx(), p.ry());
        if (!((pntIntersect.rx() == NAN) || (pntIntersect.ry() == NAN))){
            QPointF k;
            k = pntIntersect -= p;
            QPointF poss = pos();
            //k+=QPointF (0.0000001, 0.0000001);
            setPos(poss+=k);
            mPos = pos();
            updateCoord();
        } else {
            QMessageBox n;
            n.setText("Error.");
            n.exec();
        }*/

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

QLineF robotview::interWallLine(Wall& wall)
{
    QLineF linne;
    QGraphicsLineItem *l = new QGraphicsLineItem(0,0,0,0);
    for(int i = 0; i<4; i++)
    {
        l->setLine(mL[i]);
        if (wall.collidesWithItem(l)){
            linne = l->line();
            setEdgeWall(i, &wall);
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
    if (x1 == x2) return QPointF(x2, y3);
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
