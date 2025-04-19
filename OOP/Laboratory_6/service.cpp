#include "domain.h"
#include "repository.h"
#include "validator.h"
#include "service.h"
using std::string;
using std::vector;

/*
* The constructor initializes a Service object with a reference to a repository and a validator.
* >> Input:
*    - repository (Repository&): A reference to the repository that manages travel packages.
*    - validator (Validator&): A reference to the validator used for input validation.
* >> Output:
*    - None (Constructor).
*/
Service::Service(Repository& repository, Validator& validator)
	: repository(repository), validator(validator) {}

/*
* The function adds a new travel package to the repository after validating its attributes.
* >> Input:
*    - id (int): The unique identifier of the travel package.
*    - name (const string&): The name of the travel package.
*    - destination (const string&): The destination of the travel package.
*    - type (const string&): The type/category of the travel package.
*    - price (double): The price of the travel package.
* >> Output:
*    - A string indicating the result of the operation:
*      - Returns the result of `repository.add_to_repository_container(package)` if validation is successful.
*      - "#992" if validation fails.
*/
string Service::add_package(int id, const string &name, const string &destination, const string &type, double price) {

	if (validator.validate_attributes_for_travel_package(id, name, destination, type, price)) {

		Travel_Package package(id, name, destination, type, price);
		return repository.add_to_repository_container(package);}

	else {

		return "#992";
	}

}

/*
* The function removes a travel package from the repository after validating the ID.
* >> Input:
*    - id (int): The unique identifier of the travel package to be deleted.
* >> Output:
*    - A string indicating the result of the operation:
*      - Returns the result of `repository.remove_from_repository_container(id)` if validation is successful.
*      - "#990" if validation fails.
*/
string Service::delete_package(int id) {

	if (validator.validate_id_for_travel_package(id)) {

		return repository.remove_from_repository_container(id);

	}
	return "#990";
}

/*
* The function updates the details of a travel package in the repository after validating the ID and attributes from the input string.
* >> Input:
*    - id (int): The unique identifier of the travel package to be updated.
*    - update (const string&): A string containing the fields to update in the format "field:value;field:value".
* >> Output:
*    - A string indicating the result of the operation:
*      - Returns the result of `repository.update_package_from_repository_container(id, name, destination, type, price)` if the ID is valid and updates are successful.
*      - "#988" if the input string contains invalid or unrecognized fields.
*      - "#990" if the ID validation fails.
*/
string Service::update_package(int id, const string& update) {

	if (validator.validate_id_for_travel_package(id)) {

		// the variable where the new data for a package is stored
		string name = "";
		string destination = "";
		string type = "";
		double price = 0.0;

		// the variabile we need to split the update string
		string copy_update = update;
		vector<string> result;
		string delimiters = ";:";
		size_t start = 0, end;


		// the actual splitting
		while ((end = copy_update.find_first_of(delimiters, start)) != string::npos) {

			string fragment = copy_update.substr(start, end - start);
			size_t first = fragment.find_first_not_of(" "); 
			size_t last = fragment.find_last_not_of(" ");

			if (first != string::npos) {
				fragment = fragment.substr(first, last - first + 1);
			}
			else {
				fragment = "";
			}

			result.push_back(fragment);
			start = end + 1;
		}

		if (start < copy_update.length()) {

			string fragment = copy_update.substr(start);
			size_t first = fragment.find_first_not_of(" ");
			size_t last = fragment.find_last_not_of(" ");
			if (first != string::npos) {

				fragment = fragment.substr(first, last - first + 1);
			}
			else {

				fragment = "";
			}

			result.push_back(fragment);
		}

		// hendle the result
		for (size_t i = 0; i < result.size(); i++) {

			if (result[i] == "name" && (i + 1)<result.size() && validator.validate_string_attributes_for_travel_package(result[i+1]))
			{
				name = result[i + 1];
				i++;
			}
			else if(result[i]=="destination" && (i+1)<result.size() && validator.validate_string_attributes_for_travel_package(result[i + 1])) {

				destination = result[i + 1];
				i++;
			} 
			else if (result[i] == "type" && (i + 1)< result.size() && validator.validate_string_attributes_for_travel_package(result[i + 1])) {

				type = result[i + 1];
				i++;
			} 
			else if (result[i] == "price" && (i + 1) < result.size() && result[i + 1] != "" && is_digit_or_double(result[i + 1])) {

				double nr = convert_char_to_double(result[i + 1]);
				price = nr;
				i++;
				
			}
			else {
				return "#988";
			}
		}

		// give away to repository
		return repository.update_package_from_repository_container(id, name, destination, type, price);
			

	}
	return "#990";

}

