#include "GUI.h"

// HOME WINDOW
GraphicaUserInterface::GraphicaUserInterface( Service& service, QWidget* parent) : service(service), QMainWindow(parent) {
    setupHomeWindowGraphics();
    setHomeWindowTitle();
    updateLiveStatusList();
    initConnect();
    createDynamicButtons();
    updateCompleteDisplay();
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

void GraphicaUserInterface::setContainerWidgetForMainButtonsLayout() {

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
    buttonColumnLayout = new QVBoxLayout();

    filterByPriceLayout = new QHBoxLayout();
    filterByDestinationLayout = new QHBoxLayout();
    sortByPriceLayout = new QHBoxLayout();
    sortByDestinationLayout = new QHBoxLayout();

    filterByPriceButton = new QPushButton("Filter by price");
    filterByDestinationButton = new QPushButton("Filter by destination");
    sortByPriceButton = new QPushButton("Sort by price");
    sortByDestinationButton = new QPushButton("Sort by destination");

    sortByPriceLineEdit = new QLineEdit();
    sortByDestinationLineEdit = new QLineEdit();

    filterByPriceLineEdit = new QLineEdit();
    filterByDestinationLineEdit = new QLineEdit();

    filterByPriceLayout->addWidget(filterByPriceButton);
    filterByPriceLayout->addWidget(filterByPriceLineEdit);
    buttonColumnLayout->addLayout(filterByPriceLayout);

    filterByDestinationLayout->addWidget(filterByDestinationButton);
    filterByDestinationLayout->addWidget(filterByDestinationLineEdit);
    buttonColumnLayout->addLayout(filterByDestinationLayout);
    
    sortByPriceLayout->addWidget(sortByPriceButton);
    sortByPriceLayout->addWidget(sortByPriceLineEdit);
    buttonColumnLayout->addLayout(sortByPriceLayout);

    sortByDestinationLayout->addWidget(sortByDestinationButton);
    sortByDestinationLayout->addWidget(sortByDestinationLineEdit);
    buttonColumnLayout->addLayout(sortByDestinationLayout);

    sideButtonLayout->addLayout(buttonColumnLayout);
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

    wishlistButtons->addWidget(addWishLine);
    wishlistButtons->addWidget(addMainWishlist);
    wishlistButtons->addWidget(deleteMainWishlist);
    wishlistButtons->addWidget(generateWishLine);
    wishlistButtons->addWidget(generateMainWishlist);

    wishlistPages->addWidget(newWishlistPage1Button);
    wishlistPages->addWidget(newWishlistPage2Button);

    mainLayout->addLayout(wishlistButtons, 0, 0);
    mainLayout->addLayout(wishlistPages, 1, 0);
    mainLayout->addWidget(liveStatusList, 0, 1);
    mainLayout->addWidget(ContainerWidgetForLogoLayout, 0, 2);
    mainLayout->addWidget(logPanel, 0, 3);
    mainLayout->addLayout(formLayout, 1, 1);
    mainLayout->addWidget(containerWidgetForMainButtonsLayout, 1, 2);
    mainLayout->addLayout(sideButtonLayout, 1, 3);

    dinamicButtonsLayout = new QVBoxLayout;
    dinamicButtonsLayout->addWidget(new QPushButton("Hello"));
    mainLayout->addLayout(dinamicButtonsLayout,0,4);

    complete_display = new QTableWidget();
    complete_display->setColumnCount(5);
    QStringList headers;
    headers << "ID" << "NAME" << "DESTINATION" << "TYPE" << "PRICE";
    complete_display->setHorizontalHeaderLabels(headers);

    mainLayout->addWidget(complete_display,1,4);

    updateViewTable();
    mainLayout->addWidget(VT, 1, 5);
    centralWidget->setLayout(mainLayout);
    secondWindow = nullptr;
}

void GraphicaUserInterface::updateViewTable() {

    auto* model = new TravelPackageModel(this);
    const Inventory<Travel_Package>* travel_packages = service.get_all_packages();
    QVector<Travel_Package> lista;
    for (int i = 0; i < travel_packages->size(); i++) {
        lista.push_back((*(*travel_packages)[i]));
    }
    model->setPachete(lista);
    VT->setModel(model);
}

void GraphicaUserInterface::setHomeWindowTitle() {
    setWindowTitle("Tourism Agency");
}

void GraphicaUserInterface::updateLiveStatusList() {

    liveStatusList->clear();
    const Inventory<Travel_Package>* packages = service.get_all_packages();
    for (int i = 0; i < packages->size(); i++) {
        liveStatusList->addItem(QString::number((*packages)[i]->get_id()));
    }
}

void GraphicaUserInterface::initConnect() {

    QObject::connect(add_button, &QPushButton::clicked, this, &GraphicaUserInterface::addNewPackage);

    QObject::connect(delete_button, &QPushButton::clicked, this, &GraphicaUserInterface::deleteAPackage);

    QObject::connect(update_button, &QPushButton::clicked, this, &GraphicaUserInterface::updateAPackage);

    QObject::connect(search_button, &QPushButton::clicked, this, &GraphicaUserInterface::searchAPackage);

    QObject::connect(undo_button, &QPushButton::clicked, this, &GraphicaUserInterface::doUndo);

    QObject::connect(sortByPriceButton, &QPushButton::clicked, this, &GraphicaUserInterface::sortPackagesByPrice);

    QObject::connect(sortByDestinationButton, & QPushButton::clicked, this, & GraphicaUserInterface::sortPackagesByDestination);

    QObject::connect(filterByDestinationButton, &QPushButton::clicked, this, &GraphicaUserInterface::filterPackagesByDestination);

    QObject::connect(filterByPriceButton, &QPushButton::clicked, this, &GraphicaUserInterface::filterPackagesByPrice);

    QObject::connect(wishlist_button, &QPushButton::clicked, this, &GraphicaUserInterface::openSecondWindow);

    QObject::connect(addMainWishlist, &QPushButton::clicked, this, &GraphicaUserInterface::addWishlistMain);

    QObject::connect(deleteMainWishlist, &QPushButton::clicked, this, &GraphicaUserInterface::deleteWishlistMain);

    QObject::connect(generateMainWishlist, &QPushButton::clicked, this, &GraphicaUserInterface::generateWishlistMain);

    QObject::connect(newWishlistPage1Button, &QPushButton::clicked, this, &GraphicaUserInterface::openThirdWindow);

    QObject::connect(newWishlistPage2Button, &QPushButton::clicked, this, &GraphicaUserInterface::openForthWindow);

}

void GraphicaUserInterface::openThirdWindow() {

    ThirdWindow* w = new ThirdWindow(service);
    w->setAttribute(Qt::WA_DeleteOnClose);  
    w->show(); 
}

void GraphicaUserInterface::openForthWindow() {

    ForthWindow* w = new ForthWindow(service);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
   
}

void GraphicaUserInterface::addWishlistMain() {

    bool rightType;
    auto id = addWishLine->text().toInt(&rightType);
    if (rightType == false) {
        QMessageBox::warning(this, "ID ERROR", "The ID is a number");
        return;
    }

    try {
        service.add_to_wishlist_service(id);
    }
    catch (exception& e) {

        QMessageBox::warning(this, "ADD ERROR", e.what());
    }

}

void GraphicaUserInterface::deleteWishlistMain() {

    const Inventory<Travel_Package>* packages = service.get_wishlist_service();
    vector<int> ids;
    for (int i = 0; i < packages->size(); i++) {
        ids.push_back((*packages)[i]->get_id());
    }
    for (size_t i = 0; i < ids.size(); i++) {
        service.delete_from_wishlist_service(ids[i]);
    }

}

void GraphicaUserInterface::generateWishlistMain() {

    bool rightType;
    auto id = generateWishLine->text().toInt(&rightType);
    if (rightType == false) {
        QMessageBox::warning(this, "ID ERROR", "The ID is a number");
        return;
    }

    try {
        service.generate_wishlist_service(id);
    }
    catch (exception& e) {

        QMessageBox::warning(this, "ERROR ", e.what());
    }
}

void GraphicaUserInterface::addNewPackage() {

    bool rightType;
    auto id = idField->text().toInt(&rightType);
    if (rightType == false) {
        QMessageBox::warning(this, "ID ERROR","The ID is a number");
        return;
    }
    auto name = nameField->text().toStdString();
    auto destination = destinationField->text().toStdString();
    auto type = typeField->text().toStdString();
    auto price = priceField->text().toInt(&rightType);
    if (rightType == false) {
        QMessageBox::warning(this, "PRICE ERROR", "The price is a number");
        return;
    }

    logPanel->clear();
    try {
        service.add_package(id, name, destination, type, price);
    }
    catch (exception& e) {

        if (logPanel != nullptr) {
            logPanel->addItem(QString::fromStdString(e.what()));
        }
        else {
            qDebug() << "logPanel is null!";
        }
        return;
    }
    updateLiveStatusList();
    updateViewTable();
    logPanel->addItem("Package added succesfuly!");
    createDynamicButtons();
    updateCompleteDisplay();
}

void GraphicaUserInterface::deleteAPackage() {

    bool rightType;
    auto id = idField->text().toInt(&rightType);
    if (rightType == false) {
        QMessageBox::warning(this, "ID ERROR", "The ID is a number");
        return;
    }

    logPanel->clear();
    try {
        service.delete_package(id);
    }
    catch (exception& e) {

        if (logPanel != nullptr) {
            logPanel->addItem(QString::fromStdString(e.what()));
        }
        else {
            qDebug() << "logPanel is null!";
        }
        return;
    }
    updateLiveStatusList();
    updateViewTable();
    logPanel->addItem("Package was removed succesfuly!");
    createDynamicButtons();
    updateCompleteDisplay();

}

void GraphicaUserInterface::updateAPackage() {

    bool rightType;
    auto id = idField->text().toInt(&rightType);
    if (rightType == false) {
        QMessageBox::warning(this, "ID ERROR", "The ID is a number");
        return;
    }
    auto name = nameField->text().toStdString();
    auto destination = destinationField->text().toStdString();
    auto type = typeField->text().toStdString();
    auto price = priceField->text().toStdString();

    string update_string = "";

    if (name != "") {
        update_string = update_string+ "name : " + name + ";";
    }
    if (destination != "") {
        update_string = update_string+ "destination :" + destination + ";";
    }
    if (type != "") {
        update_string = update_string+"type : " + type + ";";
    }
    if (price != "") {
        update_string = update_string+"price : " + price + ";";
    }

    logPanel->clear();
    try {
        service.update_package(id, update_string);
    }
    catch (exception& e) {

        if (logPanel != nullptr) {
            logPanel->addItem(QString::fromStdString(e.what()));
        }
        else {
            qDebug() << "logPanel is null!";
        }
        return;
    }
    updateLiveStatusList();
    updateViewTable();
    logPanel->addItem("Package update succesfuly!");
    createDynamicButtons();
    updateCompleteDisplay();

}

void GraphicaUserInterface::searchAPackage() {

    bool rightType;
    auto id = idField->text().toInt(&rightType);
    if (rightType == false) {
        QMessageBox::warning(this, "ID ERROR", "The ID is a number");
        return;
    }

    logPanel->clear();
    Travel_Package* travel_package = service.search_service(id);
    if (travel_package == nullptr) {
        logPanel->addItem("No package with " + QString::number(id)+" ID");
    }
    else {
        string TP = "ID : " + std::to_string(travel_package->get_id()) +
            "\nNAME : " + travel_package->get_name() +
            "\nDESTINATION : " + travel_package->get_destination() +
            "\nTYPE : " + travel_package->get_type() +
            "\nPRICE : " + std::to_string(travel_package->get_price());
        logPanel->addItem(QString::fromStdString(TP));
    }
  
}

void GraphicaUserInterface::doUndo() {

    logPanel->clear();
    try {
        service.undo();
    }
    catch (exception& e) {
        if (logPanel != nullptr) {
            logPanel->addItem(QString::fromStdString(e.what()));
        }
        else {
            qDebug() << "logPanel is null!";
        }
        return;
    }
    updateLiveStatusList();
    logPanel->addItem("Undo operation executed successfully");
    createDynamicButtons();
    updateCompleteDisplay();
}

void GraphicaUserInterface::sortPackagesByPrice() {

    logPanel->clear();
    Inventory<Travel_Package>* sort_packages = new Inventory<Travel_Package>;
    string sort_string = "price : "+sortByPriceLineEdit->text().toStdString();
    try {
        service.sort_packages(sort_packages,sort_string);
    }
    catch (exception& e) {
        if (logPanel != nullptr) {
            logPanel->addItem(QString::fromStdString(e.what()));
        }
        else {
            qDebug() << "logPanel is null!";
        }
        delete(sort_packages);
        return;
    }
    for (int i = 0; i < sort_packages->size(); i++) {
        string TP = "ID : " + std::to_string((*sort_packages)[i]->get_id()) +
            "| NAME : " + (*sort_packages)[i]->get_name() +
            "| DESTINATION : " + (*sort_packages)[i]->get_destination() +
            "| TYPE : " + (*sort_packages)[i]->get_type() +
            "| PRICE : " + std::to_string((*sort_packages)[i]->get_price());
        logPanel->addItem(QString::fromStdString(TP));
    }
    delete(sort_packages);
}

void GraphicaUserInterface::sortPackagesByDestination() {

    logPanel->clear();

    Inventory<Travel_Package>* sort_packages = new Inventory<Travel_Package>;
    string sort_string = "destination : " + sortByDestinationLineEdit->text().toStdString();

    try {
        service.sort_packages(sort_packages, sort_string);
    }
    catch (exception& e) {
        if (logPanel != nullptr) {
            logPanel->addItem(QString::fromStdString(e.what()));
        }
        else {
            qDebug() << "logPanel is null!";
        }
        delete sort_packages;
        return;
    }

    for (int i = 0; i < sort_packages->size(); i++) {
        string TP = "ID : " + std::to_string((*sort_packages)[i]->get_id()) +
            " | NAME : " + (*sort_packages)[i]->get_name() +
            " | DESTINATION : " + (*sort_packages)[i]->get_destination() +
            " | TYPE : " + (*sort_packages)[i]->get_type() +
            " | PRICE : " + std::to_string((*sort_packages)[i]->get_price());

        logPanel->addItem(QString::fromStdString(TP));
    }
    delete(sort_packages);
}

void GraphicaUserInterface::filterPackagesByDestination() {

    logPanel->clear();

    Inventory<Travel_Package>* filteredPackages = new Inventory<Travel_Package>;
    std::string filter_string = "destination : " + filterByDestinationLineEdit->text().toStdString();

    try {
        service.filter_packages(filteredPackages, filter_string);
    }
    catch (const std::exception& e) {
        if (logPanel != nullptr) {
            logPanel->addItem(QString::fromStdString(e.what()));
        }
        else {
            qDebug() << "logPanel is null!";
        }
        delete filteredPackages;
        return;
    }

    for (int i = 0; i < filteredPackages->size(); ++i) {
        std::string TP = "ID : " + std::to_string((*filteredPackages)[i]->get_id()) +
            " | NAME : " + (*filteredPackages)[i]->get_name() +
            " | DESTINATION : " + (*filteredPackages)[i]->get_destination() +
            " | TYPE : " + (*filteredPackages)[i]->get_type() +
            " | PRICE : " + std::to_string((*filteredPackages)[i]->get_price());

        logPanel->addItem(QString::fromStdString(TP));
    }

    delete filteredPackages;
}

void GraphicaUserInterface::filterPackagesByPrice() {

    logPanel->clear();

    Inventory<Travel_Package>* filteredPackages = new Inventory<Travel_Package>;
    std::string filter_string = "price : " + filterByPriceLineEdit->text().toStdString();

    try {
        service.filter_packages(filteredPackages, filter_string);
    }
    catch (const std::exception& e) {
        if (logPanel != nullptr) {
            logPanel->addItem(QString::fromStdString(e.what()));
        }
        else {
            qDebug() << "logPanel is null!";
        }
        delete filteredPackages;
        return;
    }

    for (int i = 0; i < filteredPackages->size(); ++i) {
        std::string TP = "ID : " + std::to_string((*filteredPackages)[i]->get_id()) +
            " | NAME : " + (*filteredPackages)[i]->get_name() +
            " | DESTINATION : " + (*filteredPackages)[i]->get_destination() +
            " | TYPE : " + (*filteredPackages)[i]->get_type() +
            " | PRICE : " + std::to_string((*filteredPackages)[i]->get_price());

        logPanel->addItem(QString::fromStdString(TP));
    }

    delete filteredPackages;
}

void GraphicaUserInterface::openSecondWindow() {

    if (!secondWindow) {
        secondWindow = new SecondWindow(service);
    }
    secondWindow->show();
}

void GraphicaUserInterface::createDynamicButtons() {
   
    QLayoutItem* item;
    while ((item = dinamicButtonsLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    QMap<QString, QPushButton*> buttonsMap;
    const Inventory<Travel_Package>* packages = service.get_all_packages();

    for (int i = 0; i < packages->size(); i++) {
        QString button_name = QString::fromStdString((*packages)[i]->get_type());

        if (!buttonsMap.contains(button_name)) {
            QPushButton* button = new QPushButton(button_name, this);
            dinamicButtonsLayout->addWidget(button);
            buttonsMap[button_name] = button;

            QObject::connect(button, &QPushButton::clicked, this, [this, button_name, packages]() {
                int count = 0;
                for (int j = 0; j < packages->size(); j++) {
                    if (QString::fromStdString((*packages)[j]->get_type()) == button_name) {
                        count++;
                    }
                }

                QMessageBox::information(this, "Număr Pachete",
                    QString("Există %1 pachete de tip %2").arg(count).arg(button_name)
                );
                });
        }
    }
}

void GraphicaUserInterface::updateCompleteDisplay() {

    complete_display->clearContents();
    complete_display->setRowCount(service.get_all_packages()->size());

    const Inventory<Travel_Package>* packages = service.get_all_packages();
    for (int i = 0; i < packages->size(); i++) {

        complete_display->setItem(i, 0, new QTableWidgetItem(QString::number((*packages)[i]->get_id())));
        complete_display->setItem(i, 1, new QTableWidgetItem(QString::fromStdString((*packages)[i]->get_name())));
        complete_display->setItem(i, 2, new QTableWidgetItem(QString::fromStdString((*packages)[i]->get_destination())));
        complete_display->setItem(i, 3, new QTableWidgetItem(QString::fromStdString((*packages)[i]->get_type()))); 
        complete_display->setItem(i, 4, new QTableWidgetItem(QString::number((*packages)[i]->get_price())));
    }
}


// SECOND WINDOW
SecondWindow::SecondWindow(Service& service, QWidget* parent) : service(service), QWidget(parent) {
        
        listWidget1 = new QListWidget();
        listWidget2 = new QListWidget();

        id_LineEdit = new QLineEdit();
        file_name_LineEdit = new QLineEdit();

        add_button = new QPushButton("Add");
        delete_button = new QPushButton("Delete");
        generate_button = new QPushButton("Generate");
        statistic_button = new QPushButton("Statistic");
        export_button = new QPushButton("Export");
        generateLineEdit = new QLineEdit();

        formFieldsLayout = new QFormLayout();
        formFieldsLayout->addRow("ID : ", id_LineEdit);
        formFieldsLayout->addRow("FILE : ", file_name_LineEdit);

        buttonsSectionLayout = new QVBoxLayout();
        buttonsSectionLayout->addWidget(add_button);
        buttonsSectionLayout->addWidget(delete_button);
        buttonsSectionLayout->addWidget(generate_button);
        buttonsSectionLayout->addWidget(generateLineEdit); 
        buttonsSectionLayout->addWidget(statistic_button);
        buttonsSectionLayout->addWidget(export_button);
        buttonsSectionLayout->addStretch();

        QVBoxLayout* middleLayout = new QVBoxLayout();
        middleLayout->addLayout(formFieldsLayout);
        middleLayout->addLayout(buttonsSectionLayout);

        QHBoxLayout* mainLayout = new QHBoxLayout();
        mainLayout->addWidget(listWidget1);    
        mainLayout->addLayout(middleLayout);    
        mainLayout->addWidget(listWidget2);     

        setLayout(mainLayout);

        init_Connect();
        setWindowTitle("Wishlist");
        updatelistWidget1();
}

void SecondWindow::init_Connect() {

    QObject::connect(add_button, &QPushButton::clicked, this, &SecondWindow::addToWIshList);

    QObject::connect(delete_button, &QPushButton::clicked, this, &SecondWindow::deleteFromWishlist);

    QObject::connect(generate_button, &QPushButton::clicked, this, &SecondWindow::generateAWishlist);

    QObject::connect(statistic_button, &QPushButton::clicked, this, &SecondWindow::displayStatisticForWishlist);

    QObject::connect(export_button, &QPushButton::clicked, this, &SecondWindow::exportTheWishlist);

}

void SecondWindow::updatelistWidget1() {

    listWidget1->clear();
    const Inventory<Travel_Package>* packages = service.get_wishlist_service();
    for (int i = 0; i < packages->size(); i++) {
        listWidget1->addItem(QString::number((*packages)[i]->get_id()));
    }

}

void SecondWindow::addToWIshList() {

    bool rightType;
    auto id = id_LineEdit->text().toInt(&rightType);
    if (rightType == false) {
        QMessageBox::warning(this, "ID ERROR", "The ID is a number");
        return;
    }
    
    listWidget2->clear();
    try {
        service.add_to_wishlist_service(id);
    }
    catch (exception& e) {

        if (listWidget2 != nullptr) {
            listWidget2->addItem(QString::fromStdString(e.what()));
        }
        else {
            qDebug() << "logPanel is null!";
        }
        return;
    }
    updatelistWidget1();
    listWidget2->addItem("Package added succesfuly!");
}

void SecondWindow::deleteFromWishlist() {

    bool rightType;
    auto id = id_LineEdit->text().toInt(&rightType);
    if (rightType == false) {
        QMessageBox::warning(this, "ID ERROR", "The ID is a number");
        return;
    }

    listWidget2->clear();
    try {
        service.delete_from_wishlist_service(id);
    }
    catch (exception& e) {

        if (listWidget2 != nullptr) {
            listWidget2->addItem(QString::fromStdString(e.what()));
        }
        else {
            qDebug() << "logPanel is null!";
        }
        return;
    }
    updatelistWidget1();
    listWidget2->addItem("Package deleted succesfuly!");
}

void SecondWindow::generateAWishlist() {

    bool rightType;
    auto id = generateLineEdit->text().toInt(&rightType);
    if (rightType == false) {
        QMessageBox::warning(this, "ID ERROR", "The ID is a number");
        return;
    }

    listWidget2->clear();
    try {
        service.generate_wishlist_service(id);
    }
    catch (exception& e) {

        if (listWidget2 != nullptr) {
            listWidget2->addItem(QString::fromStdString(e.what()));
        }
        else {
            qDebug() << "logPanel is null!";
        }
        return;
    }
    updatelistWidget1();

}

void SecondWindow::displayStatisticForWishlist() {
  
    const multimap<string, Travel_Package*>* map_statistic = service.get_wishlist_statistics_service();
    listWidget2->clear();

    if (map_statistic != nullptr) {
        
        std::map<string, int> typeCount;

        for (auto it = map_statistic->begin(); it != map_statistic->end(); ++it) {
            typeCount[it->first]++;
        }

        for (auto& entry : typeCount) {
            QString displayText = QString("Obiecte de tipul: %1 - %2").arg(QString::fromStdString(entry.first)).arg(entry.second);
            listWidget2->addItem(displayText);
        }
    }
}

void SecondWindow::exportTheWishlist() {

    listWidget2->clear();
    string file_name = file_name_LineEdit->text().toStdString();
    if (file_name != "") {
        service.export_wishlist_service(file_name);
    }
    else {
        listWidget2->addItem("File name is required!");
    }
}

void SecondWindow::showEvent(QShowEvent* event) {

    QWidget::showEvent(event);
    updatelistWidget1();      
}


