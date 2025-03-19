#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "type_validator.h"
#include "service.h"
#include "domain.h"
#include "tests.h"
#include "repository.h"
#include "type_validator.h"
#include "data_validator.h"

void test_type_validator() {

	int v[] = { 1,1,1 };
	assert(verify_input(v, 3) == true);
	v[0] = 0;
	assert(verify_input(v, 3) == false);


}

void test_add_property_to_sistem() {

	char code[5];
	struct property PROPERTY;
	strcpy(code, add_property_to_sistem(123, "casa", 210.12, 499999.99, "Eroilor", 182, "Cluj-Napoca"));
	assert(strcmp(code, "#999") == 0);
	PROPERTY = get_one_property(123);
	assert(PROPERTY.cod_vanzare == 123);
	assert(PROPERTY.pret == 499999.99);
	assert(PROPERTY.suprafata_proprietate == 210.12);
	assert(strcmp(PROPERTY.tip_proprietate, "casa") == 0);
	assert(strcmp(PROPERTY.adresa.localitate, "Cluj-Napoca") == 0);
	assert(strcmp(PROPERTY.adresa.strada, "Eroilor") == 0);
	assert(PROPERTY.adresa.nr== 182);
	strcpy(code, add_property_to_sistem(1234, "casa", 210.12, 499999.99, "Eroilor", 182, "Cluj-Napoca"));
	assert(strcmp(code, "#990") == 0);
	strcpy(code, add_property_to_sistem(123, "casa", -1, 499999.99, "Eroilor", 182, "Cluj-Napoca"));
	assert(strcmp(code, "#990") == 0);
	strcpy(code, add_property_to_sistem(123, "casa", 1, -1, "Eroilor", 182, "Cluj-Napoca"));
	assert(strcmp(code, "#990") == 0);

}

void test_update_property_in_sistem() {

	char code[5];
	struct property PROPERTY;
	strcpy(code, add_property_to_sistem(124, "casa", 210.12, 499999.99, "Eroilor", -23, "Cluj-Napoca"));
	assert(strcmp(code, "#990") == 0);
	strcpy(code, update_property_service(123, "strada : Regionala CFR; pret : 499999.99 "));
	assert(strcmp(code, "#995") == 0);
	PROPERTY = get_one_property(124);
	assert(PROPERTY.cod_vanzare == 0);
	PROPERTY = get_one_property(123);
	assert(strcmp(PROPERTY.adresa.strada, "Regionala CFR") == 0);
	strcpy(code, update_property_service(112, "pret : 199.99"));
	assert(strcmp(code, "#994")==0);
	strcpy(code, update_property_service(123, "localitate : Suceava; tip_proprietate : apartament; suprafata_proprietate : 50000.00; reducere : 20; numar : 32"));
	assert(strcmp(code, "#995")==0);
	PROPERTY = get_one_property(123);
	assert(PROPERTY.reducere == 20);
	assert(PROPERTY.pret == 499999.99);
	PROPERTY = get_one_property(99);
	assert(PROPERTY.cod_vanzare == 0);

	strcpy(code, update_property_service(123, "strada : hdbJKJKSBWBAfjenxanjcebfunkmkasd"));
	assert(strcmp(code, "#998") == 0);
	strcpy(code, update_property_service(123, "localitate : hdbJKJKSBWBAfjenxanjcebfunkmkasd"));
	assert(strcmp(code, "#998") == 0);
	strcpy(code, update_property_service(123, "tip_proprietate : hdbJKJKSBWBAfjenxanjcebfunkmkasd"));
	assert(strcmp(code, "#998") == 0);
	strcpy(code, update_property_service(123, "suprafata_proprietate : 2m.45"));
	assert(strcmp(code, "#998") == 0);
	strcpy(code, update_property_service(123, "pret : 2m.45"));
	assert(strcmp(code, "#998") == 0);
	strcpy(code, update_property_service(123, "reducere : 21.3"));
	assert(strcmp(code, "#998") == 0);
	strcpy(code, update_property_service(123, "numar : 2m"));
	assert(strcmp(code, "#998") == 0);
	strcpy(code, update_property_service(123, "suprafata_proprtate : 2m.45"));
	assert(strcmp(code, "#996") == 0);
	
}

