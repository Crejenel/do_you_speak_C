#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <iostream>
#include "domain.h"
#include "container.h"
using std::string;

class Repository {

protected:

	Inventory<Travel_Package>* packages;

public:

	Repository();
	virtual void add_to_repository_container(Travel_Package* package);
	virtual void remove_from_repository_container(int id);
	virtual void update_package_from_repository_container(int id, const string& name, const string& destination, const string& type, double price);
	const Inventory<Travel_Package>* get_all_packages_from_repository_container() const;
	Travel_Package* search(int id);
	~Repository();

protected:

	bool check_object_uniqueness(int id);
	int get_the_index_for_package(int id);
};

class RepositorySAVE : public Repository {

private:

	string FILE;

public:

	RepositorySAVE(const string& name) : FILE(name) { read_from_file(); };

	void add_to_repository_container(Travel_Package* package) override;
	void remove_from_repository_container(int id)override;
	void update_package_from_repository_container(int id, const string& name, const string& destination, const string& type, double price)override;
	void read_from_file();
	void write_on_file();

	~RepositorySAVE() { write_on_file(); }
};

#endif