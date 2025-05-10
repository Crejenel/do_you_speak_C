#pragma once
#define TElem int

class Triplet {

private :
	int linie;
	int coloana;
	TElem valoare;

public:
	Triplet(int l, int c, TElem v) : linie(l), coloana(c), valoare(v) {}

	int getLinie() const { return linie; }
	int getColoana() const { return coloana; }
	TElem getValoare() const { return valoare; }

	void setLinie(int l) { linie = l; }
	void setColoana(int c) { coloana = c; }
	void setValoare(TElem v) { valoare = v; }
};