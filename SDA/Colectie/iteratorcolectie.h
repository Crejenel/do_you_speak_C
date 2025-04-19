#pragma once
#include "colectie.h"

class Colectie;
typedef int TElem;

class IteratorColectie
{
	friend class Colectie;

private:
	

	IteratorColectie(const Colectie& c);

	const Colectie& col;
	
	int poz;

	int count;


public:

	void prim();

	void urmator();

	bool valid() const;

	TElem element() const;
};

