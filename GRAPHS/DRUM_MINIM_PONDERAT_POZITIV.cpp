#include <iostream>
#include <fstream>
#define INT_MAX 2147483647
using namespace std;

//nr de noduri, nodul start, muchiile propriu-zise cu ponderi
ifstream fin("dijkstra.in");
//distanta minima dintre nodul start si toate celelate noduri.
//distanta de la nod start la nod start este 0
//distanta de la nod start la nod inaccesibil este -1
ofstream fout("dijkstra.out");

int matrice[101][101];
int nr_noduri;
int nod_inceput;
int cost[101];
int sursa[101];
bool vizitat[101] = { false };

int cauta_nod() {

	int cost_minim = INT_MAX;
	int nod_curent = 0;
	for (int i = 1; i <= nr_noduri; i++) {
		if (cost[i] <= cost_minim && vizitat[i] != true) {
			cost_minim = cost[i];
			nod_curent = i;
		}
	}
	return nod_curent;

}

void Dijkstra(int nod_start) {

	for (int i = 1; i <= nr_noduri; i++) {
		cost[i] = matrice[nod_start][i];
		if (cost[i] != INT_MAX) {
			sursa[i] = nod_start;
		}
	}
	vizitat[nod_start] = true;

	for (int i = 2; i <= nr_noduri; i++) {

		int nod_curent = cauta_nod();
		vizitat[nod_curent] = true;

		for (int j = 1; j <= nr_noduri; j++) {

			if (matrice[nod_curent][j] != INT_MAX && vizitat[j] == false && cost[nod_curent] + matrice[nod_curent][j] < cost[j]) {
				cost[j] = cost[nod_curent] + matrice[nod_curent][j];
				sursa[j] = nod_curent;
			}
		}

	}

	for(int i=1; i<=nr_noduri; i++)
	if (i == nod_start) {
			fout << "0" << " ";
	}
	else if (cost[i] == INT_MAX) {

		fout << "-1" << " ";
	}
	else {
		fout << cost[i] << " ";
	}
	
}

int main() {

	fin >> nr_noduri;
	for (int i = 1; i <= nr_noduri; i++) {
		for (int j = 1; j <= nr_noduri; j++){
			matrice[i][j] = INT_MAX;
		}
	}
	fin >> nod_inceput;

	int x, y, z;
	while (fin >> x >> y >> z) {
		
		// matrice[x][y] = matrice[y][x] = z; <- graf neorientat
		matrice[x][y] = z;

	}

	Dijkstra(nod_inceput);
	

	return 0;
}
