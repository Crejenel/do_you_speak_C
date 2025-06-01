#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int numarNoduri;
int numarMuchii;
vector<int> cicluEulerian;
vector<vector<int>> listaAdiacenta;
bool orientat = false;


void Hierholzer(int nod) {
    while (!listaAdiacenta[nod].empty()) {
        int nodUrmator = listaAdiacenta[nod].back();
        listaAdiacenta[nod].pop_back();

        if (!orientat) {
            for (auto it = listaAdiacenta[nodUrmator].begin(); it != listaAdiacenta[nodUrmator].end(); ++it) {
                if (*it == nod) {
                    listaAdiacenta[nodUrmator].erase(it);
                    break;
                }
            }
        }

        Hierholzer(nodUrmator);
    }
    cicluEulerian.push_back(nod);
}

int main() {

    ifstream fin("dateIN.txt");
    ofstream fout("dateOUT.txt");

    fin >> numarNoduri >> numarMuchii;

    listaAdiacenta = vector<vector<int>>(numarNoduri+1);

    for (int i = 0; i < numarMuchii; i++) {
        int nod1, nod2;
        fin >> nod1 >> nod2;
        listaAdiacenta[nod1].push_back(nod2);
        if (!orientat) {
            listaAdiacenta[nod2].push_back(nod1);
        }
    }

    Hierholzer(1);

    fout << cicluEulerian.size() << endl;
    for (int nod : cicluEulerian) {
        fout << nod << " ";
    }

    return 0;
}
