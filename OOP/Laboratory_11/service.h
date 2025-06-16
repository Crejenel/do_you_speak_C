#ifndef SERVICE_H
#define SERVICE_H
#include "domain.h"
#include "repository.h"
#include "validator.h"
#include "container.h"
#include "wishlist.h"
#include "undo.h"
using std::string;


class Service {

private:

	Repository& repository;
	Validator& validator;
	Wishlist& wishlist;
	Inventory<UndoAction> undo_actions;


public:

	Service(Repository& repository, Validator& validator, Wishlist& wishlist);

	void add_package(int id, const string& name, const string& destination, const string& type, double price);

	void delete_package(int id);

	void update_package(int id, const string& update);

	const Inventory<Travel_Package>* get_all_packages();

	void filter_packages(Inventory<Travel_Package>* filter_packages, const string& filter);

	void sort_packages(Inventory<Travel_Package>* sort_packages, const string& sort);

	// the wishlist
	/*
	void add_travel_package_to_wishlist(int id) {

		Travel_Package* obj = search_service(id);

		if (obj == nullptr) {
			throw ExceptionService("The travel package with the specified ID does not exist!");
		}
		else {

			Travel_Package* obj2 = new Travel_Package(*obj);
			wishlist.add_to_wishlist(obj2);
		}
	}

	void remove_travel_package_from_wishlist(int id) {

		wishlist.delete_from_wishlist(id);

	}

	void generate_a_wishlist(int number) {

		if (number <= 0) {
			throw ExceptionService("The number of travel packages must be greater than 0 ");
		}

		const Inventory<Travel_Package>* travel_packages = get_all_packages();

		if (travel_packages->size() == 0) {

			throw ExceptionService("There are no travel packages in the system right now");
		}
		if (number > travel_packages->size()) {

			throw ExceptionService("Sorry, there are too few travel packages in the system to create your wishlist right now.");
		}

		wishlist.generate_wishlist(number, travel_packages);
	}

	void export_the_wishlist(string file_name) {
		wishlist.export_wishlist(file_name);
	}

	void get_the_statistic_from_wishlist() {

	}
	*/

	Travel_Package* search_service(int id);

	void undo();


private:

	bool is_digit_or_double(const string& s) const;

	double convert_char_to_double(const string& s) const;

};

#endif