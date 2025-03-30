#include <stdbool.h>
#include <string.h>
#include "validator.h"

/*
* Functia valideaza datele de intrare pentru un participant.
* >> Intrare:
*    - `nume`: Un sir de caractere care reprezinta numele participantului.
*    - `prenume`: Un sir de caractere care reprezinta prenumele participantului.
*    - `scor`: Un numar intreg care reprezinta scorul participantului.
*    - `id`: Un numar intreg care reprezinta ID-ul participantului.
* >> Iesire:
*    - Returneaza `true` daca toate datele sunt valide (numele si prenumele contin doar litere mari/mici, lungimea lor este mai mare de 0, ID-ul este pozitiv si scorul este nenegativ).
*    - Returneaza `false` daca datele sunt invalide (de exemplu, daca numele sau prenumele contin caractere nevalide sau lungimea acestora este 0).
*/
bool validare(char nume[], char prenume[], int scor, int id){

	for (int i = 0; i < strlen(nume); i++)
		if (nume[i] < 'A' || nume[i]>'z') {
			return false;
			
		}
	for (int i = 0; i < strlen(prenume); i++)
		if (prenume[i] < 'A' || prenume[i]>'z') {
			return false;
		}
	if (strlen(nume) == 0 || strlen(prenume) == 0) {
		return false;
	}

	if (id <= 0 || scor < 0) {
		return false;
	}
	return true;
}

/*
* Functia verifica daca toate valorile dintr-un vector sunt egale cu 1.
* >> Intrare:
*    - `v`: Un vector de intregi.
*    - `lenght`: Lungimea vectorului.
* >> Iesire:
*    - Returneaza `true` daca toate elementele din vector sunt egale cu 1.
*    - Returneaza `false` daca cel putin un element din vector este diferit de 1.
*/
bool verify_input(int v[], int lenght) {

	int i;
	for (i = 0; i < lenght; i++) {
		if (v[i] != 1) {
			return false;
		}
	}
	return true;
}