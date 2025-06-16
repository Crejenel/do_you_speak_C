#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QListWidget>
#include <QPixmap>
#include <string>
using std::string;

class GraphicaUserInterface : public QMainWindow {

private :

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


public :
	
	GraphicaUserInterface(QWidget* parent = nullptr);

private :

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

};
