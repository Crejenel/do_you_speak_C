#include "validator.h"
#include <iostream>
#include <cctype>  
#include <algorithm> 
#include <string>
using std::string;
using std::any_of;

/*
* The function validates the attributes of a travel package, ensuring that each attribute meets the required conditions.
* >> Input:
*    - id (int): The ID of the travel package to validate.
*    - name (string): The name of the travel package.
*    - destination (string): The destination of the travel package.
*    - type (string): The type of the travel package.
*    - price (double): The price of the travel package.
* >> Output:
*    - Returns `true` if all attributes are valid, `false` otherwise.
* >> Behavior:
*    1. The function first checks if the ID is within the valid range (between 100 and 999).
*    2. Then, it checks if the `name`, `destination`, and `type` strings are not empty and do not contain any digits.
*    3. It ensures that the `price` is greater than zero.
*    4. If all conditions are satisfied, the function returns `true`; otherwise, it returns `false`.
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
* The function validates if a given travel package ID is within the valid range (between 100 and 999).
* >> Input:
*    - id (int): The ID of the travel package to validate.
* >> Output:
*    - Returns `true` if the ID is within the valid range, `false` otherwise.
* >> Behavior:
*    1. The function checks if the `id` is between 100 and 999 (inclusive).
*    2. If the ID is within this range, it returns `true`; otherwise, it returns `false`.
*/
bool Validator::validate_id_for_travel_package(int id) const {

	if (id <= 99 || id >= 1000) {
		return false;
	}
	return true;

}

/*
* The function validates if a given string attribute does not contain any digits and is not empty.
* >> Input:
*    - s (string): The string attribute to validate.
* >> Output:
*    - Returns `true` if the string is non-empty and does not contain any digits, `false` otherwise.
* >> Behavior:
*    1. The function checks if the string is empty or if it contains any digits using `any_of` with `isdigit`.
*    2. If the string is non-empty and contains no digits, it returns `true`; otherwise, it returns `false`.
*/
bool Validator::validate_string_attributes_for_travel_package(const string& s) const {

	if (s.empty() || any_of(s.begin(), s.end(), ::isdigit)) {
		return false;
	}
	return true;

}