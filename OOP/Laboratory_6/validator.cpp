#include "validator.h"
#include <iostream>
#include <cctype>  
#include <algorithm> 
#include <string>
using std::string;
using std::any_of;

/*
* The function validates the attributes of a travel package to ensure they meet the required criteria.
* >> Input:
*    - id (int): The unique identifier of the travel package (must be between 100 and 999).
*    - name (const string&): The name of the travel package (cannot be empty and must not contain digits).
*    - destination (const string&): The destination of the travel package (cannot be empty and must not contain digits).
*    - type (const string&): The type of the travel package (cannot be empty and must not contain digits).
*    - price (double): The price of the travel package (must be greater than 0).
* >> Output:
*    - A boolean value:
*      - true if all attributes are valid.
*      - false if any attribute fails the validation checks.
*/
bool Validator::validate_attributes_for_travel_package(int id, const string& name, const string& destination, const string& type, double price) const {

	if (id <= 99 || id >= 1000) {
		return false;
	}
	if (name.empty() || any_of(name.begin(), name.end(), ::isdigit)) {
		return false;
	}
	if (destination.empty() || any_of(destination.begin(), destination.end(), ::isdigit)) {
		return false;
	}
	if (type.empty() || any_of(type.begin(), type.end(), ::isdigit)) {
		return false;
	}
	if (price <= 0.0) {
		return false;
	}
	return true;
}

/*
* The function validates the ID of a travel package to ensure it is within the valid range (100 to 999).
* >> Input:
*    - id (int): The unique identifier of the travel package.
* >> Output:
*    - A boolean value:
*      - true if the ID is valid (between 100 and 999, inclusive).
*      - false if the ID is outside the valid range.
*/
bool Validator::validate_id_for_travel_package(int id) const {

	if (id <= 99 || id >= 1000) {
		return false;
	}
	return true;

}

/*
* The function validates a string attribute of a travel package to ensure it is not empty and does not contain digits.
* >> Input:
*    - s (const string&): The string to be validated.
* >> Output:
*    - A boolean value:
*      - true if the string is non-empty and does not contain digits.
*      - false if the string is empty or contains any digits.
*/
bool Validator::validate_string_attributes_for_travel_package(const string& s) const {

	if (s.empty() || any_of(s.begin(), s.end(), ::isdigit)) {
		return false;
	}
	return true;

}
