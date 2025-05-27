#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;
using std::fstream;
using std::ofstream;
using std::vector;
using std::stack;
using std::endl;

// nr de noduri, nr de muchii, legatura dintre 2 noduri 
fstream f("dateIN.txt");
ofstream g("dateOUT.txt");

int n; // nr de noduri
int m; // numar de arce
int nr=0; // numarul componentelor tari conexte
vector <int> graf[100], graf_transpus[100]; // reprezentarea grafului - liste de adiacenta
										    // presupunem ca nr maxim de noduri e 100
stack <int> stiva;
int vizitat[100] = { 0 };
vector<int> result[100]; // prentru afisarea efectiva a componeteor

// citeste datee din fisier
void citire() {

	f >> n >> m;
	int x, y;	
	for (int i = 0; i < m; i++) {
		f >> x >> y;
		graf[x].push_back(y);
		graf_transpus[y].push_back(x);
	}
}

//algoritmul DFS cu care populam stiva
void DFS(int nod) {

	vizitat[nod] = 1;
	for (size_t i = 0; i < graf[nod].size(); i++) {
		int vecin = graf[nod][i];
		if (vizitat[vecin] != 1) {
			DFS(vecin);
		}
	}
	stiva.push(nod);

}

//algoritmul DFS pe graful transpus cu care determinam componetele conexe
void DFS_transpus(int nod) {

	result[nr].push_back(nod);
	vizitat[nod] = 2;
	for (size_t i = 0; i < graf_transpus[nod].size(); i++) {
		int vecin = graf_transpus[nod][i];
		if (vizitat[vecin] != 2) {
			DFS_transpus(vecin);
		}
	}
}

//algoritmul efectiv a lui Kasaraju
void Kosaraju() {

	// popularea stivei efectiv
	for (int i = 1; i <= n; i++) { // i=0 daca noduri sunt numerotate de la 0
		if (vizitat[i] != 1) {
			DFS(i);
		}
	}

	// determinam componeste conexte
	while (!stiva.empty()) {
		int nod = stiva.top();
		if (vizitat[nod] == 1) {
			DFS_transpus(nod);
			nr++;
		}
		stiva.pop();
	}

}

int main() {

	citire();
	Kosaraju();
	g << nr << endl;
	for (int i = 0; i < nr; i++) {

		g << "Componenta " << i + 1 << ": ";
		for (size_t j = 0; j < result[i].size(); j++) {
			g << result[i][j] << " ";
		}
		g << endl;
	}


	return 0;
}
