#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "service.h"
#include "repository.h"
#include "domain.h"
#include "data_validator.h"

/*
* The function attempts to delete a property from the storage based on the provided code.
* >> Input:
*    - `code_delete_property`: An integer representing the code of the property to be deleted.
* >> Output:
*    - Returns the result of the `delete_property` function if the property code is valid (verified by `verify_sale_code`).
*    - Returns the string "#992" if the property code is invalid (fails `verify_sale_code`).
*/
char* delete_property_by_code(int code_delete_property) {

	if (verify_sale_code(code_delete_property)) {

		return delete_property(code_delete_property); }

	else {
		return "#992";
	}

}

/*
* The function attempts to add a property to the system using the provided details.
* >> Input:
*    - `cod_vanzare`: An integer representing the sale code of the property.
*    - `tip_proprietate`: A string representing the type of the property (e.g., apartment, house).
*    - `suprafat_proprietate`: A double representing the area of the property in square meters.
*    - `pret`: A double representing the price of the property.
*    - `strada`: A string representing the street where the property is located.
*    - `nr`: An integer representing the house/building number.
*    - `localitate`: A string representing the locality where the property is located.
* >> Output:
*    - Returns the result of the `add_property` function if all input values are valid (verified by `validation_input`).
*    - Returns the string "#990" if the input values fail validation (i.e., `validation_input` returns false).
*/
char* add_property_to_sistem(int cod_vanzare, char* tip_proprietate, double suprafat_proprietate, double pret, char* strada, int nr, char* localitate) {

	if (validation_input(cod_vanzare, tip_proprietate, suprafat_proprietate, pret, nr)) {

		return add_property(cod_vanzare, tip_proprietate, suprafat_proprietate, pret, strada, nr, localitate); }

	else {

		return "#990"; 

	}	
}

/*
* The function checks whether the given string is a valid number, either an integer or a floating-point number.
* >> Input:
*    - `s`: A string to be checked.
* >> Output:
*    - Returns `true` if the string represents a valid number (integer or floating-point).
*    - Returns `false` if the string is not a valid number.
*      - The string can have one decimal point but must only contain digits and at most one period.
*/
bool is_digit_or_double(char* s) {

	unsigned int n = (int)strlen(s);

	if (n == 0) {
		return false;
	}

	unsigned int i;
	bool decimal = true;

	for (i = 0; i < n; i++) {
		if (!isdigit(s[i])) {
			if (s[i] != '.') {
				return false; }

			else if (s[i] == '.' && decimal) {
				decimal = false;
			}
			else {
				return false;
			}
		}
	}

	return true;
}

/*
* The function checks whether the given string consists only of digits.
* >> Input:
*    - `s`: A string to be checked.
* >> Output:
*    - Returns `true` if the string consists entirely of digits.
*    - Returns `false` if the string contains any non-digit characters.
*/
bool is_digit(char* s) {

	unsigned int n = (int)strlen(s);

	if (n == 0) {
		return false;
	}

	unsigned int i;

	for (i = 0; i < n; i++) {
		if (!isdigit(s[i])) {
			return false;
		}
	}

	return true;

}

/*
* The function checks if the given string is equal to "yes".
* >> Input:
*    - `s`: A string to be checked.
* >> Output:
*    - Returns `true` if the string is exactly "yes" (case-sensitive).
*    - Returns `false` if the string is anything other than "yes".
*/
bool yes_or_no(char* s) {

	if (strcmp(s, "yes") == 0) {
		return true;
	}
	return false;
}

/*
* The function removes leading and trailing spaces from a given string.
* >> Input:
*    - `s`: A string from which spaces will be removed.
* >> Output:
*    - The string `s` is modified in-place, with leading and trailing spaces removed.
*    - No value is returned as the string is modified directly.
*/
void delete_space(char* s) {

	unsigned int start = 0;
	unsigned int end = (int)strlen(s) - 1;
	unsigned int i;

	while (isspace(s[start])) {
		start++;
	}

	while (end >= start && isspace(s[end])) {
		end--;
	}

	for (i = 0; i <= end - start; i++) {
		s[i] = s[start + i];
	}

	s[end - start + 1] = '\0';
}

