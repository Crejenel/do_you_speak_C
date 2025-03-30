#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <crtdbg.h>
#include "service.h"
#include "undo.h"
#include "tests.h"
#include "validator.h"

void run() {

	struct participant* lista = (struct participant*)calloc(10, sizeof(struct participant));
	int nr = 0;

	struct service* serv = creeaza_service(1);
	struct container_undo* undo = creaza_container_undo();
	int v[4];
	bool running = true;

	printf("<< APLICATIA RULEAZA >>\n");
	while (running) {

		printf("0. Paraseste aplicatia.\n");
		printf("1. Adauga participanti.\n");
		printf("2. Actualizeaza datele unui participant.\n");
		printf("3. Sterge participant.\n");
		printf("4. Sorteaza participantii dupa scor ( crescator ).\n");
		printf("5. Sorteaza participantii dupa scor ( descrescator ).\n");
		printf("6. Sorteaza participantii dupa nume ( crescator ).\n");
		printf("7. Sorteaza participantii dupa nume ( descrescator ).\n");
		printf("8. Filtrare participanti nepromovati.\n");
		printf("9. Filtrare participanti promovati.\n");
		printf("10. Revino la ultima operatie efectuata.\n");
		printf("11. Afisati participantii din sistem.\n");
		
		int optiune;
		printf(">> "); v[0] = scanf("%d", &optiune); while (getchar() != '\n');

		if (verify_input(v, 1)) {

			switch (optiune)
			{
			case 0:

				for (int i = 0; i < nr; i++) {
					destroy_participant(lista[i]);
				}
				free(lista);
				running = false;
				printf("! Ati iesit din program !\n");
				distruge_container_undo(undo);
				destroy_service(serv);
				break;

			case 1:

				printf("INTRODUCETI DATELE :\n");
				char nume[30];
				char prenume[30];
				int scor;
				int id;
				printf(">> nume : "); v[0] = scanf("%s", nume); while (getchar() != '\n');
				printf(">> prenume : "); v[1] = scanf("%s", prenume); while (getchar() != '\n');
				printf(">> scor : "); v[2] = scanf("%d", &scor); while (getchar() != '\n');
				printf(">> id : "); v[3] = scanf("%d", &id); while (getchar() != '\n');
				if (!verify_input(v, 4)) {
					printf("! Tipul datelor introduse este gresit !\n");
					break;
				}
				if (!verificare_unicitate(serv, id)) {
					printf("! ID-ul introdus apartine deja unui participant !\n");
					break;
				}
				if (!validare(nume, prenume, scor, id)) {
					printf("! Datele nu au putut fi validate !\n");
					break;
				}
				struct participant p = creeaza_participant(nume, prenume, scor, id);
				adauga(serv, p, undo);
				break;

			case 2:

				printf("INTRDUCETI ID-ul PARTICIPANTULUI CARUIA II INTENTIONATI SA-I ACTUALIZATI DATELE :\n");
				printf(">> id : "); v[0] = scanf("%d", &id); while (getchar() != '\n');
				if (!verify_input(v, 1)) {
					printf("! Tipul datelor introduse este gresit !\n");
					break;
				}
				if (verificare_unicitate(serv, id)) {
					printf("! ID-ul introdus nu apartine nici unui participant !\n");
					break;
				}
				printf("INTRODUCETI DATELE ACTUALIZATE ALE PARTICIPANETULUI :\n");
				printf(">> nume : "); v[0] = scanf("%s", nume); while (getchar() != '\n');
				printf(">> prenume : "); v[1] = scanf("%s", prenume); while (getchar() != '\n');
				printf(">> scor : "); v[2] = scanf("%d", &scor); while (getchar() != '\n');
				if (!verify_input(v, 3)) {
					printf("! Tipul datelor introduse este gresit !\n");
					break;
				}
				if (!validare(nume, prenume, scor, id)) {
					printf("! Datele nu au putut fi validate !\n");
					break;
				}
				p = creeaza_participant(nume, prenume, scor, id);
				actualizeaza(serv, id, p, undo);
				break;

			case 3:

				printf("INTRDUCETI ID-ul PARTICIPANTULUI pe care INTENTIONATI SA-L STERGETI :\n");
				printf(">> id : "); v[0] = scanf("%d", &id); while (getchar() != '\n');
				if (!verify_input(v, 1)) {
					printf("! Tipul datelor introduse este gresit !\n");
					break;
				}
				if (verificare_unicitate(serv, id)) {
					printf("! ID-ul introdus nu apartine nici unui participant !\n");
					break;
				}

				/////////////////////////////////////////////////////////////////////////////////
				p = get_participant(serv,id);
				lista[nr].nume = (char*)malloc(strlen(nume) + 1);
				lista[nr].prenume = (char*)malloc(strlen(prenume) + 1);
				if (p.nume == NULL && p.prenume == NULL) {
					printf("! ERROARE LA ALOCAREA MEMORIEI !\n");
				}

				lista[nr].id = p.id;
				strcpy(lista[nr].nume, p.nume);
				strcpy(lista[nr].prenume, p.prenume);
				lista[nr].scor = p.scor;
				nr++;
				for (int i = 0; i < nr; i++) {
					printf("ID : %d >> NUME : %s >> PRENUME : %s >> SCOR : %d\n", lista[i].id, lista[i].nume, lista[i].prenume, lista[i].scor);
				}
				/////////////////////////////////////////////////////////////////////////////////

;				sterge(serv, id, undo);
				break;

			case 4:
				
				sortare_dupa_scor_crescator(serv, compara_int);
				for (int i = 0; i < *(serv->nr_participanti); i++) {
					printf("ID : %d >> NUME : %s >> PRENUME : %s >> SCOR : %d\n",serv->participanti[i].id,serv->participanti[i].nume,serv->participanti[i].prenume,serv->participanti[i].scor);
				}
				break;

			case 5:
				
				sortare_dupa_scor_descrescator(serv, compara_int);
				for (int i = 0; i < *(serv->nr_participanti); i++) {
					printf("ID : %d >> NUME : %s >> PRENUME : %s >> SCOR : %d\n", serv->participanti[i].id, serv->participanti[i].nume, serv->participanti[i].prenume, serv->participanti[i].scor);
				}
				break;

			case 6:
				
				sortare_dupa_nume_crescator(serv, compara_string);
				for (int i = 0; i < *(serv->nr_participanti); i++) {
					printf("ID : %d >> NUME : %s >> PRENUME : %s >> SCOR : %d\n", serv->participanti[i].id, serv->participanti[i].nume, serv->participanti[i].prenume, serv->participanti[i].scor);
				}
				break;

			case 7:

				sortare_dupa_nume_crescator(serv, compara_string);
				for (int i = 0; i < *(serv->nr_participanti); i++) {
					printf("ID : %d >> NUME : %s >> PRENUME : %s >> SCOR : %d\n", serv->participanti[i].id, serv->participanti[i].nume, serv->participanti[i].prenume, serv->participanti[i].scor);
				}
				break;

			case 8:

				for (int i = 0; i < *(serv->nr_participanti); i++) {
					if (serv->participanti[i].scor < 50)
					{
						printf("ID : %d >> NUME : %s >> PRENUME : %s >> SCOR : %d\n", serv->participanti[i].id, serv->participanti[i].nume, serv->participanti[i].prenume, serv->participanti[i].scor);
					}	
				}
				break;
				
			case 9:

				for (int i = 0; i < *(serv->nr_participanti); i++) {
					if (serv->participanti[i].scor >= 50)
					{
						printf("ID : %d >> NUME : %s >> PRENUME : %s >> SCOR : %d\n", serv->participanti[i].id, serv->participanti[i].nume, serv->participanti[i].prenume, serv->participanti[i].scor);
					}
				}
				break;

			case 10:
				
				aplicare_undo_pe_repository(undo, serv);
				break;

			case 11 :

				for (int i = 0; i < *(serv->nr_participanti); i++) {

					printf("ID : %d >> NUME : %s >> PRENUME : %s >> SCOR : %d\n", serv->participanti[i].id, serv->participanti[i].nume, serv->participanti[i].prenume, serv->participanti[i].scor);	
				}
				break;

			default:
				printf("! Numarului introdus nu ii este asociata o comanda !\n");
			}
		}
		else {
			printf("! Trebuie sa va referiti la comenzi prin numere !\n");
		}
	
	}
}

int main() {

	//toate_testele();
	run();
	if (_CrtDumpMemoryLeaks()) {
		printf("Memory leak!");
	}
	else {
		printf("No memory leak!");
	}
		
	return 0;
}
