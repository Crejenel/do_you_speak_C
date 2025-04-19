#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define INF 1000000

int main(int argc, char* argv[]) {


	ifstream fin("intrare.txt");
	if (!fin) {
		cout << "Eroare la deschiderea fisierului intrare.txt" << endl;
		return 1;
	}

	ofstream gout("iesire.txt");
	if (!gout) {
		cout << "Eroare la deschiderea fisierului iesire.txt" << endl;
		return 1;
	}

	int nr_vf, nr_m, nod_sursa;
	fin >> nr_vf >> nr_m >> nod_sursa;

	int matrice[100][100];
	for (int i = 0; i < 100; ++i)
		for (int j = 0; j < 100; ++j)
			matrice[i][j] = INF;

	vector<int> d(nr_vf, INF);
	vector<int> f(nr_vf, 0); 

	int x, y, z;
	while (fin >> x >> y >> z) {
		matrice[x][y] = z; 
	}

	for (int i = 0; i < nr_vf; ++i)
		d[i] = matrice[nod_sursa][i];

	d[nod_sursa] = 0;
	f[nod_sursa] = 1;

	for (int step = 1; step < nr_vf; ++step) {
		int pmin = -1;
		int min_dist = INF;

		for (int i = 0; i < nr_vf; ++i) {
			if (!f[i] && d[i] < min_dist) {
				min_dist = d[i];
				pmin = i;
			}
		}

		if (pmin == -1)
			break;

		f[pmin] = 1;

		for (int i = 0; i < nr_vf; ++i) {
			if (!f[i] && d[i] > d[pmin] + matrice[pmin][i]) {
				d[i] = d[pmin] + matrice[pmin][i];
			}
		}
	}

	for (int i = 0; i < nr_vf; ++i) {
		if (d[i] == INF)
			gout << "INF ";
		else
			gout << d[i] << " ";
	}

	fin.close();
	gout.close();
	return 0;
}
