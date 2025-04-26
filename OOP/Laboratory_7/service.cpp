#include "domain.h"
#include "repository.h"
#include "validator.h"
#include "service.h"
#include "errors.h"
using std::string;

Service::Service(Repository& repository, Validator& validator)
	: repository(repository), validator(validator) {
}

void Service::add_package(int id, const string& name, const string& destination, const string& type, double price) {

	if (validator.validate_attributes_for_travel_package(id, name, destination, type, price)) {

		Travel_Package* package = new Travel_Package(id, name, destination, type, price);
		repository.add_to_repository_container(package);
	}
	else {
		throw ExceptionService("Invalid attributes for travel package");
	}

}

void Service::delete_package(int id) {

	if (validator.validate_id_for_travel_package(id)) {

		return repository.remove_from_repository_container(id);}
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

		// hendle the result
		for (int i = 0; i < result.size(); i++) {

			if ((*result[i]) == "name" && (i + 1) < result.size() && validator.validate_string_attributes_for_travel_package((*result[i + 1])))
			{
				name = (*result[i + 1]);
				i++;
			}
			else if (*result[i] == "destination" && (i + 1) < result.size() && validator.validate_string_attributes_for_travel_package(*result[i + 1])) {

				destination = *result[i + 1];
				i++;
			}
			else if (*result[i] == "type" && (i + 1) < result.size() && validator.validate_string_attributes_for_travel_package(*result[i + 1])) {

				type = *result[i + 1];
				i++;
			}
			else if (*result[i] == "price" && (i + 1) < result.size() && *result[i + 1] != "" && is_digit_or_double(*result[i + 1])) {

				double nr = convert_char_to_double(*result[i + 1]);
				price = nr;
				i++;

			}
			else {
				
				throw ExceptionService("Invalid attributes for travel package");

			}
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

		for (int i = 0; i < packages->size(); i++) {
			if ((*packages)[i]->get_destination() == *result[1]) {

				Travel_Package* package = new Travel_Package(*(*packages)[i]);

				filter_packages->add(package);
			}
		}
	} 
	else if (*result[0] == "price") {

		if (is_digit_or_double(*result[1])) {

			double price = convert_char_to_double(*result[1]);

			for (int i = 0; i < packages->size(); i++) {

				if ((*packages)[i]->get_price() <= price) {

					Travel_Package* package = new Travel_Package(*(*packages)[i]);

					filter_packages->add(package);
				}
			}
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
	bool insert;

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

	if (result.size() == 1) {
		
		throw ExceptionService("Invalid sort");
	}

	if (*result[0] == "destination") {

		if (*result[1] == "ascending")
		{
			for (int i = 0; i < packages->size(); i++) {

				insert = false;

				if (sort_packages->size()==0) {

					Travel_Package* package = new Travel_Package(*(*packages)[i]);

					sort_packages->add(package);
					continue;
				}

				for (int j = sort_packages->size(); j > 0; j--) {
					if ((*packages)[i]->get_destination() >= (*sort_packages)[j - 1]->get_destination()) {

						Travel_Package* package = new Travel_Package(*(*packages)[i]);

						sort_packages->insert( j, package);
						insert = true;
						break;
					}
				}

				if (!insert) {

					Travel_Package* package = new Travel_Package(*(*packages)[i]);

					sort_packages->insert(0,package);
				}
			}
		}
		else if (*result[1] == "descending") {

			for (int i = 0; i < packages->size(); i++) {

				insert = false;

				if (sort_packages->size()==0) {

					Travel_Package* package = new Travel_Package(*(*packages)[i]);

					sort_packages->add(package);
					continue;
				}

				for (int j = sort_packages->size(); j > 0; j--) {

					if ((*packages)[i]->get_destination() <= (*sort_packages)[j - 1]->get_destination()) {

						Travel_Package* package = new Travel_Package(*(*packages)[i]);

						sort_packages->insert( j, package);
						insert = true;
						break;}}

				if (!insert) { Travel_Package* package = new Travel_Package(*(*packages)[i]); sort_packages->insert(0, package);}
			}
		}
		else {
			throw ExceptionService("Invalid sort");
		}

	} 
	else if (*result[0] == "price") {

		if (*result[1] == "ascending")
		{
			for (int i = 0; i < packages->size(); i++) {
				insert = false;

				if (sort_packages->size()==0) {

					Travel_Package* package = new Travel_Package(*(*packages)[i]);

					sort_packages->add(package);
					continue;
				}

				for (int j = sort_packages->size(); j > 0; j--) {
					if ((*packages)[i]->get_price() >= (*sort_packages)[j - 1]->get_price()) {

						Travel_Package* package = new Travel_Package(*(*packages)[i]);

						sort_packages->insert(j, package);
						insert = true;
						break;
					}
				}

				if (!insert) {

					Travel_Package* package = new Travel_Package(*(*packages)[i]);

					sort_packages->insert(0, package);
				}
			}
		}
		else if (*result[1] == "descending") {

			for (int i = 0; i < packages->size(); i++) {
				insert = false;

				if (sort_packages->size()==0) {

					Travel_Package* package = new Travel_Package(*(*packages)[i]);

					sort_packages->add(package);
					continue;
				}

				for (int j = sort_packages->size(); j > 0; j--) {
					if ((*packages)[i]->get_price() <= (*sort_packages)[j - 1]->get_price()) {

						Travel_Package* package = new Travel_Package(*(*packages)[i]);

						sort_packages->insert( j, package);
						insert = true;
						break;}}

				if (!insert) { Travel_Package* package = new Travel_Package(*(*packages)[i]); sort_packages->insert(0, package);}
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

bool Service::is_digit_or_double(const string& s) const {

	size_t n = s.size();

	if (n == 0) { return false; }

	size_t i;
	bool decimal = true;

	for (i = 0; i < n; i++) {
		if (!isdigit(s[i])) {
			if (s[i] != '.') {
				return false;
			}

			else if (s[i] == '.' && decimal) {
				decimal = false;
			}
			else {
				return false;
			}
		}
	}

	return true;
}

double Service::convert_char_to_double(const string& s)const {

	size_t n = s.size();
	int nr_low = 0;
	int nr_hi = 0;
	int ten = 0;

	size_t i;
	bool decimal = true;

	for (i = 0; i < n; i++) {

		if (s[i] == '.') {

			decimal = false;
		}
		else if (decimal) {

			nr_hi = nr_hi * 10 + (s[i] - '0');
		}
		else if (!decimal) {

			nr_low = nr_low * 10 + (s[i] - '0');
			ten++;
		}

	}
	return nr_hi + (nr_low / pow(10, ten));

}

Travel_Package* Service::search_service(int id) {

	return repository.search(id);
}