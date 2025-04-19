#pragma once
typedef int TElem;
class IteratorColectie;

class Colectie {

	friend class IteratorColectie;

private:

	TElem* vf;
	TElem maxim;
	TElem minim;
	int nr;

public:


	Colectie();

	void adauga(TElem element);

	bool sterge(TElem element);

	bool cauta(TElem element) const;

	int nrAparitii(TElem element) const;

	int dim() const;

	bool vida() const;

	IteratorColectie iterator() const;

	~Colectie();

};