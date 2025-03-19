#include <stdio.h>
#include <stdbool.h>
#include "type_validator.h"

bool verify_input(int v[], int lenght) {

	int i;
	for (i = 0; i < lenght; i++) {
		if (v[i] != 1) {
			return false;
		}
	}
	return true;
}