#define _CRT_SECURE_NO_WARNINGS
#include "service.h"
#include "undo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
* Funcția alocă și inițializează o structură de tip `service`.
* >> Intrare:
*    - `nr`: Un număr întreg care reprezintă numărul de participanți ce vor fi alocați.
* >> Ieșire:
*    - Returnează un pointer către o structură `service` nou alocată, dacă alocarea memoriei are succes.
*    - Returnează `NULL` dacă alocarea memoriei eșuează în orice etapă.
*/
struct service* creeaza_service(int nr) {

	struct service* serv = (struct service*)malloc(sizeof(struct service));
	if (serv == NULL) { return NULL; }

	serv->nr_participanti = (int*)calloc(1,sizeof(int));
	if (serv->nr_participanti == NULL) { free(serv); return NULL;}

	serv->participanti = (struct participant*)malloc(nr*sizeof(struct participant));
	if (serv->participanti == NULL) { free(serv->nr_participanti); free(serv); return NULL;}

	return serv;
}

/*
* Funcția creează și inițializează o structură de tip `participant`.
* >> Intrare:
*    - `nume`: Un șir de caractere care reprezintă numele participantului.
*    - `prenume`: Un șir de caractere care reprezintă prenumele participantului.
*    - `scor`: Un număr întreg care reprezintă scorul participantului.
*    - `id`: Un număr întreg care reprezintă identificatorul unic al participantului.
* >> Ieșire:
*    - Returnează o structură `participant` inițializată cu valorile primite ca parametri.
*/
struct participant creeaza_participant(char* nume, char* prenume, int scor, int id){

	struct participant p;
	p.scor = scor;
	p.id = id;
	p.nume = (char*)malloc(strlen(nume) + 1);
	p.prenume = (char*)malloc(strlen(prenume) + 1);
	if (p.nume != NULL && p.prenume != NULL) {
		strcpy_s(p.nume, strlen(nume) + 1, nume);
		strcpy_s(p.prenume, strlen(prenume) + 1, prenume);
	}
	return p;
}

/*
* Funcția eliberează memoria alocată pentru un `participant`.
* >> Intrare:
*    - `p`: O structură `participant` ale cărei câmpuri `nume` și `prenume` au fost alocate dinamic.
* >> Ieșire:
*    - Nu returnează nicio valoare.
*/
void destroy_participant(struct participant p) {
	
	free(p.nume);
	free(p.prenume);
}

/*
* Funcția eliberează memoria alocată pentru un obiect de tip `service`.
* >> Intrare:
*    - `serv`: Un pointer către structura `service` care trebuie eliberată.
* >> Ieșire:
*    - Nu returnează nicio valoare.
*/
void destroy_service(struct service* serv) {

	for (int i = 0; i < *serv->nr_participanti; i++)
	{
		destroy_participant(serv->participanti[i]);
	}

	free(serv->nr_participanti);
	free(serv->participanti);
	free(serv);
}

/*
* Funcția compară două valori întregi și determină ordinea acestora.
* >> Intrare:
*    - `scor1`: Un număr întreg care reprezintă prima valoare de comparat.
*    - `scor2`: Un număr întreg care reprezintă a doua valoare de comparat.
* >> Ieșire:
*    - Returnează `1` dacă `scor1` este mai mic decât `scor2`.
*    - Returnează `0` în caz contrar.
*/
int compara_int(int scor1, int scor2) {
	if (scor1 < scor2)
		return 1;
	return 0;
}

/*
* Funcția compară două șiruri de caractere lexicografic.
* >> Intrare:
*    - `s1`: Un șir de caractere care reprezintă primul string de comparat.
*    - `s2`: Un șir de caractere care reprezintă al doilea string de comparat.
* >> Ieșire:
*    - Returnează `1` dacă `s1` este lexicografic mai mic decât `s2`.
*    - Returnează `0` în caz contrar.
*/
int compara_string(char* s1, char* s2) {
	if (strcmp(s1, s2) < 0)
		return 1;
	return 0;
}

/*
* Funcția verifică dacă doi participanți sunt egali pe baza ID-ului.
* >> Intrare:
*    - `p1`: O structură `participant` care reprezintă primul participant.
*    - `p2`: O structură `participant` care reprezintă al doilea participant.
* >> Ieșire:
*    - Returnează `true` dacă ID-urile celor doi participanți sunt egale.
*    - Returnează `false` în caz contrar.
*/
bool egale(struct participant p1, struct participant p2) {
	if (p1.id == p2.id)
		return true;
	return false;
}

