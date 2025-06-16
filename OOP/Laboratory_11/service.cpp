#include "domain.h"
#include "repository.h"
#include "validator.h"
#include "service.h"
#include "errors.h"
#include "undo.h"
#include <algorithm>
#include <vector>
using std::string;

Service::Service(Repository& repository, Validator& validator, Wishlist& wishlist)
	: repository(repository), validator(validator), wishlist(wishlist){
}

void Service::add_package(int id, const string& name, const string& destination, const string& type, double price) {

	if (validator.validate_attributes_for_travel_package(id, name, destination, type, price)) {

		Travel_Package* package = new Travel_Package(id, name, destination, type, price);
		repository.add_to_repository_container(package);
		undo_actions.add(new UndoAdd(repository, new Travel_Package(id, name, destination, type, price)));
	}
	else {
		throw ExceptionService("Invalid attributes for travel package");
	}

}

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

		if (result.size() > 1 && result.size() % 2 == 0) {

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

const  Inventory<Travel_Package>* Service::get_all_packages() {

	return repository.get_all_packages_from_repository_container();
}

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

		std::for_each(packages->begin_ascendent(), packages->end_ascendent(), [&filter_packages, &result](Travel_Package* pkg) {

			if (pkg->get_destination() == *result[1]) {

				Travel_Package* new_pkg = new Travel_Package(*pkg);
				filter_packages->add(new_pkg);
			}
			});

	}
	else if (*result[0] == "price") {

		if (is_digit_or_double(*result[1])) {

			double price = convert_char_to_double(*result[1]);

			std::for_each(packages->begin_ascendent(), packages->end_ascendent(), [&filter_packages, price](Travel_Package* pkg) {

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

bool Service::is_digit_or_double(const std::string& s) const {

	if (s.empty()) return false;

	bool found_dot = false;
	for (char c : s) {
		if (isdigit(c)) continue;
		if (c == '.' && !found_dot) {
			found_dot = true;
			continue;
		}
		return false;
	}
	return true;
}

double Service::convert_char_to_double(const string& s)const {

	return std::stod(s);

}

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