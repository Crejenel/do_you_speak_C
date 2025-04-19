#include "Iterator.h"
#include "ColectieRelatie.h"
#include <exception>

//CAZ FAVORABIL = CAZ MEDIU = CAZ DEFAVORABIL = THETA(1)
IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	prim();
}

//CAZ FAVORABIL = CAZ MEDIU = CAZ DEFAVORABIL = THETA(1)
TElem IteratorColectie::element() const {
	
	if(valid()) return curent->valoare;
	throw std::exception();
}

//CAZ FAVORABIL = CAZ MEDIU = CAZ DEFAVORABIL = THETA(1)
bool IteratorColectie::valid() const {
	
	if (curent == nullptr) return false;
	return true;
}

//CAZ FAVORABIL = CAZ MEDIU = CAZ DEFAVORABIL = THETA(1)
void IteratorColectie::urmator() {
	
	if (curent == nullptr && SFARSIT == true) curent = col.lista;
	ELEMENT* aux = curent;
	if (!valid() && sfarsit == true) throw std::exception();
	else if (!valid() && sfarsit == false) sfarsit = true;
	else if(curent!=nullptr) curent = (ELEMENT*)aux->fata;
	
	if (SFARSIT == true) SFARSIT = false;

}

//CAZ FAVORABIL = CAZ MEDIU = CAZ DEFAVORABIL = THETA(1)
void IteratorColectie::anterior() {

	if (curent == nullptr && sfarsit == true) curent = col.ultim;
	ELEMENT* aux = curent;
	
	if (!valid() && SFARSIT == true) throw std::exception();
	if (!valid() && SFARSIT == false) SFARSIT = true;
	else if(curent!=nullptr) curent = (ELEMENT*)aux->spate;

	if (sfarsit == true) sfarsit = false;

}

//CAZ FAVORABIL = CAZ MEDIU = CAZ DEFAVORABIL = THETA(1)
void IteratorColectie::prim() {
	
	if (col.nr == 0)
	{
		curent = nullptr; sfarsit = true;
	}
	curent = col.lista; sfarsit = false;

}

/*
FUNTIE urmator(it)

	DACA curent == NULL SI 'SFARSIT' == true ATUNCI
		curent <- col.lista
	SFARSIT DACA

	aux <- curent

	DACA NU valid() SI sfarsit == true ATUNCI
		ARUNCA EXCEPTIE
	SFARSIT DACA

	ALTFEL DACA NU valid() SI sfarsit == false ATUNCI
		sfarsit <- true
	SFARSIT ALTFEL DACA

	ALTFEL DACA curent != NULL ATUNCI 
		curent <- aux->fata
	SFARSIT ALTFEL DACA

	DACA 'SFARSIT' == true ATUNCI
		'SFARSIT' <- false
	SFARSIT DACA

SFARSIT FUNCTIE
*/