#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//the layers accessible to the interface
#include "type_validator.h"
#include "service.h"
#include "domain.h"

//Not accessible to the repository, but we need to declare a pointer variable to capture the returned results from the repository.
#include "repository.h"

/*
*This function deallocates memory for the variables storing the characteristics of a property.
*/
void free_all_the_specifications_of_a_property( int* cod_vanzare, char* tip_proprietate, double* suprafat_proprietate, double* pret, char* strada, int* nr, char* localitate) {
	
	free(cod_vanzare);
	free(tip_proprietate);
	free(suprafat_proprietate);
	free(pret);
	free(strada);
	free(nr);
	free(localitate);
}

/*
* This function displays the application menu.
* -> required parameters for the call : -
* -> returned data : -
*/
void display_the_menu() {

	printf("Choose one of the following commands : \n");
	printf("0. Exit the program.\n");
	printf("1. Add a property.\n");
	printf("2. Delete a property.\n");
	printf("3. Display a property.\n");
	printf("4. Update a property.\n");
	printf("5. Filter the properties.\n");
	printf("6. Sort the properties.\n");

}

/*
* This function activates the application's user interface.
* -> required parameters for the call : -
* -> returned data : -
*/
void user_interface() {

	//variables used in the interface code
	bool running = true;
	int command;
	int* verify = (int*)malloc(7 * sizeof(int));
	char* error_code = (char*)malloc(5 * sizeof(char));


	printf("<< The estate agency aplication is running >> \n");
	while (running) {
		display_the_menu();
		printf(">> ");
		verify[0] = scanf("%d", &command);
		if (verify_input(verify,1)) {
			while (getchar() != '\n');
			switch (command)
			{
			case 0:
				printf("<< You've exit the program! >>\n");
				running = false;
				free(verify); free(error_code);
				break;
			case 1:

				//get the information for a property from the user
				printf("To enter a property into the system, please type its specification : \n");

				//the specifications of a property
				int* cod_vanzare = (int*)malloc(1 * sizeof(int));
				char* tip_proprietate = (char*)malloc(11 * sizeof(char));
				double* suprafat_proprietate = (double*)malloc(1 * sizeof(double));
				double* pret = (double*)malloc(1 * sizeof(double));
				char* strada = (char*)malloc(30 * sizeof(char));
				int* nr = (int*)malloc(1 * sizeof(int));
				char* localitate = (char*)malloc(30 * sizeof(char));

				printf("..sale code : "); verify[0] = scanf("%d", cod_vanzare); while (getchar() != '\n');
				printf("..property type : "); verify[1] = scanf("%s", tip_proprietate); while (getchar() != '\n');
				printf("..dimension : "); verify[2] = scanf("%lf", suprafat_proprietate); while (getchar() != '\n');
				printf("..price : "); verify[3] = scanf("%lf", pret); while (getchar() != '\n');
				printf("..adress : --> street : "); verify[4] = scanf("%[^\n]", strada); while (getchar() != '\n');
				printf("           --> city : "); verify[5] = scanf("%[^\n]", localitate); while (getchar() != '\n');
				printf("           --> number : "); verify[6] = scanf("%d", nr); while (getchar() != '\n');

				//verify that the information has been read with the correct type
				if (!verify_input(verify, 7)) {

					printf("!! ERROR : Something went wrong !!\n");
					printf("________Please__try__again________\n");
					//if not free the memory
					free_all_the_specifications_of_a_property(cod_vanzare, tip_proprietate, suprafat_proprietate, pret, strada, nr, localitate);
					break;
				}

				//forward the data to the service and extract the operation code
				strcpy(error_code, add_property_to_sistem(*cod_vanzare, tip_proprietate, *suprafat_proprietate, *pret, strada, *nr, localitate));
				printf("%s\n", error_code);
				//at the end free the memory
				free_all_the_specifications_of_a_property(cod_vanzare, tip_proprietate, suprafat_proprietate, pret, strada, nr, localitate);
				break;

			case 2:

				//get the sale code from the property which the user would like to delete
				printf("To delete a property, please enter its sale code.\n");
				int* code_delete_property = (int*)malloc(1 * sizeof(int));
				printf(">>"); verify[0] = scanf("%d", code_delete_property); while (getchar() != '\n');

				//verify that the information has been read with the correct type
				if (!verify_input(verify, 1)) {

					printf("!! ERROR : Something went wrong !!\n");
					printf("________Please__try__again________\n");
					//if not free the memory
					free(code_delete_property);
					break;
				}

				//forward the data to the service and extract the operation code
				strcpy(error_code, delete_property_by_code(*code_delete_property));
				printf("%s\n", error_code);
				//at the end free the memory
				free(code_delete_property);
				break;

			case 3:

				//get the sale code from the property which the user would like to view
				printf("Which property would you like to see? Enter its sale code :\n");
				int* code_display = (int*)malloc(1 * sizeof(int));
				printf(">>"); verify[0] = scanf("%d", code_display); while (getchar() != '\n');

				//verify that the information has been read with the correct type
				if (!verify_input(verify, 1)) {

					printf("!! ERROR : Something went wrong !!\n");
					printf("________Please__try__again________\n");
					free(code_display);
					break;
				}

				//forward the data to the service and extract the pointer to the property object that matches the sale code the user has entered
				struct property* PROPERTY = get_one_property(*code_display);

				//if the service returns a pointer to an empty property object, it means that there is no such property with the code the user entered in the system
				if (PROPERTY == NULL) {

					printf("!! ERROR : There is no property with %d code sale in the sistem!\n", *code_display);
					printf("________________________________Please__try__again___________________________\n");
					//if no free the memory
					free(code_display); free(PROPERTY);
					break;

				}

				//if not, the property will be displayed
				printf("-----> TIP PROPRIETATE : %s\n-----> SUPRAFATA : %.2f\n-----> PRET : %.2f\n", PROPERTY->tip_proprietate, PROPERTY->suprafata_proprietate, PROPERTY->pret);
				printf("-----> LOCALITATE : %s\n", PROPERTY->adresa.localitate);
				printf("-----> STRADA : %s\n", PROPERTY->adresa.strada);
				printf("-----> NUMARUL : %d\n", PROPERTY->adresa.nr);
				printf("-------------------------------------------------------------------------\n");
				//at the end free the memory
				free(code_display); free(PROPERTY);
				break;

			case 4:

				//get the sale code for the property the user would like to update
				printf("To update a property, first enter its code sale : ");
				int* code_sale = (int*)malloc(1 * sizeof(int));
				verify[0] = scanf("%d", code_sale); while (getchar() != '\n');

				//get the information from the user about which characteristics will be updated
				printf("For the characteristic you want to update, type as in the example :\n");
				printf("<< EXAMPLE : pret : 12; localitate : Suceava >>\n");
				printf("<< NOTE : If you enter text with incorrect syntax, only some of the property attributes may be changed! >>\n");
				printf(">> ");
				char* update = (char*)malloc(200 * sizeof(char));
				verify[1] = scanf("%[^\n]", update);

				//verify that the information has been read with the correct type
				if (!verify_input(verify, 2)) {

					printf("!! ERROR : Something went wrong !!\n");
					printf("________Please__try__again________\n");
					//if not free the memory
					free(code_sale); free(update);
					break;
				}

				//forward the data to the service and extract the operation code
				strcpy(error_code, update_property_service(*code_sale, update));
				printf("%s\n", error_code);
				//at the end free the memory
				free(code_sale); free(update);
				break;

			case 5 :

				//get the filtres from the user
				printf("Please select your filters: \n");

				char* characteristic = (char*)malloc(30 * sizeof(char));
				char* value = (char*)malloc(30 * sizeof(char));
				char* yesnt = (char*)malloc(5 * sizeof(char));

				printf(">> The characteristic: "); verify[0] = scanf("%[^\n]", characteristic); while (getchar() != '\n');
				printf(">> The value: "); verify[1] = scanf("%s", value); while (getchar() != '\n');
				printf("If the value refers to a number, do you want to see properties with numbers greater than your value or not? \n");
				printf("Note : if you will type something else then 'yes' the answer will be 'no'.\n");
				printf(">> "); verify[2] = scanf("%s", yesnt); while (getchar() != '\n');

				//verify that the information has been read with the correct type
				if (!verify_input(verify, 3)) {

					printf("!! ERROR : Something went wrong !!\n");
					printf("________Please__try__again________\n");
					//if not free the memory
					free(characteristic); free(value); free(yesnt);
					break;
				}

				//forward the data to the service and get a pointer to a container that contains the filtered properties
				//NOTE : This pointer points to a dynamically allocated structure. Let's not forget to free it.
				struct storage* STORAGE;
				STORAGE = filtering_property(characteristic, value, yesnt);

				if (STORAGE == NULL) {

					printf("<< ERROR : You have introduces inccorect data! >>\n");
					printf("___________________TRY_AGAIN_____________________\n");
					//if not free the memory
					free(characteristic); free(value); free(yesnt); free(STORAGE->proprietati); free(STORAGE);
					break;
				}
				else {

					int i;
					for (i = 0; i < STORAGE->property_count; i++) {
						printf("%d | %s | %.2f | %.2f | %s\n", STORAGE->proprietati[i].cod_vanzare, STORAGE->proprietati[i].tip_proprietate, STORAGE->proprietati[i].suprafata_proprietate, STORAGE->proprietati[i].pret, STORAGE->proprietati[i].adresa.localitate);
					}

				}
				//at the end free the memory
				free(characteristic); free(value); free(yesnt);  free(STORAGE->proprietati); free(STORAGE);
				break;

			case 6 :

				// get the sorting information from the user
				printf("Please write the value by which you would like the properties to be sorted.\n");
				char* sorting = (char*)malloc(100 * sizeof(char));
				
				verify[0] = scanf("%[^\n]", sorting); while (getchar() != '\n');

				//verify that the information has been read with the correct type
				if (!verify_input(verify, 1)) {

					printf("!! ERROR : Something went wrong !!\n");
					printf("________Please__try__again________\n");
					//if not free the memory
					free(sorting);
					break;

				}

				//forward the data to the service and get a pointer to a container that contains the sorted properties
				//NOTE : This pointer points to a dynamically allocated structure. Let's not forget to free it.
				struct storage* STORAGEE;
				STORAGEE = sorting_property(sorting);
				
				//display the result
				if (STORAGEE == NULL) {
					
					printf("!! ERROR: Wrong data entered !!\n");
					printf("________Please__try__again________\n");
					//if not free the memory
					free(sorting); free(STORAGEE->proprietati); free(STORAGEE);
					break;

				}
				int i;
				for (i = 0; i < STORAGEE->property_count; i++) {

					printf("-----> TIP PROPRIETATE : %s\n-----> SUPRAFATA : %.2f\n-----> PRET : %.2f\n", STORAGEE->proprietati[i].tip_proprietate, STORAGEE->proprietati[i].suprafata_proprietate, STORAGEE->proprietati[i].pret);
					printf("-----> LOCALITATE : %s\n", STORAGEE->proprietati[i].adresa.localitate);
					printf("-----> STRADA : %s\n", STORAGEE->proprietati[i].adresa.strada);
					printf("-----> NUMARUL : %d\n", STORAGEE->proprietati[i].adresa.nr);
					printf("-------------------------------------------------------------------------\n");
				}
				//at the end free the memory
				free(sorting); free(STORAGEE->proprietati); free(STORAGEE);
				break;

			default:

				printf("!! ERROR : You've entered a command that is not part of the meniu !! \n");
				printf("_______________________Please__try__again____________________________\n");
				while (getchar() != '\n');
				break;
			}
		}
		else {
			printf("!! ERROR : You need to refer to the commands using integer numbers !!\n");
			printf("_______________________Please__try__again____________________________\n");
		}
	}
}