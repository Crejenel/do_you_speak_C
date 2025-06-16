#include "domain.h"
#include <iostream>
#include <string>
using std::string;

int Travel_Package::get_id() const { return id; }
string Travel_Package::get_name() const { return name; }
string Travel_Package::get_destination() const { return destination; }
string Travel_Package::get_type() const { return type; }
double Travel_Package::get_price() const { return price; }

void Travel_Package::set_id(const int new_id) { id = new_id; }
void Travel_Package::set_name(const string& new_name) { name = new_name; }
void Travel_Package::set_destination(const string& new_destination) { destination = new_destination; }
void Travel_Package::set_type(const string& new_type) { type = new_type; }
void Travel_Package::set_price(const double new_price) { price = new_price; }

// Overloading the << operator
std::ostream& operator<<(std::ostream& out, const Travel_Package& package) {
    out << "\033[32mPackage '" << package.id << "'\033[0m >> name : \033[35m" << package.name
        << ";\033[0m destination : \033[35m" << package.destination
        << ";\033[0m type : \033[35m" << package.type
        << ";\033[0m price : \033[35m" << package.price << "\033[0m";
    return out;
}

string Travel_Package::to_html() const {
    return "<tr><td>" + std::to_string(id) + "</td><td>" + name + "</td><td>" + destination + "</td><td>" + type + "</td><td>" + std::to_string(price) + "</td></tr>\n";
}

Travel_Package::Travel_Package(int id, const string& name, const string& destination, const string& type, double price) {
    this->id = id;
    this->name = name;
    this->destination = destination;
    this->type = type;
    this->price = price;
}

Travel_Package::Travel_Package(const Travel_Package& other)
    : id(other.id), name(other.name), destination(other.destination), type(other.type), price(other.price) {
    std::cout << "*";
}

Travel_Package& Travel_Package::operator=(const Travel_Package& other) {
    if (this != &other) {
        id = other.id;
        name = other.name;
        destination = other.destination;
        type = other.type;
        price = other.price;
    }
    return *this;
}

Travel_Package::~Travel_Package() {}