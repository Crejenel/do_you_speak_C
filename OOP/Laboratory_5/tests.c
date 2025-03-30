#include "service.h"
#include "tests.h"
#include "validator.h"
#include "undo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

void test_adauga() {

	struct service* serv = creeaza_service(1);
	struct container_undo* undo = creaza_container_undo();

	struct participant p = creeaza_participant("Miriam", "Popescu", 10, 1);
	adauga(serv, p, undo);
	struct participant q = creeaza_participant("Miriam", "Popescu", 10, 2);
	assert(egale(p, q) == false);
	destroy_participant(q);

	p = creeaza_participant("Andrei", "Dumitru", 10, 2);
	adauga(serv, p, undo);

	assert(serv->participanti[0].id==1);
	assert(strcmp(serv->participanti[0].nume,"Miriam")==0);
	assert(serv->participanti[1].id==2);
	assert(strcmp(serv->participanti[1].nume,"Andrei") == 0);

	assert(*(serv->nr_participanti) == 2);
	assert(undo->size == 2);
	
	assert(*(((struct service*)undo->back[0])->nr_participanti) == 1);
	assert(*(((struct service*)undo->back[1])->nr_participanti) == 2);
	assert(strcmp(((struct service*)undo->back[0])->participanti[0].nume,"Miriam") == 0);
	assert(strcmp(((struct service*)undo->back[1])->participanti[0].nume, "Miriam") == 0);
	assert(strcmp(((struct service*)undo->back[1])->participanti[1].nume, "Andrei") == 0);

	aplicare_undo_pe_repository(undo, serv);

	assert(*(serv->nr_participanti) == 1);
	assert(serv->participanti[0].id == 1);
	assert(strcmp(serv->participanti[0].nume, "Miriam") == 0);

	distruge_container_undo(undo);
	destroy_service(serv);

}

void test_sterge() {

	struct service* serv = creeaza_service(1);
	struct container_undo* undo = creaza_container_undo();

	struct participant p = creeaza_participant("Ana", "Aniuc", 10, 1);
	adauga(serv, p, undo);
	p = creeaza_participant("Marius", "Otniel", 20, 2);
	adauga(serv, p, undo);

	sterge(serv, 1, undo);

	assert(undo->size == 3);
	assert(*(serv->nr_participanti) == 1);
	assert(*(((struct service*)undo->back[2])->nr_participanti) == 1);
	assert(((struct service*)undo->back[2])->participanti[0].id == 2);

	aplicare_undo_pe_repository(undo, serv);

	assert(undo->size == 2);
	assert(*(serv->nr_participanti) == 2);
	assert(*(((struct service*)undo->back[1])->nr_participanti) == 2);
	assert(((struct service*)undo->back[1])->participanti[0].id == 1);
	assert(serv->participanti[0].id == 1);
	assert(serv->participanti[1].id == 2);

	distruge_container_undo(undo);
	destroy_service(serv);
}

void test_actualizare() {

	struct service* serv = creeaza_service(1);
	struct container_undo* undo = creaza_container_undo();

	struct participant p = creeaza_participant("Andronic", "Macelaru", 10, 1);
	adauga(serv, p, undo);
	p = creeaza_participant("Ioana", "Serdenciuc", 20, 2);
	adauga(serv, p, undo);

	p = creeaza_participant("Zac", "Backly", 30, 3);
	actualizeaza(serv, 1, p, undo);

	assert(*(serv->nr_participanti) == 2);
	assert(strcmp(serv->participanti[0].nume, "Zac") == 0);

	sterge(serv, 3, undo);
	assert(*(serv->nr_participanti) == 1);

	aplicare_undo_pe_repository(undo, serv);
	aplicare_undo_pe_repository(undo, serv);

	assert(*(serv->nr_participanti) == 2);
	assert(strcmp(serv->participanti[0].nume, "Andronic") == 0);

	distruge_container_undo(undo);
	destroy_service(serv);
}

void test_sortare_dupa_scor_descrescator() {

	struct service* serv = creeaza_service(1);
	struct container_undo* undo = creaza_container_undo();

	struct participant p1 = creeaza_participant("Popescu", "Ion", 10, 1);
	struct participant p2 = creeaza_participant("Ionescu", "Maria", 20, 2);
	struct participant p3 = creeaza_participant("Georgescu", "Andrei", 30, 3);

	adauga(serv, p1, undo);
	adauga(serv, p2, undo);
	adauga(serv, p3, undo);

	sortare_dupa_scor_descrescator(serv, &compara_int);
	assert(egale(serv->participanti[0], p3) == true);
	assert(egale(serv->participanti[1], p2) == true);
	assert(egale(serv->participanti[2], p1) == true);

	distruge_container_undo(undo);
	destroy_service(serv);
}

