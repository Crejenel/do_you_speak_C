#pragma once
#include "multime.h"
#include <stack>
#include <exception>

class IteratorMultime {

	friend class Multime;

private:

	const Multime& mult;
	std::stack<int> stiva;
	IteratorMultime(const Multime& m);

public:

	void prim();
	void urmator();
	bool valid() const;
	TElem element() const;
};
