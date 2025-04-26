#include "repository.h"
#include "container.h"
#include <iostream>
using std::string;

Repository::Repository() {

	packages = new Inventory<Travel_Package>();
}

void Repository::add_to_repository_container(Travel_Package* package) {

	if (check_object_uniqueness(package->get_id())) {

		packages->add(package);
	}
	else {
		throw ExceptionRepository("package already exists in repository");
	}
}

void Repository::remove_from_repository_container(int id) {

	if (!check_object_uniqueness(id)) {

		int index = get_the_index_for_package(id);

		if (index != -1) {

			packages->remove(index);
		}
	}
	else {

		throw ExceptionRepository("package not found in repository");
	}
	
}

void Repository::update_package_from_repository_container(int id, const string& name, const string& destination, const string& type, double price) {

	int index = get_the_index_for_package(id);
	if (index != -1) {

		if (name != "") {
			(*packages)[index]->set_name(name);
		}
		if (destination != "") {
			(*packages)[index]->set_destination(destination);
		}
		if (type != "") {
			(*packages)[index]->set_type(type);
		}
		if (price != 0.0) {
			(*packages)[index]->set_price(price);
		}
	}
	else {
		throw ExceptionRepository("package not found in repository");
	}
}

const Inventory<Travel_Package>* Repository::get_all_packages_from_repository_container() const {
	return packages;
}

bool Repository::check_object_uniqueness(int id) {

	for (int i = 0; i < packages->size(); i++) {
		if ((*packages)[i]->get_id() == id) {
			return false;
		}
	}
	return true;
}

int Repository::get_the_index_for_package(int id) {

	for (int i = 0; i < packages->size(); i++) {
		if ((*packages)[i]->get_id() == id) {
			return i;
		}
	}
	return -1;
}

Travel_Package* Repository::search(int id) {

	for (int  i = 0; i < packages->size(); i++) {

		if ((*packages)[i]->get_id() == id) {
			return (*packages)[i];
		}
	}
	return nullptr;
}

Repository::~Repository() {
	delete packages;
}