#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "repository.h"


struct storage Storage = { 0 };

/*
* The function manages the storage of properties by dynamically adjusting the size of the array holding the properties.
* >> Input: None.
* >> Output: A string representing the result of the storage management process.
*           - If there is no property in storage, it initializes the storage with a size of 10 and returns "#000".
*           - If the storage is full (i.e., the property count equals the storage maximum), it attempts to expand the storage.
*             It reallocates the memory, doubling the storage size, and returns "#010" if successful.
*           - If memory allocation fails at any point (either when initializing or resizing the storage), it returns "#888".
*           - If no expansion is needed (i.e., the storage is not full), it simply returns "#001".
*/
char* storage_management() {

	if (Storage.property_count == 0) {
		Storage.proprietati = (struct property*)calloc(10, sizeof(struct property));
		if (Storage.proprietati == NULL) {
			return "#888";
		}
		Storage.max = 10;
		return "#000";
		
	}
	else if (Storage.property_count + 1 == Storage.max) {

		struct storage AUX;
		AUX.proprietati = (struct property*)calloc(Storage.property_count, sizeof(struct property));
		if (AUX.proprietati == NULL) {
			return "#888";
		}
		AUX.property_count = Storage.property_count;
		AUX.max = Storage.max;

		int i;
		for (i = 0; i < Storage.property_count; i++) {
			AUX.proprietati[i] = Storage.proprietati[i];
		}

		free(Storage.proprietati);

		Storage.proprietati = (struct property*)calloc(Storage.max * 2, sizeof(struct property));
		if (Storage.proprietati == NULL) {
			free(AUX.proprietati);
			return "#888";
		}

		for (i = 0; i < AUX.property_count; i++) {
			Storage.proprietati[i] = AUX.proprietati[i];
		}

		Storage.property_count = AUX.property_count;
		Storage.max = Storage.max * 2;

		free(AUX.proprietati);
		return "#010";
	}
	return "#001";
}

/*
* The function frees the memory allocated for the properties in storage.
* >> Input: None.
* >> Output: None.
*           - It releases the memory that was previously allocated for the properties array in the Storage structure.
*           - After calling this function, the Storage.proprietati pointer will be invalid and should not be used.
*/
void free_storage() {

	free(Storage.proprietati);
}

/*
* The function adds a property to the storage if it doesn't already exist, and ensures that there is enough space by expanding the storage if needed.
* >> Input:
*    - cod_vanzare (int): A unique sale code for the property.
*    - tip_proprietate (char*): A string representing the type of the property (e.g., house, apartment).
*    - suprafat_proprietate (double): The area of the property in square meters.
*    - pret (double): The price of the property.
*    - strada (char*): The street name where the property is located.
*    - nr (int): The number of the property on the street.
*    - localitate (char*): The locality where the property is located.
* >> Output:
*    - A string indicating the result of the operation:
*      - "#999" if the property was successfully added and there was no need to expand storage.
*      - "#010999" if the property was successfully added and the storage was expanded.
*      - "#998" if the property already exists (determined by the sale code).
*      - "#888" if there was a memory allocation failure.
*/
char* add_property(int cod_vanzare, char* tip_proprietate, double suprafat_proprietate, double pret, char* strada, int nr, char* localitate){

	bool ok = true;
	char code[5];
	strcpy(code, storage_management());

	if (strcmp(code, "#010") == 0) {
		ok = false;
	}
	else if(strcmp(code,"#888")==0){
		return "#888";
	}

	int* index = (int*)malloc(sizeof(int));
	if (index == NULL) {
		return "#888";
		
	}
	*index = exist_property(cod_vanzare);

	if (!(*index>-1)) {

		Storage.proprietati[Storage.property_count].cod_vanzare = cod_vanzare;
		strcpy(Storage.proprietati[Storage.property_count].tip_proprietate, tip_proprietate);
		Storage.proprietati[Storage.property_count].suprafata_proprietate = suprafat_proprietate;
		Storage.proprietati[Storage.property_count].pret = pret;
		strcpy(Storage.proprietati[Storage.property_count].adresa.strada, strada);
		Storage.proprietati[Storage.property_count].adresa.nr = nr;
		strcpy(Storage.proprietati[Storage.property_count].adresa.localitate, localitate);
		Storage.proprietati[Storage.property_count].reducere = 0;
		Storage.property_count++;
		free(index);
		if (ok == true) {
			return "#999";
		}
		else {
			return "#010999";
		}
		}	
	else {

		free(index);
		return "#998";
	}
}