/*
* The function retrieves all travel packages from the repository.
* >> Input:
*    - None.
* >> Output:
*    - A constant reference to a vector containing all travel packages in the repository.
*/
const vector<Travel_Package>& Service::get_all_packages() {

	return repository.get_all_packages_from_repository_container();
}

/*
* The function filters travel packages based on a specified criterion (destination or price) and stores the filtered packages in the provided vector.
* >> Input:
*    - filter_packages (vector<Travel_Package>&): A reference to a vector where the filtered travel packages will be stored.
*    - filter (const string&): A string containing the filter criterion in the format "criterion:value".
* >> Output:
*    - A string indicating the result of the operation:
*      - "#993" if the filter was applied successfully and the matching packages were found.
*      - "#986" if the filter criterion is invalid or the format is incorrect.
*/
const string Service::filter_packages(vector < Travel_Package > &filter_packages, const string &filter) {

	string criterion = "";
	string filter_copy = filter;

	vector<string> result;
	string delimiters = ":";
	size_t start = 0, end;

	while ((end = filter_copy.find_first_of(delimiters, start)) != string::npos) {

		string fragment = filter_copy.substr(start, end - start);
		size_t first = fragment.find_first_not_of(" ");
		size_t last = fragment.find_last_not_of(" ");

		if (first != string::npos) {
			fragment = fragment.substr(first, last - first + 1);
		}
		else {
			fragment = "";
		}

		result.push_back(fragment);
		start = end + 1;
	}

	if (start < filter_copy.length()) {

		string fragment = filter_copy.substr(start);
		size_t first = fragment.find_first_not_of(" ");
		size_t last = fragment.find_last_not_of(" ");
		if (first != string::npos) {

			fragment = fragment.substr(first, last - first + 1);
		}
		else {

			fragment = "";
		}

		result.push_back(fragment);
	}

	const vector < Travel_Package > &packages = repository.get_all_packages_from_repository_container();

	if (result.size() == 1) {
		return "#986";
	}

	if (result[0] == "destination") {
		for (size_t i = 0; i < packages.size(); i++) {
			if (packages[i].get_destination() == result[1]) {
				filter_packages.push_back(packages[i]);
			}
		}
		return "#993";
	}
	
	if (result[0] == "price") {

		if (is_digit_or_double(result[1])) {

			double price = convert_char_to_double(result[1]);

			for (size_t i = 0; i < packages.size(); i++) {
				if (packages[i].get_price() <= price) {
					filter_packages.push_back(packages[i]);
				}
			}
			return "#993";}
		else {
			return "#986";
		}
	}

	return "#986";
}

