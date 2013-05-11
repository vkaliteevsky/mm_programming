#ifndef BOOMDETECTOR_H
#define BOOMDETECTOR_H
/*
class BoomDetector
{
public:
    BoomDetector();
};
*/

#include <QMessageBox>

#include <QGraphicsItem>

class BoomDetector: public QObject
{
    Q_OBJECT
public:
    // это чтобы нельзя было сделать пустой детектор
    BoomDetector(){}
public:
    BoomDetector(QGraphicsItem* firstItem, QGraphicsItem* secondItem):
        mrRobot(firstItem), mrWall(secondItem){}
    virtual ~BoomDetector(){}
protected:
    QGraphicsItem* mrRobot;
    QGraphicsItem* mrWall;
public slots:
    void ToDetect()
    {
        bool b = mrRobot->collidesWithItem(mrWall);
        if(b == true)
            QMessageBox::warning(NULL, "BOOM", "Killed him self on the wall");
    }
};


#endif // BOOMDETECTOR_H
