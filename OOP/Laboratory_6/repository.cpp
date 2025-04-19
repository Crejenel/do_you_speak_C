#include "domain.h"
#include "repository.h"
#include <iostream>
#include <vector>
using std::vector;
using std::string;

/*
* The function adds a travel package to the repository if it doesn't already exist.
* >> Input:
*    - package (Travel_Package): An object representing the travel package to be added.
* >> Output:
*    - A string indicating the result of the operation:
*      - "#999" if the package was successfully added.
*      - "#998" if a package with the same ID already exists.
*/
string Repository:: add_to_repository_container(Travel_Package &package) {
	if (check_object_uniqueness(package.get_id())) {
		packages.push_back(package);
		return "#999"; }
	else { return "#998";}}

/*
* The function removes a travel package from the repository if it exists.
* >> Input:
*    - id (int): The unique identifier of the travel package to be removed.
* >> Output:
*    - A string indicating the result of the operation:
*      - "#997" if the package was successfully removed.
*      - "#996" if the package does not exist in the repository.
*/
string Repository::remove_from_repository_container(int id) {

	if (!check_object_uniqueness(id)) {

		int index = get_the_index_for_package(id);

		if (index != -1) {

			packages.erase(packages.begin() + index);
			return "#997";
		}
	}
	return "#996";
}

/*
* The function updates the details of an existing travel package in the repository.
* >> Input:
*    - id (int): The unique identifier of the travel package to be updated.
*    - name (const string&): The new name of the package (if not empty, it will be updated).
*    - destination (const string&): The new destination of the package (if not empty, it will be updated).
*    - type (const string&): The new type of the package (if not empty, it will be updated).
*    - price (double): The new price of the package (if not 0.0, it will be updated).
* >> Output:
*    - A string indicating the result of the operation:
*      - "#995" if the package was successfully updated.
*      - "#994" if the package with the given ID does not exist.
*/
string Repository:: update_package_from_repository_container(int id, const string &name, const string &destination, const string &type, double price) {

	int index = get_the_index_for_package(id);
	if (index != -1 ) {

		if (name != "") {
			packages[index].set_name(name);
		}
		if (destination != "") {
			packages[index].set_destination(destination);
		}
		if (type != "") {
			packages[index].set_type(type);
		}
		if (price != 0.0) {
			packages[index].set_price(price);
		}
		return "#995"; }
	else {
		return "#994";
	}
}

/*
* The function retrieves all travel packages stored in the repository.
* >> Input:
*    - None.
* >> Output:
*    - A constant reference to a vector containing all travel packages in the repository.
*/
const vector<Travel_Package>& Repository:: get_all_packages_from_repository_container() const {
	return packages;
}

/*
* The function checks whether a travel package with the given ID already exists in the repository.
* >> Input:
*    - id (int): The unique identifier of the travel package to check.
* >> Output:
*    - A boolean value:
*      - false if a package with the given ID already exists.
*      - true if the package does not exist in the repository.
*/
bool Repository:: check_object_uniqueness(int id) {

	for (size_t i = 0; i < packages.size(); i++) {
		if (packages[i].get_id() == id ) {
			return false;
		}
	}
	return true;
}

/*
* The function retrieves the index of a travel package in the repository based on its ID.
* >> Input:
*    - id (int): The unique identifier of the travel package.
* >> Output:
*    - An integer representing the index of the package in the repository.
*      - Returns the index (>= 0) if the package is found.
*      - Returns -1 if no package with the given ID exists.
*/
int Repository:: get_the_index_for_package(int id) {

	for (int i = 0; i <(int) packages.size(); i++) {
		if (packages[i].get_id() == id) {
			return i;
		}
	}
	return -1;
}

Travel_Package& Repository::search(int id) {

	for (size_t i = 0; i < packages.size(); i++) {
		if (packages[i].get_id() == id) {
			return packages[i];
		}
	}
	static Travel_Package empty_package(0,"","","",0);  // Obiect gol
	return empty_package;
}