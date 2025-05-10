#include "ITERATOR.h"
#include <exception>
#include <iostream>
using std::exception;

// caz favorabil = caz mediu = caz defavorabil = θ(1)
IteratorMatrice::IteratorMatrice(const Matrice& c) : matrice(c) {
    
    i = 0;
    j = 0;
}

// caz favorabil = caz mediu = caz defavorabil = θ(1)
void IteratorMatrice::prim() {
    i = 0;
    j = 0;
}

/*
subalgoritm urmator(it) 
*****************************************
* -> nu returneaza nimic, dar in schimb *
* se schimba valorile pt i si j         *
*****************************************

    it.j <- it.j + 1

    daca it.j >= nrColoane(it.matrice) atunci
        it.j <- 0
        it.i <- it.i + 1
    sfarsit daca

    daca it.i >= nrLinii(it.matrice) atunci
        it.i <- -1
        it.j <- -1
    sfarsit daca

sfarsit subalgoritm
*/
// caz favorabil = caz mediu = caz defavorabil = θ(1)
void IteratorMatrice::urmator() {

    j++;
    if (j >= matrice.nrColoane()) {
        j = 0;
        i++;
    }
    if (i >= matrice.nrLinii()) {
        i = -1;
        j = -1;
    }
}

// caz favorabil = caz mediu = caz defavorabil = θ(1)
bool IteratorMatrice::valid() const {

    if (i == -1 && j == -1) {
        return false;
    }
    else {
        return true;
    }

}

/*
metoda IteratorMatrice::element(it) const 
***************************************
* -> aruca exceptie daca valid e fals *
* -> retuneaza un int apeland functia *
* 'element' a obiectului matrice      *
***************************************

    daca valid(it) e fals atunci
        @arunca exceptie
    sfarsit daca

    returneaza element(it.matrice, it.i, it.j)

sfarsit metoda
*/
// caz favorabil = θ(1); caz mediu = O(k); caz defavorabil = θ(k) | k fiind nr elementelor nenule din matrica rara
TElem IteratorMatrice::element() const {

    if (!valid()) {
        throw exception();
    }
    return matrice.element(i, j);
}
