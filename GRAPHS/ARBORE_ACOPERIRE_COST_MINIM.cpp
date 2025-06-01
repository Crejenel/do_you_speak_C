#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

fstream fin("dateIN.txt");
ofstream fout("dateOUT.txt");

// datele primite
int n, m, COST = 0;
struct muchie {

	int x, y, cost;

}M[100]; // reprezentare grafului

//datele unde vom stoca rezultatul
pair<int, int>rezulat[100];
int nr=0; // nr de muchii din rezultat

// pentru rezolvare
int tati[100];
int rang[100];

void citire() {

	fin >> n >> m;
	for (int i = 0; i < m; i++) {
		fin >> M[i].x >> M[i].y >> M[i].cost;
	}

}

bool compara(muchie a, muchie b) {
	return a.cost < b.cost;
}

void sortare() {

	sort(M, M + m, compara);

}

void initializare() {

	for (int i = 0; i < n; i++) {
		tati[i] = i;
		rang[i] = 1;
	}
}

int gaseste(int nod) {

	while (tati[nod] != nod) {
		nod = tati[nod];
	}
	return nod;

}

void unire(int nod1, int nod2) {

	if (rang[nod1] < rang[nod2]) {
		tati[nod1] = nod2;
	}
	if (rang[nod2] < rang[nod1]) {
		tati[nod2] = nod1;
	}
	if (rang[nod1] == rang[nod2]) {
		tati[nod1] = nod2;
		rang[nod2]++;
	}
}

void kruskal() {

	for (int i = 0; i < m; i++) {

		if (gaseste(M[i].x) != gaseste(M[i].y)) {

			unire(gaseste(M[i].x), gaseste(M[i].y));
			rezulat[nr].first = M[i].x;
			rezulat[nr].second = M[i].y;
			COST += M[i].cost;
			nr++;
		}
	}

}

void afisare() {

	fout << COST << endl;
	for (int i = 0; i < nr; i++) {
		fout << rezulat[i].first << " " << rezulat[i].second << endl;
	}

}

int main() {

	citire();
	sortare();
	initializare();
	kruskal();
	afisare();

	return 0;
}
