#include "graphical_user_interface.h"

GraphicaUserInterface::GraphicaUserInterface(QWidget* parent) : QMainWindow(parent) {
    setupHomeWindowGraphics();
    setHomeWindowTitle();
    updateLiveStatusList();
    initConnect();
}

void GraphicaUserInterface::setLiveStatusList() {

    liveStatusList = new QListWidget();
}

void GraphicaUserInterface::setContainerWidgetForLogoLayout() {

    logoLayout = new QVBoxLayout();
    QLabel* image_label = new QLabel();
    QPixmap pixmap("Media/logo.jpg");
    image_label->setPixmap(pixmap);
    ContainerWidgetForLogoLayout = new QWidget();
    ContainerWidgetForLogoLayout->setLayout(logoLayout);
    ContainerWidgetForLogoLayout->setStyleSheet("background-color: black;");
    logoLayout->addWidget(image_label, 0, Qt::AlignCenter);

}

void GraphicaUserInterface::setLogPanel() {
    logPanel = new QListWidget();
}

void GraphicaUserInterface::setFormLayout() {

    formLayout = new QFormLayout();
    nameField = new QLineEdit;
    formLayout->addRow("Name : ", nameField);
    typeField = new QLineEdit;
    formLayout->addRow("Type : ", typeField);
    destinationField = new QLineEdit;
    formLayout->addRow("Destination : ", destinationField);
    priceField = new QLineEdit;
    formLayout->addRow("Price : ", priceField);
    idField = new QLineEdit;
    formLayout->addRow("ID : ", idField);

}

void GraphicaUserInterface::setContainerWidgetForMainButtonsLayout(){

    mainButtonsLayout = new QHBoxLayout();

    containerWidgetForMainButtonsLayout = new QWidget();

    mainButtonGroup1 = new QVBoxLayout();
    mainButtonGroup2 = new QVBoxLayout();

    add_button = new QPushButton("add");
    mainButtonGroup1->addWidget(add_button);
    delete_button = new QPushButton("delete");
    mainButtonGroup1->addWidget(delete_button);
    update_button = new QPushButton("update");
    mainButtonGroup1->addWidget(update_button);
    mainButtonsLayout->addLayout(mainButtonGroup1);

    undo_button = new QPushButton("undo");
    mainButtonGroup2->addWidget(undo_button);
    search_button = new QPushButton("search");
    mainButtonGroup2->addWidget(search_button);
    wishlist_button = new QPushButton("wishlist");
    mainButtonGroup2->addWidget(wishlist_button);
    mainButtonsLayout->addLayout(mainButtonGroup2);

    containerWidgetForMainButtonsLayout->setLayout(mainButtonsLayout);
    containerWidgetForMainButtonsLayout->setStyleSheet("background-color: black;");
}

void GraphicaUserInterface::setSideButtonLayout() {

    sideButtonLayout = new QHBoxLayout();
    QVBoxLayout* c = new QVBoxLayout();
    QHBoxLayout* d = new QHBoxLayout();
    d->addWidget(new QPushButton("filter"));
    d->addWidget(new QLabel("by price"));
    d->addWidget(new QLineEdit());
    c->addLayout(d);
    QHBoxLayout* e = new QHBoxLayout();
    e->addWidget(new QPushButton("filter"));
    e->addWidget(new QLabel("by destination"));
    e->addWidget(new QLineEdit());
    c->addLayout(e);
    QHBoxLayout* f = new QHBoxLayout();
    f->addWidget(new QPushButton("sort"));
    f->addWidget(new QLabel("by price"));
    f->addWidget(new QLineEdit());
    c->addLayout(f);
    QHBoxLayout* g = new QHBoxLayout();
    g->addWidget(new QPushButton("sort"));
    g->addWidget(new QLabel("by destination"));
    g->addWidget(new QLineEdit());
    c->addLayout(g);
    sideButtonLayout->addLayout(c);
}

void GraphicaUserInterface::setupHomeWindowGraphics() {

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QGridLayout* mainLayout = new QGridLayout();
    setLiveStatusList();
    setContainerWidgetForLogoLayout();
    setLogPanel();
    setFormLayout();
    setContainerWidgetForMainButtonsLayout();
    setSideButtonLayout();

    mainLayout->addWidget(liveStatusList, 0, 0);
    mainLayout->addWidget(ContainerWidgetForLogoLayout, 0, 1);
    mainLayout->addWidget(logPanel, 0, 2);
    mainLayout->addLayout(formLayout, 1, 0);
    mainLayout->addWidget(containerWidgetForMainButtonsLayout, 1, 1);
    mainLayout->addLayout(sideButtonLayout, 1, 2);

    centralWidget->setLayout(mainLayout);
}

void GraphicaUserInterface::setHomeWindowTitle() {
    setWindowTitle("Tourism Agency");
}

void GraphicaUserInterface::updateLiveStatusList() {
    
    string packet;
    for (int i = 1; i <= 10; i++) {
        packet = "Packet " + std::to_string(i);
        liveStatusList->addItem(QString::fromStdString(packet));
    }
 
}

void GraphicaUserInterface::initConnect() {


}