#include <iostream>
#include <stdexcept>
#include <assert.h>
using namespace std;

/*
* Date intrare : un numar intreg x
* Date iesire : oglinditul numarului x
* Preconditii : x trebuie sa fie strict pozitiv
*/
int f(int x) {

	if (x <= 0)
		throw std::exception("Invalid argument!");

	int rez = 0;
	while (x)
	{
		rez = rez * 10 + x % 10;
		x /= 10;
	}
	return rez;
}

void  test_t() {

	int a = 1221;
	assert(1221 == f(a));

	int b = 8;
	assert(8 == f(b));

	int c = 93671;
	assert(17639 == f(c));

	try {
		f(-12);
		assert(false);
	}
	catch (exception& e) {
		assert(string(e.what()) == "Invalid argument!");
	}

	cout << "Testul pentru functia f a trecut!";
}

int main() {

	test_t();

	return 0;
}
