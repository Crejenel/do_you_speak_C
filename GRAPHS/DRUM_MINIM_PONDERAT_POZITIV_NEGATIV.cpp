#include <iostream>
#include <fstream>
#define INT_MAX 2147483647
using namespace std;

ifstream fin("data.txt");
ofstream fout("result.txt");

int nr_noduri;
int nod_start;
int matrice[101][101];
int sursa[101];

void afiseaza_drum(int nod) {

	if (nod == nod_start) {
		fout << nod_start << " ";
		return;
	}

	if (sursa[nod] == -1) {
		fout << "Nu exista "<<endl;
		return;
	}

	afiseaza_drum(sursa[nod]); 
	fout << nod << " ";
}

void BellmanFord() {

	int distante[101];
	for (int i = 1; i <= nr_noduri; i++) {
		distante[i] = INT_MAX;
		sursa[i] = -1;
	}
	distante[nod_start] = 0;

	for (int i = 1; i <= nr_noduri; i++) {
		if (matrice[nod_start][i] != INT_MAX) {
			distante[i] = matrice[nod_start][i];
			sursa[i] = nod_start;
		}
	}

	bool oprire;

	for (int i = 2; i <= nr_noduri; i++) {
		oprire = true;
		for (int j = 1; j <= nr_noduri; j++) {
			if (distante[j] != INT_MAX)
			{
				for (int k = 1; k <= nr_noduri; k++)
				{
					if (matrice[j][k] != INT_MAX && matrice[j][k] + distante[j] < distante[k]) {
						distante[k] = matrice[j][k] + distante[j];
						sursa[k] = j;
						oprire = false;
					}
				}
			}
		}
		if (oprire == true) {
			break;
		}
	}

	for (int i = 1; i <= nr_noduri; i++) {
		fout << distante[i] << " ";
	}
	fout << endl;

	for (int i = 1; i <= nr_noduri; i++) {

		fout << "Drumul de la nodul " << nod_start << " catre " << i << " este : ";
		afiseaza_drum(i);
		fout << endl;
	}

}

int main() {

	fin >> nr_noduri;
	fin >> nod_start;

	for (int i = 1; i <= nr_noduri; i++) {
		for (int j = 1; j <= nr_noduri; j++) {
			matrice[i][j] = INT_MAX;
		}
	}

	int x, y, z;
	while (fin >> x >> y >> z) {

		//matrice[x][y] = matrice[y][x] = z; <- graf neorientat
		matrice[x][y] = z;
	}

	BellmanFord();

	return 0;
}
