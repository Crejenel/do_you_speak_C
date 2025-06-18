#include <iostream>
#include <assert.h>
#include <stdexcept>
using namespace std;

/*
*	DATE INTRARE : un numar intreg
*	DATE IESIRE : adevarat daca a e prim, false in caz contrar ( 1 e considerat prim )
*	PRECONDITII : numarul intreg trebuie sa fie strict pozitiv
*/
bool f(int a) {

	if (a <= 0)
		throw std::exception("Illegal argument");

	int d = 2;
	while (d < a && a % d>0) d++;
	return d >= a;
}


void test_f() {

	assert(f(1) == true);
	assert(f(2) == true);
	assert(f(121) == false);
	assert(f(12112) == false);
	assert(f(5) == true);

	try {
		f(-1);
		assert(false);
	}
	catch (std::exception& e) {
		assert(true);
	}

	cout << "Testul pentru functia f a trecut!";
}

int main() {

	test_f();

	return 0;
}
