#include <iostream>
#include <fstream>
using namespace std;

//fisierul contine nr de varfuri si muchiile grafului
ifstream fin("data.txt");
//fisierul contine nr de componente conexte si componentele conexe efectiv
ofstream fout("result.txt");

int matrice[101][101]{ 0 };
int culori[101]{ 0 };
int nr_noduri;

void DFS(int nod,int culoare) {

	for (int i = 1; i <= nr_noduri; i++) {

		if (matrice[nod][i] == 1 && culori[i] == 0) {
			culori[i] = culoare;
			DFS(i, culoare);
		}
	}

}

int main() {

	
	fin >> nr_noduri;

	int x, y;
	int culoare = 0;
	
	
	while(fin>>x>>y){

		matrice[x][y] = matrice[y][x] = 1;
		//matrice[x][y]= 1; <- pentru grafuri orientate
	}

	for (int i = 1; i <= nr_noduri; i++) {
		if (culori[i] == 0) {
			culoare++;
			culori[i] = culoare;
			DFS(i, culoare);
		}
	}

	fout << culoare << endl;

	for (int i = 1; i <= culoare; i++) {
		for (int j = 1; j <= nr_noduri; j++) {
			if (culori[j] == i) {
				fout << j << " ";
			}
		}
		fout << endl;
	}

	return 0;
}
