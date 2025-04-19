#include "tests.h"
#include "domain.h"
#include <iostream>
#include <string>
#include <assert.h>
#include <stdlib.h>
#include <vector>
using std::cout;
using std::endl;

Tests::Tests(Service &service) 
	: service(service){}

void Tests::test_add(){
	
	string code;
	code = service.add_package(111, "Mult soare!", "Mamaia", "Pachet de familie", 4999.99);
	assert(code == "#999");

	code = service.add_package(111, "O noapte de groaza", "Hotelul Vampirului", "Individual", 359.99);
	assert(code == "#998");

	code = service.add_package(11, "O noapte de groaza", "Hotelul Vampirului", "Individual", 359.99);
	assert(code == "#992");

	code = service.add_package(111, "O no4pte de gr39aza", "Hotelul Vampirului", "Individual", 359.99);
	assert(code == "#992");

	code = service.add_package(111, "O noapte de groaza", "Ho9elul Vam5iru0ui", "Individual", 359.99);
	assert(code == "#992");

	code = service.add_package(111, "O noapte de groaza", "Hotelul Vampirului", "Indi3vi7ual", 359.99);
	assert(code == "#992");

	code = service.add_package(111, "O noapte de groaza", "Hotelul Vampirului", "Individual", -120);
	assert(code == "#992");

}

void Tests::test_delete() {

	string code;
	code = service.add_package(222, "O noapte de groaza", "Hotelul Vampirului", "Individual", 359.99);
	assert(code == "#999");

	code = service.add_package(333, "Muntele Alb", "Muntele Everest", "Pentru doi", 6700);
	assert(code == "#999");

	code = service.delete_package(333);
	assert(code == "#997");

	code = service.delete_package(33);
	assert(code == "#990");

	code = service.delete_package(333);
	assert(code == "#996");


}

void Tests::test_update() {

	string code;
	code = service.add_package(333, "Muntele Alb", "Muntele Everest", "Pentru doi", 6700);
	assert(code == "#999");

	code = service.update_package(333, "name : Frumusetile Dunarii; destination : Delta Dunarii; type : Pachet de familie; price : 8999.99");
	assert(code == "#995");

	code = service.update_package(333, " name : destination : Muntele Everest");
	assert(code == "#988");

	code = service.update_package(444, "name : Muntele Alb");
	assert(code == "#994");

	code = service.update_package(44, "name : Muntele Alb");
	assert(code == "#990");

	code = service.update_package(333, " price : abc");
	assert(code == "#988");

	code = service.update_package(333, " price : 1.2.3");
	assert(code == "#988");

	code = service.update_package(333, ";");
	assert(code == "#988");

	code = service.update_package(333, " name : ");
	assert(code == "#988");


	
}

void Tests::test_get() {

	string code;
	code = service.add_package(444, "Muntele Alb", "Muntele Everest", "Pentru doi", 6700);
	assert(code == "#999");

	const vector <Travel_Package>& packages = service.get_all_packages();
	assert(packages.size() == 4);

	assert(packages[0].get_id() == 111);
	assert(packages[1].get_destination() == "Hotelul Vampirului");
	assert(packages[2].get_name() == "Frumusetile Dunarii");
	assert(packages[3].get_price() == 6700);

}

void Tests::test_filter() {

	string code;
	code = service.add_package(555, "Muntele Alb", "Muntele Everest", "Pachet de failie", 12999.99);
	assert(code == "#999");

	vector <Travel_Package> filter_packages;
	service.filter_packages(filter_packages, "price : 500");

	assert(filter_packages.size() == 1);
	assert(filter_packages[0].get_id() == 222);
	filter_packages.clear();

	service.filter_packages(filter_packages, "destination : Muntele Everest");
	assert(filter_packages.size() == 2);
	assert(filter_packages[0].get_id() == 444);
	assert(filter_packages[1].get_id() == 555);
	filter_packages.clear();

	code = service.filter_packages(filter_packages, "price :");
	assert(code == "#986");

	code = service.filter_packages(filter_packages, " ");
	assert(code == "#986");

	code = service.filter_packages(filter_packages, "price: ");
	assert(code == "#986");

	code = service.filter_packages(filter_packages, "type: Packet de familie");
	assert(code == "#986");

	code = service.filter_packages(filter_packages, ":");
	assert(code == "#986");

}

void Tests::test_sort() {

	string code;
	vector <Travel_Package> sort_packages;
	code = service.sort_packages(sort_packages, "destination : ascending");
	assert(code == "#991");
	assert(sort_packages.size() == 5);

	assert(sort_packages[0].get_id() == 333);
	assert(sort_packages[1].get_id() == 222);
	assert(sort_packages[2].get_id() == 111);
	assert(sort_packages[3].get_id() == 444);
	assert(sort_packages[4].get_id() == 555);
	sort_packages.clear();

	code = service.sort_packages(sort_packages, "destination : descending");
	assert(code == "#991");
	assert(sort_packages.size() == 5);

	assert(sort_packages[0].get_id() == 444);
	assert(sort_packages[1].get_id() == 555);
	assert(sort_packages[2].get_id() == 111);
	assert(sort_packages[3].get_id() == 222);
	assert(sort_packages[4].get_id() == 333);
	sort_packages.clear();

	code = service.sort_packages(sort_packages, "price : descending");
	assert(code == "#991");
	assert(sort_packages.size() == 5);

	assert(sort_packages[0].get_id() == 555);
	assert(sort_packages[1].get_id() == 333);
	assert(sort_packages[2].get_id() == 444);
	assert(sort_packages[3].get_id() == 111);
	assert(sort_packages[4].get_id() == 222);
	sort_packages.clear();

	code = service.sort_packages(sort_packages, "price : ascending");
	assert(code == "#991");
	assert(sort_packages.size() == 5);

	assert(sort_packages[0].get_id() == 222);
	assert(sort_packages[1].get_id() == 111);
	assert(sort_packages[2].get_id() == 444);
	assert(sort_packages[3].get_id() == 333);
	assert(sort_packages[4].get_id() == 555);
	sort_packages.clear();

	code = service.sort_packages(sort_packages, "price");
	assert(code == "#984");
	code = service.sort_packages(sort_packages, "ascending : price");
	assert(code == "#984");
	code = service.sort_packages(sort_packages, "price : 123");
	assert(code == "#984");
	code = service.sort_packages(sort_packages, " ");
	assert(code == "#984");
	code = service.sort_packages(sort_packages, ":");
	assert(code == "#984");


}

void Tests::test_domain() {

	Travel_Package package(111, "Magic Asia", "Tokyo", "Pentru doi", 3999.99);
	assert(package.get_type() == "Pentru doi");

	cout << package;
	system("cls");

	Travel_Package& p = service.search_service(111);
	assert(p.get_id() == 111);
	p = service.search_service(999);

}

void Tests::run_all_tests() {

	test_add();
	test_delete();
	test_update();
	test_get();
	test_filter();
	test_sort();
	test_domain();
	cout<< "<<\033[32mALL THE TESTS PASSED! \033[0m>>" << endl;
}
