#include <assert.h>
#include <cstdlib>
#include "tests.h"
#include "container.h"
#include "repository.h"
#include "domain.h"
#include "validator.h"
#include "wishlist.h"
#include "service.h"
#include <vector>
using std::cout;
using std::endl;
using std::move;
using std::vector;

void QualityAssurance::test_undo() {

	Validator validator;
	Repository repository;
	Wishlist wishlist;
	Service service(wishlist, repository, validator);
	service.add_package(111, "a", "p", "c", 1);
	service.add_package(222, "x", "y", "z", 2);
	service.update_package(111, "destination:b");
	service.delete_package(222);

	assert(service.get_all_packages()->size() == 1);
	service.undo();
	assert(service.get_all_packages()->size() == 2);
	service.undo();
	assert(service.search_service(111)->get_destination() == "p");
	service.undo();
	service.undo();
	assert(service.get_all_packages()->size() == 0);
	try {
		service.undo();

	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "No action to undo!");
	}
}

void QualityAssurance::test_domain() {

	Travel_Package travel_package(1, "Paris", "France", "luxurious", 1000);

	assert(travel_package.get_id() == 1);
	assert(travel_package.get_name() == "Paris");
	assert(travel_package.get_destination() == "France");
	assert(travel_package.get_type() == "luxurious");
	assert(travel_package.get_price() == 1000);

	travel_package.set_name("London");
	travel_package.set_destination("UK");
	travel_package.set_type("luxurious");
	travel_package.set_price(1200);

	Travel_Package travel_package2(0, "", "", "", 0);
	travel_package2 = travel_package;
	assert(travel_package2.get_id() == 1);
	assert(travel_package2.get_name() == "London");
	assert(travel_package2.get_destination() == "UK");
	assert(travel_package2.get_type() == "luxurious");
	assert(travel_package2.get_price() == 1200);

	Travel_Package travel_package3(travel_package);
	assert(travel_package3.get_id() == 1);
	assert(travel_package3.get_name() == "London");
	assert(travel_package3.get_destination() == "UK");
	assert(travel_package3.get_type() == "luxurious");
	assert(travel_package3.get_price() == 1200);
}

void QualityAssurance::test_container() {


	Inventory<int> inventory;
	for (int i = 1; i <= 5; i++) {
		inventory.add(new int(i));
	}
	assert(inventory.size() == 5);
	inventory.add(new int(6));

	for (int i = 8; i <= 11; i++) {
		inventory.add(new int(i));
	}
	assert(inventory.size() == 10);
	inventory.insert(6, new int(7));
	assert(inventory.size() == 11);

	int j = 0;
	for (int i = 11; i > 0; i--) {
		inventory.set(j++, new int(i));
	}

	Inventory<int> inventory2(inventory);
	assert(inventory2.size() == 11);

	j = 11;
	for (auto it = inventory2.begin_ascendent(); it != inventory2.end_ascendent(); ++it) {
		assert(*(*it) == j--);
	}

	assert(inventory[0] != inventory2[0]);
	assert(*inventory[0] == *inventory2[0]);

	inventory.remove(0);
	assert(inventory.size() == 10);

	Inventory<int> inventory3(5);
	for (int i = 1; i <= 5; i++) {
		inventory3.add(new int(i));
	}
	inventory3 = inventory2;
	assert(inventory3.size() == 11);

	j = 11;
	for (auto it = inventory3.begin_ascendent(); it != inventory3.end_ascendent(); ++it) {
		assert(*(*it) == j--);
	}

	Inventory<int> inventory4(std::move(inventory3));

	try {
		inventory3.remove(0); assert(false);
	}
	catch (ExceptionContainer& e) {
		assert(e.get_message() == "Index out of range");
	}

	try {
		inventory3.insert(1, new int(1)); assert(false);
	}
	catch (ExceptionContainer& e) {

		assert(e.get_message() == "Index out of range");
	}

	assert(inventory4.size() == 11);

	try {
		inventory4.get(20); assert(false);
	}
	catch (ExceptionContainer& e) {
		assert(e.get_message() == "Index out of range");
	}

	try {
		inventory4[-1]; assert(false);
	}
	catch (ExceptionContainer& e) {
		assert(e.get_message() == "Index out of range");
	}

	Inventory <int> inventory5(-5);

	inventory5 = std::move(inventory4);

	j = 1;
	for (auto it = inventory5.begin_descendent(); it != inventory5.end_descendent(); ++it) {
		assert(*(*it) == j++);
	}

	try {
		inventory5.add(nullptr); assert(false);
	}
	catch (ExceptionContainer& e) {
		assert(e.get_message() == "connot add a null pointer in container");
	}

	try {
		inventory5.set(0, nullptr); assert(false);
	}
	catch (ExceptionContainer& e) {
		assert(e.get_message() == "connot add a null pointer in container");
	}

	try {
		inventory5.insert(0, nullptr); assert(false);
	}
	catch (ExceptionContainer& e) {
		assert(e.get_message() == "connot add a null pointer in container");
	}
	inventory5.clear();

}

