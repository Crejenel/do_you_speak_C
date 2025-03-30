#include <stdbool.h>
#ifndef SERVICE_H
#define SERVICE_H

struct participant {
    int id;
    int scor;
    char* nume;
    char* prenume;
};

struct service {
    int* nr_participanti;
    struct participant* participanti;
};

struct participant creeaza_participant(char* nume, char* prenume, int scor, int id);
void destroy_participant(struct participant p);

struct service* creeaza_service(int nr);
void destroy_service(struct service* serv);

void adauga(struct service* serv, struct participant p, struct container_undo* undo);
bool egale(struct participant p1, struct participant p2);

void sterge(struct service* serv, int id, struct container_undo* undo);
void actualizeaza(struct service* serv, int id, struct participant p, struct container_undo* undo);

void sortare_dupa_nume_crescator(struct service* serv, int(*compara_string)(char*, char*));
void sortare_dupa_nume_descrescator(struct service* serv, int(*compara_string)(char*, char*));
void sortare_dupa_scor_crescator(struct service* serv, int(*compara_int)(int, int));
void sortare_dupa_scor_descrescator(struct service* serv, int(*compara_int)(int, int));

int compara_int(int scor1, int scor2);
int compara_string(char* s1, char* s2);

bool verificare_unicitate(struct service* serv, int id);
struct participant get_participant(struct service* serv, int id);

#endif
