#include "domain.h"
#include "repository.h"
#include "validator.h"
#include "service.h"
#include "errors.h"
#include "undo.h"
#include <algorithm>
#include <vector>
using std::string;

Service::Service(Repository& repository, Validator& validator)
	: repository(repository), validator(validator) {
}

/*
* The function adds a new travel package to the repository.
* >> Input:
*    - id (int): The ID of the travel package.
*    - name (string): The name of the travel package.
*    - destination (string): The destination of the travel package.
*    - type (string): The type of the travel package.
*    - price (double): The price of the travel package.
* >> Output:
*    - Throws an exception if the attributes are invalid or if the travel package cannot be added.
*    - Calls the repository's method to add the package if the validation passes.
* >> Behavior:
*    - The function first validates the provided attributes for the new travel package using the `validate_attributes_for_travel_package` method from the `Validator` class.
*    - If the validation is successful (i.e., the attributes are valid):
*        - A new `Travel_Package` object is created using the provided parameters.
*        - The package is then added to the repository by calling `add_to_repository_container` of the repository.
*    - If the validation fails (e.g., if any attribute is invalid), an `ExceptionService` is thrown with the message "Invalid attributes for travel package".
*/
void Service::add_package(int id, const string& name, const string& destination, const string& type, double price) {

	if (validator.validate_attributes_for_travel_package(id, name, destination, type, price)) {

		Travel_Package* package = new Travel_Package(id, name, destination, type, price);
		repository.add_to_repository_container(package);
		undo_actions.add(new UndoAdd(repository,new Travel_Package(id,name,destination,type,price)));
	}
	else {
		throw ExceptionService("Invalid attributes for travel package");
	}

}

/*
* The function deletes a travel package from the repository based on the provided ID.
* >> Input:
*    - id (int): The ID of the travel package to be deleted.
* >> Output:
*    - Throws an exception if the ID is invalid.
*    - Calls the repository's method to remove the package if the ID is valid.
* >> Behavior:
*    - The function first validates the provided ID using the `validate_id_for_travel_package` method from the `Validator` class.
*    - If the ID is valid:
*        - The function calls `remove_from_repository_container` from the repository to delete the package with the provided ID.
*    - If the ID is invalid (i.e., outside the acceptable range or incorrect format), an `ExceptionService` is thrown with the message "you provided an invalid id".
*/
void Service::delete_package(int id) {

	if (validator.validate_id_for_travel_package(id)) {

		Travel_Package* TP = search_service(id);
		if (TP != nullptr) {
			undo_actions.add(new UndoRemove(repository, new Travel_Package(*TP)));
		}
		repository.remove_from_repository_container(id);
	}
	else {
		throw ExceptionService("you provided an invalid id");
	}
}

/*
* The function updates an existing travel package in the repository based on the provided ID and update string.
* >> Input:
*    - id (int): The ID of the travel package to be updated.
*    - update (string): A semicolon-delimited string that contains the attributes to be updated (e.g., "name:New Name;price:500").
* >> Output:
*    - Updates the travel package in the repository if the ID is valid and attributes are valid.
*    - Throws an exception if the ID is invalid or if the update string is malformed.
* >> Behavior:
*    1. The function first validates the provided ID using the `validate_id_for_travel_package` method from the `Validator` class.
*    2. If the ID is valid:
*        - It splits the `update` string based on the delimiters `;` and `:`, which separate the attribute name and its new value.
*        - It validates the extracted attribute-value pairs:
*          - `name`, `destination`, and `type` should be valid strings (using `validate_string_attributes_for_travel_package`).
*          - `price` should be a valid number (using `is_digit_or_double` and `convert_char_to_double`).
*        - If any attribute is invalid or the update string is improperly formatted, an `ExceptionService` is thrown with the message "Invalid attributes for travel package".
*    3. If all attributes are valid, the corresponding travel package in the repository is updated using `update_package_from_repository_container`.
*    4. If the ID is invalid (i.e., not within the expected range), an `ExceptionService` is thrown with the message "you provided an invalid id".
*/
void Service::update_package(int id, const string& update) {

	if (validator.validate_id_for_travel_package(id)) {

		// the variable where the new data for a package is stored
		string name = "";
		string destination = "";
		string type = "";
		double price = 0.0;

		// the variabile we need to split the update string
		string copy_update = update;
		Inventory<string> result;
		string delimiters = ";:";
		size_t start = 0, end;


		// the actual splitting
		while ((end = copy_update.find_first_of(delimiters, start)) != string::npos) {

			string* fragment = new string;
			*fragment = copy_update.substr(start, end - start);
			size_t first = (*fragment).find_first_not_of(" ");
			size_t last = (*fragment).find_last_not_of(" ");

			if (first != string::npos) {
				*fragment = (*fragment).substr(first, last - first + 1);
			}
			else {
				*fragment = "";
			}

			result.add(fragment);
			start = end + 1;
		}

		if (start < copy_update.length()) {

			string* fragment = new string;
			*fragment = copy_update.substr(start);
			size_t first = (*fragment).find_first_not_of(" ");
			size_t last = (*fragment).find_last_not_of(" ");
			if (first != string::npos) {

				*fragment = (*fragment).substr(first, last - first + 1);
			}
			else {

				*fragment = "";
			}

			result.add(fragment);
		}

		if (result.size() > 1 && result.size()%2==0) {

			for (auto it = result.begin_ascendent(); it != result.end_ascendent(); ++it) {

				if (**it == "name" && ++it != result.end_ascendent() && validator.validate_string_attributes_for_travel_package(**it)) {
					name = **it;
				}
				else if (**it == "destination" && ++it != result.end_ascendent() && validator.validate_string_attributes_for_travel_package(**it)) {
					destination = **it;
				}
				else if (**it == "type" && ++it != result.end_ascendent() && validator.validate_string_attributes_for_travel_package(**it)) {
					type = **it;
				}
				else if (**it == "price" && ++it != result.end_ascendent() && **it != "" && is_digit_or_double(**it)) {
					price = convert_char_to_double(**it);
				}
				else {
					throw ExceptionService("Invalid attributes for travel package");
				}
			}
		}
		else {

			throw ExceptionService("Invalid attributes for travel package");
		}

		Travel_Package* TP = search_service(id);
		if (TP != nullptr) {
			undo_actions.add(new UndoUpdate(repository, new Travel_Package(*TP)));
		}
		repository.update_package_from_repository_container(id, name, destination, type, price);
	}
	else {
		throw ExceptionService("you provided an invalid id");
	}
}

