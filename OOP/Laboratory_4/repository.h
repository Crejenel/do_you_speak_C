#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "domain.h"

struct storage {

	int property_count;
	int max;
	struct property* proprietati;

};

char* storage_management();

void free_storage();

char* add_property(int cod_vanzare, char* tip_proprietate, double suprafat_proprietate, double pret, char* strada, int nr, char* localitate);

char* delete_property(int code_sale);

char* update_property(int code_sale, struct property* pro);

int exist_property(int code_sale);

struct storage* filtering_property_char(char* criterio, char* value);

struct storage* filtering_property_number(char* criterio, double* numar, bool greater);

struct property* get_property(int code_sale);

struct storage* get_all();

struct property* get_property(int code_sale);


#endif