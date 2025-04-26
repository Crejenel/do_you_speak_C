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

	//the getters
	int get_id() const;
	string get_name() const;
	string get_destination() const;
	string get_type() const;
	double get_price() const;

	//the setters
	void set_name(const string& new_name);
	void set_destination(const string& new_destination);
	void set_type(const string& new_type);
	void set_price(const double new_price);

	//Overloading the << operator for output
	friend std::ostream& operator<<(std::ostream& out, const Travel_Package& package);

	//the constructer
	Travel_Package(int id, const string& name, const string& destination, const string& type, double price);

	Travel_Package(const Travel_Package& other);

	Travel_Package& operator=(const Travel_Package& other);

	~Travel_Package();

};

#endif 