void QualityAssurance::test_repository() {

	Repository repository;

	Travel_Package* travel_package1 = new Travel_Package(1, "Paris", "France", "luxurious", 1000);
	Travel_Package* travel_package2 = new Travel_Package(2, "London", "UK", "luxurious", 1200);
	Travel_Package* travel_package3 = new Travel_Package(3, "Rome", "Italy", "luxurious", 800);
	Travel_Package* travel_package4 = new Travel_Package(4, "Berlin", "Germany", "luxurious", 900);

	repository.add_to_repository_container(travel_package1);
	repository.add_to_repository_container(travel_package2);
	repository.add_to_repository_container(travel_package3);
	repository.add_to_repository_container(travel_package4);

	try {
		repository.add_to_repository_container(travel_package1); assert(false);
	}
	catch (ExceptionRepository& e) {
		assert(e.get_message() == "package already exists in repository");
	}

	try {
		repository.remove_from_repository_container(5); assert(false);
	}
	catch (ExceptionRepository& e) {
		assert(e.get_message() == "package not found in repository");
	}

	repository.remove_from_repository_container(1);
	assert(repository.search(1) == nullptr);

	repository.update_package_from_repository_container(2, "New York", "America", "luxurious", 3999.99);
	assert(repository.search(2)->get_name() == "New York");
	assert(repository.search(2)->get_destination() == "America");
	assert(repository.search(2)->get_type() == "luxurious");
	assert(repository.search(2)->get_price() == 3999.99);

	try {
		repository.update_package_from_repository_container(5, "New York", "America", "luxurious", 3999.99); assert(false);
	}
	catch (ExceptionRepository& e) {
		assert(e.get_message() == "package not found in repository");
	}

	const Inventory<Travel_Package>* packages = repository.get_all_packages_from_repository_container();
	assert(packages->size() == 3);
}

void QualityAssurance::test_validator() {

	Validator validator;

	assert(validator.validate_attributes_for_travel_package(1, "Paris", "France", "luxurious", 1000) == false);
	assert(validator.validate_attributes_for_travel_package(100, "Paris", "France", "luxurious", 1000) == true);

	assert(validator.validate_attributes_for_travel_package(100, "Paris", "France", "luxurious", -1000) == false);
	assert(validator.validate_attributes_for_travel_package(100, "Paris", "France", "luxurious", 0) == false);

	assert(validator.validate_attributes_for_travel_package(100, "", "France", "luxurious", 1000) == false);
	assert(validator.validate_attributes_for_travel_package(100, "Paris", "", "luxurious", 1000) == false);
	assert(validator.validate_attributes_for_travel_package(100, "Paris", "France", "", 1000) == false);

	assert(validator.validate_id_for_travel_package(1) == false);
	assert(validator.validate_id_for_travel_package(100) == true);

	assert(validator.validate_string_attributes_for_travel_package("Paris") == true);
	assert(validator.validate_string_attributes_for_travel_package("Paris123") == false);

}

