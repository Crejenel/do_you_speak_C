#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "type_validator.h"
#include "service.h"
#include "domain.h"
#include "tests.h"
#include "repository.h"
#include "data_validator.h"


void test_type_validator() {

	int v[] = { 1,1,1 };
	assert(verify_input(v, 3) == true);
	v[0] = 0;
	assert(verify_input(v, 3) == false);


}

void test_add_property_to_sistem() {

	char code[5];
	struct property* PROPERTY;

	strcpy(code, add_property_to_sistem(123, "casa", 210.12, 499999.99, "Eroilor", 182, "Cluj-Napoca"));
	assert(strcmp(code, "#999") == 0);
	PROPERTY = get_one_property(123);
	assert(PROPERTY->cod_vanzare == 123);
	assert(PROPERTY->pret == 499999.99);
	assert(PROPERTY->suprafata_proprietate == 210.12);
	assert(strcmp(PROPERTY->tip_proprietate, "casa") == 0);
	assert(strcmp(PROPERTY->adresa.localitate, "Cluj-Napoca") == 0);
	assert(strcmp(PROPERTY->adresa.strada, "Eroilor") == 0);
	assert(PROPERTY->adresa.nr== 182);
    free(PROPERTY);

	strcpy(code, add_property_to_sistem(1234, "casa", 210.12, 499999.99, "Eroilor", 182, "Cluj-Napoca"));
	assert(strcmp(code, "#990") == 0);
	strcpy(code, add_property_to_sistem(123, "casa", -1, 499999.99, "Eroilor", 182, "Cluj-Napoca"));
	assert(strcmp(code, "#990") == 0);
	strcpy(code, add_property_to_sistem(123, "casa", 1, -1, "Eroilor", 182, "Cluj-Napoca"));
	assert(strcmp(code, "#990") == 0);
	

}

void test_update_property_in_sistem() {

	char code[5];
	struct property* PROPERTY;

	strcpy(code, add_property_to_sistem(124, "casa", 210.12, 499999.99, "Eroilor", -23, "Cluj-Napoca"));
	assert(strcmp(code, "#990") == 0);

	strcpy(code, update_property_service(123, "strada : Regionala CFR; pret : 499999.99 "));
	assert(strcmp(code, "#995") == 0);
	PROPERTY = get_one_property(124);
	assert(PROPERTY == NULL);
	free(PROPERTY);

	PROPERTY = get_one_property(123);
	assert(strcmp(PROPERTY->adresa.strada, "Regionala CFR") == 0);
	strcpy(code, update_property_service(112, "pret : 199.99"));
	assert(strcmp(code, "#994")==0);
	strcpy(code, update_property_service(123, "localitate : Suceava; tip_proprietate : apartament; suprafata_proprietate : 50000.00; reducere : 20; numar : 32"));
	assert(strcmp(code, "#995")==0);
	free(PROPERTY);
	
	PROPERTY = get_one_property(123);
	assert(PROPERTY->reducere == 20);
	assert(PROPERTY->pret == 499999.99);
	free(PROPERTY);

	PROPERTY = get_one_property(99);
	assert(PROPERTY == NULL);
	

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

	strcpy(code, add_property_to_sistem(124, "apartament", 85.5, 199999.99, "Dimitrie Cantemir", 45, "Bucuresti"));
	assert(strcmp(code, "#999") == 0);

	strcpy(code, add_property_to_sistem(125, "casa", 150.25, 350000.75, "Mihai Eminescu", 10, "Iasi"));
	assert(strcmp(code, "#999") == 0);

	strcpy(code, add_property_to_sistem(126, "apartament", 95.75, 250000.50, "George Cosbuc", 33, "Iasi"));
	assert(strcmp(code, "#999") == 0);

	strcpy(code, add_property_to_sistem(127, "casa", 320.40, 750000.00, "Strada Mare", 58, "Bucuresti"));
	assert(strcmp(code, "#999") == 0);

	strcpy(code, add_property_to_sistem(128, "apartament", 60.0, 120000.99, "Calea Mosilor", 18, "Cluj-Napoca"));
	assert(strcmp(code, "#999") == 0);

	struct storage* STORAGE;
	STORAGE = filtering_property("localitate", "Suceava", "nu");
	assert(strcmp(STORAGE->proprietati[0].adresa.localitate,"Suceava")==0);
	free(STORAGE->proprietati);
	free(STORAGE);

	STORAGE = filtering_property("tip proprietate", "apartament", "abc");
	assert(strcmp(STORAGE->proprietati[0].tip_proprietate, "apartament") == 0);
	assert(strcmp(STORAGE->proprietati[1].tip_proprietate, "apartament") == 0);
	assert(strcmp(STORAGE->proprietati[2].tip_proprietate, "apartament") == 0);
	assert(strcmp(STORAGE->proprietati[3].tip_proprietate, "apartament") == 0);
	free(STORAGE->proprietati);
	free(STORAGE);

	STORAGE = filtering_property("pret", "120000.99", "yes");
	assert(STORAGE->proprietati[0].pret == 499999.99);
    assert(STORAGE->proprietati[1].pret == 199999.99);
	assert(STORAGE->proprietati[2].pret == 350000.75);
	assert(STORAGE->proprietati[3].pret == 250000.50);
	assert(STORAGE->proprietati[4].pret == 750000.00);
	assert(STORAGE->proprietati[5].pret == 120000.99); 
	free(STORAGE->proprietati);
	free(STORAGE);

	STORAGE = filtering_property("pret", "120000.99", "no");
	assert(STORAGE->proprietati[0].pret == 120000.99);
	free(STORAGE->proprietati);
	free(STORAGE);

	STORAGE = filtering_property("dimensiune", "95.75", "no");
	assert(STORAGE->proprietati[0].suprafata_proprietate == 85.5);
	assert(STORAGE->proprietati[1].suprafata_proprietate == 95.75);
	assert(STORAGE->proprietati[2].suprafata_proprietate == 60.0);
	free(STORAGE->proprietati);
	free(STORAGE);

	STORAGE = filtering_property("dimensiune", "95.75", "yes");
	assert(STORAGE->proprietati[0].suprafata_proprietate == 50000.00);
	assert(STORAGE->proprietati[1].suprafata_proprietate == 150.25);
	assert(STORAGE->proprietati[2].suprafata_proprietate == 95.75);
	assert(STORAGE->proprietati[3].suprafata_proprietate == 320.40);
	free(STORAGE->proprietati);
	free(STORAGE);

	STORAGE = filtering_property("suprafata proprietate", "95.75", "yes");
	assert(STORAGE == NULL);


}

