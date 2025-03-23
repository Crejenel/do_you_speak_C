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
* The function deletes a property from the storage based on the provided sale code.
* >> Input: an integer 'code_delete_property' representing the sale code of the property to be deleted (int).
* >> Output: a string representing the result of the deletion attempt.
*           - If the sale code is valid and the property is deleted successfully, it returns the result of 'delete_property'.
*           - If the sale code is invalid, it returns "#992" indicating an invalid code.
*/
char* delete_property_by_code(int code_delete_property) {

	if (verify_sale_code(code_delete_property)) {

		return delete_property(code_delete_property); }

	else {
		return "#992";
	}

}

/*
* The function adds a new property to the system if the input is valid.
* >> Input:
*    - an integer 'cod_vanzare' representing the sale code of the property (int),
*    - a string 'tip_proprietate' representing the type of the property (char[]),
*    - a double 'suprafat_proprietate' representing the area of the property (double),
*    - a double 'pret' representing the price of the property (double),
*    - a string 'strada' representing the street name (char[]),
*    - an integer 'nr' representing the street number (int),
*    - a string 'localitate' representing the locality of the property (char[]).
* >> Output:
*    - If the input is valid, it returns the result of 'add_property' to add the property to the system.
*    - If the input is invalid, it returns "#990" indicating invalid input.
*/
char* add_property_to_sistem(int cod_vanzare, char tip_proprietate[], double suprafat_proprietate, double pret, char strada[], int nr, char localitate[]) {

	if (validation_input(cod_vanzare, tip_proprietate, suprafat_proprietate, pret, nr)) {

		struct property Property;
		Property.cod_vanzare = cod_vanzare;
		strcpy(Property.tip_proprietate, tip_proprietate);
		Property.suprafata_proprietate = suprafat_proprietate;
		Property.pret = pret;
		strcpy(Property.adresa.strada, strada);
		Property.adresa.nr = nr;
		strcpy(Property.adresa.localitate, localitate);
		Property.reducere = 0;
		return add_property(&Property); }

	else {

		return "#990"; 

	}	
}

/*
* The function checks if a given string is a valid representation of a number (integer or decimal).
* >> Input:
*    - a string 's' (char*) to be checked.
* >> Output:
*    - true if the string is a valid integer or decimal number.
*    - false if the string contains invalid characters or multiple decimal points.
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
* The function checks if a given string contains only digits.
* >> Input:
*    - a string 's' (char*) to be checked.
* >> Output:
*    - true if the string consists only of digit characters.
*    - false if the string contains any non-digit characters or is empty.
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
* The function checks if the given string is "yes".
* >> Input:
*    - a string 's' (char*) to be checked.
* >> Output:
*    - true if the string is exactly "yes" (case-sensitive).
*    - false if the string is not "yes".
*/
bool yes_or_no(char* s) {

	if (strcmp(s, "yes") == 0) {
		return true;
	}
	return false;
}

/*
* The function removes leading and trailing whitespace characters from a given string.
* >> Input:
*    - a string 's' (char*) from which leading and trailing spaces will be removed.
* >> Output:
*    - The string 's' is modified in-place with leading and trailing spaces removed.
*    - No return value.
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
* The function converts a string representing a number into a double precision floating point number.
* >> Input:
*    - a string 's' (char*) representing a numeric value, potentially with a decimal point.
* >> Output:
*    - A double value corresponding to the numeric value of the input string.
*           - The function parses both the integer and fractional parts of the number.
*           - If there is no decimal point, the fractional part is assumed to be zero.
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
* The function processes an update request for a property, parses the input string, and applies the updates.
* >> Input:
*    - an integer 'input' representing the property code (int), used to locate the property to be updated.
*    - a string 'update' (char*) containing key-value pairs separated by semicolons or colons, where keys correspond to the fields of the property and values represent the updated values.
* >> Output:
*    - A string representing the result of the update attempt:
*        - "#998" if any field is invalid or exceeds the length limit.
*        - "#996" if an unrecognized field is encountered.
*        - The result of 'update_property' if the update was successful.
*/
char* update_property_service(int input, char* update) {

	int ordine = 1;
	char camp[30] = "";
	struct property NEW = { 0 };
	char UPDATE[200];
	strcpy(UPDATE, update);

	char* p = strtok(UPDATE, ";:");
	while (p != NULL) {

		delete_space(p);

		if (ordine % 2 == 1) {

			strcpy(camp, p);

		}
		else if (ordine % 2 == 0) {

			if (strcmp("strada", camp) == 0) {

				if (strlen(p) < 29) {
					strcpy(NEW.adresa.strada, p);
				}
				else {
					return "#998";
				}
			}
			else if (strcmp("localitate", camp) == 0) {

				if (strlen(p) < 29) {
					strcpy(NEW.adresa.localitate, p);
				}
				else {
					return "#998";
				}

			}
			else if (strcmp("tip_proprietate", camp) == 0) {

				if (strlen(p) < 29) {
					strcpy(NEW.tip_proprietate, p);
				}
				else {
					return "#998";
				}

			}
			else if (strcmp("suprafata_proprietate", camp) == 0) {

				if (is_digit_or_double(p)) {
					NEW.suprafata_proprietate = convert_char_to_double(p);
				}
				else {
					return "#998";
				}

			}
			else if (strcmp("pret", camp) == 0) {

				if (is_digit_or_double(p)) {
					NEW.pret = convert_char_to_double(p);
				}
				else {
					return "#998";
				}
			}
			else if (strcmp("reducere", camp) == 0) {

				if (is_digit(p)) {
					NEW.reducere = atoi(p);
				}
				else {
					return "#998";
				}
			}
			else if (strcmp("numar", camp) == 0) {

				if (is_digit(p)) {
					NEW.adresa.nr = atoi(p);
				}
				else {
					return "#998";
				}
			}
			else {
				return "#996";
			}
		}

		ordine++;
		p = strtok(NULL, ";:");
	}


	return update_property(input, &NEW);
}

