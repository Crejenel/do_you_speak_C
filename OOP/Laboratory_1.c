#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

void menu() {
	printf("1.Citire numere\n");
	printf("2.Afisare suma a n numere\n");
	printf("3.Exit\n");
}
double suma(double* vector, int n) {

	double s = 0;
	for (int i = 0;i < n;i++) {
		s = s + vector[i];
	}
	return s;
}
void citire_nr(int nr, double* vector) {

	for (int i = 0;i < nr; i++) {
		do {
			printf("Introduceti numarul %d: ", i + 1);
			scanf_s("%lf", &vector[i]);
			if (vector[i] <= 0) {
				printf("Numarul nu poate fii negativ!\n");
			}

		} while (vector[i] <= 0);

	}
}
int main() {
	int nr;
	double* vector;
	printf("Introduceti numarul de elemente ala sirurului: ");
	scanf_s("%d", &nr);
	assert(nr >= 0);
	if (nr <= 0) {
		printf("Numarul trebuie sa fie mai mare ca 0!");
	}
	vector = (double*) malloc(nr * sizeof(double));
	int option;
	double s;
	bool oprire = false;
	while (!oprire) {
		menu();
		printf("Introduceti optiunea: ");
		scanf_s("%d", &option);
		switch (option)
		{
		case 1:
			citire_nr(nr, vector);
			break;
		case 2:
			s = suma(vector, nr);
			printf("Suma este: %.3lf", s);
			break;
		case 3:
			oprire = true;
			break;
		default:
			break;
		}
	}
	printf("by!");
	free(vector);
	return 0;
}
