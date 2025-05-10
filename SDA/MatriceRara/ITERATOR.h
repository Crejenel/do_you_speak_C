#pragma once
#include "MATRICE.h"

class Matrice;

class IteratorMatrice
{
	friend class Matrice;

private:


	IteratorMatrice(const Matrice& c);

	const Matrice& matrice;

	int i;
	int j;

public:

	void prim();

	void urmator();

	bool valid() const;

	TElem element() const;
};