void QualityAssurance::test_service() {

	Repository repository;
	Validator validator;
	Wishlist wishlist;
	Service service(wishlist, repository, validator);

	service.add_package(111, "Paris", "France", "luxurious", 1000);
	service.add_package(222, "London", "UK", "luxurious", 1200);
	service.add_package(333, "Rome", "Italy", "luxurious", 800);

	assert(service.get_all_packages()->size() == 3);

	service.update_package(111, "destination : New York; name : America; type : buget; price : 9987.01");
	assert(true);

	assert(service.get_all_packages()->size() == 3);
	assert(service.search_service(111)->get_destination() == "New York");
	assert(service.search_service(111)->get_name() == "America");
	assert(service.search_service(111)->get_type() == "buget");
	assert(service.search_service(111)->get_price() == 9987.01);
	assert(service.search_service(111)->get_id() == 111);

	service.delete_package(111);
	assert(service.get_all_packages()->size() == 2);

	Inventory <Travel_Package>* filter_packages = new Inventory<Travel_Package>();

	service.filter_packages(filter_packages, "destination: Italy");
	assert(filter_packages->size() == 1);
	assert((*filter_packages)[0]->get_destination() == "Italy");

	delete filter_packages;
	filter_packages = new Inventory<Travel_Package>();

	service.filter_packages(filter_packages, "price: 2000");
	assert(filter_packages->size() == 2);
	assert((*filter_packages)[0]->get_destination() == "UK");
	assert((*filter_packages)[1]->get_destination() == "Italy");
	delete filter_packages;

	Inventory<Travel_Package>* sorted_packages = new Inventory<Travel_Package>();
	service.sort_packages(sorted_packages, "destination: ascending");
	assert(sorted_packages->size() == 2);
	assert((*sorted_packages)[0]->get_destination() == "Italy");
	assert((*sorted_packages)[1]->get_destination() == "UK");
	delete sorted_packages;

	sorted_packages = new Inventory<Travel_Package>();
	service.sort_packages(sorted_packages, "destination: descending");
	assert(sorted_packages->size() == 2);
	assert((*sorted_packages)[0]->get_destination() == "UK");
	assert((*sorted_packages)[1]->get_destination() == "Italy");
	delete sorted_packages;

	sorted_packages = new Inventory<Travel_Package>();
	service.sort_packages(sorted_packages, "price: ascending");
	assert(sorted_packages->size() == 2);
	assert((*sorted_packages)[0]->get_price() == 800);
	assert((*sorted_packages)[1]->get_price() == 1200);
	delete sorted_packages;

	sorted_packages = new Inventory<Travel_Package>();
	service.sort_packages(sorted_packages, "price: descending");
	assert(sorted_packages->size() == 2);
	assert((*sorted_packages)[0]->get_price() == 1200);
	assert((*sorted_packages)[1]->get_price() == 800);
	delete sorted_packages;

	try {
		service.update_package(222, "price:12.00.2"); assert(false);
	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "Invalid attributes for travel package");
	}

	try {
		service.update_package(222, "price:459i9.21"); assert(false);
	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "Invalid attributes for travel package");
	}

	try {
		service.add_package(222, "Paris", "France", "luxurious", -12); assert(false);
	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "Invalid attributes for travel package");
	}

	try {
		service.delete_package(1111); assert(false);
	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "you provided an invalid id");
	}

	try {
		service.update_package(1111, "destination: New York; name: America; type: buget; price: 9987"); assert(false);
	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "you provided an invalid id");
	}

	try {
		service.update_package(222, "language : english");
	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "Invalid attributes for travel package");
	}

	try {
		service.update_package(222, " : "); assert(false);
	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "Invalid attributes for travel package");
	}

	filter_packages = new Inventory<Travel_Package>();
	try {
		service.filter_packages(filter_packages, " : "); assert(false);
	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "Invalid filter");
	}

	try {
		service.filter_packages(filter_packages, " destination:"); assert(false);
	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "Invalid filter");
	}

	try {
		service.filter_packages(filter_packages, "price : 9.3.2"); assert(false);
	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "Invalid filter");
	}
	delete filter_packages;

	sorted_packages = new Inventory<Travel_Package>();
	try {
		service.sort_packages(sorted_packages, " : "); assert(false);
	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "Invalid sort");
	}

	service.add_package(444, "Paris", "France", "luxurious", 1000);
	service.add_package(555, "London", "UK", "luxurious", 1200);

	service.sort_packages(sorted_packages, "destination: ascending");
	assert(sorted_packages->size() == 4);
	delete sorted_packages;

	try {
		service.sort_packages(sorted_packages, "destination:"); assert(false);
	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "Invalid sort");
	}

	sorted_packages = new Inventory<Travel_Package>();
	service.sort_packages(sorted_packages, "price: ascending");
	assert(sorted_packages->size() == 4);

	try {
		service.sort_packages(sorted_packages, "price: apple"); assert(false);
	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "Invalid sort");
	}

	try {
		service.sort_packages(sorted_packages, "destination : lemon"); assert(false);
	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "Invalid sort");
	}
	delete sorted_packages;
}

