#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

ifstream f("fisier.txt");

int culoare[100] = {0};
int comp_conex = 0;
int i, j, l, x, y, gasit, numar;
int nr_noduri;
int nr_muchii=0;
int muchii[2][100] = {0};
int matrice_adiacenta[100][100] = {0};
int matrice_incidenta[100][100] = {0};
int matricea_distantelor[100][100] = {0};

void DFS(int nod) {

	culoare[nod] = 1;
	for (int k = 1; k <= nr_noduri; k++) {
		if (matrice_adiacenta[k][nod] == 1 && culoare[k] == 0) {
			DFS(k);
		}
	}
}

int dis_min(int x, int y) {

	int Dis[101] = {};
	queue<int> Q;
	Q.push(x);
	Dis[x] = 1;
	while (!Q.empty()) {
		int nod = Q.front();
		Q.pop();
		for (int k = 1; k <= nr_noduri; k++) {
			if (matrice_adiacenta[nod][k] == 1 && Dis[k] == 0) {
				Dis[k] = Dis[nod] + 1;
				Q.push(k);
			}
		}
	}
	return Dis[y]-1;


}


int main() {

	f >> nr_noduri;
	vector<vector<int>> listaAdiacenta(nr_noduri + 1);
	
	std :: cout << endl << "Din fisier in matrice de adiacenta : " << endl;
	while (f >> x >> y) { 
		matrice_adiacenta[x][y] = 1; matrice_adiacenta[y][x]=1;
		muchii[0][nr_muchii] = x; 
		muchii[1][nr_muchii] = y; 
		nr_muchii++; }
	for (i = 1; i <= nr_noduri; i++)
	{
		for (j = 1; j <= nr_noduri; j++) {
			std::cout << matrice_adiacenta[i][j] << " ";
		}
		std::cout << endl;
	}

	std::cout << endl << "Din matricea de adiacenta in lista de adiacenta : " << endl;
	for (i = 1; i <= nr_noduri; i++)
	{
		for (j = 1; j <= nr_noduri; j++) {
			
			if (matrice_adiacenta[i][j] == 1) {
				listaAdiacenta[i].push_back(j);
			}
		}
	}
	for (i = 1; i <= nr_noduri; ++i) {
		std::cout << "Nodul " << i << ": ";
		if (!listaAdiacenta[i].empty()) { 
			j = (int)listaAdiacenta[i].size(); 
			while (j > 0) {
				std::cout << listaAdiacenta[i][listaAdiacenta[i].size() - j] << " ";
				--j;
			}
		}
		std::cout << endl;
	}

	std::cout << endl << "Din lista de adiacenta in matrice de incidenta : " << endl;
	for (i = 1; i <= nr_noduri; ++i) {
		if (!listaAdiacenta[i].empty()) { 
			j = (int)listaAdiacenta[i].size(); 
			while (j > 0) {
				int valoare = listaAdiacenta[i][listaAdiacenta[i].size() - j];
				for(l=0; l<nr_muchii; l++){
					if((i==muchii[0][l] && valoare==muchii[1][l]) || (i==muchii[1][l] && valoare==muchii[0][l]))
					{
						matrice_incidenta[i][l+1] = 1;
					}
				}	
				--j;
			}
		}
	}
	for (i = 0; i < nr_muchii; i++) { 
		std::cout << "(" << muchii[0][i] << ";" << muchii[1][i] << ") | "; }
	for (i = 1; i <= nr_noduri; i++) { 
		matrice_incidenta[i][0] = i; }
	std::cout << endl;
	for (i = 1; i <= nr_noduri; i++)
	{
		for (j = 0; j <= nr_noduri; j++) {

			std::cout << matrice_incidenta[i][j];
			if (j == 0) { std::cout << "|"; }
			std::cout << " ";
		}
		std::cout << endl;
	}

	std::cout << endl << "Din matrice de incidenta in lista de adiacenta : " << endl;
	for (i = 1; i <= nr_noduri; ++i) {
		while(!listaAdiacenta[i].empty()) {
			listaAdiacenta[i].pop_back();
		}
	}
	for (i = 1; i <= nr_noduri; i++)
	{
		for (int j = 1; j <= nr_noduri; j++) {

			if (matrice_incidenta[i][j] == 1) {

				if (muchii[0][j - 1] != i) { listaAdiacenta[i].push_back(muchii[0][j - 1]); }
				if (muchii[1][j - 1] != i) { listaAdiacenta[i].push_back(muchii[1][j - 1]); }
			}
		}
	}
	for (i = 1; i <= nr_noduri; ++i) {
		std::cout << "Nodul " << i << ": ";
		if (!listaAdiacenta[i].empty()) {
			j = (int)listaAdiacenta[i].size();
			while (j > 0) {
				std::cout << listaAdiacenta[i][listaAdiacenta[i].size() - j] << " ";
				--j;
			}
		}
		std::cout << endl;
	}
	
	std::cout <<endl<<"Din lista de adiacenta in matrice de adiacenta : "<<endl;
	memset(matrice_adiacenta, 0, sizeof(matrice_adiacenta));
	for (i = 1; i <= nr_noduri; ++i) {
		if (!listaAdiacenta[i].empty()) {
			j = (int)listaAdiacenta[i].size();
			while (j > 0) {
				matrice_adiacenta[i][listaAdiacenta[i][listaAdiacenta[i].size() - j]] = 1;
				--j;
			}
		}
	}
	for (i = 1; i <= nr_noduri; i++)
	{
		for (int j = 1; j <= nr_noduri; j++) {
	
			std::cout << matrice_adiacenta[i][j] << " ";
		}
		std::cout << endl;
	}

	std::cout <<endl << "Sa se determine nodurile izolate din lista : ";
	gasit = 0;
	for (i = 1; i <= nr_noduri; ++i) {
			j = (int)listaAdiacenta[i].size();
			if (j == 0) {
				std::cout << i << " ";
				gasit = 1;
			}
	}
	if (gasit == 0) {
		std::cout << "-";
	}
	std::cout << endl;

	std::cout << endl << "Sa se determine daca graful este regulat : ";
	gasit = 1;
	numar = 0;
	for (i = 1; i <= nr_noduri; ++i) {
		if (!listaAdiacenta[i].empty()) {
			j = (int)listaAdiacenta[i].size();
			if (i == 1) {
				numar = j;
			}
			else {
				if (numar != j) { gasit = 0; break; }
			}
		}
	}
	if (gasit == 0) {
		std::cout << "NU";
	}
	else {
		std::cout << "DA";
	}
	std::cout << endl;

	std::cout << endl << "Sa se determine daca graful este conex : ";
	for (i = 1; i <= nr_noduri; i++) {
		if (culoare[i] == 0) {
			comp_conex++;
			DFS(i);
		}
	}
	
	if (comp_conex > 1) {
		cout << "NU"<< endl;
	}
	else {
		cout << "DA" << endl;
	}

	std::cout << endl << "Sa se determine matricea distantelor a unui graf neorientat : "<<endl;
	for (i = 1; i <= nr_noduri; i++)
	{
		for (j = 1; j <= nr_noduri; j++) {

			matricea_distantelor[i][j] = dis_min(i, j);
		}
	}
	for (i = 1; i <= nr_muchii; i++) {

		for (j = 1; j <= nr_muchii; j++) {
			std::cout << matricea_distantelor[i][j] << " ";
		}
		std::cout << endl;
	}

		
	return 0;
}
