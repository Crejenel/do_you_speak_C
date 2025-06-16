#ifndef WISHLIST_H
#define WISHLIST_H
#include "container.h"
#include "domain.h"
#include "observable.h"
#include <map>
using std::string;
using std::multimap;

class Wishlist : public Observable {

private:

	Inventory<Travel_Package>* favorites;

	std::multimap<string, Travel_Package*> wishlist_map;


public:

	Wishlist();

	void add_to_wishlist(Travel_Package* travel_package);

	void delete_from_wishlist(int id);

	const Inventory<Travel_Package>* get_wishlist() const;

	void generate_wishlist(int number, const Inventory<Travel_Package>* travel_packages);

	void export_wishlist(const string& file_name);

	const multimap<string, Travel_Package*>* get_wishlist_map() const;

	~Wishlist();
};


#endif