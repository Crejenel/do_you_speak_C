#include "TESTS_SCURT.h"
#include <assert.h>
#include "MATRICE.h"
#include <iostream>

using namespace std;

void testAll() { 

	Matrice m(4, 4);
	assert(m.nrLinii() == 4);
	assert(m.nrColoane() == 4);
	m.modifica(1, 1, 5);
	assert(m.element(1, 1) == 5);
	assert(m.modifica(1, 1, 6) == 5);
	assert(m.element(1, 2) == 0);

	Matrice matrice(10, 10);
	IteratorMatrice it = matrice.iterator();
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (i % 2 == 0 || j % 2 == 0) {
				matrice.modifica(i, j, 1);
			}
		}
	}
		
	int contor = 0;
	while (it.valid()) {
			
		if (it.element() == 1) {
			contor++;
		}
		it.urmator();		
	}
	assert(contor == 75);

	cout << "Testul scurt a trecut!" << endl;
}
