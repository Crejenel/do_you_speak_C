#include "repository.h"
#include "container.h"
#include <iostream>
#include <algorithm>
#include <iterator>
using std::string;

Repository::Repository() {

	packages = new Inventory<Travel_Package>();
}

/*
* The function adds a travel package to the repository container if it doesn't already exist.
* >> Input:
*    - package (Travel_Package*): A pointer to the Travel_Package object to be added to the repository.
* >> Output:
*    - If the package is successfully added to the repository, no value is returned.
* >> Exception:
*    - Throws an ExceptionRepository if a package with the same ID already exists in the repository.
* >> Behavior:
*    - The function checks if the package ID is unique by calling `check_object_uniqueness`.
*    - If the package is unique, it is added to the repository's container.
*    - If the package already exists (i.e., a package with the same ID exists), an exception is thrown.
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
* The function removes a travel package from the repository container based on its ID.
* >> Input:
*    - id (int): The ID of the travel package to be removed.
* >> Output:
*    - If the package is successfully removed, no value is returned.
* >> Exception:
*    - Throws an ExceptionRepository if the package with the given ID does not exist in the repository.
* >> Behavior:
*    - The function first checks if the package with the given ID exists in the repository by calling `check_object_uniqueness`.
*    - If the package exists, it retrieves the index of the package using `get_the_index_for_package` and removes it from the container.
*    - If the package does not exist, an exception is thrown indicating that the package was not found.
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
* The function updates the details of a travel package in the repository container based on its ID.
* >> Input:
*    - id (int): The ID of the travel package to be updated.
*    - name (string): The new name for the package (can be an empty string if no update).
*    - destination (string): The new destination for the package (can be an empty string if no update).
*    - type (string): The new type of the package (can be an empty string if no update).
*    - price (double): The new price for the package (should be non-zero to update).
* >> Output:
*    - If the package is successfully updated, no value is returned.
* >> Exception:
*    - Throws an ExceptionRepository if the package with the given ID does not exist in the repository.
* >> Behavior:
*    - The function looks for the travel package with the given ID using `get_the_index_for_package`.
*    - If the package exists, it updates the fields (name, destination, type, price) if the provided values are non-empty or non-zero.
*    - If the package with the specified ID does not exist, an exception is thrown.
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
* The function retrieves all the travel packages from the repository container.
* >> Input:
*    - None.
* >> Output:
*    - Returns a pointer to the Inventory<Travel_Package> containing all travel packages in the repository.
* >> Behavior:
*    - The function provides read-only access to the repository's container of travel packages.
*    - The caller can use the returned pointer to access the list of packages.
*    - Since the function is marked `const`, it guarantees that no modifications will be made to the repository's package data.
*/
const Inventory<Travel_Package>* Repository::get_all_packages_from_repository_container() const {
	return packages;
}

/*
* The function checks whether a travel package with the given ID already exists in the repository.
* >> Input:
*    - id (int): The ID of the travel package to be checked.
* >> Output:
*    - Returns true if no travel package with the given ID exists in the repository.
*    - Returns false if a travel package with the given ID is found.
* >> Behavior:
*    - The function uses `std::find_if` to search for a package with the specified ID in the repository.
*    - If no package is found, the function returns `true`, indicating the package can be added.
*    - If a package with the same ID already exists, the function returns `false`.
*/
bool Repository::check_object_uniqueness(int id) {

	auto it = std::find_if(packages->begin_ascendent(), packages->end_ascendent(),[id](const Travel_Package* pkg) { return pkg->get_id() == id; });
	return it == packages->end_ascendent();
}

/*
* The function retrieves the index of the travel package with the given ID from the repository.
* >> Input:
*    - id (int): The ID of the travel package whose index is to be retrieved.
* >> Output:
*    - Returns the index of the travel package in the repository if found.
*    - Returns -1 if no package with the specified ID exists.
* >> Behavior:
*    - The function uses `std::find_if` to search for a package with the specified ID in the repository.
*    - If a package is found, it returns the index of the package using `it.get_index()`.
*    - If no package with the given ID is found, it returns `-1`.
*/
int Repository::get_the_index_for_package(int id) {

	auto it = std::find_if(packages->begin_ascendent(), packages->end_ascendent(), [id](const Travel_Package* pkg) { return pkg->get_id() == id; });
	if (it == packages->end_ascendent()) {return -1;}
	else {
		return it.get_index();
	}
}

/*
* The function searches for a travel package by its ID in the repository.
* >> Input:
*    - id (int): The ID of the travel package to search for.
* >> Output:
*    - Returns a pointer to the Travel_Package if found.
*    - Returns nullptr if no travel package with the given ID exists in the repository.
* >> Behavior:
*    - The function iterates over the repository's package list using an ascending iterator (`begin_ascendent` and `end_ascendent`).
*    - It compares the ID of each package with the provided ID.
*    - If a package with the matching ID is found, the function returns a pointer to that package.
*    - If no such package is found, the function returns `nullptr`.
*/
Travel_Package* Repository::search(int id) {


	for (auto it = packages->begin_ascendent(); it != packages->end_ascendent(); ++it) {
		if ((*it)->get_id() == id) {
			return *it;
		}
	}
	return nullptr;
}

Repository::~Repository() {
	delete packages;
}