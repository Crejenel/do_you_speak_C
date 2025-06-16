#include "iterator.h"

// Θ(h) 	Θ(h)	Θ(n)
IteratorMultime::IteratorMultime(const Multime& m) : mult(m) {

	prim();
}

// Θ(1) 	Θ(h)	Θ(n)
void IteratorMultime::prim() {

	while (!stiva.empty())
		stiva.pop();

	int curent = mult.radacina;

	while (curent != -1) {

		stiva.push(curent);
		curent = mult.noduri[curent].stanga; // parcurgere in in-ordine
	}
}

// Θ(1)
bool IteratorMultime::valid() const {

	return !stiva.empty();
}

// Θ(1)
TElem IteratorMultime::element() const {

	if (!valid())
		throw std::exception();
	return mult.noduri[stiva.top()].element;
}

// Θ(1) 	Θ(h)	Θ(n)
void IteratorMultime::urmator() {

	if (!valid())
		throw std::exception();

	int curent = stiva.top();
	stiva.pop();

	if (mult.noduri[curent].dreapta != -1) {
		curent = mult.noduri[curent].dreapta;
		while (curent != -1) {
			stiva.push(curent);
			curent = mult.noduri[curent].stanga;
		}
	}
}
