#include <limits>
#include <string>
#include "service.h"
#include "interface.h"
#include "domain.h"
using std::cout;
using std::endl;
using std::cin;

UI::UI(Service& service) : service(service) {}

void UI::run() {

	cout << "\033[0;33m******>> THE APPLICATION IS RUNNING <<******\033[0m" << endl << endl;
	bool running = true;
	Inventory<bool>* verify = new Inventory<bool>;
	string code;

	while (running) {

		display_the_menu();

		int action;
		cout << ">> ";
		cin >> action;

		verify->clear();
		bool* val = new bool[1];
		*val = !cin.fail();
		verify->add(val);

		cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (verify_type_of_input(verify) && action >= 0) {

			switch (action)
			{
			case 0:
			{

				running = false;
				delete verify;
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

				verify->clear();

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
				val = new bool[1];
				*val = !cin.fail();
				verify->add(val);

				cout << "Enter Destination: ";
				getline(cin, destination);
				val = new bool[1];
				*val = !destination.empty();
				verify->add(val);

				cout << "Enter Type: ";
				getline(cin, type);
				val = new bool[1];
				*val = !type.empty();
				verify->add(val);

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

				try {
					service.add_package(id, name, destination, type, price);
					cout << "\033[32mTravel Package added succesfully!\033[0m" << endl;
				}
				catch (const ExceptionService& e) {
					e.print_exception();
				}
				catch (const ExceptionRepository& e) {
					e.print_exception();
				}
				catch (const ExceptionContainer& e) {
					e.print_exception();
				}
				
				break;
			}
			case 2:
			{
				cout << ">> To update a travel package from the system, please use the following syntax <<" << endl;
				cout << "   ------>> an atribute of an travel package ( not id ) : new value; <<------- " << endl;
				string update;
				verify->clear();
				cout << ">> "; getline(cin, update);
				val = new bool[1];
				*val = !cin.fail();
				verify->add(val);

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

				try {
					service.update_package(id, update);
					cout << "\033[32mTravel Package update succesfully!\033[0m" << endl;
				}
				catch (const ExceptionService& e) {
					e.print_exception();
				}
				catch (const ExceptionRepository& e) {
					e.print_exception();
				}
				catch (const ExceptionContainer& e) {
					e.print_exception();
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

				try {
					service.delete_package(id);
					cout << "\033[32mTravel Package deleted succesfully!\033[0m" << endl;
				}
				catch (const ExceptionService& e) {
					e.print_exception();
				}
				catch (const ExceptionRepository& e) {
					e.print_exception();
				}
				catch (const ExceptionContainer& e) {
					e.print_exception();
				}
				break;
			}
			case 4:
			{

				const Inventory<Travel_Package>* packages = service.get_all_packages();

				if (packages->size() == 0) {
					cout << ">>\033[32m There are no travel packages in the system right now\033[0m <<" << endl;
					break;
				}
				for (int i = 0; i < packages->size(); i++) {
					cout << *((*packages)[i]) << endl;
				}

				break;
			}
			case 5:
			{
				cout << ">> To filter the travel packages from the sistem, please use the following sintax <<" << endl;
				cout << "   --->> an atribute of an travel package ( price / destination ) : value <<---- " << endl;
				cout << "<< \033[33mNOTE\033[0m : The price filter selects travel packages with a price less than or equal to the specified value >>" << endl;

				string filter;
				verify->clear();

				cout << ">> "; getline(cin, filter);
				val = new bool[1];
				*val = !filter.empty();
				verify->add(val);

				if (!verify_type_of_input(verify)) {
					cout << "<< \033[1;31mERROR\033[0m: The filter string is required >>" << endl;
					break;
				}

				Inventory<Travel_Package>* filter_packages = new Inventory<Travel_Package>;

				try {

					service.filter_packages(filter_packages, filter);

					if (filter_packages->size() == 0) {
						cout << ">>\033[32m There are no travel packages in the system with that specifications\033[0m <<" << endl;
					}
					else {
						for (int i = 0; i < filter_packages->size(); i++) {
							cout << *((*filter_packages)[i]) << endl;
						}
					}
					
				}
				catch (const ExceptionService& e) {
					e.print_exception();
				}
				catch (const ExceptionRepository& e) {
					e.print_exception();
				}
				catch (const ExceptionContainer& e) {
					e.print_exception();
				}

				delete filter_packages;
				break;
			}
			case 6:
			{
				cout << ">> To sort the travel packages from the sistem, please use the following sintax <<" << endl;
				cout << "--->> an atribute of an travel package ( price / destination ) : order ( ascending / descending ) <<---- " << endl;
				string sort;
				verify->clear();

				cout << ">> "; getline(cin, sort);
				val = new bool[1];
				*val = !sort.empty();
				verify->add(val);
				
				if (!verify_type_of_input(verify)) {
					cout << "<< \033[1;31mERROR\033[0m: The sort string is required >>" << endl;
					break;
				}

				Inventory<Travel_Package>* sort_packages = new Inventory<Travel_Package>;

				try {

					service.sort_packages(sort_packages, sort);

					if (sort_packages->size() == 0) {
						cout << ">>\033[32m There are no travel packages in the system right now\033[0m <<" << endl;
						break;
					}
					else {
						for (int i = 0; i < sort_packages->size(); i++) {
							cout << *((*sort_packages)[i]) << endl;
						}
					}
				}
				catch (const ExceptionService& e) {
					e.print_exception();
				}
				catch (const ExceptionRepository& e) {
					e.print_exception();
				}
				catch (const ExceptionContainer& e) {
					e.print_exception();
				}
				
				delete sort_packages;
				break;
			}
			case 7:
			{
				cout << "ENTER ID :";
				int i;
				cin >> i; cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				Travel_Package* obj = service.search_service(i);
				if (obj->get_id() == 0) {
					cout << "Nu s-a gasit!" << endl;
				}
				else {
					cout << *obj << endl;
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

bool UI::verify_type_of_input(Inventory<bool>* verify) const {

	for (int i = 0; i < verify->size(); i++) {
		if (*(*verify)[i] == false) {
			return false;
		}
	}
	return true;
}