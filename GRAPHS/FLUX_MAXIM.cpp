#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
ifstream fin("a.txt");

// Edmonds - Karp

const int N = 1000; // Dimensiune maximă
int mat[N][N], matrez[N][N]; // Capacități inițiale și reziduale

// Funcția BFS care caută un drum de creștere și construiește vectorul de părinți
bool bfs(int s, int t, int V, int parinte[]) {

    bool vizitat[N] = { false };
    queue<int> q;

    q.push(s);
    vizitat[s] = true;
    parinte[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (!vizitat[v] && matrez[u][v] > 0) {
                parinte[v] = u;
                vizitat[v] = true;
                q.push(v);
            }
        }
    }

    return vizitat[t]; // Întoarce true dacă am ajuns la destinație
}

int main() {

    int V = 0; // Număr noduri
    int E = 0; // Număr muchii

    fin >> V >> E;

    // Citirea grafului
    for (int i = 0; i < E; i++) {
        int a, b, c;
        fin >> a >> b >> c;
        mat[a][b] = c;
        matrez[a][b] = c;
    }

    int s = 0;         // Sursa
    int t = V - 1;     // Destinația

    int parinte[N];    // Vector pentru drumuri
    int flux_max = 0;  // Rezultatul final

    // Cât timp există drumuri de creștere
    while (bfs(s, t, V, parinte)) {
        int path = 99999999;

        // Găsim capacitatea minimă pe drum
        for (int v = t; v != s; v = parinte[v]) {
            int u = parinte[v];
            path = min(path, matrez[u][v]);
        }

        // Actualizăm graful rezidual
        for (int v = t; v != s; v = parinte[v]) {
            int u = parinte[v];
            matrez[u][v] -= path;
            matrez[v][u] += path;
        }

        flux_max += path; // Adăugăm la fluxul total
    }

    cout << "Fluxul maxim este: " << flux_max << "\n";

    return 0;
}
