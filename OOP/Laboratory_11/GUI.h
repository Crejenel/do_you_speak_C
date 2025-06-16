#pragma once
#include "service.h"
#include <QShowEvent>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QListWidget>
#include <QPixmap>
#include <QMessageBox>
#include <QTableWidget>
#include <QPainter>
#include <QRandomGenerator>
#include <QListView>
#include <QTableView>
#include <domain_model.h>
#include <string>
#include <vector>
using std::string;
using std::vector;

class SecondWindow;

class GraphicaUserInterface : public QMainWindow {

private:
	
	SecondWindow* secondWindow;
	Service service;
	QWidget* centralWidget;
	QListWidget* liveStatusList;
	QVBoxLayout* logoLayout;
	QWidget* ContainerWidgetForLogoLayout;
	QListWidget* logPanel;
	QFormLayout* formLayout;
	QLineEdit* nameField;
	QLineEdit* typeField;
	QLineEdit* destinationField;
	QLineEdit* priceField;
	QLineEdit* idField;
	QHBoxLayout* mainButtonsLayout;
	QVBoxLayout* mainButtonGroup1;
	QPushButton* add_button;
	QPushButton* delete_button;
	QPushButton* update_button;
	QVBoxLayout* mainButtonGroup2;
	QPushButton* undo_button;
	QPushButton* search_button;
	QPushButton* wishlist_button;
	QWidget* containerWidgetForMainButtonsLayout;
	QHBoxLayout* sideButtonLayout;
	QVBoxLayout* buttonColumnLayout;
	QHBoxLayout* filterByPriceLayout;
	QHBoxLayout* filterByDestinationLayout;
	QHBoxLayout* sortByPriceLayout;
	QHBoxLayout* sortByDestinationLayout;
	QPushButton* filterByPriceButton;
	QPushButton* filterByDestinationButton;
	QPushButton* sortByPriceButton;
	QPushButton* sortByDestinationButton;
	QLineEdit* sortByPriceLineEdit;
	QLineEdit* sortByDestinationLineEdit;
	QLineEdit* filterByPriceLineEdit;
	QLineEdit* filterByDestinationLineEdit;
	QVBoxLayout* dinamicButtonsLayout;
	QTableWidget* complete_display;
	QVBoxLayout* wishlistButtons = new QVBoxLayout;
	QVBoxLayout* wishlistPages = new QVBoxLayout;
	QLineEdit* addWishLine = new QLineEdit;
	QLineEdit* generateWishLine = new QLineEdit;
	QPushButton* addMainWishlist = new QPushButton("add to wishlist");
	QPushButton* deleteMainWishlist = new QPushButton("delete your wislist");
	QPushButton* generateMainWishlist = new QPushButton("generate a wishlist");
	QPushButton* newWishlistPage1Button = new QPushButton("CosCRUDGUI");
	QPushButton* newWishlistPage2Button = new QPushButton("CosReadOnlyGUI");
	QTableView* VT = new QTableView;

public:

	GraphicaUserInterface( Service& service, QWidget* parent = nullptr);

private:

	void updateViewTable();

	void setupHomeWindowGraphics();

	void setLiveStatusList();

	void setContainerWidgetForLogoLayout();

	void setLogPanel();

	void setFormLayout();

	void setContainerWidgetForMainButtonsLayout();

	void setSideButtonLayout();

	void setHomeWindowTitle();

	void updateLiveStatusList();

	void initConnect();

	void addNewPackage();

	void deleteAPackage();

	void updateAPackage();

	void searchAPackage();

	void doUndo();

	void sortPackagesByPrice();

	void sortPackagesByDestination();

	void filterPackagesByDestination();

	void filterPackagesByPrice();

	void openSecondWindow();

	void createDynamicButtons();

	void updateCompleteDisplay();

	void addWishlistMain();

	void deleteWishlistMain();

	void generateWishlistMain();

	void openThirdWindow();

	void openForthWindow();

};

class SecondWindow : public QWidget {

	Service& service;
	QListWidget* listWidget1;
	QListWidget* listWidget2;
	QFormLayout* formFieldsLayout;
	QLineEdit* id_LineEdit;
	QLineEdit* file_name_LineEdit;
	QVBoxLayout* buttonsSectionLayout;
	QPushButton* add_button;
	QPushButton* delete_button;
	QPushButton* generate_button;
	QPushButton* statistic_button;
	QPushButton* export_button;
	QLineEdit* generateLineEdit;

public :