/*
* The function deletes a property from the storage based on the provided sale code.
* >> Input:
*    - code_sale (int): The sale code of the property to be deleted.
* >> Output:
*    - A string representing the result of the deletion attempt:
*      - "#997" if the property is successfully deleted.
*      - "#996" if the sale code is not found in the storage.
*      - "#888" if there was a memory allocation failure.
*/
char* delete_property(int code_sale){

	bool find = false;

	int* i = (int*)malloc(sizeof(int));
	if (i == NULL) {
		return "#888";
	}
	for ((*i) = 0; (*i) < Storage.property_count; (*i)++) {
		if (Storage.proprietati[(*i)].cod_vanzare == code_sale)
		{
			find = true;
		}
		if (find) {
			Storage.proprietati[(*i)] = Storage.proprietati[(*i) + 1];
		}
	}
	if (find) {
		Storage.property_count--;
		free(i);
		return "#997"; }
	else {
		free(i);
		return "#996";
	}

}

/*
* The function updates a property in the storage based on the provided sale code and the new property data.
* >> Input:
*    - code_sale (int): The sale code of the property to be updated.
*    - pro (struct property*): A pointer to a structure containing the new property data.
* >> Output:
*    - A string representing the result of the update attempt:
*      - "#995" if the property is successfully updated.
*      - "#994" if the property with the given sale code is not found.
*      - "#888" if there was a memory allocation failure.
*/
char* update_property(int code_sale, struct property* pro){

	int* index = (int*)malloc(sizeof(int));
	if (index == NULL) {
		return "#888";
	}
	(*index) = exist_property(code_sale);

	if ((*index)>-1) {

		if (pro->adresa.nr != 0) {
			Storage.proprietati[(*index)].adresa.nr = pro->adresa.nr;
		}
		if (strcmp(pro->adresa.localitate,"")) {
			strcpy(Storage.proprietati[(*index)].adresa.localitate,pro->adresa.localitate);
		}
		if (strcmp(pro->adresa.strada, "")) {
			strcpy(Storage.proprietati[(*index)].adresa.strada, pro->adresa.strada);
		}
		if (pro->pret != 0.0) {
			Storage.proprietati[(*index)].pret = pro->pret;
		}
		if (pro->reducere != 0) {
			Storage.proprietati[(*index)].reducere = pro->reducere;
		}
		if (pro->suprafata_proprietate != 0.0) {
			Storage.proprietati[(*index)].suprafata_proprietate = pro->suprafata_proprietate;
		}
		if (strcmp(pro->tip_proprietate, "")) {
			strcpy(Storage.proprietati[(*index)].tip_proprietate, pro->tip_proprietate);
		}
		free(index); free(pro);
		return "#995"; }
	else {
		free(index); free(pro);
		return "#994";
	}

}

/*
* The function checks if a property with the given sale code exists in the storage.
* >> Input:
*    - code_sale (int): The sale code of the property to be checked.
* >> Output:
*    - An integer representing the index of the property if found.
*      - A value greater than or equal to 0 if the property exists.
*      - -1 if the property does not exist.
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
* The function filters properties based on a specified character-based criterion (e.g., "localitate" or "tip proprietate") and value.
* >> Input:
*    - criterio (char*): The criterion for filtering (e.g., "localitate" or "tip proprietate").
*    - value (char*): The value to match against the specified criterion.
* >> Output:
*    - A pointer to a new `struct storage` containing properties that match the given criterion and value:
*      - If matching properties are found, they are added to the new storage, and the storage is returned.
*      - If no matching properties are found, the storage is empty, and it is still returned.
*      - NULL is returned if memory allocation fails or if the criterion is unrecognized.
*/
struct storage* filtering_property_char(char* criterio, char* value) {

	int i;
	struct storage* STORAGE = (struct storage*)calloc(1,sizeof(struct storage));
	if (STORAGE == NULL) {
		free(criterio); free(value);
		return NULL;
	}
	STORAGE->proprietati = (struct property*)calloc(Storage.property_count+1, sizeof(struct property));
	if (STORAGE->proprietati == NULL) {
		free(STORAGE); free(criterio); free(value);
		return NULL;
	}

	if (strcmp(criterio, "localitate") == 0) {

		for (i = 0; i < Storage.property_count; i++) {

			if (strcmp(Storage.proprietati[i].adresa.localitate, value) == 0) {
				STORAGE->proprietati[STORAGE->property_count] = Storage.proprietati[i];
				STORAGE->property_count++;
			}
		}
		free(criterio); free(value);
		return STORAGE;
	}
	else if (strcmp(criterio, "tip proprietate") == 0) {
		for (i = 0; i < Storage.property_count; i++) {
			if (strcmp(Storage.proprietati[i].tip_proprietate, value) == 0) {
				STORAGE->proprietati[STORAGE->property_count] = Storage.proprietati[i];
				STORAGE->property_count++;
			}
		}
		free(criterio); free(value);
		return STORAGE;
	}
	else {
		free(STORAGE->proprietati); free(STORAGE);
		return NULL;
	}

}