/*
* The function retrieves all the travel packages from the repository.
* >> Input:
*    - None.
* >> Output:
*    - A constant pointer to an `Inventory<Travel_Package>` object containing all the travel packages in the repository.
*    - The returned pointer provides access to the packages in a read-only manner.
* >> Behavior:
*    1. The function calls the `get_all_packages_from_repository_container` method of the `Repository` class to retrieve the container of all travel packages.
*    2. The function does not modify the repository or the packages it returns.
*    3. If there are no travel packages in the repository, it will return a pointer to an empty `Inventory<Travel_Package>`.
*    4. The repository and its contents remain unchanged during the execution of this function.
*/
const  Inventory<Travel_Package>* Service::get_all_packages() {

	return repository.get_all_packages_from_repository_container();
}

/*
* The function filters the travel packages based on the specified filter criteria (destination or price).
* >> Input:
*    - filter_packages (Inventory<Travel_Package>*): A pointer to the `Inventory<Travel_Package>` where the filtered travel packages will be stored.
*    - filter (string): A string that specifies the filter criteria in the form "criterion:value" (e.g., "destination:Paris" or "price:500").
* >> Output:
*    - The function filters the travel packages from the repository based on the provided criteria (destination or price).
*    - The filtered packages are added to the `filter_packages` inventory.
*    - If the filter string is malformed or invalid, an exception (`ExceptionService`) is thrown.
* >> Behavior:
*    1. The function splits the `filter` string by the delimiter ":" to separate the filter criterion and its value.
*    2. If the filter string is not well-formed (i.e., there is no criterion or value), an exception is thrown.
*    3. Based on the extracted filter criterion:
*       - If the criterion is "destination", it compares the destination of each travel package in the repository to the specified value and adds matching packages to the `filter_packages` inventory.
*       - If the criterion is "price", it compares the price of each package to the specified value and adds packages with a price less than or equal to the specified value to the `filter_packages` inventory.
*    4. If the filter criterion is unrecognized (not "destination" or "price"), an exception is thrown.
*    5. If the filter value for "price" is not a valid number, an exception is thrown.
*    6. If any invalid data is encountered during filtering, an exception is thrown with the message "Invalid filter".
*/
void Service::filter_packages(Inventory<Travel_Package>* filter_packages, const string& filter) {

	string criterion = "";
	string filter_copy = filter;

	Inventory<string> result;
	string delimiters = ":";
	size_t start = 0, end;

	while ((end = filter_copy.find_first_of(delimiters, start)) != string::npos) {

		string* fragment = new string;
		*fragment = filter_copy.substr(start, end - start);
		size_t first = (*fragment).find_first_not_of(" ");
		size_t last = (*fragment).find_last_not_of(" ");

		if (first != string::npos) {
			*fragment = (*fragment).substr(first, last - first + 1);
		}
		else {
			*fragment = "";
		}

		result.add(fragment);
		start = end + 1;
	}

	if (start < filter_copy.length()) {

		string* fragment = new string;
		*fragment = filter_copy.substr(start);
		size_t first = (*fragment).find_first_not_of(" ");
		size_t last = (*fragment).find_last_not_of(" ");
		if (first != string::npos) {

			*fragment = (*fragment).substr(first, last - first + 1);
		}
		else {

			*fragment = "";
		}

		result.add(fragment);
	}

	const Inventory<Travel_Package>* packages = repository.get_all_packages_from_repository_container();

	if (result.size() == 1) {
		throw ExceptionService("Invalid filter");
	}

	if (*result[0] == "destination") {

		std::for_each(packages->begin_ascendent(), packages->end_ascendent(),[&filter_packages, &result](Travel_Package* pkg) {
				
				if (pkg->get_destination() == *result[1]) {
					
					Travel_Package* new_pkg = new Travel_Package(*pkg);
					filter_packages->add(new_pkg);  
				}
		});

	}
	else if (*result[0] == "price") {

		if (is_digit_or_double(*result[1])) {

			double price = convert_char_to_double(*result[1]);

			std::for_each(packages->begin_ascendent(), packages->end_ascendent(), [&filter_packages,price](Travel_Package* pkg) {

				if (pkg->get_price() <= price) {

					Travel_Package* new_pkg = new Travel_Package(*pkg);
					filter_packages->add(new_pkg);
				}
			});
		}
		else {

			throw ExceptionService("Invalid filter");

		}
	}
	else {
		throw ExceptionService("Invalid filter");
	}

}

