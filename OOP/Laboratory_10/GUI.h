#pragma once
#include "service.h"
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
#include <string>
using std::string;

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

public:

	GraphicaUserInterface( Service& service, QWidget* parent = nullptr);

private:

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

};