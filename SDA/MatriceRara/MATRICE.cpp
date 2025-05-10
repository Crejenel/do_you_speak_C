#include "MATRICE.h"
#include "ITERATOR.h"
#include <exception>
#include <iostream>
using namespace std;

// caz favorabil = caz mediu = caz defavorabil = θ(1)
Matrice::Matrice(int m, int n) {

	if (m <= 0 || n <= 0) {throw exception("Numarul de linii si de coloane nu poate fi negativ!"); }
	linii = m;
	coloane = n;
	valoare = new Triplet*[5];
	urmator = new int[5];
	capacitate = 5;
	for (int i = 0; i < capacitate; i++) 
	{
		valoare[i] = nullptr;
		if (i == capacitate - 1) {
			urmator[i] = -1;
		}
		else {
			urmator[i] = i + 1;
		}
	}
	PrimLiber = 0;
	UltimLiber = capacitate - 1;
	PrimOcupat = -1;
}

// caz favorabil = caz mediu = caz defavorabil = θ(1)
int Matrice::nrLinii() const {
	return linii;
}

// caz favorabil = caz mediu = caz defavorabil = θ(1)
int Matrice::nrColoane() const {
	return coloane;
}

// caz favorabil = θ(1); caz mediu = O(k); caz defavorabil = θ(k) | k fiind nr elementelor nenule din matrica rara
TElem Matrice::element(int i, int j) const {
	
	if (i < 0 || i >= linii || j < 0 || j >= coloane) { throw exception("Pozitia nu este valida!");}

	int deplasator = PrimOcupat;
	if (deplasator == -1) { return 0; }
	while (deplasator != -1) {
		if (valoare[deplasator]->getLinie() == i && valoare[deplasator]->getColoana() == j) {
			return valoare[deplasator]->getValoare();
		}
		deplasator = urmator[deplasator];
	}
	return 0;
	
}

