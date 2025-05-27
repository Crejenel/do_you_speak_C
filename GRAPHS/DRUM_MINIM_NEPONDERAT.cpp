#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
//fisierul contine nr de varfuri, nr de muchii, muchiile, nr de perechi de varfuri la care
//vrem sa le aflam distantele si varfurile propriu-zise
ifstream fin("data.txt");

//fisierul contine drumul minim dintre varfurile precizate, iar daca nu exista drum se va
//considera distanta negativa
ofstream out("result.txt");

int nr_noduri;
int nr_muchii;
int matrice[101][101];

//Algoritmul lui Moore
int DrumMinim(int start, int final) {

	if (start <= 0 || final <= 0) {
		out << "ERROARE! ";
		return -999;
	}

	int distante[101]{ 0 };
	queue<int> coada;
	distante[start] = 1;
	coada.push(start);

	//Pentru a afisa drumul explicit :
	int parinte[101]{ 0 };
	parinte[start] = -1;

	while (!coada.empty()) {

		int nod = coada.front();
		coada.pop();

		for (int i = 1; i <= nr_noduri; i++) {

			if (matrice[nod][i] == 1 && distante[i] == 0) {
				coada.push(i);
				distante[i] = distante[nod] + 1;
				parinte[i] = nod;
			}
		}
	}

	if (distante[final] == 0) {
		return -1;
	}
	else {

		vector<int>drum;
		int nod = final;
		while (nod != -1) {
			drum.push_back(nod);
			nod = parinte[nod];
		}

		out << "Am gasit un drum intre " << start << " si " << final << " : " << endl;
		for (int i = (int)drum.size() - 1; i >= 0; i--) {
			out << drum[i] << " ";
		}
		out << endl;
		return distante[final] - 1;
	}

}

int main() {

	fin >> nr_noduri;
	fin >> nr_muchii;

	for (int i = 1, x, y; i <= nr_muchii; i++) {

		fin >> x >> y;
		matrice[x][y] = matrice[y][x] = 1;
		//matrice[x][y] = 1; <- pentru graf orientat
	}

	int k;
	fin >> k;
	for (int i = 1, x, y; i <= k; i++) {

		fin >> x >> y;
		int drumMinim = DrumMinim(x,y);
		if (drumMinim != -999) {
			out << "Distanta minima intre nodurile " << x << " - " << y << " este " << drumMinim << endl;
		}
		else {
			out << "Nodurile nu au fost date corespunzator !" << endl;
		}
		out << endl;
	}

	return 0;
}