void test_over_write_property_in_sistem() {
	
	char code[8];
	strcpy(code, add_property_to_sistem(111, "casa", 210.12, 499999.99, "Eroilor", 182, "Cluj-Napoca"));
	assert(strcmp(code, "#999") == 0);
	strcpy(code, add_property_to_sistem(222, "casa", 210.12, 499999.99, "Eroilor", 182, "Cluj-Napoca"));
	assert(strcmp(code, "#999") == 0);
	strcpy(code, add_property_to_sistem(333, "casa", 210.12, 499999.99, "Eroilor", 182, "Cluj-Napoca"));
	assert(strcmp(code, "#999") == 0);
	strcpy(code, add_property_to_sistem(444, "casa", 210.12, 499999.99, "Eroilor", 182, "Cluj-Napoca"));
	assert(strcmp(code, "#010999") == 0);


	strcpy(code, delete_property_by_code(111));
	assert(strcmp(code, "#997") == 0);
	strcpy(code, delete_property_by_code(222));
	assert(strcmp(code, "#997") == 0);
	strcpy(code, delete_property_by_code(333));
	assert(strcmp(code, "#997") == 0);
	strcpy(code, delete_property_by_code(444));
	assert(strcmp(code, "#997") == 0);
	
}

void test_sort_propertis() {

	struct storage* STORAGE = sorting_property(" pret : descrescator ");
	assert(STORAGE->proprietati[0].pret == 750000.00);
	assert(STORAGE->proprietati[1].pret == 499999.99);
	assert(STORAGE->proprietati[2].pret == 350000.75);
	assert(STORAGE->proprietati[3].pret == 250000.50);
	assert(STORAGE->proprietati[4].pret == 199999.99);
	assert(STORAGE->proprietati[5].pret == 120000.99);
	free(STORAGE->proprietati);
	free(STORAGE);

	STORAGE = sorting_property(" dimensiune : crescator");
	assert(STORAGE->proprietati[0].suprafata_proprietate == 60.0);
	assert(STORAGE->proprietati[1].suprafata_proprietate == 85.5);
	assert(STORAGE->proprietati[2].suprafata_proprietate == 95.75);
	assert(STORAGE->proprietati[3].suprafata_proprietate == 150.25);
	assert(STORAGE->proprietati[4].suprafata_proprietate == 320.40);
	assert(STORAGE->proprietati[5].suprafata_proprietate == 50000.00);
	free(STORAGE->proprietati);
	free(STORAGE);

	STORAGE = sorting_property(" dimensiune : descrescator");
	free(STORAGE->proprietati);
	free(STORAGE);

	STORAGE = sorting_property(" pret : crescator");
	free(STORAGE->proprietati);
	free(STORAGE);

	STORAGE = sorting_property(" dimensiune : barba");
	free(STORAGE->proprietati);
	free(STORAGE);

	STORAGE = sorting_property(" blabla : crescator");
	free(STORAGE->proprietati);
	free(STORAGE);

}

void test_delete_property_from_sistem() {

	char code[5];
	struct property* PROPERTY;
	strcpy(code, add_property_to_sistem(123, "casa", 210.12, 499999.99, "Eroilor", 1, "Cluj-Napoca"));
	assert(strcmp(code, "#998") == 0);
	strcpy(code, delete_property_by_code(123));
	assert(strcmp(code, "#997")==0);
	PROPERTY = get_one_property(123);
	assert(PROPERTY==NULL);
	strcpy(code, delete_property_by_code(123));
	assert(strcmp(code, "#996")==0);
	strcpy(code, delete_property_by_code(4216));
	assert(strcmp(code, "#992") == 0);
	free(PROPERTY);


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

void test_free_storage() {
	free_storage();
}


void run_all_tests() {

	test_type_validator();
	test_add_property_to_sistem();
	test_update_property_in_sistem();
	test_filter_properties();
	test_over_write_property_in_sistem();
	test_sort_propertis();
	test_delete_property_from_sistem();
	test_sub_function_service();
	test_validation_input();
	test_free_storage();

	printf(" *** \n");
}