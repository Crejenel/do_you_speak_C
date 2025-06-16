#include "repository.h"
#include "container.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <exception>
#include <sstream>
#include <string>
using std::string;
using std::ifstream;
using std::ofstream;
using std::exception;
using std::getline;
using std::istringstream;
using std::stoi;
using std::endl;

Repository::Repository() {

	packages = new Inventory<Travel_Package>();
}

void Repository::add_to_repository_container(Travel_Package* package) {

	if (check_object_uniqueness(package->get_id())) {

		packages->add(package);
	}
	else {

		throw ExceptionRepository("package already exists in repository");
	}
}

void Repository::remove_from_repository_container(int id) {

	if (!check_object_uniqueness(id)) {

		int index = get_the_index_for_package(id);

		if (index != -1) {

			packages->remove(index);
		}
	}
	else {

		throw ExceptionRepository("package not found in repository");
	}

}

void Repository::update_package_from_repository_container(int id, const string& name, const string& destination, const string& type, double price) {

	int index = get_the_index_for_package(id);
	if (index != -1) {

		if (name != "") {
			(*packages)[index]->set_name(name);
		}
		if (destination != "") {
			(*packages)[index]->set_destination(destination);
		}
		if (type != "") {
			(*packages)[index]->set_type(type);
		}
		if (price != 0.0) {
			(*packages)[index]->set_price(price);
		}
	}
	else {
		throw ExceptionRepository("package not found in repository");
	}
}

const Inventory<Travel_Package>* Repository::get_all_packages_from_repository_container() const {
	return packages;
}

bool Repository::check_object_uniqueness(int id) {

	auto it = std::find_if(packages->begin_ascendent(), packages->end_ascendent(), [id](const Travel_Package* pkg) { return pkg->get_id() == id; });
	return it == packages->end_ascendent();
}

int Repository::get_the_index_for_package(int id) {

	auto it = std::find_if(packages->begin_ascendent(), packages->end_ascendent(), [id](const Travel_Package* pkg) { return pkg->get_id() == id; });
	if (it == packages->end_ascendent()) { return -1; }
	else {
		return it.get_index();
	}
}

Travel_Package* Repository::search(int id) {


	for (auto it = packages->begin_ascendent(); it != packages->end_ascendent(); ++it) {
		if ((*it)->get_id() == id) {
			return *it;
		}
	}
	return nullptr;
}

Repository::~Repository() {
	delete packages;
}

void RepositorySAVE::read_from_file() {

	ifstream fin(FILE + ".txt");

	string linie;
	while (getline(fin, linie)) {

		istringstream cuvinte(linie);
		string cuvant;

		Travel_Package* travel_package = new Travel_Package;
		int contor = 0;
		while (cuvinte >> cuvant) {

			if (contor == 0) {
				travel_package->set_id(stoi(cuvant));
				contor++;
			}
			else if (contor == 1) {
				travel_package->set_name(cuvant);
				contor++;
			}
			else if (contor == 2) {
				travel_package->set_destination(cuvant);
				contor++;
			}
			else if (contor == 3) {
				travel_package->set_type(cuvant);
				contor++;
			}
			else if (contor == 4) {
				travel_package->set_price(stod(cuvant));
				contor++;
			}
		}
		add_to_repository_container(travel_package);
	}
	fin.close();
}

void RepositorySAVE::write_on_file() {

	ofstream fout(FILE + ".txt");

	const Inventory<Travel_Package>* Packages = get_all_packages_from_repository_container();

	for (int i = 0; i < Packages->size(); i++) {

		Travel_Package* pkg = (*Packages)[i];
		fout << pkg->get_id() << " "
			<< pkg->get_name() << " "
			<< pkg->get_destination() << " "
			<< pkg->get_type() << " "
			<< pkg->get_price() << "\n";
	}

	fout.close();

}