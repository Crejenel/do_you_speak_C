#include <iostream>
#include <fstream>
#include <queue>
#include <string>
using namespace std;

ifstream f("file.txt");
int mat[50][50] = { 0 };
int nr_nod;
bool visited[50];
int parent[50];  
int labirint[100][100];
int start_x, start_y, finish_x, finish_y;

#define MAX_NOD_i 21
#define MAX_NOD_j 40

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };
bool vizitat[MAX_NOD_i][MAX_NOD_j] = { false };
int parinteX[MAX_NOD_i][MAX_NOD_j] = { -1 };
int parinteY[MAX_NOD_i][MAX_NOD_j] = { -1 };


// EX 5
void DFS_VISIT(int u) {
    visited[u] = true;
    cout << "Varful descoperit: " << u << endl;

    for (int v = 1; v <= nr_nod; v++) {
        if (mat[u][v] == 1 && !visited[v]) {
            parent[v] = u;  
            DFS_VISIT(v);
        }
    }
}
void DFS() {
    for (int i = 1; i <= nr_nod; i++) {
        visited[i] = false;
        parent[i] = -1; 
    }

    for (int i = 1; i <= nr_nod; i++) {
        if (!visited[i]) {
            cout << "Inceperea unui nou arbore din nodul " << i << endl;
            DFS_VISIT(i);
        }
    }
}
void exercitiul_5() {
    cout << endl;
	DFS();
    
}

// EX 1
void exercitiul_1(int x) {

    int Dis[51] = {};
    int Par[51] = {};
    queue<int> Q;
    Q.push(x);
    Dis[x] = 1;
    while (!Q.empty()) {
        int nod = Q.front();
        Q.pop();
        for (int k = 1; k <= nr_nod; k++) {
            if (mat[nod][k] == 1 && Dis[k] == 0) {
                Dis[k] = Dis[nod] + 1;
                Q.push(k);
            }
        }
    }

    int dis = 999;
    int nod = 0;
    for (int i = 1; i <= nr_nod; i++) {
        if ((Dis[i] - 1 < dis) && (Dis[i] - 1 > 0))
        {
            nod = i;
            dis = Dis[i] - 1;
        }  
    }

	if (dis == 999)
		cout << "Nu exista drum de la " << x << " la niciun nod" << endl;
	else
		cout << "Lantul minim de la " << x << " este pana la " << nod << " si are lungimea " << dis << endl;


}

// EX 2
void exercitiul_2() {

    int i, j, k;
	int MIT[50][50] = {0};
    for (i = 1; i <= nr_nod; i++)
    {
        int Dis[51] = {};
        queue<int> Q;
        Q.push(i);
        Dis[i] = 1;
        while (!Q.empty()) {
            int nod = Q.front();
            Q.pop();
            for (k = 1; k <= nr_nod; k++) {
                if (mat[nod][k] == 1 && Dis[k] == 0) {
                    Dis[k] = Dis[nod] + 1;
                    Q.push(k);
                }
            }
        }

        for (j = 1; j <= nr_nod; j++) {
            if (Dis[j] - 1 == 1 || j==i)
            {
                MIT[i][j] = 1;
            }
        }

    }

	for (i = 1; i <= nr_nod; i++)
	{
		for (j = 1; j <= nr_nod; j++)
		{
			cout << MIT[i][j] << " ";
		}
		cout << endl;
	}

}

// EX 4
void exercitiul_4(int x) {

    int Dis[51] = {};
    queue<int> Q;
    Q.push(x);
    Dis[x] = 1;
    while (!Q.empty()) {
        int nod = Q.front();
        Q.pop();
        for (int k = 1; k <= nr_nod; k++) {
            if (mat[nod][k] == 1 && Dis[k] == 0) {
                Dis[k] = Dis[nod] + 1;
                Q.push(k);
            }
        }
    }

    
    for (int i = 1; i <= nr_nod; i++) {

        if (Dis[i] - 1 > 0)
        {
            cout << "Distanta de la " << x << " pana la " << i << " are lungimea " << Dis[i] - 1 << endl;
        }
    }
    
}

