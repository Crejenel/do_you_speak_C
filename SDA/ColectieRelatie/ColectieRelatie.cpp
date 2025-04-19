#include "ColectieRelatie.h"
#include "Iterator.h"
#include "domeniu.h"
#include <iostream>

using namespace std;

//CAZ FAVORABIL = CAZ MEDIU = CAZ DEFAVORABIL = THETA(1)
bool rel(TElem e1, TElem e2) {

	if (e1 <= e2) return true;
	return false;
}

//CAZ FAVORABIL = CAZ MEDIU = CAZ DEFAVORABIL = THETA(1)
Colectie::Colectie() {
	
	lista = NULL;
	nr = 0;
	ultim = NULL;
}

//CAZ FAVORABIL = THETA(1); CAZ MEDIU = O(NR); CAZ DEFAVORABIL = THETA(NR)
void Colectie::adauga(TElem e) {

	ELEMENT* element = new ELEMENT;
	element->spate = nullptr;
	element->fata = nullptr;
	element->valoare = e;

	if (nr == 0) {

		lista = element;
		ultim = element;
		nr++;
		return;
	}

	// pointerul de unde incepe lista ( primul element )
	ELEMENT* curent = lista;
	bool adaugat = false;
		
	//cazul adaugarii la inceputul listei (1)
	if (rel(element->valoare,curent->valoare)) {
		curent->spate = element;
		element->fata = curent;
		nr++;
		lista = element;
		return;
	}


	// nu l-am pus la inceputul listei, trecem la urmatorul
	curent = (ELEMENT*)lista->fata;

	//caz special (2)
	if (nr == 2) {

		curent->fata = element;
		element->spate = curent;
		nr++;
		ultim = element;
		return;

	}

	//cazul in care adaugam in interiorul listei (3)
	curent = lista;
	ELEMENT* urmatorul = nullptr;

	for(int i=0; i<nr; i++)
	{
		if (rel(element->valoare, curent->valoare))
		{
			element->spate = curent->spate;
			element->fata = curent;
			curent->spate = element;
			((ELEMENT*)(element->spate))->fata = element;
			adaugat = true;
			break;
		}
		if (i != nr - 1) {
			ELEMENT* urmatorul = (ELEMENT*)curent->fata;
			curent = urmatorul;
		}
		
	}

	// adaugam la sfarsit (4)
	if (!adaugat) {

		curent->fata = element;
		element->spate = curent;
		ultim = element;
		nr++;
		return;
	}

	nr++;
	return;

}

//CAZ FAVORABIL = THETA(1); CAZ MEDIU = OMEGA(NR); CAZ DEFAVORABIL = THETA(NR)
bool Colectie::sterge(TElem e) {
	
	ELEMENT* curent = lista;

	//cazul in care lista e vida 
	if (vida()) return false;

	//cazul in care stergem singurul element din lista
	if (nr == 1 && curent->valoare == e) {
		lista = nullptr;
		ultim = nullptr;
		delete curent;
		nr--;
		return true;
	}

	//cazul in care spergem de pe prima pozitie
	if (curent->valoare == e) {
		
		((ELEMENT*)curent->fata)->spate = nullptr;
		lista = ((ELEMENT*)curent->fata);
		delete curent;
		nr--;
		return true;
	}

	//cazul in care stergem din mijlocul listei
	ELEMENT* urmatorul = nullptr;

	for (int i = 0; i < nr-1; i++)
	{
		if (curent->valoare == e) {

			ELEMENT* INAINTE = ((ELEMENT*)curent->fata);
			ELEMENT* INAPOI = ((ELEMENT*)curent->spate);

			INAPOI->fata = ((ELEMENT*)curent->fata);
			INAINTE->spate = ((ELEMENT*)curent->spate);

			delete curent;
			nr--;
			return true;
		}
		
		ELEMENT* urmatorul = (ELEMENT*)curent->fata;
		curent = urmatorul;
	}

	//cazul in care stergem de la final
	if (curent->valoare == e) {

		ELEMENT* INAPOI = ((ELEMENT*)curent->spate);
		ultim = INAPOI;
		INAPOI->fata = nullptr;
		delete curent;
		nr--;
		return true;
	}

	return false;

}

//CAZ FAVORABIL = THETA(1); CAZ MEDIU = OMEGA(NR); CAZ DEFAVORABIL = THETA(NR)
bool Colectie::cauta(TElem elem) const {
	
	ELEMENT* curent = lista;

	while (curent != nullptr) {

		ELEMENT* urmatorul = (ELEMENT*)curent->fata;
		if (curent->valoare == elem) return true;
		curent = urmatorul;
	}
	return false;
}

//CAZ FAVORABIL = THETA(1); CAZ MEDIU = OMEGA(NR); CAZ DEFAVORABIL = THETA(NR)
int Colectie::nrAparitii(TElem elem) const {
	
	int count=0;
	bool gasit=false;

	ELEMENT* curent = lista;

	for (int i = 0; i < nr; i++)
	{
		if ( curent->valoare == elem && gasit==false) {
			gasit = true;
			count++;
		}
		else if (curent->valoare == elem && gasit == true) {
			count++;
		}
		else if (curent->valoare != elem && gasit == true) {
			break;
		}

		if (i != nr - 1) {
			ELEMENT* urmatorul = (ELEMENT*)curent->fata;
			curent = urmatorul;
		}

	}

	return count;

}

//CAZ FAVORABIL = CAZ MEDIU = CAZ DEFAVORABIL = THETA(1)
int Colectie::dim() const {
	
	return nr;
}

//CAZ FAVORABIL = CAZ MEDIU = CAZ DEFAVORABIL = THETA(1)
bool Colectie::vida() const {

	if (nr == 0) return true;
	return false;
}

//CAZ FAVORABIL = CAZ MEDIU = CAZ DEFAVORABIL = THETA(1)
IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

//CAZ FAVORABIL = CAZ MEDIU = CAZ DEFAVORABIL = THETA(NR)
Colectie::~Colectie() {
	
	ELEMENT* curent = lista;

	while (curent != nullptr) {

		ELEMENT* urmatorul = (ELEMENT*)curent->fata;
		delete curent;
		curent = urmatorul;
	}

}
