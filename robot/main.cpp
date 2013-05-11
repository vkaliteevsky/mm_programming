#include "view/robotview.h"
#include "view/world.h"


 #include <QtGui>

 #include <math.h>

//#include <QGraphicsItem>

#include "boomdetector.h"


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    world * world1 = new world;
    //world1->run();
   // world1->show();
    // Add scene and Items

    return app.exec();
}
