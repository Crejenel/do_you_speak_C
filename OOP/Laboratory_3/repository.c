#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "repository.h"


struct storage Storage = { 0 };

/*
* The function attempts to add a property to the storage if it doesn't already exist.
* >> Input: a pointer to a 'property' struct 'pro' (struct property*).
* >> Output: a string representing the result of the operation.
*           - "#999" if the property was successfully added.
*           - "#998" if the property already exists or the storage is full.
*/
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

/*
* The function attempts to delete a property from the storage based on the sale code.
* >> Input: an integer 'code_sale' representing the sale code of the property to be deleted (int).
* >> Output: a string representing the result of the operation.
*           - "#997" if the property was successfully deleted.
*           - "#996" if the property was not found.
*/
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

/*
* The function updates the properties of an existing property in the storage based on the sale code.
* >> Input: an integer 'code_sale' representing the sale code of the property to be updated (int),
*           and a pointer to a 'property' struct 'pro' containing the new property data (struct property*).
* >> Output: a string representing the result of the operation.
*           - "#995" if the property was successfully updated.
*           - "#994" if the property with the given sale code was not found.
*/
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

/*
* The function checks if a property with the given sale code exists in the storage.
* >> Input: an integer 'code_sale' representing the sale code of the property to search for (int).
* >> Output: the index of the property in the storage if found (int),
*           or -1 if the property with the given sale code does not exist.
*/
int exist_property(int code_sale){

	int i;
	for (i = 0; i < Storage.property_count; i++) {
		if (Storage.proprietati[i].cod_vanzare == code_sale) {
			return i;
		}
	}
	return -1;
}

/*
* The function filters properties based on a string-based criterion (e.g., property type or locality).
* >> Input: a string 'criterio' representing the filtering criterion (char*),
*           and a string 'value' representing the value to filter by (char*).
* >> Output: a pointer to a 'storage' struct containing the filtered properties.
*           - If the 'criterio' is "tip proprietate", it filters properties by type.
*           - If the 'criterio' is "localitate", it filters properties by locality.
*           - If the 'criterio' is "error", it indicates no valid filtering was applied.
*/
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

/*
* The function filters properties based on a numeric criterion (e.g., price or property area).
* >> Input: a string 'criterio' representing the filtering criterion (char*),
*           a double 'numar' representing the value to filter by (double),
*           and a boolean 'greater' indicating whether to filter by greater or smaller than 'numar' (bool).
* >> Output: a pointer to a 'storage' struct containing the filtered properties.
*           - If the 'criterio' is "pret", it filters properties by price.
*           - If the 'criterio' is "suprafata proprietate", it filters properties by area.
*/
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

/*
* The function retrieves a property from the storage based on the given sale code.
* >> Input: an integer 'code_sale' representing the sale code of the property to be retrieved (int).
* >> Output: a 'property' struct representing the property with the given sale code.
*           - If the property is found, it returns the property.
*           - If the property is not found, it returns a property struct with default values (all fields set to 0).
*/
struct property get_property(int code_sale) {

	struct property PROPRIETATE = { 0 };
	int index = exist_property(code_sale);
	if (index>-1) {

		PROPRIETATE = Storage.proprietati[index];
		
	}
	return PROPRIETATE;
}

/*
* The function retrieves all the properties from the storage.
* >> Input: None.
* >> Output: a pointer to a 'storage' struct containing all properties in the storage.
*/
struct storage* get_all() {

	static struct storage STORAGE;
	STORAGE = Storage;
	return &Storage;

}


