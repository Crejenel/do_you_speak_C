#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <iostream>
#include <vector>
#include "domain.h"
using std::vector;
using std::string;

class Repository {

//private atributes of the class
private:

	vector <Travel_Package> packages;

//public methods of the class
public:

	string add_to_repository_container(Travel_Package &package);

	string remove_from_repository_container(int id);

	string update_package_from_repository_container(int id, const string& name, const string& destination, const string& type, double price);

	const vector<Travel_Package>& get_all_packages_from_repository_container() const;
	
	Travel_Package& search(int id);

//private methods of the class
private:

	bool check_object_uniqueness(int id);

	int get_the_index_for_package(int id);
};

#endif