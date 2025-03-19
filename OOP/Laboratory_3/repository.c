#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "repository.h"


struct storage Storage = { 0 };

char* add_property(struct property* pro){

	int index = exist_property(pro->cod_vanzare);
	if (!(index>-1) && Storage.property_count < 98) {
		Storage.proprietati[Storage.property_count] = *pro;
		Storage.property_count++;
		return "#999"; }
	else {

		return "#998";
	}
}

char* delete_property(int code_sale){

	bool find = false;

	int i;
	for (i = 0; i < Storage.property_count; i++) {
		if (Storage.proprietati[i].cod_vanzare == code_sale)
		{
			find = true;
		}
		if (find) {
			Storage.proprietati[i] = Storage.proprietati[i + 1];
		}
	}
	if (find) {

		Storage.property_count--;
		return "#997"; }
	else {
		return "#996";
	}

}

char* update_property(int code_sale, struct property* pro){

	int index = exist_property(code_sale);
	if (index>-1) {

		if (pro->adresa.nr != 0) {
			Storage.proprietati[index].adresa.nr = pro->adresa.nr;
		}
		if (strcmp(pro->adresa.localitate,"")) {
			strcpy(Storage.proprietati[index].adresa.localitate,pro->adresa.localitate);
		}
		if (strcmp(pro->adresa.strada, "")) {
			strcpy(Storage.proprietati[index].adresa.strada, pro->adresa.strada);
		}
		if (pro->pret != 0.0) {
			Storage.proprietati[index].pret = pro->pret;
		}
		if (pro->reducere != 0) {
			Storage.proprietati[index].reducere = pro->reducere;
		}
		if (pro->suprafata_proprietate != 0.0) {
			Storage.proprietati[index].suprafata_proprietate = pro->suprafata_proprietate;
		}
		if (strcmp(pro->tip_proprietate, "")) {
			strcpy(Storage.proprietati[index].tip_proprietate, pro->tip_proprietate);
		}
		return "#995"; }
	else {
		return "#994";
	}

}

int exist_property(int code_sale){

	int i;
	for (i = 0; i < Storage.property_count; i++) {
		if (Storage.proprietati[i].cod_vanzare == code_sale) {
			return i;
		}
	}
	return -1;
}

struct storage* filtering_property_char(char* criterio, char* value) {

	static struct storage STORAGE;
	int i;
	for (i = 0; i < STORAGE.property_count; i++) {

		STORAGE.proprietati[i].cod_vanzare = 0;
		STORAGE.proprietati[i].pret = 0;
		STORAGE.proprietati[i].reducere = 0;
		STORAGE.proprietati[i].suprafata_proprietate = 0;
		strcpy(STORAGE.proprietati[i].tip_proprietate,"");
		strcpy(STORAGE.proprietati[i].adresa.localitate, "");
		strcpy(STORAGE.proprietati[i].adresa.strada, "");
		STORAGE.proprietati[i].adresa.nr = 0;
	}
	STORAGE.property_count = 0;

	if (strcmp(criterio, "error") != 0) {

		if (strcmp(criterio, "tip proprietate") == 0) {

				for (i = 0; i < Storage.property_count; i++) {

					if (strcmp(Storage.proprietati[i].tip_proprietate, value) == 0) {
						STORAGE.proprietati[STORAGE.property_count] = Storage.proprietati[i];
						STORAGE.property_count++;
					}

				}
				return &STORAGE;

			}


		if (strcmp(criterio, "localitate") == 0) {

			for (i = 0; i < Storage.property_count; i++) {

				if (strcmp(Storage.proprietati[i].adresa.localitate, value) == 0) {
					STORAGE.proprietati[STORAGE.property_count] = Storage.proprietati[i];
					STORAGE.property_count++;
				}
			}
			return &STORAGE; } }

	else {

		STORAGE.property_count = -1;
	}

	return &STORAGE;

}

struct storage* filtering_property_number(char* criterio, double numar, bool greater) {

	static struct storage STORAGE;
	int i;
	for (i = 0; i < STORAGE.property_count; i++) {

		STORAGE.proprietati[i].cod_vanzare = 0;
		STORAGE.proprietati[i].pret = 0;
		STORAGE.proprietati[i].reducere = 0;
		STORAGE.proprietati[i].suprafata_proprietate = 0;
		strcpy(STORAGE.proprietati[i].tip_proprietate, "");
		strcpy(STORAGE.proprietati[i].adresa.localitate, "");
		strcpy(STORAGE.proprietati[i].adresa.strada, "");
		STORAGE.proprietati[i].adresa.nr = 0;
	}
	STORAGE.property_count = 0;

	if (strcmp(criterio, "pret") == 0) {


		for (i = 0; i < Storage.property_count; i++) {

			if (Storage.proprietati[i].pret >= numar && greater) {
				STORAGE.proprietati[STORAGE.property_count] = Storage.proprietati[i];
				STORAGE.property_count++;
			}
			else if (Storage.proprietati[i].pret <= numar && (!(greater))) {
				STORAGE.proprietati[STORAGE.property_count] = Storage.proprietati[i];
				STORAGE.property_count++;
			}
		}
		return &STORAGE;

	} else if (strcmp(criterio, "suprafata proprietate") == 0) {


		for (i = 0; i < Storage.property_count; i++) {

			if (Storage.proprietati[i].suprafata_proprietate >= numar && greater) {
				STORAGE.proprietati[STORAGE.property_count] = Storage.proprietati[i];
				STORAGE.property_count++;
			}
			else if (Storage.proprietati[i].suprafata_proprietate <= numar && (!(greater))) {
				STORAGE.proprietati[STORAGE.property_count] = Storage.proprietati[i];
				STORAGE.property_count++;
			}
		}
		return &STORAGE;

	}
	

}

struct property get_property(int code_sale) {

	struct property PROPRIETATE = { 0 };
	int index = exist_property(code_sale);
	if (index>-1) {

		PROPRIETATE = Storage.proprietati[index];
		
	}
	return PROPRIETATE;
}

struct storage* get_all() {

	static struct storage STORAGE;
	STORAGE = Storage;
	return &Storage;

}


