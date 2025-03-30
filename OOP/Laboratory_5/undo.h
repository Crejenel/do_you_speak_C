#ifndef UNDO_H
#define UNDO_H

struct container_undo {

	void** back;
	int size;

};

struct container_undo* creaza_container_undo();

void distruge_container_undo(struct container_undo* undo);

void adauga_in_container_undo(struct container_undo* undo, void* p);

void aplicare_undo_pe_repository(struct container_undo* undo, struct service* serv);

#endif