/*
* The function sorts the travel packages based on the specified sorting criteria (destination or price).
* >> Input:
*    - sort_packages (Inventory<Travel_Package>*): A pointer to the `Inventory<Travel_Package>` where the sorted travel packages will be stored.
*    - sort (string): A string that specifies the sorting criteria in the form "criterion:order" (e.g., "destination:ascending" or "price:descending").
* >> Output:
*    - The function sorts the travel packages from the repository based on the provided criteria and order.
*    - The sorted packages are added to the `sort_packages` inventory.
*    - If the sort string is malformed or invalid, an exception (`ExceptionService`) is thrown.
* >> Behavior:
*    1. The function splits the `sort` string by the delimiter ":" to separate the sort criterion and its order (ascending or descending).
*    2. If the sort string is not well-formed (i.e., there is no criterion or order), an exception is thrown.
*    3. Based on the extracted sort criterion:
*       - If the criterion is "destination", it sorts the travel packages by their destination in the specified order (ascending or descending) and adds them to the `sort_packages` inventory.
*       - If the criterion is "price", it sorts the travel packages by their price in the specified order (ascending or descending) and adds them to the `sort_packages` inventory.
*    4. If the sort criterion is unrecognized (not "destination" or "price"), an exception is thrown.
*    5. If the sort order is unrecognized (not "ascending" or "descending"), an exception is thrown.
*    6. If any invalid data is encountered during sorting, an exception is thrown with the message "Invalid sort".
*/
void Service::sort_packages(Inventory<Travel_Package>* sort_packages, const string& sort) {

	string criterion = "";
	string sort_copy = sort;

	Inventory<string> result;
	string delimiters = ":";
	size_t start = 0, end;

	while ((end = sort_copy.find_first_of(delimiters, start)) != string::npos) {

		string* fragment = new string;
		*fragment = sort_copy.substr(start, end - start);
		size_t first = (*fragment).find_first_not_of(" ");
		size_t last = (*fragment).find_last_not_of(" ");

		if (first != string::npos) {
			*fragment = (*fragment).substr(first, last - first + 1);
		}
		else {
			*fragment = "";
		}

		result.add(fragment);
		start = end + 1;
	}

	if (start < sort_copy.length()) {

		string* fragment = new string;
		*fragment = sort_copy.substr(start);
		size_t first = (*fragment).find_first_not_of(" ");
		size_t last = (*fragment).find_last_not_of(" ");
		if (first != string::npos) {

			*fragment = (*fragment).substr(first, last - first + 1);
		}
		else {

			*fragment = "";
		}

		result.add(fragment);
	}

	const Inventory<Travel_Package>* packages = repository.get_all_packages_from_repository_container();
	std::vector<Travel_Package*> SORTED_PACHAGES;
	for (auto it = packages->begin_ascendent(); it != packages->end_ascendent(); ++it) {
		SORTED_PACHAGES.push_back(*it);
	}

	if (result.size() == 1) {

		throw ExceptionService("Invalid sort");
	}

	if (*result[0] == "destination") {

		if (*result[1] == "ascending")
		{
			std::sort(SORTED_PACHAGES.begin(), SORTED_PACHAGES.end(), [](const Travel_Package* a, const Travel_Package* b) {
				return a->get_destination() < b->get_destination();
				});

			for (auto it = SORTED_PACHAGES.begin(); it != SORTED_PACHAGES.end(); ++it) {
				Travel_Package* package = new Travel_Package(**it);
				sort_packages->add(package);
			}
			
		}
		else if (*result[1] == "descending") {

			std::sort(SORTED_PACHAGES.begin(), SORTED_PACHAGES.end(), [](const Travel_Package* a, const Travel_Package* b) {
				return a->get_destination() > b->get_destination();
				});

			for (auto it = SORTED_PACHAGES.begin(); it != SORTED_PACHAGES.end(); ++it) {
				Travel_Package* package = new Travel_Package(**it);
				sort_packages->add(package);
			}
		}
		else {
			throw ExceptionService("Invalid sort");
		}

	}
	else if (*result[0] == "price") {

		if (*result[1] == "ascending")
		{
			
			std::sort(SORTED_PACHAGES.begin(), SORTED_PACHAGES.end(), [](const Travel_Package* a, const Travel_Package* b) {
				return a->get_price() < b->get_price();
				});

			for (auto it = SORTED_PACHAGES.begin(); it != SORTED_PACHAGES.end(); ++it) {
				Travel_Package* package = new Travel_Package(**it);
				sort_packages->add(package);
			}
		}
		else if (*result[1] == "descending") {

			std::sort(SORTED_PACHAGES.begin(), SORTED_PACHAGES.end(), [](const Travel_Package* a, const Travel_Package* b) {
				return a->get_price() > b->get_price();
				});

			for (auto it = SORTED_PACHAGES.begin(); it != SORTED_PACHAGES.end(); ++it) {
				Travel_Package* package = new Travel_Package(**it);
				sort_packages->add(package);
			}
		}
		else {
			throw ExceptionService("Invalid sort");
		}

	}
	else {
		throw ExceptionService("Invalid sort");
	}

}