/*
* The function retrieves a single property based on the sale code.
* >> Input:
*    - an integer 'code_sale' representing the sale code of the property to be retrieved.
* >> Output:
*    - The property corresponding to the sale code if the code is valid.
*    - A property with default values (initialized to 0 or empty strings) if the sale code is invalid.
*/
struct property get_one_property(int code_sale) {

	struct property PROPERTY = { 0 };

	if (verify_sale_code(code_sale)) {

		return get_property(code_sale);

	}
	return PROPERTY;
}

/*
* The function filters properties based on a specified criterion and value, with an optional greater-than comparison.
* >> Input:
*    - a string 'criterio' (char*) representing the field name (e.g., "localitate", "tip proprietate", "suprafata proprietate", "pret").
*    - a string 'value' (char*) representing the value to filter by, which will be matched against the field in the properties.
*    - a string 'greater' (char*) that indicates whether the filtering condition should check for greater-than ('yes') or less-than/equal-to ('no') comparison on numeric fields.
* >> Output:
*    - A pointer to a struct 'storage' containing the filtered properties.
*    - If the criterion is invalid or the value is not suitable for the field, the function will return an empty storage or an error response.
*/
struct storage* filtering_property(char* criterio, char* value, char* greater) {

	bool yesnt;
	double numar;
	char criterio_f[30];
	char value_f[30];
	char greater_f[5];
	strcpy(criterio_f, criterio);
	strcpy(value_f, value);
	strcpy(greater_f, greater);

	delete_space(criterio_f);
	delete_space(value_f);
	delete_space(greater_f);

	yesnt = yes_or_no(greater);

	if (strcmp("localitate", criterio_f) == 0) {

		return filtering_property_char(criterio_f, value_f);
		

	}
	else if (strcmp("tip proprietate", criterio_f) == 0) {

		return filtering_property_char(criterio_f, value_f); }
	else if (strcmp("suprafata proprietate", criterio_f) == 0 && is_digit_or_double(value)) {

		numar = convert_char_to_double(value_f);
		return filtering_property_number(criterio_f, numar, yesnt); }
	else if (strcmp("pret", criterio_f) == 0 && is_digit_or_double(value_f)) {

		numar = convert_char_to_double(value_f);
		return filtering_property_number(criterio_f, numar, yesnt);}
	else {

		return filtering_property_char("error", "");
	}

}

/*
* The function sorts properties based on a specified field and order (ascending or descending).
* >> Input:
*    - a string 'sorting' (char*) that specifies the field to sort by and the sorting order.
*    The format of the string should be "<field>:<order>", where:
*    - 'field' can be "pret" (price) or "dimensiune" (size),
*    - 'order' can be either "crescator" (ascending) or "descrescator" (descending).
* >> Output:
*    - A pointer to a struct 'storage' containing the sorted properties.
*    - If the sorting criteria is invalid, the function returns NULL.
*/
struct storage* sorting_property(char* sorting) {

	struct storage* STORAGE  = get_all();
	struct property temp = { 0 };

	char aux[100];
	char auxx[50]="";
	char auxxx[50]="";
	strcpy(aux, sorting);
	char* p = strtok(aux, ":");
	int ordine = 1;
	int i, j, poz;
	
	while (p != NULL) {

		delete_space(p);

		if (ordine % 2 == 1) {

			strcpy(auxx, p);

		}
		else if (ordine % 2 == 0) {

			strcpy(auxxx, p);
		}

		ordine++;
		p = strtok(NULL, ":");
	}
	
	if (!(strcmp(auxxx, "crescator") == 0 || strcmp(auxxx, "descrescator") == 0)) {
		return NULL;
	}

	if (strcmp(auxx, "pret") == 0) {


		for (i = 0; i < STORAGE->property_count; i++) {
			poz = i;
			for (j = i + 1; j < STORAGE->property_count; j++) {
				if (STORAGE->proprietati[poz].pret > STORAGE->proprietati[j].pret && strcmp(auxxx,"crescator")==0) {
					poz = j;
				}
				else if (!(STORAGE->proprietati[poz].pret > STORAGE->proprietati[j].pret || strcmp(auxxx, "crescator") == 0)) {
					poz = j;
				}
			}
			temp = STORAGE->proprietati[i];
			STORAGE->proprietati[i] = STORAGE->proprietati[poz];
			STORAGE->proprietati[poz] = temp;
		}
		return STORAGE; }

	else if (strcmp(auxx, "dimensiune") == 0) {

		for (i = 0; i < STORAGE->property_count; i++) {
			poz = i;
			for (int j = i + 1; j < STORAGE->property_count; j++) {
				if (STORAGE->proprietati[poz].suprafata_proprietate > STORAGE->proprietati[j].suprafata_proprietate && strcmp(auxxx, "crescator") == 0) {
					poz = j;
				}
				else if (!(STORAGE->proprietati[poz].suprafata_proprietate > STORAGE->proprietati[j].suprafata_proprietate || strcmp(auxxx, "crescator") == 0)) {
					poz = j;
				}
			}
			temp = STORAGE->proprietati[i];
			STORAGE->proprietati[i] = STORAGE->proprietati[poz];
			STORAGE->proprietati[poz] = temp;
		}
		return STORAGE; }

	else {
		return NULL;
	}

}