	SecondWindow(Service& service, QWidget* parent = nullptr);

private :

	void init_Connect();
	void updatelistWidget1();
	void addToWIshList();
	void deleteFromWishlist();
	void generateAWishlist();
	void displayStatisticForWishlist();
	void exportTheWishlist();
	void showEvent(QShowEvent* event) override;
};

class ThirdWindow : public QWidget, public Observer {

private:

	Service& service;
	QVBoxLayout* mainLayout;
	QTableWidget* tableWidget;
	QPushButton* clearButton;
	QPushButton* generateButton;
	QLineEdit* generateLine;

public:

	ThirdWindow(Service& service, QWidget* parent = nullptr) : service(service), QWidget(parent) {

		mainLayout = new QVBoxLayout(this);
		tableWidget = new QTableWidget(this);
		clearButton = new QPushButton("<< delete wishlist >>", this);
		generateButton = new QPushButton("<< generate wishlist >>", this);
		generateLine = new QLineEdit;

		tableWidget->setColumnCount(5);
		QStringList headers;
		headers << "ID" << "NAME" << "DESTINATION" << "TYPE" << "PRICE";
		tableWidget->setHorizontalHeaderLabels(headers);

		mainLayout->addWidget(tableWidget);
		mainLayout->addWidget(clearButton);
		mainLayout->addWidget(generateButton);
		mainLayout->addWidget(generateLine);

		setLayout(mainLayout);
		connect();
		updateTabel();

		service.get_wishlist().addObserver(this);
	}

	~ThirdWindow() {
		
		service.get_wishlist().removeObserver(this);
	}

	void update() override {
		updateTabel();  
	}

	void connect() {
		QObject::connect(clearButton, &QPushButton::clicked, this, &ThirdWindow::remove);
		QObject::connect(generateButton, &QPushButton::clicked, this, &ThirdWindow::generate);
	}

	void remove() {
		const auto* packages = service.get_wishlist_service();
		int n = packages->size();
		for (int i = 0; i < n; i++) {
			service.delete_from_wishlist_service((*packages)[0]->get_id());
		}
	}

	void generate() {
		bool ok;
		int nr = generateLine->text().toInt(&ok);
		if (!ok) {
			QMessageBox::warning(this, "Input error", "Please enter a valid number.");
			return;
		}

		try {
			service.generate_wishlist_service(nr);
		}
		catch (const std::exception& e) {
			QMessageBox::warning(this, "Error", e.what());
		}

	}

	void updateTabel() {
		tableWidget->clearContents();
		tableWidget->setRowCount(service.get_wishlist_service()->size());

		const auto* packages = service.get_wishlist_service();
		for (int i = 0; i < packages->size(); i++) {
			tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number((*packages)[i]->get_id())));
			tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString((*packages)[i]->get_name())));
			tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString((*packages)[i]->get_destination())));
			tableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString((*packages)[i]->get_type())));
			tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number((*packages)[i]->get_price())));
		}
	}

	void showEvent(QShowEvent* event) override {
		QWidget::showEvent(event);
		updateTabel();
	}
};

class ForthWindow : public QWidget, public Observer {

private:
	Service& service;

public:

	ForthWindow(Service& service, QWidget* parent = nullptr): QWidget(parent), service(service){
		setMinimumSize(400, 300);
		service.get_wishlist().addObserver(this);
		update();
	}

	~ForthWindow() override {
		service.get_wishlist().removeObserver(this);
	}

	void paintEvent(QPaintEvent* ev) override {
		Q_UNUSED(ev);

		QPainter p(this);
		p.setRenderHint(QPainter::Antialiasing);

		int w = width();
		int h = height();

		if (w <= 0 || h <= 0)  
			return;

		int n = service.get_wishlist_service()->size();

		for (int i = 0; i < n; ++i) {
			int radius = 20;
			int x = QRandomGenerator::global()->bounded(width() - 2 * radius);
			int y = QRandomGenerator::global()->bounded(height() - 2 * radius);

			QColor color = QColor::fromHsv(QRandomGenerator::global()->bounded(360), 255, 200);
			p.setBrush(color);
			p.setPen(Qt::NoPen);

			p.drawEllipse(x, y, 2 * radius, 2 * radius);
		}
	}

	void update() override {
		QWidget::update();
	}

	void showEvent(QShowEvent* event) override {
		QWidget::showEvent(event);
		update();
	}
};