// caz favorabil = θ(1); caz mediu = O(k); caz defavorabil = θ(k) | k fiind nr elementelor nenule din matrica rara
TElem Matrice::modifica(int i, int j, TElem e) {
	

	if (i < 0 || i >= linii || j < 0 || j >= coloane) { throw exception("Pozitia nu este valida!"); }
	int deplasator = PrimOcupat;
	TElem valoare_de_modificat = element(i, j);

	//cazul in care nu facem modificari
	if (valoare_de_modificat == 0 && e == 0) { return 0; }

	// cazul in care nu e niciun element nevid in matrice
	if (deplasator == -1) 
	{
		valoare[PrimLiber] = new Triplet(i, j, e);
		PrimOcupat = PrimLiber;
		PrimLiber = urmator[PrimLiber];
		urmator[PrimOcupat] = -1;
		return 0;
	}

	// cazul in care trebuie sa facem redimensionare la vectori
	if (PrimLiber==-1) {

		Triplet** auxiliar_valoare = new Triplet* [capacitate * 2];
		int* auxiliar_urmator = new int[capacitate * 2];

		for (int k = 0; k < capacitate; k++) {
			auxiliar_valoare[k] = valoare[k];
			auxiliar_urmator[k] = urmator[k];
		}

		PrimLiber = capacitate;
		for (int k = capacitate; k < capacitate * 2; k++) {
			auxiliar_valoare[k] = nullptr;
			if (k == capacitate * 2 - 1) {
				auxiliar_urmator[k] = -1;
			}
			else 
			{
				auxiliar_urmator[k] = k + 1;
			}
		}
		capacitate = capacitate * 2;
		UltimLiber = capacitate - 1;
		delete urmator;
		delete valoare;
		valoare = auxiliar_valoare;
		urmator = auxiliar_urmator;
		
	}

	//cazul in care adaugam un element in matrice
	if (valoare_de_modificat == 0 && e != 0) {

		valoare[PrimLiber] = new Triplet(i, j, e);
		int aux = urmator[PrimLiber];

		// cazul in care inseram la inceput
		if (valoare[PrimOcupat]->getLinie() >= i) {

			if (valoare[PrimOcupat]->getColoana() >= j) {

				urmator[PrimLiber] = PrimOcupat;
				PrimOcupat = PrimLiber;
				PrimLiber = aux;
				return 0;
			}
		}

		//cazul in care inseram la mijloc
		while (urmator[deplasator] != -1) {

			if (valoare[urmator[deplasator]]->getLinie() >= i) {

				if (valoare[urmator[deplasator]]->getColoana() >= j) {

					urmator[PrimLiber] = urmator[deplasator];
					urmator[deplasator] = PrimLiber;
					PrimLiber = aux;
					return 0;
				}
			}
			deplasator = urmator[deplasator];
		}

		//cazul in care inseram la final
		if(urmator[deplasator]!=-1){ deplasator = urmator[deplasator]; }
		urmator[deplasator] = PrimLiber;
		urmator[PrimLiber] = -1;
		PrimLiber = aux;
		return 0;
		
	}

	//cazul in care stergem un element din matrice
	if (valoare_de_modificat != 0 && e == 0) {

		//stergem de pe prima pozitie
		if (valoare[PrimOcupat]->getLinie() == i && valoare[PrimOcupat]->getColoana() == j) {
			
			delete valoare[PrimOcupat];
			valoare[PrimOcupat] = nullptr;

			if (PrimLiber == -1) {

				PrimLiber = PrimOcupat;
				UltimLiber = PrimLiber;
				urmator[PrimLiber] = -1;
			}
			else {

				urmator[UltimLiber] = PrimOcupat;
				UltimLiber = PrimOcupat;
				urmator[UltimLiber] = -1;
			}

			PrimOcupat = urmator[PrimOcupat];
			return valoare_de_modificat;
		}

		//stergem din mijloc
		while (urmator[deplasator] != -1) {

			if (valoare[urmator[deplasator]]->getLinie() == i) {

				if (valoare[urmator[deplasator]]->getColoana() == j) {

					if (PrimLiber == -1) {

						PrimLiber = urmator[deplasator];
						UltimLiber = PrimLiber;
						urmator[deplasator] = urmator[urmator[deplasator]];
						delete valoare[urmator[deplasator]];
						valoare[urmator[deplasator]] = nullptr;
						urmator[UltimLiber] = -1;
						return valoare_de_modificat;


					}
					else {

						urmator[UltimLiber] = urmator[deplasator];
						UltimLiber = urmator[UltimLiber];
						urmator[deplasator] = urmator[urmator[deplasator]];
						urmator[UltimLiber] = -1;
						delete valoare[urmator[deplasator]];
						valoare[urmator[deplasator]] = nullptr;
						return valoare_de_modificat;
					}
					
				}
			}
			deplasator = urmator[deplasator];
		}

		//stergem de pe ultima pozitie
		urmator[deplasator] = -1;
		deplasator = urmator[deplasator];
		delete valoare[deplasator];
		valoare[deplasator] = nullptr;

		if (PrimLiber == -1) {

			
			PrimLiber = deplasator;
			UltimLiber = PrimLiber;
			return valoare_de_modificat;
		}
		else {
			
			urmator[UltimLiber] = deplasator;
			UltimLiber = deplasator;
			return valoare_de_modificat;
		}
		
	}

	//cazul in care suprascriem un element din matrice
	if (valoare_de_modificat != 0 && e != 0) {

		while (deplasator != -1) {

			if (valoare[deplasator]->getLinie() == i && valoare[deplasator]->getColoana() == j) {
				valoare[deplasator]->setValoare(e);
				return valoare_de_modificat;
			}
			deplasator = urmator[deplasator];
		}
	}

	//ceva nu a mers bine
	return -1;
}

// caz favorabil = caz mediu = caz defavorabil = θ(1)
IteratorMatrice Matrice::iterator() const {

	return IteratorMatrice(*this);

}




