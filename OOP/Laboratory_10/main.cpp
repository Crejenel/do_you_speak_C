#include <QtWidgets/QApplication>
#include <tests.h>
#include <GUI.h>
#include "service.h"

int main(int argc, char *argv[])
{

    QualityAssurance quality_assurance;
    quality_assurance.test_all();

    QApplication a(argc, argv);
    string file_name = "SAVE";
    RepositorySAVE repository(file_name);
    Validator validator;
    Wishlist wishlist;
    Service service(wishlist, repository, validator);
    GraphicaUserInterface gui(service);
    gui.show();

    return a.exec();
}
