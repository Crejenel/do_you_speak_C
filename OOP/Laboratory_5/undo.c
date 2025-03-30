#include "undo.h"
#include "service.h"
#include <stdio.h>
#include <stdlib.h>

/*
* Functia creeaza un container pentru operatiuni de undo.
* >> Intrare:
*    - Nicio intrare.
* >> Iesire:
*    - Returneaza un pointer catre un container de undo, sau `NULL` daca alocarea memoriei esueaza.
*/
struct container_undo* creaza_container_undo() {

    struct container_undo* undo = (struct container_undo*)calloc(1, sizeof(struct container_undo));
    if (undo == NULL) { return NULL;}

    undo->back = (void**)calloc(1, sizeof(void*));
    if (undo->back == NULL) { free(undo); return NULL;}
    return undo;
}

/*
* Functia distruge un container de undo si elibereaza memoria asociata.
* >> Intrare:
*    - `undo`: Un pointer catre containerul de undo care trebuie distrus.
* >> Iesire:
*    - Nu returneaza nicio valoare.
*/
void distruge_container_undo(struct container_undo* undo) {

    int i,j;
    for (i = 0; i < undo->size; i++) {
            
        for (j = 0; j < *(((struct service*)undo->back[i])->nr_participanti); j++)
        {
            destroy_participant(((struct service*)undo->back[i])->participanti[j]);
        }
        free(((struct service*)undo->back[i])->nr_participanti);
        free(((struct service*)undo->back[i])->participanti);
        free(undo->back[i]);
    }
    free(undo->back);
    free(undo);
}

/*
* Functia adauga o operatiune intr-un container de undo.
* >> Intrare:
*    - `undo`: Un pointer catre containerul de undo in care se adauga operatiunea.
*    - `p`: Un pointer catre operatiunea care trebuie adaugata.
* >> Iesire:
*    - Nu returneaza nicio valoare.
*/
void adauga_in_container_undo(struct container_undo* undo, void* p) {
    
    void** pointer = undo->back;
    void** new_back = (void**)realloc(undo->back, (undo->size + 1) * sizeof(void*));

    if (new_back == NULL) { undo->back = pointer; return;}

    undo->back = new_back;
    undo->back[undo->size] = p; 
    undo->size++;
}

/*
* Functia aplica operatiunea de undo asupra unui serviciu, restabilind starea anterioara.
* >> Intrare:
*    - `undo`: Un pointer catre containerul de undo care contine operatiunile anterioare.
*    - `serv`: Un pointer catre serviciul asupra caruia se aplica operatiunea de undo.
* >> Iesire:
*    - Nu returneaza nicio valoare.
*/
void aplicare_undo_pe_repository(struct container_undo* undo, struct service* serv) {

    if (undo->size > 0) {

        if (undo->size == 1) {

            free(((struct service*)undo->back[0])->nr_participanti);
            destroy_participant(((struct service*)undo->back[0])->participanti[0]);
            free(((struct service*)undo->back[0])->participanti);
            
            free(undo->back[0]);
            undo->size = 0;

            destroy_participant(serv->participanti[0]);
            free(serv->participanti);
            serv->participanti = NULL;
            *(serv->nr_participanti) = 0;

            return;}

        else if(undo->size > 1) {

            for (int i = 0; i < *serv->nr_participanti; i++)
            {
                destroy_participant(serv->participanti[i]);
            }
            free(serv->nr_participanti);
            free(serv->participanti);

            for (int i = 0; i < *(((struct service*)undo->back[undo->size - 1])->nr_participanti); i++) {
                destroy_participant(((struct service*)undo->back[undo->size - 1])->participanti[i]);
            }
            free(((struct service*)undo->back[undo->size-1])->nr_participanti);
            free(((struct service*)undo->back[undo->size-1])->participanti);
            free(undo->back[undo->size-1]);
            undo->size--;

            serv->nr_participanti = (int*)calloc(1, sizeof(int));
            if (serv->nr_participanti == NULL) { return; }

            *(serv->nr_participanti) = *(((struct service*)undo->back[undo->size - 1])->nr_participanti);

            serv->participanti = (struct participant*)malloc(*(serv->nr_participanti) * sizeof(struct participant));
            if (serv->participanti==NULL) { free(serv->nr_participanti); return;}

            for (int i = 0; i < *(serv->nr_participanti); i++) {

                struct participant p = creeaza_participant(((struct service*)undo->back[undo->size - 1])->participanti[i].nume, ((struct service*)undo->back[undo->size - 1])->participanti[i].prenume, ((struct service*)undo->back[undo->size - 1])->participanti[i].scor, ((struct service*)undo->back[undo->size - 1])->participanti[i].id);
                serv->participanti[i] = p;
            }

        }

        void** new_back = (void**)realloc(undo->back, undo->size * sizeof(void*));

        if (new_back == NULL) { return;}

        undo->back = new_back;
    }
}