/*
* The function converts a string representing a number into a double precision floating-point number.
* >> Input:
*    - `s`: A string representing a number, which can include a decimal point.
* >> Output:
*    - Returns the equivalent double value of the string `s`.
*      - The string can represent a valid integer or floating-point number (e.g., "123.45").
*      - Assumes the input string is a valid number format.
*/
double convert_char_to_double(char* s) {

	unsigned int n = (int)strlen(s);
	int nr_low = 0;
	int nr_hi = 0;
	int ten = 0;

	unsigned int i;
	bool decimal = true;

	for (i = 0; i < n; i++) {

		if (s[i] == '.') {

			decimal = false;
		}
		else if (decimal) {

			nr_hi = nr_hi * 10 + (s[i] - '0');
		}
		else if (!decimal) {

			nr_low = nr_low * 10 + (s[i] - '0');
			ten++;
		}

	}
	return nr_hi + (nr_low / pow(10, ten));


}

/*
* The function compares two double values and returns a boolean result based on their relationship.
* >> Input:
*    - `x`: A double value to be compared.
*    - `y`: A double value to be compared.
* >> Output:
*    - Returns `true` if `x` is greater than `y`.
*    - Returns `false` if `x` is less than or equal to `y`.
*/
bool compare(double x, double y) {

	if (x > y) {
		return true;
	}
	else {
		return false;
	}

}

/*
* The function sorts the properties in the given `storage` based on the specified field and order (ascending or descending).
* >> Input:
*    - `STORAGE`: A pointer to a `struct storage` containing an array of properties to be sorted.
*    - `compare`: A function pointer used to compare two double values. It determines how the properties will be compared (e.g., for sorting by price or size).
*    - `camp`: A string specifying the field to be used for sorting. It can be either "pret" (price) or "dimensiune" (size).
*    - `auxxx`: A string indicating the sorting order. It can be "crescator" (ascending) or any other value for descending order.
* >> Output:
*    - The function sorts the properties in the `STORAGE` array in place, modifying their order based on the comparison of the chosen field (`camp`) and the order (`auxxx`).
*    - No value is returned as the sorting is done directly on the `STORAGE` data.
* >> Behavior:
*    - If `camp` is "pret", the properties will be sorted by price (`pret`).
*    - If `camp` is "dimensiune", the properties will be sorted by size (`suprafata_proprietate`).
*    - The `compare` function is used to compare values and determine the sorting order.
*    - The order is determined by the `auxxx` string ("crescator" for ascending, otherwise for descending).
*    - If memory allocation for a temporary `property` fails, the function returns early without sorting.
*/
void selection_sort(struct storage* STORAGE, bool (*compare)(double,double), char* camp, char* auxxx) {

	struct property* temp = (struct property*)calloc(1, sizeof(struct property));
	if (temp == NULL) {
		return;
	}
	int i, j;
	int poz=0;

	if (strcmp(camp, "pret")==0)
	{

		for (i = 0; i < STORAGE->property_count; i++) {
			poz = i;
			for (j = i; j < STORAGE->property_count; j++) {
				if (compare(STORAGE->proprietati[poz].pret,STORAGE->proprietati[j].pret) && strcmp(auxxx, "crescator") == 0) {
					poz = j;
				}
				else if (!(compare(STORAGE->proprietati[poz].pret, STORAGE->proprietati[j].pret) || strcmp(auxxx, "crescator") == 0)) {
					poz = j;
				}
			}
			*temp = STORAGE->proprietati[i];
			STORAGE->proprietati[i] = STORAGE->proprietati[poz];
			STORAGE->proprietati[poz] = *temp;
		}

	}
	else if (strcmp(camp, "dimensiune") == 0) {

		for (i = 0; i < STORAGE->property_count; i++) {
			poz = i;
			for (j = i; j < STORAGE->property_count; j++) {
				if (compare(STORAGE->proprietati[poz].suprafata_proprietate, STORAGE->proprietati[j].suprafata_proprietate) && strcmp(auxxx, "crescator") == 0) {
					poz = j;
				}
				else if (!(compare(STORAGE->proprietati[poz].suprafata_proprietate, STORAGE->proprietati[j].suprafata_proprietate) || strcmp(auxxx, "crescator") == 0)) {
					poz = j;
				}
			}
			*temp = STORAGE->proprietati[i];
			STORAGE->proprietati[i] = STORAGE->proprietati[poz];
			STORAGE->proprietati[poz] = *temp;
		}
		
		
	}
	free(temp);
	

}

