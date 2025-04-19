#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <iostream>
using std::string;

class Validator {

public:

	bool validate_attributes_for_travel_package(int id, const string& name, const string& destination, const string& type, double price) const;

	bool validate_id_for_travel_package(int id) const;

	bool validate_string_attributes_for_travel_package(const string& s) const;

};

#endif