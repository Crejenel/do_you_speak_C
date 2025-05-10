#ifndef SERVICE_H
#define SERVICE_H
#include "domain.h"
#include "repository.h"
#include "validator.h"
#include "container.h"
#include "undo.h"
using std::string;


class Service {

private:

	Repository& repository;
	Validator& validator;
	Inventory<UndoAction> undo_actions;


public:

	Service(Repository& repository, Validator& validator);

	void add_package(int id, const string& name, const string& destination, const string& type, double price);

	void delete_package(int id);

	void update_package(int id, const string& update);

	const Inventory<Travel_Package>* get_all_packages();

	void filter_packages(Inventory<Travel_Package>* filter_packages, const string& filter);

	void sort_packages(Inventory<Travel_Package>* sort_packages, const string& sort);

	Travel_Package* search_service(int id);

	void undo();


private:

	bool is_digit_or_double(const string& s) const;

	double convert_char_to_double(const string& s) const;

};

#endif