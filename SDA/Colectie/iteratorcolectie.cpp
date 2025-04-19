#include <iostream>
#include <exception>
#include "iteratorcolectie.h"
#include "colectie.h"

IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	prim();
}

void IteratorColectie::prim() {

	if (col.dim() == 0) {
		poz = -1;
	}
	else {
		
		poz = 0;
		int i = 0;
		while (col.vf[i] == 0) {
			i++;
		}
		poz = i;
		count = col.vf[poz]-1;
	}
	
}

void IteratorColectie::urmator() {
	
	if (count == 0) {

		if (poz < 0) { throw std::exception(); }

			while (true) {

				poz++;
				if (valid() == false) { poz = -1; break; }
				if (col.vf[poz] > 0) {
					count = col.vf[poz]-1;
					break;
				}
			}
	}
	else {
		count--;
	}

	
}

bool IteratorColectie::valid() const {

	if (poz < 0) {
		return false;
	}
	else if(poz > abs(col.minim-col.maxim)) {

		return false;
	}
	return true;
}

TElem IteratorColectie::element() const {
	
	if (col.minim != 0) {
		return col.minim + poz;
	}
	return poz;
}
