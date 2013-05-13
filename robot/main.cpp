#include "view/robotview.h"
#include "view/world.h"

 #include <QApplication>
 #include <QtGui>

 #include <math.h>

//#include <QGraphicsItem>




int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    world * world1 = new world;
    world1->close();
    //world1->run();
    //world1->show();


    return app.exec();
}
