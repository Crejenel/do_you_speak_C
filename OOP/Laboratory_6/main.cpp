#include "repository.h"
#include "service.h"
#include "validator.h"
#include "user_interface.h"
#include "tests.h"
#include <iostream>
#include <vector>
using std::cout;
using std::endl;

int main() {
	
	//the tests
	Validator validator;
	Repository repository;

	Service service(repository, validator);

	UI interface(service);
	//Tests tests(service);

	interface.run();
	//tests.run_all_tests();

	return 0;
}