/*
* The function checks whether the given string `s` represents a valid number (either an integer or a decimal number).
* >> Input:
*    - s (string): The string to be checked for being a valid digit or double.
* >> Output:
*    - Returns `true` if the string is a valid integer or double (with at most one decimal point).
*    - Returns `false` otherwise.
* >> Behavior:
*    1. The function first checks if the string is empty. If it is, it immediately returns `false`.
*    2. It then iterates over each character in the string:
*       - If the character is a digit, it continues.
*       - If the character is a dot ('.'), it checks if it has already found a dot in the string. If not, it allows the dot; if one has already been found, it returns `false`.
*    3. If all characters are either digits or at most one dot, the function returns `true`; otherwise, it returns `false`.
*/
bool Service::is_digit_or_double(const std::string& s) const {

	if (s.empty()) return false;

	bool found_dot = false;
	for (char c : s) {
		if (isdigit(c)) continue;
		if (c == '.' && !found_dot) {
			found_dot = true;
			continue;
		}
		return false;}
	return true;
}

/*
* The function converts a string to a double using the `std::stod` method.
* >> Input:
*    - s (string): The string to be converted to a double.
* >> Output:
*    - Returns the `double` value of the string `s`.
* >> Behavior:
*    1. The function uses `std::stod` to convert the string to a double and directly returns the result.
*    2. If the string is not a valid number, `std::stod` will throw an exception (e.g., `std::invalid_argument` or `std::out_of_range`), which should be handled elsewhere in the code.
*/
double Service::convert_char_to_double(const string& s)const {

	return std::stod(s);

}

/*
* The function searches for a travel package by its ID in the repository.
* >> Input:
*    - id (int): The ID of the travel package to search for.
* >> Output:
*    - Returns a pointer to the `Travel_Package` object if it exists in the repository.
*    - Returns `nullptr` if the package is not found in the repository.
* >> Behavior:
*    1. The function calls the `search` method from the `Repository` class to find a travel package with the specified ID.
*    2. If the package is found, it returns the corresponding `Travel_Package` object; otherwise, it returns `nullptr`.
*/
Travel_Package* Service::search_service(int id) {

	return repository.search(id);
}

void Service::undo() {

	if (undo_actions.size() == 0) {
		throw ExceptionService("No action to undo!");
	}
	else {
		undo_actions[undo_actions.size() - 1]->doUndo();
		undo_actions.remove(undo_actions.size() - 1);
	}

}