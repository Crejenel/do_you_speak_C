#include <iostream>
#include <limits>
#include <string>
#include "service.h"
#include "user_interface.h"
#include "domain.h"
using std::cout;
using std::endl;
using std::cin;
using std::vector;

UI::UI(Service& service) : service(service){}

void UI::run() {

	cout << "\033[0;33m******>> THE APPLICATION IS RUNNING <<******\033[0m" << endl << endl;
	bool running = true;
	vector <bool> verify;
	string code;

	while (running) {

		display_the_menu();

		int action;
		cout << ">> ";
		cin >> action;

		verify.clear();
		verify.push_back(!cin.fail());

		cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (verify_type_of_input(verify) && action >= 0) {

			switch (action)
			{
				case 0:
				{

					running = false;
					cout << "\033[0;36m******>> THE APPLICATION WAS CLOSED <<******\033[0m" << endl;
					break;
				}
				case 1:
				{
					cout << ">> To introduce a travel package into the system, please enter its specifications <<" << endl;

					int id;
					string name;
					string destination;
					string type;
					double price;

					verify.clear();

					cout << "Enter ID: ";
					if (!(cin >> id)) {
						cout << "<< \033[1;31mERROR\033[0m: Wrong input type for ID >>" << endl;
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						break;
					}

					cin.ignore();
					cout << "Enter Name: ";
					getline(cin, name);
					verify.push_back(!name.empty());

					cout << "Enter Destination: ";
					getline(cin, destination);
					verify.push_back(!destination.empty());

					cout << "Enter Type: ";
					getline(cin, type);
					verify.push_back(!type.empty());

					if (!verify_type_of_input(verify)) {
						cout << "<< \033[1;31mERROR\033[0m: Name, destination and type is required >>" << endl;
						break;
					}

					cout << "Enter Price: ";
					if (!(cin >> price)) {
						cout << "<< \033[1;31mERROR\033[0m: Wrong input type for Price >>" << endl;
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						break;
					}

					code = service.add_package(id, name, destination, type, price);
					if ( (code[3] - '0') % 2 == 0) {
						cout << "!! \033[1;31mERROR\033[0m " << code << " !!" << endl;
					}
					else {
						cout << "\033[32mTravel Package added succesfully!\033[0m" << endl;
					}
					
					break;
				}
				case 2 :
				{	
					cout << ">> To update a travel package from the system, please use the following syntax <<" << endl;
					cout << "   ------>> an atribute of an travel package ( not id ) : new value; <<------- " << endl;
					string update;
					verify.clear();
					cout << ">> "; getline(cin, update);
					verify.push_back(!update.empty());
					if (!verify_type_of_input(verify)) {
						cout << "<< \033[1;31mERROR\033[0m: The update string is required >>" << endl;
						break;
					}
					
					int id;
					cout << "Enter the ID for the travel package that you would like to update : ";
					if (!(cin >> id)) {
						cout << "<< \033[1;31mERROR\033[0m: Wrong input type for ID >>" << endl;
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						break;
					}

					code = service.update_package(id, update);
					if ((code[3] - '0') % 2 == 0) {
						cout << "!! \033[1;31mERROR\033[0m " << code << " !!" << endl;
					}
					else {
						cout << "\033[32mTravel Package update succesfully!\033[0m" << endl;
					}

					break;
				}
				case 3:
				{	
					cout << ">> To delete a package code from the system, please type its ID <<" << endl;
					cout << ">> ";
					int id;
					if (!(cin >> id)) {
						cout << "<< \033[1;31mERROR\033[0m: Wrong input type for ID >>" << endl;
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						break;
					}

					code = service.delete_package(id);
					if((code[3] - '0') % 2 == 0) {
						cout << "!! \033[1;31mERROR\033[0m " << code << " !!" << endl;
					}
					else {
						cout << "\033[32mTravel Package deleted succesfully!\033[0m" << endl;
					}

					break;
				}
				case 4:
				{

					const vector <Travel_Package>& packages = service.get_all_packages();

					if (packages.size() == 0) {
						cout << ">>\033[32m There are no travel packages in the system right now\033[0m <<" << endl;
						break;
					}
					for (size_t i = 0; i < packages.size(); i++) {
						cout << packages[i] << endl;
					}
					break;
					
				}
				case 5 :
				{
					cout << ">> To filter the travel packages from the sistem, please use the following sintax <<" <<endl;
					cout << "   --->> an atribute of an travel package ( price / destination ) : value <<---- " << endl;
					cout << "<< \033[33mNOTE\033[0m : The price filter selects travel packages with a price less than or equal to the specified value >>" << endl;

					string filter;
					verify.clear();

					cout << ">> "; getline(cin, filter);
					verify.push_back(!filter.empty());
					if (!verify_type_of_input(verify)) {
						cout << "<< \033[1;31mERROR\033[0m: The filter string is required >>" << endl;
						break;
					}

					vector < Travel_Package > filter_packages;
					code = service.filter_packages(filter_packages, filter);
					if ((code[3] - '0') % 2 == 0) {
						cout << "!! \033[1;31mERROR\033[0m " << code << " !!" << endl;
					}
					else {

						if (filter_packages.size() == 0) {
							cout << ">>\033[32m There are no travel packages in the system with that specifications\033[0m <<" << endl;
							break;
						}
						for (size_t i = 0; i < filter_packages.size(); i++) {
							cout << filter_packages[i] << endl;
						}
					}

					break;
				}
				case 6 :
				{
					cout << ">> To sort the travel packages from the sistem, please use the following sintax <<" << endl;
					cout << "--->> an atribute of an travel package ( price / destination ) : order ( ascending / descending ) <<---- " << endl;
					string sort;
					verify.clear();

					cout << ">> "; getline(cin, sort);
					verify.push_back(!sort.empty());
					if (!verify_type_of_input(verify)) {
						cout << "<< \033[1;31mERROR\033[0m: The sort string is required >>" << endl;
						break;
					}

					vector < Travel_Package > sort_packages;
					code = service.sort_packages(sort_packages, sort);

					if ((code[3] - '0') % 2 == 0) {

						cout << "!! \033[1;31mERROR\033[0m " << code << " !!" << endl;
					}
					else {

						if (sort_packages.size() == 0) {
							cout << ">>\033[32m There are no travel packages in the system right now\033[0m <<" << endl;
							break;
						}
						for (size_t i = 0; i < sort_packages.size(); i++) {
							cout << sort_packages[i] << endl;
						}
					}

					break;
				}
				case 7:
				{
					cout << "ENTER ID :";
					int i;
					cin >> i; cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					Travel_Package& obj = service.search_service(i);
					if (obj.get_id() == 0) {
						cout << "Nu s-a gasit!" << endl;
					}
					else {
						cout << obj;
					}
					break;
				}
				default:
				{
					cout << "<< \033[1;31mERROR\033[0m: No such command in menu >>" << endl;
				}
			}

		}
		else {
			cout << "<< \033[1;31mERROR\033[0m: You need to refer to a command using natural numbers only! >>" << endl;
		}

	}

}

void UI::display_the_menu() const {

	cout << "\033[0;34m----------Please choose an action-----------\033[0m" << endl;
	cout << "0. Exit the application." << endl;
	cout << "1. Add a travel package to the system." << endl;
	cout << "2. Update a travel package in the system." << endl;
	cout << "3. Remove a travel package from the system." << endl;
	cout << "4. Display all travel packages in the system." << endl;
	cout << "5. Filter the travel packages by a criterion." << endl;
	cout << "6. Display all travel packages sorted by a criterion." << endl;
	cout << "7. Search." << endl;

}

bool UI::verify_type_of_input(vector <bool> &verify) const {

	for (size_t i = 0; i < verify.size(); i++) {
		if (verify[i] == false) {
			return false;
		}
	}
	return true;
}
