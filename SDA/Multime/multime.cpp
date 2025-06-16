#include "multime.h"
#include "iterator.h"
#include <stdexcept>

// relatia din multime, ordine crescatoare
bool rel(TElem e1, TElem e2) {
	return e1 <= e2;
}

// constructorul multimii
Multime::Multime() {
	radacina = -1;
	dimensiune = 0;
}

// Θ(1)
int Multime::alocaNod(TElem e){

	int poz;
	if (!stivaLibere.empty()) {

		poz = stivaLibere.back();
		stivaLibere.pop_back();
		noduri[poz].element = e;
		noduri[poz].stanga = -1;
		noduri[poz].dreapta = -1;
		noduri[poz].tata = -1;
	}
	else {
		poz = (int)noduri.size();
		noduri.push_back({ e, -1, -1, -1 });
	}
	return poz;
}

// Θ(1)
void Multime::dealocaNod(int poz) {
	stivaLibere.push_back(poz);
}

// Θ(1) 	Θ(log n)	Θ(n)
bool Multime::adauga(TElem e){

	// devine radacina
	if (radacina == -1) {

		radacina = alocaNod(e);
		dimensiune++;
		return true;
	}

	int curent = radacina;
	int parinte = -1;

	while (curent != -1) {

		if (noduri[curent].element == e)
			return false;  // element existent

		parinte = curent;

		if (rel(e, noduri[curent].element))
			curent = noduri[curent].stanga;
		else
			curent = noduri[curent].dreapta;
	}

	int nou = alocaNod(e);
	noduri[nou].tata = parinte;

	if (rel(e, noduri[parinte].element))
		noduri[parinte].stanga = nou;
	else
		noduri[parinte].dreapta = nou;

	dimensiune++;
	return true;
}

// Θ(1) 	Θ(log n)	Θ(n)
bool Multime::cauta(TElem e) const {

	int cur = radacina;
	while (cur != -1) {
		if (noduri[cur].element == e)
			return true;

		if (rel(e, noduri[cur].element))
			cur = noduri[cur].stanga;
		else
			cur = noduri[cur].dreapta;
	}
	return false;
}

// Θ(1)
int Multime::dim() const {
	return dimensiune;
}

// Θ(1) 
bool Multime::vida() const {
	return dimensiune == 0;
}

// Θ(1) 	Θ(log n)	Θ(n)
int Multime::maximNod(int rad) const {

	while (noduri[rad].dreapta != -1)
		rad = noduri[rad].dreapta;
	return rad;
}

// Θ(1) 	Θ(log n)	Θ(n)
bool Multime::sterge(TElem e) {

	int curent = radacina;
	int parinte = -1;

	while (curent != -1 && noduri[curent].element != e) {
		parinte = curent;
		if (rel(e, noduri[curent].element))
			curent = noduri[curent].stanga;
		else
			curent = noduri[curent].dreapta;
	}

	if (curent == -1)
		return false; // nu exista

	// Cazul 1: nodul are cel mult un copil
	if (noduri[curent].stanga == -1 || noduri[curent].dreapta == -1) {
		int copil = (noduri[curent].stanga != -1 ? noduri[curent].stanga : noduri[curent].dreapta);

		if (curent == radacina)
			radacina = copil;
		else if (noduri[parinte].stanga == curent)
			noduri[parinte].stanga = copil;
		else
			noduri[parinte].dreapta = copil;

		if (copil != -1)
			noduri[copil].tata = parinte;

		dealocaNod(curent);
		dimensiune--;
		return true;
	}
	else {

		// Cazul 2: nodul are 2 copii – îl înlocuim cu predecesorul (maxim din stânga)
		int predecesor = noduri[curent].stanga;
		int parintePre = curent;

		while (noduri[predecesor].dreapta != -1) {
			parintePre = predecesor;
			predecesor = noduri[predecesor].dreapta;
		}

		noduri[curent].element = noduri[predecesor].element;

		int copil = noduri[predecesor].stanga;

		if (parintePre == curent)
			noduri[parintePre].stanga = copil;
		else
			noduri[parintePre].dreapta = copil;

		if (copil != -1)
			noduri[copil].tata = parintePre;

		dealocaNod(predecesor);
		dimensiune--;
		return true;
	}
}

// Θ(1) 	Θ(n)	Θ(n)
/*
* 
Algoritm diferentaMaxMin(Multime M)
	>> diferentaMaxMin <- MAX(M) - MIN(M)
	>> M multme valida

  Daca vida(M) atunci
	diferentaMaxMin <- -1
  SfarsitDaca

  curentMin <- M.radacina
  Cat timp M.noduri[curentMin].stanga ≠ -1 executa
	curentMin <- M.noduri[curentMin].stanga
  SfarsitCat
  valoareMinima <- M.noduri[curentMin].element

  curentMax <- M.radacina
  Cat timp M.noduri[curentMax].dreapta ≠ -1 executa
	curentMax <- M.noduri[curentMax].dreapta
  SfarsitCat
  valoareMaxima <- M.noduri[curentMax].element

  diferentaMaxMin <- valoareMaxima - valoareMinima

SfarsitAlgoritm
*		
*/
int Multime::diferentaMaxMin() const {

	if (vida()) {
		return -1;
	}

	int curentMin = radacina;
	while (noduri[curentMin].stanga != -1) {
		curentMin = noduri[curentMin].stanga;
	}
	int valoareMinima = noduri[curentMin].element;

	int valoareMaxima = maximNod(radacina);

	return valoareMaxima - valoareMinima;
}

// Θ(1)
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

// Θ(1)
Multime::~Multime() {
}