void QualityAssurance::test_wislist() {

	Wishlist wishlist;
	Travel_Package* travel_package1 = new Travel_Package(1, "Paris", "France", "luxurious", 1000);
	Travel_Package* travel_package2 = new Travel_Package(2, "London", "UK", "luxurious", 1200);
	wishlist.add_to_wishlist(travel_package1);
	try {
		wishlist.add_to_wishlist(travel_package1); assert(false);
	}
	catch (ExceptionWishlist& e) {
		assert(e.get_message() == "Travel package already exists in your wishlist");
	}

	wishlist.add_to_wishlist(travel_package2);
	assert(wishlist.get_wishlist()->size() == 2);

	wishlist.delete_from_wishlist(1);
	assert(wishlist.get_wishlist()->size() == 1);
	assert((*wishlist.get_wishlist())[0]->get_id() == 2);

	try {
		wishlist.delete_from_wishlist(1); assert(false);
	}
	catch (ExceptionWishlist& e) {
		assert(e.get_message() == "Travel package not found in your wishlist");
	}

	Inventory<Travel_Package>* travel_packages = new Inventory<Travel_Package>();
	travel_packages->add(new Travel_Package(3, "Paris", "France", "luxurious", 1000));
	travel_packages->add(new Travel_Package(4, "London", "UK", "luxurious", 1200));

	wishlist.generate_wishlist(2, travel_packages);
	assert(wishlist.get_wishlist()->size() == 2);

	wishlist.export_wishlist("MyWishlist");
	const multimap<string, Travel_Package*>* wishlist_map = wishlist.get_wishlist_map();
	for (auto it = wishlist_map->begin(); it != wishlist_map->end(); ++it) {
		if (it == wishlist_map->begin() || it->first != std::prev(it)->first) {
			continue;
		}
	}
	delete travel_package1;
	delete travel_package2;
	delete travel_packages;
}

void QualityAssurance::test_wishlist_from_service() {

	Repository repository;
	Validator validator;
	Wishlist wishlist;
	Service service(wishlist, repository, validator);

	repository.add_to_repository_container(new Travel_Package(111, "a", "b", "c", 1));
	repository.add_to_repository_container(new Travel_Package(222, "a", "b", "c", 1));
	repository.add_to_repository_container(new Travel_Package(333, "x", "y", "z", 2));
	repository.add_to_repository_container(new Travel_Package(444, "x", "y", "z", 2));

	service.add_to_wishlist_service(111);
	service.add_to_wishlist_service(222);
	service.add_to_wishlist_service(333);
	service.add_to_wishlist_service(444);

	try {
		service.add_to_wishlist_service(1); assert(false);
	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "The id is not valid!");
	}

	try {
		service.add_to_wishlist_service(555); assert(false);
	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "The travel package with the specified ID does not exist");
	}

	const Inventory<Travel_Package>* packages = service.get_wishlist_service();
	assert(packages->size() == 4);

	service.delete_from_wishlist_service(222);

	try {
		service.add_to_wishlist_service(-1); assert(false);
	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "The id is not valid!");
	}

	service.generate_wishlist_service(4);

	try {
		service.generate_wishlist_service(-1);; assert(false);
	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "The number cannot be negative or 0!");
	}

	try {
		service.generate_wishlist_service(20);; assert(false);
	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "Sorry, there are too few travel packages in the system to create your wishlist right now.");

	}

	const multimap<string, Travel_Package*>* statistic = service.get_wishlist_statistics_service();

	std::map<std::string, int> count_per_key;
	for (const auto& pair : *statistic) {
		const std::string& key = pair.first;
		Travel_Package* pkg = pair.second;

		assert(pkg->get_type() == key);

		count_per_key[key]++;
	}

	for (const auto& entry : count_per_key) {
		assert(entry.second == 2);
	}
	string file_name = "MyWishlist";
	string file_name_none = "";
	service.export_wishlist_service(file_name);

	try {
		service.export_wishlist_service(file_name_none);
	}
	catch (ExceptionService& e) {
		assert(e.get_message() == "You must enter the name of the file!");
	}

}

void QualityAssurance::test_SAVE() {

	RepositorySAVE repository("SAVE_TEST");
	Validator validator;
	Wishlist wishlist;
	Service service(wishlist, repository, validator);
	service.delete_package(111);
	service.add_package(111, "a", "b", "c", 1);
	assert(service.search_service(111)->get_id() == 111);
	service.update_package(111, "price:2");
}

void QualityAssurance::test_all() {

	test_undo();
	test_domain();
	test_container();
	test_repository();
	test_validator();
	test_service();
	test_wislist();
	test_wishlist_from_service();
	test_SAVE();
	cout << "All tests passed!" << endl;
}