#include <stdio.h>
#include <stdbool.h>
#include <math.h>

 /**
 * The <<menu>> function prints a list of specific tasks as a menu for an application.
 */
void menu() {

	printf("0. Exit the program.\n");
	printf("1. Tiparti o suma partiala n din dezvoltarea seriei Taylor a functiei sin(x).\n");
}

/**
* The <<factorial>> function calculates the value for !x.
* It requires 1 parameter :
* >> x : a pozitive integer number
* It returns the value for !x.
*/
int factorial(int x) {

	if (x == 0) { return 1; }

	int result = 1;
	for (int i = 1; i <= x; i++) {
		result *= i;
	}
	return result;

}

/**
 * The <<Taylor>> function calculates the following expression: sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ... (*) using the factorial function.
 * It requires 2 parameters:
 * >> x: a positive integer number
 * >> n: a positive integer number, not 0
 * It returns the expression (*) as a double data type.
 */
double Taylor(int x, int n) {

	double sign = -1.0;
	double result = 0.0;
	int index = 1;
	int odd = 3;

	if (n == 1){ return x;}

	result = x;
	while (index != n) {
		result = result + (sign * ((pow(x, odd)) / factorial(odd)));
		index++;
		odd += 2;
		sign *= (-1);
	}

	return result;		
}

int main() {

	bool stop = false;
	char comanda;
	int x;
	int n;

	printf("<< The application is running >>\n");
	while (!stop) {
		menu();
		printf("Introduceti o comanda din menu : ");
		scanf_s(" %c", &comanda, 1);

		switch (comanda)
		{
		case '0':
			printf("<< The program has closed! >>\n");
			stop = !stop;
			break;

		case '1':
			//get the x from the user
			printf(">> Introduce a value for x : ");
			scanf_s("%d", &x);
			if (x < 0) { printf("ERROR : The value for x should be pozitive! Try again!"); break; }

			//get the n from the user
			printf(">> Introduce a value for n : ");
			scanf_s("%d", &n);
			if (n <= 0) { printf("ERROR: The value for n should be a positive number greater than 0"); break; }

			//print the result by calling the function <<Taylor>>
			printf("%f\n", Taylor(x, n));
			break;

		default:
			//tratam cazul in care inputul utilizatorului nu corespunde cu nicio comanda din meniu
			printf("ERROR: The command entered does not appear in the application menu!\n");
			break;
		}

	}

	return 0;
}