/*
* The function sorts travel packages based on a specified criterion (destination or price) in either ascending or descending order and stores the sorted packages in the provided vector.
* >> Input:
*    - sort_packages (vector<Travel_Package>&): A reference to a vector where the sorted travel packages will be stored.
*    - sort (const string&): A string containing the sorting criterion and order in the format "criterion:order" (e.g., "destination:ascending").
* >> Output:
*    - A string indicating the result of the operation:
*      - "#991" if the packages were successfully sorted.
*      - "#984" if the sorting criterion or order is invalid.
*/
const string Service::sort_packages(vector < Travel_Package >& sort_packages, const string& sort) {

	string criterion = "";
	string sort_copy = sort;
	bool insert;

	vector<string> result;
	string delimiters = ":";
	size_t start = 0, end;

	while ((end = sort_copy.find_first_of(delimiters, start)) != string::npos) {

		string fragment = sort_copy.substr(start, end - start);
		size_t first = fragment.find_first_not_of(" ");
		size_t last = fragment.find_last_not_of(" ");

		if (first != string::npos) {
			fragment = fragment.substr(first, last - first + 1);
		}
		else {
			fragment = "";
		}

		result.push_back(fragment);
		start = end + 1;
	}

	if (start < sort_copy.length()) {

		string fragment = sort_copy.substr(start);
		size_t first = fragment.find_first_not_of(" ");
		size_t last = fragment.find_last_not_of(" ");
		if (first != string::npos) {

			fragment = fragment.substr(first, last - first + 1);
		}
		else {

			fragment = "";
		}

		result.push_back(fragment);
	}

	const vector < Travel_Package >& packages = repository.get_all_packages_from_repository_container();

	if (result.size() == 1) {
		return "#984";
	}

	if (result[0] == "destination") {

		if (result[1] == "ascending")
		{
			for (size_t i = 0; i < packages.size(); i++) {

				insert = false;

				if (sort_packages.empty()) {
					sort_packages.push_back(packages[i]);
					continue;
				}

				for (size_t j = sort_packages.size(); j > 0; j--) {
					if (packages[i].get_destination() >= sort_packages[j - 1].get_destination()) {
						sort_packages.insert(sort_packages.begin() + j, packages[i]);
						insert = true;
						break;
					}
				}

				if (!insert) {
					sort_packages.insert(sort_packages.begin(), packages[i]);
				}
			}
			return "#991";}

		else if (result[1] == "descending") {

			for (size_t i = 0; i < packages.size(); i++) {

				insert = false;

				if (sort_packages.empty()) {
					sort_packages.push_back(packages[i]);
					continue;
				}

				for (size_t j = sort_packages.size(); j > 0; j--) {
					if (packages[i].get_destination() <= sort_packages[j - 1].get_destination()) {
						sort_packages.insert(sort_packages.begin() + j, packages[i]);
						insert = true;
						break;
					}
				}

				if (!insert) {
					sort_packages.insert(sort_packages.begin(), packages[i]);
				}
			}
			return "#991";
		}
		
	}

	if (result[0] == "price") {

		if (result[1] == "ascending")
		{
			for (size_t i = 0; i < packages.size(); i++) {
				insert = false;

				if (sort_packages.empty()) {
					sort_packages.push_back(packages[i]);
					continue;
				}

				for (size_t j = sort_packages.size(); j > 0; j--) {
					if (packages[i].get_price() >= sort_packages[j - 1].get_price()) {
						sort_packages.insert(sort_packages.begin() + j, packages[i]);
						insert = true;
						break;
					}
				}

				if (!insert) {
					sort_packages.insert(sort_packages.begin(), packages[i]);
				}
			}
			return "#991";
		}
		else if (result[1] == "descending") {

			for (size_t i = 0; i < packages.size(); i++) {
				insert = false;

				if (sort_packages.empty()) {
					sort_packages.push_back(packages[i]);
					continue;
				}

				for (size_t j = sort_packages.size(); j > 0; j--) {
					if (packages[i].get_price() <= sort_packages[j - 1].get_price()) {
						sort_packages.insert(sort_packages.begin() + j, packages[i]);
						insert = true;
						break;
					}
				}

				if (!insert) {
					sort_packages.insert(sort_packages.begin(), packages[i]);
				}
			}
			return "#991";

		}
		return "#984";
	}

	return "#984";

}

/*
* The function checks if a given string represents a valid number (either an integer or a decimal).
* >> Input:
*    - s (const string&): The string to be checked.
* >> Output:
*    - A boolean value:
*      - true if the string is a valid integer or decimal number.
*      - false if the string is not a valid number.
*/
bool Service::is_digit_or_double(const string &s) const {

	size_t n = s.size();

	if (n == 0) { return false; }

	size_t i;
	bool decimal = true;

	for (i = 0; i < n; i++) {
		if (!isdigit(s[i])) {
			if (s[i] != '.') {
				return false;}

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

/*
* The function converts a string representing a number to a double.
* >> Input:
*    - s (const string&): The string to be converted to a double.
* >> Output:
*    - A double value representing the numerical value of the string.
*      - Returns the corresponding double value after converting the string (including handling decimal points).
*/
double Service::convert_char_to_double(const string &s)const {

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

Travel_Package& Service::search_service(int id) {

	return repository.search(id);
}
