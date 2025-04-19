#ifndef TESTS_H
#define TESTS_H
#include <iostream>
#include "service.h"

class Tests {

private:

	Service service;

public:

	Tests(Service& service);

	void test_add();

	void test_delete();

	void test_update();

	void test_get();

	void test_filter();

	void test_sort();

	void test_domain();

	void run_all_tests();

};

#endif 