/*
* The function updates the property details in the system based on the provided input and update string.
* >> Input:
*    - `input`: An integer representing the identifier of the property to be updated.
*    - `update`: A string containing the updates for the property, formatted as "field:value" pairs separated by `;:` (e.g., "strada:Main St;pret:500000").
* >> Output:
*    - Returns the result of the `update_property` function.
*    - If memory allocation fails at any stage, returns error codes:
*      - "#888" for general memory allocation failure.
*      - "#998" if a field value is invalid (e.g., the string is too long or the value is not a valid number).
*      - "#996" if the field name is invalid or unrecognized.
*/
char* update_property_service(int input, char* update) {

	int* ordine = (int*)malloc(1 * sizeof(int));
	if (ordine == NULL) {
		return "#888";
	}
	*ordine = 1;

	char* camp = (char*)malloc(30 * sizeof(char));
	if (camp == NULL) {
		free(ordine);
		return "#888";
	}

	struct property* NEW = (struct property*)malloc(sizeof(struct property));
	if (NEW == NULL) {
		free(ordine); free(camp); 
		return "#888";
	}
	*NEW = (struct property){ 0 };

	char* UPDATE = (char*)malloc(200 * sizeof(char));
	if (UPDATE == NULL) {
		free(ordine); free(camp); free(NEW);
		return "#888";
	}
	strcpy(UPDATE, update);

	char* p = strtok(UPDATE, ";:");
	while (p != NULL) {

		delete_space(p);

		if ((*ordine) % 2 == 1) {

			strcpy(camp, p);

		}
		else if ((*ordine) % 2 == 0) {

			if (strcmp("strada", camp) == 0) {

				if (strlen(p) < 29) {
					strcpy(NEW->adresa.strada, p);
				}
				else {
					free(ordine); free(UPDATE); free(camp); free(NEW);
					return "#998";
				}
			}
			else if (strcmp("localitate", camp) == 0) {

				if (strlen(p) < 29) {
					strcpy(NEW->adresa.localitate, p);
				}
				else {
					free(ordine); free(UPDATE); free(camp); free(NEW);
					return "#998";
				}

			}
			else if (strcmp("tip_proprietate", camp) == 0) {

				if (strlen(p) < 29) {
					strcpy(NEW->tip_proprietate, p);
				}
				else {
					free(ordine); free(UPDATE); free(camp); free(NEW);
					return "#998";
				}

			}
			else if (strcmp("suprafata_proprietate", camp) == 0) {

				if (is_digit_or_double(p)) {
					NEW->suprafata_proprietate = convert_char_to_double(p);
				}
				else {
					free(ordine); free(UPDATE); free(camp); free(NEW);
					return "#998";
				}

			}
			else if (strcmp("pret", camp) == 0) {

				if (is_digit_or_double(p)) {
					NEW->pret = convert_char_to_double(p);
				}
				else {
					free(ordine); free(UPDATE); free(camp); free(NEW);
					return "#998";
				}
			}
			else if (strcmp("reducere", camp) == 0) {

				if (is_digit(p)) {
					NEW->reducere = atoi(p);
				}
				else {
					free(ordine); free(UPDATE); free(camp); free(NEW);
					return "#998";
				}
			}
			else if (strcmp("numar", camp) == 0) {

				if (is_digit(p)) {
					NEW->adresa.nr = atoi(p);
				}
				else {
					free(ordine); free(UPDATE); free(camp); free(NEW);
					return "#998";
				}
			}
			else {
				free(ordine); free(UPDATE); free(camp); free(NEW);
				return "#996";
			}
		}

		(*ordine)++;
		p = strtok(NULL, ";:");
	}

	free(ordine); free(UPDATE); free(camp);
	return update_property(input, NEW);
}

/*
* The function retrieves a property based on the provided sale code.
* >> Input:
*    - `code_sale`: An integer representing the sale code of the property to be retrieved.
* >> Output:
*    - Returns a pointer to a `struct property` corresponding to the given sale code.
*    - Returns `NULL` if the sale code is invalid (fails `verify_sale_code`).
*/
struct property* get_one_property(int code_sale) {


	if (verify_sale_code(code_sale)) {

		return get_property(code_sale);

	}
	return NULL;
}

/*
* The function filters properties based on the provided criterion and value.
* >> Input:
*    - `criterio`: A string specifying the field to filter properties by (e.g., "localitate", "tip proprietate", "dimensiune", "pret").
*    - `value`: A string representing the value to compare against for the given criterion.
*    - `greater`: A string indicating whether the filter should consider values greater than the specified `value`. Possible values are "yes" or "no".
* >> Output:
*    - Returns a pointer to a `struct storage` containing the filtered properties.
*    - Returns `NULL` if any memory allocation fails.
*    - If the field name is not recognized or the value format is invalid, returns a result from the `filtering_property_char` function with an "error" criterion.
*    - If the field is "localitate" or "tip proprietate", it filters using the `filtering_property_char` function.
*    - If the field is "dimensiune" or "pret", it filters using the `filtering_property_number` function after validating and converting the value to a double.
*/
struct storage* filtering_property(char* criterio, char* value, char* greater) {

