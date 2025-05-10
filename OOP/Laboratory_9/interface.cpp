#include <limits>
#include <string>
#include <vector>
#include <map>
#include "service.h"
#include "interface.h"
#include "domain.h"
#include "wishlist.h"
using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::map;

UI::UI(Service& service, Wishlist& wishlist) : service(service), wishlist(wishlist) {}

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
				if (obj==nullptr) {
					cout << "Nu s-a gasit!" << endl;
				}
				else {
					cout << *obj << endl;
				}
				break;
			}
			case 8: 
			{
				cout << ">> To add a travel package to your wishlist, please enter its ID <<" << endl;
				cout << ">> ";
				int id;
				if (!(cin >> id)) {
					cout << "<< \033[1;31mERROR\033[0m: Wrong input type for ID >>" << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					break;
				}
				Travel_Package* obj = service.search_service(id);

				if (obj == nullptr) {
					cout << "<< \033[1;31mERROR\033[0m: The travel package with the specified ID does not exist >>" << endl;
					break;
				}
				else {
					Travel_Package* obj2 = new Travel_Package(*obj);
					try {
						
						wishlist.add_to_wishlist(obj2);
						cout << "\033[32mTravel Package added to your wishlist succesfully!\033[0m" << endl;
					}
					catch (const ExceptionWishlist& e) {
						e.print_exception();
						delete obj2;
					}
				}
				break;
			}
			case 9:
			{
				cout << ">> To remove a travel package from your wishlist, please enter its ID <<" << endl;
				cout << ">> ";
				int id;
				if (!(cin >> id)) {
					cout << "<< \033[1;31mERROR\033[0m: Wrong input type for ID >>" << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					break;
				}
				try {
					wishlist.delete_from_wishlist(id);
					cout << "\033[32mTravel Package removed from your wishlist succesfully!\033[0m" << endl;
				}
				catch (const ExceptionWishlist& e) {
					e.print_exception();
				}
				break;
			}
			case 10:
			{
				cout << ">> To generate a wishlist, please enter the number of travel packages that you want to add to your wishlist <<" << endl;
				cout << ">> ";
				int number;
				if (!(cin >> number)) {
					cout << "<< \033[1;31mERROR\033[0m: Wrong input type for number >>" << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					break;
				}
				if (number <= 0) {
					cout << "<< \033[1;31mERROR\033[0m: The number of travel packages must be greater than 0 >>" << endl;
					break;
				}

				const Inventory<Travel_Package>* travel_packages = service.get_all_packages();
				if (travel_packages->size() == 0) {
					cout << "<< \033[1;31mERROR\033[0m: There are no travel packages in the system right now >>" << endl;
					break;
				}
				if (number > travel_packages->size()) {
					cout << "<< \033[1;31mERROR\033[0m: Sorry, there are too few travel packages in the system to create your wishlist right now.>>" << endl;
					break;
				}
			
				wishlist.generate_wishlist(number,travel_packages);
				cout << "\033[32mWishlist generated succesfully!\033[0m" << endl;
				break;
			}
			case 11: 
			{
				const Inventory<Travel_Package>* wishlist_packages = wishlist.get_wishlist();
				if (wishlist_packages->size() == 0) {
					cout << ">>\033[32m There are no travel packages in your wishlist right now\033[0m <<" << endl;
					break;
				}
				for (int i = 0; i < wishlist_packages->size(); i++) {
					cout << *((*wishlist_packages)[i]) << endl;
				}
				break;
			}
			case 12:
			{
				cout << ">> To export your wishlist, please enter the name of the file <<" << endl;
				cout << ">> ";
				string file_name;
				getline(cin, file_name);
				val = new bool[1];
				*val = !file_name.empty();
				verify->add(val);
				if (!verify_type_of_input(verify)) {
					cout << "<< \033[1;31mERROR\033[0m: The file name is required >>" << endl;
					break;
				}
				
				wishlist.export_wishlist(file_name);
				cout << "\033[32mWishlist exported succesfully!\033[0m" << endl;
				
				break;
			}
			case 13:
			{
				const multimap<string, Travel_Package*>* wishlist_map = wishlist.get_wishlist_map();
				for (auto it = wishlist_map->begin(); it != wishlist_map->end(); ++it) {
					if (it == wishlist_map->begin() || it->first != std::prev(it)->first) {
						std::cout << "Type: " << it->first << " | Number: " << wishlist_map->count(it->first) << std::endl;
					}
				}
				break;
			}
			case 14: 
			{
				try {
					service.undo();
				}
				catch(ExceptionService& e){
					e.print_exception();
					break;
				}
				cout << "\033[32mUndo was executed succesfuly!\033[0m" << endl;
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

	cout << "\033[0;34m---------- Please choose an action ----------\033[0m" << endl;
	cout << "0. Exit the application." << endl;
	cout << "1. Add a travel package to the system." << endl;
	cout << "2. Update a travel package in the system." << endl;
	cout << "3. Remove a travel package from the system." << endl;
	cout << "4. Display all travel packages in the system." << endl;
	cout << "5. Filter travel packages by a criterion." << endl;
	cout << "6. Display all travel packages sorted by a criterion." << endl;
	cout << "7. Search for a travel package." << endl;
	cout << "8. Add a travel package to your wishlist." << endl;
	cout << "9. Remove a travel package from your wishlist." << endl;
	cout << "10. Generate a wishlist." << endl;
	cout << "11. View your wishlist." << endl;
	cout << "12. Export your wishlist." << endl;
	cout << "13. Display the statistics." << endl;
	cout << "14. Undo" << endl;

}

bool UI::verify_type_of_input(Inventory<bool>* verify) const {

	for (int i = 0; i < verify->size(); i++) {
		if (*(*verify)[i] == false) {
			return false;
		}
	}
	return true;
}