/*
* The function filters properties based on a specified numeric criterion (e.g., "pret" or "dimensiune") and number, with an option for greater or less than comparison.
* >> Input:
*    - criterio (char*): The criterion for filtering (e.g., "pret" or "dimensiune").
*    - numar (double*): A pointer to the number to compare against.
*    - greater (bool): If true, properties greater than or equal to `numar` are included; if false, properties less than or equal to `numar` are included.
* >> Output:
*    - A pointer to a new `struct storage` containing properties that match the given criterion and number:
*      - If matching properties are found, they are added to the new storage, and the storage is returned.
*      - If no matching properties are found, the storage is empty, and it is still returned.
*      - NULL is returned if memory allocation fails or if the criterion is unrecognized.
*/
struct storage* filtering_property_number(char* criterio, double* numar, bool greater) {

	int i;
	struct storage* STORAGE = (struct storage*)calloc(1, sizeof(struct storage));
	if (STORAGE == NULL) {
		free(criterio); free(numar);
		return NULL;
	}
	STORAGE->proprietati = (struct property*)calloc(Storage.property_count + 1, sizeof(struct property));
	if (STORAGE->proprietati == NULL) {
		free(STORAGE); free(criterio); free(numar);
		return NULL;
	}
	if (strcmp(criterio, "pret") == 0) {


		for (i = 0; i < Storage.property_count; i++) {

			if (Storage.proprietati[i].pret >= *numar && greater==true) {
				STORAGE->proprietati[STORAGE->property_count] = Storage.proprietati[i];
				STORAGE->property_count++;
			}
			else if(Storage.proprietati[i].pret <= *numar && greater==false) {

					STORAGE->proprietati[STORAGE->property_count] = Storage.proprietati[i];
					STORAGE->property_count++;
			}
		}
		free(criterio); free(numar);
		return STORAGE;
	}
	else if (strcmp(criterio, "dimensiune") == 0) {

		for (i = 0; i < Storage.property_count; i++) {

			if (Storage.proprietati[i].suprafata_proprietate >= *numar && greater==true) {
				
				STORAGE->proprietati[STORAGE->property_count] = Storage.proprietati[i];
				STORAGE->property_count++;
			}
			else if (Storage.proprietati[i].suprafata_proprietate <= *numar && greater == false) {

					STORAGE->proprietati[STORAGE->property_count] = Storage.proprietati[i];
					STORAGE->property_count++;
			}
		}
		free(criterio); free(numar);
		return STORAGE;
	}
	else {
		free(criterio); free(numar);
		return NULL;
	}

	
	
}

/*
* The function retrieves a property based on the provided sale code.
* >> Input:
*    - code_sale (int): The sale code of the property to retrieve.
* >> Output:
*    - A pointer to a `struct property` representing the property if found.
*      - NULL if the property with the given sale code does not exist or if memory allocation fails.
*/
struct property* get_property(int code_sale) {

	struct property* PROPERTY = (struct property*)malloc(sizeof(struct property));
	if (PROPERTY == NULL) {
		return NULL;
	}
	*PROPERTY = (struct property){ 0 };

	int index = exist_property(code_sale);
	if (index>-1) {

		*PROPERTY = Storage.proprietati[index];
		return PROPERTY;
		
	}
	free(PROPERTY);
	return NULL;
}

/*
* The function retrieves all properties from the storage.
* >> Input: None.
* >> Output:
*    - A pointer to a new `struct storage` containing all the properties in the storage.
*      - NULL if memory allocation fails.
*/
struct storage* get_all() {

	struct storage* STORAGE = (struct storage*)calloc(1, sizeof(struct storage));
	if (STORAGE == NULL) {
		return NULL;
	}
	STORAGE->proprietati = (struct property*)calloc(Storage.property_count + 1, sizeof(struct property));
	if (STORAGE->proprietati == NULL) {
		free(STORAGE);
		return NULL;
	}
	int i;
	for (i = 0; i < Storage.property_count; i++) {

		STORAGE->proprietati[STORAGE->property_count] = Storage.proprietati[i];
		STORAGE->property_count++;
	}

	return STORAGE;

}