	bool yesnt;
	double* numar = (double*)malloc(sizeof(double));
	if (numar == NULL) {
		return NULL;
	}
	char* criterio_f = (char*)malloc(30 * sizeof(char));
	if (criterio_f == NULL) {
		free(numar);
		return NULL;
	}
	char* value_f = (char*)malloc(30 * sizeof(char));
	if (value_f == NULL) {
		free(numar); free(criterio_f);
		return NULL;
	}
	char* greater_f = (char*)malloc(5 * sizeof(char)); 
	if (greater_f == NULL) {
		free(numar); free(criterio_f); free(value_f);
		return NULL;
	}

	strcpy(criterio_f, criterio);
	strcpy(value_f, value);
	strcpy(greater_f, greater);

	delete_space(criterio_f);
	delete_space(value_f);
	delete_space(greater_f);

	yesnt = yes_or_no(greater);

	if (strcmp("localitate", criterio_f) == 0) {

		free(numar); free(greater_f);
		return filtering_property_char(criterio_f, value_f);

	}
	else if (strcmp("tip proprietate", criterio_f) == 0) {

		free(numar); free(greater_f);
		return filtering_property_char(criterio_f, value_f); 
	
	}
	else if (strcmp("dimensiune", criterio_f) == 0 && is_digit_or_double(value)) {

		*numar = convert_char_to_double(value_f);
		free(value_f); free(greater_f);
		return filtering_property_number(criterio_f, numar, yesnt); 
	
	}
	else if (strcmp("pret", criterio_f) == 0 && is_digit_or_double(value_f)) {

		*numar = convert_char_to_double(value_f);
		free(value_f); free(greater_f);
		return filtering_property_number(criterio_f, numar, yesnt);
	
	}
	else {
		free(value_f); free(greater_f); free(numar); free(criterio_f);
		return filtering_property_char("error", "");
	}

}

/*
* The function sorts the properties in the storage based on the provided sorting criteria.
* >> Input:
*    - `sorting`: A string representing the sorting criteria, in the format "field:order" (e.g., "pret:crescator" for ascending price sorting).
* >> Output:
*    - Returns a pointer to a `struct storage` containing the sorted properties.
*    - Returns `NULL` if memory allocation fails at any stage.
*    - If the sorting field is unrecognized or the order is invalid (neither "crescator" nor "descrescator"), the function returns the original `STORAGE` without sorting.
*    - If the field is "pret" (price) or "dimensiune" (size), it sorts the properties using the `selection_sort` function with the specified order.
*/
struct storage* sorting_property(char* sorting) {

	struct storage* STORAGE;

	STORAGE  = get_all();

	if (STORAGE == NULL) {
		return NULL;
	}

	char* aux = (char*)malloc(100 * sizeof(char));
	if (aux == NULL) {
		free(STORAGE->proprietati); free(STORAGE);
		return NULL;
	}
	char* auxx = (char*)malloc(50 * sizeof(char));
	if (auxx == NULL) {
		free(STORAGE->proprietati); free(STORAGE); free(aux);
		return NULL;
	}
	char* auxxx = (char*)malloc(50 * sizeof(char));
	if (auxxx == NULL) {
		free(STORAGE->proprietati);  free(STORAGE); free(aux); free(auxx);
		return NULL;
	}

	int* ordine = (int*)malloc(sizeof(int));
	if (ordine == NULL) {
		free(STORAGE->proprietati);  free(STORAGE); free(aux); free(auxx); free(auxxx);
		return NULL;
	}
	*ordine = 1;

	strcpy(aux, sorting);
	char* p = strtok(aux, ":");

	
	while (p != NULL) {

		delete_space(p);

		if (*ordine % 2 == 1) {

			strcpy(auxx, p);

		}
		else if (*ordine % 2 == 0) {

			strcpy(auxxx, p);
		}

		(*ordine)++;
		p = strtok(NULL, ":");
	}
	
	if (!(strcmp(auxxx, "crescator") == 0 || strcmp(auxxx, "descrescator") == 0)) {
		free(aux); free(auxx); free(auxxx); free(ordine);
		return STORAGE;
	}

	if (strcmp(auxx, "pret") == 0) {


		selection_sort(STORAGE, compare, auxx, auxxx);
		free(aux); free(auxx); free(auxxx); free(ordine);
		return STORAGE; }

	else if (strcmp(auxx, "dimensiune") == 0) {

		selection_sort(STORAGE, compare, auxx, auxxx);
		free(aux); free(auxx); free(auxxx); free(ordine);
		return STORAGE; }

	else {
		free(aux); free(auxx); free(auxxx); free(ordine);
		return STORAGE;
	}

}