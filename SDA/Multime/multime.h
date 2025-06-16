#pragma once
#include <vector>
typedef int TElem;
typedef bool(*Relatie)(TElem, TElem);
bool rel(TElem, TElem);
class IteratorMultime;

class Multime {

	friend class IteratorMultime;

private:

	struct Nod {

		TElem element;
		int stanga;
		int dreapta;
		int tata;
	};

	std::vector<Nod> noduri;
	int radacina;
	int dimensiune;
	std::vector<int> stivaLibere;

	int alocaNod(TElem e);
	void dealocaNod(int poz);
	int maximNod(int rad) const;

public:

	Multime();
	bool adauga(TElem e);
	bool sterge(TElem e);
	bool cauta(TElem e) const;
	int dim() const;
	bool vida() const;
	IteratorMultime iterator() const;
	int diferentaMaxMin() const;
	~Multime();
};
