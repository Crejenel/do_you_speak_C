#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include <iostream>
#include "container.h"
#include "service.h"
#include "wishlist.h"


class UI {

private:

	Service& service;

	Wishlist& wishlist;

public:

	UI(Service& service, Wishlist &wishlist);

	void run();

private:

	void display_the_menu() const;

	bool verify_type_of_input(Inventory<bool>* verify) const;

};

#endif