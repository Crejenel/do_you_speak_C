#ifndef TRAVEL_PACKAGE_H
#define TRAVEL_PACKAGE_H
#include <iostream>
using std::string;

class Travel_Package {

private:

	int id;
	string name;
	string destination;
	string type;
	double price;

public:

	int get_id() const;
	string get_name() const;
	string get_destination() const;
	string get_type() const;
	double get_price() const;

	void set_id(const int new_id);
	void set_name(const string& new_name);
	void set_destination(const string& new_destination);
	void set_type(const string& new_type);
	void set_price(const double new_price);

	string to_html() const;

	Travel_Package(int id, const string& name, const string& destination, const string& type, double price);

	Travel_Package() : id(0), name(""), destination(""), type(""), price(0) {};

	Travel_Package(const Travel_Package& other);

	Travel_Package& operator=(const Travel_Package& other);

	~Travel_Package();

};

#endif 