void test_filter_properties() {

	char code[5];
	struct storage* STORAGE;

	strcpy(code, add_property_to_sistem(124, "casa", 301.22, 560000.99, "Zalelalelalei", 77, "Cluj-Napoca"));
	assert(strcmp(code, "#999") == 0);
	STORAGE = filtering_property("tip proprietate", "casa", "abc");
	assert(STORAGE->property_count == 1);
	assert(strcmp(STORAGE->proprietati[0].tip_proprietate, "casa") == 0);
	strcpy(code, add_property_to_sistem(125, "apartament", 50, 10001, "Ion Creanga", 21, "Cluj-Napoca"));
	assert(strcmp(code, "#999") == 0);
	STORAGE = filtering_property("tip proprietate", "apartament", "yes");
	assert(strcmp(STORAGE->proprietati[0].tip_proprietate, "apartament") == 0);
	assert(strcmp(STORAGE->proprietati[1].tip_proprietate, "apartament") == 0);
	assert(STORAGE->property_count == 2);

	STORAGE = filtering_property("reducere", "20", "yes");
	assert(STORAGE->property_count == -1);

	STORAGE = filtering_property("pret", "499999.99", "yes");
	assert(STORAGE->property_count == 2);
	assert(STORAGE->proprietati[0].pret == 499999.99);
	assert(STORAGE->proprietati[1].pret == 560000.99);

	STORAGE = filtering_property("pret", "499999.99", "no");
	assert(STORAGE->property_count == 2);
	assert(STORAGE->proprietati[0].pret == 499999.99);
	assert(STORAGE->proprietati[1].pret == 10001);

	STORAGE = filtering_property("suprafata proprietate", "50", "no");
	assert(STORAGE->property_count == 1);
	assert(STORAGE->proprietati[0].suprafata_proprietate == 50);

	STORAGE = filtering_property("suprafata proprietate", "50", "yes");
	assert(STORAGE->property_count == 3);
	assert(STORAGE->proprietati[0].suprafata_proprietate == 50000.00);
	assert(STORAGE->proprietati[1].suprafata_proprietate == 301.22);
	assert(STORAGE->proprietati[2].suprafata_proprietate == 50);

	STORAGE = filtering_property("localitate", "Cluj-Napoca ", "no");
	assert(STORAGE->property_count == 2);




}

void test_sort_propertis() {

	struct storage* STORAGE = sorting_property(" pret : descrescator ");
	assert(STORAGE->proprietati[0].pret == 560000.99);
	assert(STORAGE->proprietati[1].pret == 499999.99);
	assert(STORAGE->proprietati[2].pret == 10001);
	STORAGE = sorting_property(" dimensiune : crescator");
	assert(STORAGE->proprietati[0].suprafata_proprietate == 50);
	assert(STORAGE->proprietati[1].suprafata_proprietate == 301.22);
	assert(STORAGE->proprietati[2].suprafata_proprietate == 50000);
	STORAGE = sorting_property(" dimensiune : descrescator");
	STORAGE = sorting_property(" pret : crescator");
	STORAGE = sorting_property(" dimensiune : barba");
	assert(STORAGE == NULL);
	STORAGE = sorting_property(" blabla : crescator");
	assert(STORAGE == NULL);

}

void test_delete_property_from_sistem() {

	char code[5];
	struct property PROPERTY;
	strcpy(code, add_property_to_sistem(123, "casa", 210.12, 499999.99, "Eroilor", 1, "Cluj-Napoca"));
	assert(strcmp(code, "#998") == 0);
	strcpy(code, delete_property_by_code(123));
	assert(strcmp(code, "#997")==0);
	PROPERTY = get_one_property(123);
	assert(PROPERTY.cod_vanzare == 0);
	strcpy(code, delete_property_by_code(123));
	assert(strcmp(code, "#996")==0);
	strcpy(code, delete_property_by_code(4216));
	assert(strcmp(code, "#992") == 0);


}

void test_sub_function_service() {

	assert(!is_digit_or_double(""));
	assert(!is_digit_or_double("123,4"));
	assert(!is_digit_or_double("1.2.3"));
	assert(!is_digit(""));
	assert(!is_digit("12m"));

}

void test_validation_input() {

	assert(!validation_input(123, "masina", 1, 1, 1));
}


void run_all_tests() {

	test_type_validator();
	test_add_property_to_sistem();
	test_update_property_in_sistem();
	test_filter_properties();
	test_sort_propertis();
	test_delete_property_from_sistem();
	test_sub_function_service();
	test_validation_input();

	printf(" *** \n");
}