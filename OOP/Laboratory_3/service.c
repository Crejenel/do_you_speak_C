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



char* delete_property_by_code(int code_delete_property) {

	if (verify_sale_code(code_delete_property)) {

		return delete_property(code_delete_property); }

	else {
		return "#992";
	}

}

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

bool yes_or_no(char* s) {

	if (strcmp(s, "yes") == 0) {
		return true;
	}
	return false;
}

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

struct property get_one_property(int code_sale) {

	struct property PROPERTY = { 0 };

	if (verify_sale_code(code_sale)) {

		return get_property(code_sale);

	}
	return PROPERTY;
}

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