#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include <iostream>
#include <vector>
#include "service.h"


class UI {

private:

	Service& service;

public:

	UI(Service& service);

	void run();

private:

	void display_the_menu() const;

	bool verify_type_of_input(vector <bool>& verify) const;

};

#endif