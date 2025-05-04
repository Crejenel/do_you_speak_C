#include "validator.h"
#include <iostream>
#include <cctype>  
#include <algorithm> 
#include <string>
using std::string;
using std::any_of;

/*
* The function validates the attributes for a travel package, ensuring that all fields meet the specified criteria.
* >> Input:
*    - id (int): The ID of the travel package.
*    - name (const string&): The name of the travel package.
*    - destination (const string&): The destination of the travel package.
*    - type (const string&): The type of the travel package.
*    - price (double): The price of the travel package.
* >> Output:
*    - A boolean value:
*      - true if all attributes are valid.
*      - false if any attribute is invalid.
* >> Validation Rules:
*    - ID must be a three-digit number (100-999).
*    - Name, destination, and type must not be empty or contain digits.
*    - Price must be greater than 0.0.
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
* The function validates the ID for a travel package to ensure it is a valid three-digit number.
* >> Input:
*    - id (int): The ID to be validated.
* >> Output:
*    - A boolean value:
*      - true if the ID is a valid three-digit number (between 100 and 999 inclusive).
*      - false if the ID is not a valid three-digit number.
* >> Validation Rule:
*    - The ID must be a three-digit integer (greater than or equal to 100 and less than or equal to 999).
*/
bool Validator::validate_id_for_travel_package(int id) const {

	if (id <= 99 || id >= 1000) {
		return false;
	}
	return true;

}

/*
* The function validates that a string attribute (such as name, destination, or type) is not empty and does not contain digits.
* >> Input:
*    - s (const string&): The string attribute to be validated.
* >> Output:
*    - A boolean value:
*      - true if the string is valid (not empty and does not contain digits).
*      - false if the string is empty or contains digits.
*/
bool Validator::validate_string_attributes_for_travel_package(const string& s) const {

	if (s.empty() || any_of(s.begin(), s.end(), ::isdigit)) {
		return false;
	}
	return true;

}