// EX 3
bool citesteLabirintDinFisier(char numeFisier[]) {

    ifstream fisier(numeFisier); 

    if (!fisier.is_open()) {  

        std::cout << "Eroare la deschiderea fisierului!" << endl;
        return false;
    }

    string linie;
    int i = 0;  

    
    while (getline(fisier, linie) && i < MAX_NOD_i) {

        for (int j = 0; j <= linie.length(); j++) {
            
            if (linie[j] == 'S') {
                start_x = i+1; start_y = j;  
            }
            else if (linie[j] == 'F') {
                finish_x = i-1; finish_y = j;
            }
            labirint[i][j] = (linie[j] == '1') ? 0 : 1;
        }
        i++;
    }

    fisier.close(); 
	return true;
}
void afiseazaLabirint() {

    for (int i = 0; i < MAX_NOD_i; i++) {
        for (int j = 0; j <= MAX_NOD_j; j++) {
			cout << labirint[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

}
bool esteValida(int x, int y) {
    return (x >= 0 && x < MAX_NOD_i && y >= 0 && y < MAX_NOD_j && labirint[x][y] == 1 && !vizitat[x][y]);
}
bool BFS(){

    queue<pair<int, int>> q;
    q.push({ start_x, start_y });
    vizitat[start_x][start_y] = true;

    while (!q.empty()) {
        pair<int, int> curent = q.front();
        q.pop();
        int x = curent.first;
        int y = curent.second;

        if (x == finish_x && y == finish_y) {
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int nou_x = x + dx[i];
            int nou_y = y + dy[i];

            if (esteValida(nou_x, nou_y)) {
                vizitat[nou_x][nou_y] = true;
                parinteX[nou_x][nou_y] = x;  
                parinteY[nou_x][nou_y] = y; 
                q.push({ nou_x, nou_y });
            }
        }
    }

    return false;  
}
void afiseazaDrum(){

    int x = finish_x;
    int y = finish_y;
    vector<pair<int, int>> drum;

    while (x != start_x || y != start_y) {
        drum.push_back({ x, y });
        int temp_x = parinteX[x][y];
        int temp_y = parinteY[x][y];
        x = temp_x;
        y = temp_y;
    }
    drum.push_back({ start_x, start_y });

    for (int i = drum.size() - 1; i >= 0; i--) {
		labirint[drum[i].first][drum[i].second] = 2;
    }
}
void exercitiul_3() {

    char numeFisier[] = "labirint.txt";
    if (!citesteLabirintDinFisier(numeFisier)) {
        printf("Eroare la citirea labirintului din fisier!\n");
        return;
    }
    std::cout << endl;
    afiseazaLabirint();
    cout << "Coordonatele lui S sunt : " << start_x << " " << start_y << endl;
    cout << "Coordonatele lui F sunt : " << finish_x << " " << finish_y << endl;
	std::cout << endl;

    if (BFS()) {
        
		cout << " Labirintul cu solutie : " << endl;
		afiseazaDrum();
		afiseazaLabirint();
    }
    else {
        cout << "Nu exista solutie!" << endl;
    }
}

int main() {

    //-------------------------------------------
    int x, y, w;
    f >> nr_nod;

    while (f >> x >> y) {
        mat[x][y] = 1;
    }
    for (int i = 1; i <= nr_nod; i++) {
        for (int j = 1; j <= nr_nod; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

    //--------------------------------------------
    cout <<endl<< ">> Exercitiul 1 : Introduceti nodul sursa : ";
    std::cin >> w;
    exercitiul_1(w);

    //--------------------------------------------
    cout << endl << ">> Exercitiul 2 : Matricea inchiderii tranzitive : "<<endl;
    exercitiul_2();

    //--------------------------------------------
    cout << endl <<">> Exercitiul 4 : Introduceti nodul sursa : ";
    std:: cin >> w;
    exercitiul_4(w);

    //--------------------------------------------
    cout << endl << ">> Exercitiul 5 : ";
    exercitiul_5();

    //--------------------------------------------
    std::cout << endl << ">> Exercitiul 3 : Labirintul sub forma de matrice de adiacenta : " << endl;
    exercitiul_3();


    return 0;;
}