/*
* Funcția adaugă un participant într-un serviciu și gestionează operațiile de undo.
* >> Intrare:
*    - `serv`: Un pointer către structura `service` unde se adaugă participantul.
*    - `p`: O structură `participant` care reprezintă participantul ce trebuie adăugat.
*    - `undo`: Un pointer către un container de operațiuni undo.
* >> Ieșire:
*    - Nu returnează nicio valoare.
*/
void adauga(struct service* serv, struct participant p, struct container_undo* undo) {

	void* pointer = serv->participanti;
	(*serv->nr_participanti)++;
	serv->participanti = (struct participant*)realloc(serv->participanti, *(serv->nr_participanti) * sizeof(struct participant));
	if (serv->participanti == NULL) { serv->participanti = pointer; (*serv->nr_participanti)--; return; }

	serv->participanti[*(serv->nr_participanti) - 1] = p;

	//  -----------------undo----------------- // 
	struct service* SERV = creeaza_service(*(serv->nr_participanti));
	if (SERV->participanti == NULL) { return;}

	int i;
	for (i = 0; i < *(serv->nr_participanti); i++) {
		
		struct participant p = creeaza_participant(serv->participanti[i].nume, serv->participanti[i].prenume, serv->participanti[i].scor, serv->participanti[i].id);
		SERV->participanti[i] = p;

	}
	*SERV->nr_participanti = *serv->nr_participanti;
	adauga_in_container_undo(undo, SERV);
}

/*
* Funcția șterge un participant dintr-un serviciu pe baza ID-ului și gestionează operațiile de undo.
* >> Intrare:
*    - `serv`: Un pointer către structura `service` din care se șterge participantul.
*    - `id`: Un număr întreg care reprezintă ID-ul participantului care trebuie șters.
*    - `undo`: Un pointer către un container de operațiuni undo.
* >> Ieșire:
*    - Nu returnează nicio valoare.
*/
void sterge(struct service* serv, int id, struct container_undo* undo) {

	for (int i = 0; i < *(serv->nr_participanti); i++) {

		if (serv->participanti[i].id==id) {

            destroy_participant(serv->participanti[i]);
			for (int j = i; j < *(serv->nr_participanti) - 1; j++)
			{
				serv->participanti[j] = serv->participanti[j + 1];
			}
			(*serv->nr_participanti)--;

			//  -----------------undo----------------- //
			struct service* SERV = creeaza_service(*(serv->nr_participanti));
			if (SERV->participanti == NULL) { return;}

			int i;
			for (i = 0; i < *(serv->nr_participanti); i++) {

				struct participant p = creeaza_participant(serv->participanti[i].nume, serv->participanti[i].prenume, serv->participanti[i].scor, serv->participanti[i].id);
				SERV->participanti[i] = p;

			}
			*SERV->nr_participanti = *serv->nr_participanti;
			adauga_in_container_undo(undo, SERV);
		}
	}
}

/*
* Funcția actualizează un participant dintr-un serviciu pe baza ID-ului și gestionează operațiile de undo.
* >> Intrare:
*    - `serv`: Un pointer către structura `service` în care se actualizează participantul.
*    - `id`: Un număr întreg care reprezintă ID-ul participantului care trebuie actualizat.
*    - `p`: O structură `participant` care reprezintă noile informații ale participantului.
*    - `undo`: Un pointer către un container de operațiuni undo.
* >> Ieșire:
*    - Nu returnează nicio valoare.
*/
void actualizeaza(struct service* serv, int id, struct participant p, struct container_undo* undo) {

	for (int i = 0; i < *(serv->nr_participanti); i++)
		if (serv->participanti[i].id == id)
		{
			destroy_participant(serv->participanti[i]);
			serv->participanti[i] = p;

			//  -----------------undo----------------- // 
			struct service* SERV = creeaza_service(*(serv->nr_participanti));
			if (SERV->participanti == NULL) { return;}

			int i;
			for (i = 0; i < *(serv->nr_participanti); i++) {

				struct participant p = creeaza_participant(serv->participanti[i].nume, serv->participanti[i].prenume, serv->participanti[i].scor, serv->participanti[i].id);
				SERV->participanti[i] = p;

			}
			*SERV->nr_participanti = *serv->nr_participanti;
			adauga_in_container_undo(undo, SERV);
			break; }
}