void test_sortare_dupa_nume_descrescator() {

	struct service* serv = creeaza_service(1);
	struct container_undo* undo = creaza_container_undo();

	struct participant p1 = creeaza_participant("a", "b", 3, 1);
	struct participant p2 = creeaza_participant("c", "d", 4, 2);
	adauga(serv, p1, undo);
	adauga(serv, p2, undo);
	sortare_dupa_nume_descrescator(serv, &compara_string);
	assert(egale(serv->participanti[0], p2) == true);

	distruge_container_undo(undo);
	destroy_service(serv);
}

void test_sortare_dupa_scor_crescator() {

	struct service* serv = creeaza_service(1);
	struct container_undo* undo = creaza_container_undo();

	struct participant p1 = creeaza_participant("Popescu", "Ion", 10, 1);
	struct participant p2 = creeaza_participant("Ionescu", "Maria", 30, 2);
	struct participant p3 = creeaza_participant("Georgescu", "Andrei", 20, 3);

	adauga(serv, p1, undo);
	adauga(serv, p2, undo);
	adauga(serv, p3, undo);

	sortare_dupa_scor_crescator(serv, &compara_int);

	assert(egale(serv->participanti[0], p1) == true);
	assert(egale(serv->participanti[1], p3) == true);
	assert(egale(serv->participanti[2], p2) == true);

	distruge_container_undo(undo);
	destroy_service(serv);
}

void test_sortare_dupa_nume_crescator() {

	struct service* serv = creeaza_service(1);
	struct container_undo* undo = creaza_container_undo();

	struct participant p1 = creeaza_participant("Popescu", "Ion", 10, 1);
	struct participant p2 = creeaza_participant("Ionescu", "Maria", 20, 2);
	struct participant p3 = creeaza_participant("Georgescu", "Andrei", 30, 3);

	adauga(serv, p1, undo);
	adauga(serv, p2, undo);
	adauga(serv, p3, undo);

	sortare_dupa_nume_crescator(serv, &compara_string);
	assert(egale(serv->participanti[0], p3) == true);
	assert(egale(serv->participanti[1], p2) == true);
	assert(egale(serv->participanti[2], p1) == true);

	distruge_container_undo(undo);
	destroy_service(serv);
}

void test_undo() {

	struct service* serv = creeaza_service(1);
	struct container_undo* undo = creaza_container_undo();

	struct participant p = creeaza_participant("Ana", "Aniuc", 10, 1);
	adauga(serv, p, undo);

	aplicare_undo_pe_repository(undo, serv);
	assert(undo->size == 0);
	assert(*(serv->nr_participanti) == 0);

	p = creeaza_participant("Ana", "Aniuc", 10, 1);
	adauga(serv, p, undo);
	assert(serv->participanti[0].id == 1);
	assert(*(serv->nr_participanti) == 1);

	p = get_participant(serv,1);
	assert(p.id == 1);

	distruge_container_undo(undo);
	destroy_service(serv);
}

void test_validator() {

	struct service* serv = creeaza_service(1);
	struct container_undo* undo = creaza_container_undo();

	struct participant p = creeaza_participant("Ana", "Aniuc", 10, 1);
	adauga(serv, p, undo);

	assert(validare("nu1e", "prenume", 10, 1) == false);
	assert(validare("nume", "pr0nume", -10, 1) == false);
	assert(validare("nume", "prenume", -10, 1) == false);
	assert(validare("nume", "prenume", 10, -1) == false);
	assert(validare("nume", "prenume", 10, 1) == true);
	assert(validare("", "prenume", 10, 1) == false);
	int v[] = { 1,1,1 };
	assert(verify_input(v, 3) == true);
	v[0] = 0;
	assert(verify_input(v, 3) == false);
	assert(verificare_unicitate(serv, 1) == false);
	assert(verificare_unicitate(serv, 2) == true);

	distruge_container_undo(undo);
	destroy_service(serv);



}

void toate_testele() {
	
	test_adauga();
	test_sterge();
	test_actualizare();
	test_sortare_dupa_scor_descrescator();
	test_sortare_dupa_nume_descrescator();
	test_sortare_dupa_scor_crescator();
	test_sortare_dupa_nume_crescator();
	test_validator();
	test_undo();

	printf("Toate testele trecute\n");
	
}
