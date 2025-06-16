#include "validator.h"
#include <iostream>
#include <cctype>  
#include <algorithm> 
#include <string>
using std::string;
using std::any_of;

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

bool Validator::validate_id_for_travel_package(int id) const {

	if (id <= 99 || id >= 1000) {
		return false;
	}
	return true;

}

bool Validator::validate_string_attributes_for_travel_package(const string& s) const {

	if (s.empty() || any_of(s.begin(), s.end(), ::isdigit)) {
		return false;
	}
	return true;

}