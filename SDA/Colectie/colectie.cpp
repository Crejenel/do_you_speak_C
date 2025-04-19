#include <iostream>
#include <algorithm>
#include "colectie.h"
#include "iteratorcolectie.h"
#define NULLtelem -1
using std::copy;
using std::fill;


Colectie::Colectie() {

	vf = new TElem[1];
	nr = 0;
	maxim = NULLtelem;
	minim = NULLtelem;

}

void Colectie::adauga(TElem element) {

	if (dim() == 0) {

		if (element < 0) {

			minim = element;
			maxim = 0;
			delete[] vf;
			vf = new TElem[maxim - minim + 1]();
			vf[0]++;
				
		}
		if (element == 0) {

			minim = maxim = 0;
			delete[] vf;
			vf = new TElem[1]();
			vf[0]++;

		}
		if (element > 0) {

			minim = 0;
			maxim = element;
			delete[] vf;
			vf = new TElem[maxim - minim + 1]();
			vf[element]++;
		}
			
	}

	if(dim()>0){

		if (minim <= element && element <= maxim) {

			vf[element - minim]++;

		}

		else if (element > maxim) {

				
			int old_size = maxim - minim + 1;
			maxim = element;
			int new_size = maxim - minim + 1;

			TElem* new_vf = new TElem[new_size]();

			copy(vf, vf + old_size, new_vf);

			delete[] vf;
			vf = new_vf;
			vf[new_size - 1]++;

		}

		else if (element < minim) {

				
			int old_size = maxim - minim + 1;
			minim = element;
			int new_size = maxim - element + 1;

			TElem* new_vf = new TElem[new_size]();

			copy(vf, vf + old_size, new_vf + (new_size - old_size)); 

			delete[] vf;
			vf = new_vf;
			vf[0]++;

		}

	}

	nr++;
}

bool Colectie::sterge(TElem element) {


	if (dim() == 0) {
		return false;
	}

	if (cauta(element) == false) {
		return false;
	}
	else {

		if (element == minim && vf[0] > 1) {
			vf[0]--;
			nr--;
			return true;
		}
		else if (element == minim && vf[0] == 1) {

			int old_size = abs(maxim - minim) + 1;

			int aux=0;
			vf[0]--;

			for (int i = 1; i <= abs(maxim-minim); i++) {
				if (vf[i] > 0) {
					minim = i + minim;
					aux = i;
					break;
				}
			}
			
			int new_size = abs(maxim - minim) + 1;
			TElem* new_vf = new TElem[new_size]();
			int j = 0;
			for (int i = aux; i < old_size; i++) {

				new_vf[j] = vf[i];

				j++;
			}
			delete[] vf;
			vf = new_vf;
			nr--;
			return true;
				
		}

		if (element == maxim && vf[abs(minim - maxim)] > 1) {
			vf[abs(minim-maxim)]--;
			nr--;
			return true;
		}
		else if(element==maxim && vf[abs(minim - maxim)] == 1) {
			int aux = 0;
			vf[abs(minim - maxim)]--;

			for (int i = abs(minim - maxim) - 1; i >= 0; i--) {
				if (vf[i] > 0) {
					maxim = i + minim;
					aux = i;
					break;
				}
			}

			int new_size = abs(maxim - minim) + 1;
			TElem* new_vf = new TElem[new_size]();
			int j = 0;
			for (int i = 0; i < new_size; i++) {
				new_vf[j] = vf[i];
				j++;
			}
			delete[] vf;
			vf = new_vf;
			nr--;
			return true;
		}

		vf[abs(minim - element)]--;
		nr--;
		return true;
	}
		
}

bool Colectie::cauta(TElem element) const {

	if (dim() == 0) {
		return false;
	}
	if (element < minim || element > maxim) {
		return false;
	}
	else if(vf[abs(minim-element)]>0) {
		return true;
	}
	else {
		return false;
	}
}
	
int Colectie::nrAparitii(TElem element) const {

	if (cauta(element) == false) {
		return 0;
	}
	else {
		return vf[abs(minim - element)];
	}
}

int Colectie::dim() const{
	return nr;
}

bool Colectie::vida() const {

	return dim() == 0;
}

IteratorColectie Colectie::iterator() const {

	return IteratorColectie(*this);
}

Colectie::~Colectie() {
	delete[] vf;
}
