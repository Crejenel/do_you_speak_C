#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//the layers accessible to the interface
#include "type_validator.h"
#include "service.h"
#include "domain.h"

//Not accessible to the repository, but we need to declare a pointer variable to capture the returned results from the repository.
#include "repository.h"

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
	int verify[7];
	char error_code[5];
	char characteristic[30];
	char value[30];
	char yesnt[5];


	//the specifications of a property
	int cod_vanzare;
	char tip_proprietate[11];
	double suprafat_proprietate;
	double pret;
	char strada[30];
	int nr;
	char localitate[30];
	


	printf("<< The estate agency aplication is running >> \n");
	while (running) {
		display_the_menu();
		printf(">> ");
		verify[0] = scanf("%d", &command);
		if (verify_input(verify,1)) {
			switch (command)
			{
			case 0:
				printf("<< You've exit the program! >>\n");
				running = false;
				break;
			case 1:

				//get the information for a property from the user
				printf("To enter a property into the system, please type its specification : \n");
				printf("..sale code : "); verify[0] = scanf("%d", &cod_vanzare); while (getchar() != '\n');
				printf("..property type : "); verify[1] = scanf("%s", tip_proprietate); while (getchar() != '\n');
				printf("..dimension : "); verify[2] = scanf("%lf", &suprafat_proprietate); while (getchar() != '\n');
				printf("..price : "); verify[3] = scanf("%lf", &pret); while (getchar() != '\n');
				printf("..adress : --> street : "); verify[4] = scanf("%[^\n]", strada); while (getchar() != '\n');
				printf("           --> city : "); verify[5] = scanf("%[^\n]", localitate); while (getchar() != '\n');
				printf("           --> number : "); verify[6] = scanf("%d", &nr); while (getchar() != '\n');

				//verify that the information has been read with the correct type
				if (!verify_input(verify, 7)) {

					printf("!! ERROR : Something went wrong !!\n");
					printf("________Please__try__again________\n");
					break;
				}

				//forward the data to the service and extract the operation code
				strcpy(error_code, add_property_to_sistem(cod_vanzare, tip_proprietate, suprafat_proprietate, pret, strada, nr, localitate));
				printf("%s\n", error_code);
				break;

			case 2:

				//get the sale code from the property which the user would like to delete
				printf("To delete a property, please enter its sale code.\n");
				int code_delete_property;
				printf(">>"); verify[0] = scanf("%d", &code_delete_property); while (getchar() != '\n');

				//verify that the information has been read with the correct type
				if (!verify_input(verify, 1)) {

					printf("!! ERROR : Something went wrong !!\n");
					printf("________Please__try__again________\n");
					break;
				}

				//forward the data to the service and extract the operation code
				strcpy(error_code, delete_property_by_code(code_delete_property));
				printf("%s\n", error_code);
				break;

			case 3:

				//get the sale code from the property which the user would like to view
				printf("Which property would you like to see? Enter its sale code :\n");
				int code_display;
				printf(">>"); verify[0] = scanf("%d", &code_display); while (getchar() != '\n');

				//verify that the information has been read with the correct type
				if (!verify_input(verify, 1)) {

					printf("!! ERROR : Something went wrong !!\n");
					printf("________Please__try__again________\n");
					break;
				}

				//forward the data to the service and extract the pointer to the property object that matches the sale code the user has entered
				struct property PROPERTY = get_one_property(code_display);

				//if the service returns a pointer to an empty property object, it means that there is no such property with the code the user entered in the system
				if (PROPERTY.cod_vanzare == 0) {

					printf("!! ERROR : There is no property with %d code sale in the sistem!\n",code_display);
					printf("________________________________Please__try__again___________________________\n");
					break;
				}

				//if not, the property will be displayed
				printf("-----> TIP PROPRIETATE : %s\n-----> SUPRAFATA : %.2f\n-----> PRET : %.2f\n", PROPERTY.tip_proprietate, PROPERTY.suprafata_proprietate, PROPERTY.pret);
				printf("-----> LOCALITATE : %s\n", PROPERTY.adresa.localitate);
				printf("-----> STRADA : %s\n", PROPERTY.adresa.strada);
				printf("-----> NUMARUL : %d\n", PROPERTY.adresa.nr);
				printf("-------------------------------------------------------------------------\n");
				break;

			case 4:

				//get the sale code for the property the user would like to update
				printf("To update a property, first enter its code sale : ");
				int code_sale;
				verify[0] = scanf("%d", &code_sale); while (getchar() != '\n');

				//get the information from the user about which characteristics will be updated
				printf("For the characteristic you want to update, type as in the example :\n");
				printf("<< EXAMPLE : pret : 12; localitate : Suceava >>\n");
				printf("<< NOTE : If you enter text with incorrect syntax, only some of the property attributes may be changed! >>\n");
				printf(">> ");
				char update[200];
				verify[1] = scanf("%[^\n]", update);

				//verify that the information has been read with the correct type
				if (!verify_input(verify, 2)) {

					printf("!! ERROR : Something went wrong !!\n");
					printf("________Please__try__again________\n");
					break;
				}

				//forward the data to the service and extract the operation code
				strcpy(error_code, update_property_service(code_sale, update));
				printf("%s\n", error_code);

				break;

			case 5 :

				//get the filtres from the user
				printf("Please select your filters: \n");
				printf(">> The characteristic: "); verify[0] = scanf("%[^\n]", characteristic); while (getchar() != '\n');
				printf(">> The value: "); verify[1] = scanf("%s", value); while (getchar() != '\n');
				printf("If the value refers to a number, do you want to see properties with numbers greater than your value or not? \n");
				printf("Note : if you will type something else then 'yes' the answer will be 'no'.\n");
				printf(">> "); verify[2] = scanf("%s", yesnt); while (getchar() != '\n');

				//verify that the information has been read with the correct type
				if (!verify_input(verify, 3)) {

					printf("!! ERROR : Something went wrong !!\n");
					printf("________Please__try__again________\n");
					break;
				}

				//forward the data to the service and get a pointer to a container that contains the filtered properties
				struct storage* STORAGE;
				STORAGE = filtering_property(characteristic, value, yesnt);
				if (STORAGE->property_count == -1) {

					printf("<< ERROR : You have introduces inccorect data! >>\n");
					printf("___________________TRY_AGAIN_____________________\n");
				}
				else {

					int i;
					for (i = 0; i < STORAGE->property_count; i++) {
						printf("%d | %s | %.2f | %.2f | %s\n", STORAGE->proprietati[i].cod_vanzare, STORAGE->proprietati[i].tip_proprietate, STORAGE->proprietati[i].suprafata_proprietate, STORAGE->proprietati[i].pret, STORAGE->proprietati[i].adresa.localitate);
					}
				}

			case 6 :

				// get the sorting information from the user
				printf("Please write the value by which you would like the properties to be sorted.\n");
				char sorting[100]; verify[0] = scanf("%[^\n]", sorting); while (getchar() != '\n');

				//verify that the information has been read with the correct type
				if (!verify_input(verify, 1)) {

					printf("!! ERROR : Something went wrong !!\n");
					printf("________Please__try__again________\n");
					break;

				}

				//forward the data to the service and get a pointer to a container that contains the sorted properties
				STORAGE = sorting_property(sorting);
				
				//display the result
				if (STORAGE == NULL) {
					
					printf("!! ERROR: Wrong data entered !!\n");
					printf("________Please__try__again________\n");
					break;

				}
				int i;
				for (i = 0; i < STORAGE->property_count; i++) {

					printf("-----> TIP PROPRIETATE : %s\n-----> SUPRAFATA : %.2f\n-----> PRET : %.2f\n", STORAGE->proprietati[i].tip_proprietate, STORAGE->proprietati[i].suprafata_proprietate, STORAGE->proprietati[i].pret);
					printf("-----> LOCALITATE : %s\n", STORAGE->proprietati[i].adresa.localitate);
					printf("-----> STRADA : %s\n", STORAGE->proprietati[i].adresa.strada);
					printf("-----> NUMARUL : %d\n", STORAGE->proprietati[i].adresa.nr);
					printf("-------------------------------------------------------------------------\n");
				}


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