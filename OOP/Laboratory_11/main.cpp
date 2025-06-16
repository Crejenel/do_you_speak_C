#include <qapplication.h>
#include "graphical_user_interface.h"
#include <iostream>
#include "tests.h"

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    QualityAssurance a;
    a.test_all();
    
    GraphicaUserInterface GUI;

    GUI.show();

    return app.exec();
}
