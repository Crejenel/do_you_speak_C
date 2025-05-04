#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include <vector>
#include "tests.h"
#include "repository.h"
#include "service.h"
#include "validator.h"
#include "interface.h"
#include "wishlist.h"
using std::cout;
using std::endl;

template <typename MyVector>
void addTravel_Package(MyVector& v, int cate) {

	for (int i = 0; i < cate; i++) {

		Travel_Package* tp = new Travel_Package{ i, std::to_string(i) + "_name",std::to_string(i) + "_destination", std::to_string(i) + "_type", i + 10.0 };
		v.add(tp);
	}
}

template <typename MyVector>
MyVector testCopyIterate(MyVector& v) {

	double totalPrice = 0;

	for (auto it = v.begin_ascendent(); it != v.end_ascendent(); ++it) {
		totalPrice += (*it)->get_price();
	}

	Travel_Package* p = new Travel_Package{ 100, "100_name", "100_destination", "100_type", totalPrice };
	v.add(p);

	assert(totalPrice == 5950.0);
	return v;
}

template <typename MyVector>
void testCreateCopyAssign() {

	MyVector v;//default constructor
	addTravel_Package(v, 100);
	assert(v.size() == 100);
	assert(v.get(50)->get_type() == "50_type");

	MyVector v2{ v };//constructor de copiere
	assert(v2.size() == 100);
	assert(v2.get(50)->get_type() == "50_type");

	MyVector v3;//default constructor
	v3 = v;//operator=   assignment
	assert(v3.size() == 100);
	assert(v3.get(50)->get_type() == "50_type");

	auto v4 = testCopyIterate(v3);
	assert(v4.size() == 101);
	assert(v4.get(50)->get_type() == "50_type");
}

template <typename MyVector>
void testAll() {

	Inventory<Travel_Package> v;
	addTravel_Package(v, 100);
	assert(v.size() == 100);
	testCopyIterate<Inventory<Travel_Package>>(v);
	testCreateCopyAssign<Inventory<Travel_Package>>();

}

void play() {

	QualityAssurance quality_assurance;
	quality_assurance.test_all();

	Repository repository;
	Validator validator;
	Wishlist wishlist;
	Service service(repository, validator);
	UI ui(service,wishlist);
	ui.run();
}


int main() {


	testAll<Inventory<Travel_Package>>();
	play();
	if (_CrtDumpMemoryLeaks()) { cout << "Memory leaks detected!" << endl; }
	else {
		cout << "No memory leaks detected!" << endl;
	}

	return 0;
}