/*
* Funcția sortează participanții dintr-un serviciu în ordine crescătoare după nume.
* >> Intrare:
*    - `serv`: Un pointer către structura `service` care conține participanții ce trebuie sortați.
*    - `compara_string`: Un pointer către o funcție de comparare a șirurilor de caractere.
* >> Ieșire:
*    - Nu returnează nicio valoare.
*/
void sortare_dupa_nume_crescator(struct service* serv, int(*compara_string)(char*, char*)) {
	for (int i = 0; i < *(serv->nr_participanti) - 1; i++)
		for (int j = i + 1; j < *(serv->nr_participanti); j++)
			if (!compara_string(serv->participanti[i].nume, serv->participanti[j].nume)) {
				struct participant aux = serv->participanti[i];
				serv->participanti[i] = serv->participanti[j];
				serv->participanti[j] = aux;
			}
}

/*
* Funcția sortează participanții dintr-un serviciu în ordine descrescătoare după nume.
* >> Intrare:
*    - `serv`: Un pointer către structura `service` care conține participanții ce trebuie sortați.
*    - `compara_string`: Un pointer către o funcție de comparare a șirurilor de caractere.
* >> Ieșire:
*    - Nu returnează nicio valoare.
*/
void sortare_dupa_nume_descrescator(struct service* serv, int(*compara_string)(char*, char*)) {
	for (int i = 0; i < *(serv->nr_participanti) - 1; i++)
		for (int j = i + 1; j < *(serv->nr_participanti); j++)
			if (compara_string(serv->participanti[i].nume, serv->participanti[j].nume)) { 
				struct participant aux = serv->participanti[i];
				serv->participanti[i] = serv->participanti[j];
				serv->participanti[j] = aux;
			}
}

/*
* Funcția sortează participanții dintr-un serviciu în ordine crescătoare după scor.
* >> Intrare:
*    - `serv`: Un pointer către structura `service` care conține participanții ce trebuie sortați.
*    - `compara_int`: Un pointer către o funcție de comparare a valorilor întregi.
* >> Ieșire:
*    - Nu returnează nicio valoare.
*/
void sortare_dupa_scor_crescator(struct service* serv, int(*compara_int)(int, int)) {
	for (int i = 0; i < *(serv->nr_participanti) - 1; i++)
		for (int j = i + 1; j < *(serv->nr_participanti); j++)
			if (compara_int(serv->participanti[j].scor, serv->participanti[i].scor)) {
				struct participant aux = serv->participanti[i];
				serv->participanti[i] = serv->participanti[j];
				serv->participanti[j] = aux;
			}
}

/*
* Funcția sortează participanții dintr-un serviciu în ordine descrescătoare după scor.
* >> Intrare:
*    - `serv`: Un pointer către structura `service` care conține participanții ce trebuie sortați.
*    - `compara_int`: Un pointer către o funcție de comparare a valorilor întregi.
* >> Ieșire:
*    - Nu returnează nicio valoare.
*/
void sortare_dupa_scor_descrescator(struct service* serv, int(*compara_int)(int, int)){

	for (int i = 0; i < *(serv->nr_participanti) - 1; i++)
		for (int j = i + 1; j < *(serv->nr_participanti); j++)
			if (!compara_int(serv->participanti[j].scor, serv->participanti[i].scor)) {//serv->participanti[i].scor < serv->participanti[j].scor
				struct participant aux = serv->participanti[i];
				serv->participanti[i] = serv->participanti[j];
				serv->participanti[j] = aux;
			}
}

/*
* Funcția verifică dacă un participant cu un anumit ID există deja într-un serviciu.
* >> Intrare:
*    - `serv`: Un pointer către structura `service` în care se caută participantul.
*    - `id`: Un număr întreg care reprezintă ID-ul participantului ce trebuie verificat.
* >> Ieșire:
*    - Returnează `true` dacă ID-ul nu este găsit în lista de participanți (adică ID-ul este unic).
*    - Returnează `false` dacă ID-ul există deja în lista de participanți.
*/
bool verificare_unicitate(struct service* serv,int id) {

	for (int i = 0; i < *(serv->nr_participanti); i++) {
		if (serv->participanti[i].id == id) {
			return false;
		}
	}
	return true;
}

/*
* Funcția returnează un participant dintr-un serviciu pe baza ID-ului.
* >> Intrare:
*    - `serv`: Un pointer către structura `service` din care se extrage participantul.
*    - `id`: Un număr întreg care reprezintă ID-ul participantului căutat.
* >> Ieșire:
*    - Returnează participantul care are ID-ul specificat.
*    - Comportamentul este nedefinit dacă ID-ul nu există în lista de participanți.
*/
struct participant get_participant(struct service* serv, int id) {

	int i;
	for (i = 0; i < *(serv->nr_participanti); i++) {
		if (serv->participanti[i].id == id) {
			break; } }

	return serv->participanti[i];

}
