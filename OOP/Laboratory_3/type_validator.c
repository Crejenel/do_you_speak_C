#include <stdio.h>
#include <stdbool.h>
#include "type_validator.h"

/*
* The function checks if all elements in the input array are equal to 1.
* >> Input:
*    - an array 'v' (int[]), which contains integer values to be checked.
*    - an integer 'length' (int), the number of elements in the array.
* >> Output:
*    - true if all elements in the array are equal to 1.
*    - false if any element in the array is different from 1.
*/
bool verify_input(int v[], int lenght) {

	int i;
	for (i = 0; i < lenght; i++) {
		if (v[i] != 1) {
			return false;
		}
	}
	return true;
}