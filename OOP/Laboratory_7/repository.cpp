#include "repository.h"
#include "container.h"
#include <iostream>
using std::string;

Repository::Repository() {

	packages = new Inventory<Travel_Package>();
}

/*
* The function adds a travel package to the repository's container if it does not already exist.
* >> Input:
*    - package (Travel_Package*): A pointer to the travel package object to be added.
* >> Output:
*    - None (void).
* >> Exceptions:
*    - Throws ExceptionRepository with message "package already exists in repository"
*      if a package with the same ID already exists in the repository.
*/
void Repository::add_to_repository_container(Travel_Package* package) {

	if (check_object_uniqueness(package->get_id())) {

		packages->add(package);
	}
	else {
		throw ExceptionRepository("package already exists in repository");
	}
}

/*
* The function removes a travel package from the repository's container based on its ID.
* >> Input:
*    - id (int): The unique identifier of the travel package to be removed.
* >> Output:
*    - None (void).
* >> Exceptions:
*    - Throws ExceptionRepository with message "package not found in repository"
*      if no package with the given ID exists in the repository.
*/
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

/*
* The function updates the attributes of a travel package in the repository's container based on its ID.
* >> Input:
*    - id (int): The unique identifier of the travel package to be updated.
*    - name (const string&): The new name of the package (ignored if empty).
*    - destination (const string&): The new destination of the package (ignored if empty).
*    - type (const string&): The new type of the package (ignored if empty).
*    - price (double): The new price of the package (ignored if 0.0).
* >> Output:
*    - None (void).
* >> Exceptions:
*    - Throws ExceptionRepository with message "package not found in repository"
*      if no package with the given ID exists in the repository.
*/
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

/*
* The function returns a constant pointer to the container holding all travel packages in the repository.
* >> Input:
*    - None.
* >> Output:
*    - A constant pointer to an Inventory<Travel_Package> object containing all travel packages.
* >> Notes:
*    - The returned pointer provides read-only access to the container.
*/
const Inventory<Travel_Package>* Repository::get_all_packages_from_repository_container() const {
	return packages;
}

/*
* The function checks whether a travel package with the given ID is unique within the repository.
* >> Input:
*    - id (int): The unique identifier to be checked.
* >> Output:
*    - A boolean value:
*      - true if no package with the given ID exists in the repository (i.e., the ID is unique).
*      - false if a package with the given ID already exists.
*/
bool Repository::check_object_uniqueness(int id) {

	for (int i = 0; i < packages->size(); i++) {
		if ((*packages)[i]->get_id() == id) {
			return false;
		}
	}
	return true;
}

/*
* The function retrieves the index of a travel package in the repository's container based on its ID.
* >> Input:
*    - id (int): The unique identifier of the travel package.
* >> Output:
*    - An integer representing the index of the package in the container.
*      - Returns the index (≥ 0) if the package is found.
*      - Returns -1 if no package with the given ID exists.
*/
int Repository::get_the_index_for_package(int id) {

	for (int i = 0; i < packages->size(); i++) {
		if ((*packages)[i]->get_id() == id) {
			return i;
		}
	}
	return -1;
}

/*
* The function searches for a travel package in the repository based on its ID.
* >> Input:
*    - id (int): The unique identifier of the travel package to be searched.
* >> Output:
*    - A pointer to the Travel_Package object if found.
*    - nullptr if no package with the given ID exists in the repository.
*/
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