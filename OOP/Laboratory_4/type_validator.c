#include <stdio.h>
#include <stdbool.h>
#include "type_validator.h"

/*
* The function verifies if all elements in the provided array are equal to 1.
* >> Input:
*    - `v`: An array of integers to be checked.
*    - `length`: The number of elements in the array `v`.
* >> Output:
*    - Returns `true` if all elements in the array are equal to 1.
*    - Returns `false` if any element in the array is not equal to 1.
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