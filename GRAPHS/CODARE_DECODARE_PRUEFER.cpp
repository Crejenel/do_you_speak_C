#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <utility>
using std::fstream;
using std::ofstream;
using std::vector;
using std::endl;
using std::pair;
using std::set;

fstream f("DATE.txt");
ofstream g("REZULTAT.txt");

// reprezentarea matriciei
vector<vector<int>> adiacenta;
// vector de parinti ai nodurilor
vector<int> parinte;

// avem nevoie de parintii fiecarui nod in codare
void DFS(int nodCurent) {

    for (int vecin : adiacenta[nodCurent]) {
        if (vecin != parinte[nodCurent]) {
            parinte[vecin] = nodCurent;
            DFS(vecin);
        }
    }
}

vector<int> codPruefer() {

    // extragem numarul de noduri 
    int numarNoduri = (int)adiacenta.size();
    parinte.resize(numarNoduri);

    // aflam toti parintii nodurilor
    parinte[numarNoduri - 1] = -1;
    DFS(numarNoduri - 1);

    // avem nevoie de un vector de grad-uri
    vector<int> grad(numarNoduri);
    // initializam cu 'necunoscut' o variabila in care v-om stoca prima frunza cea mai mica
    int primulNodFrunza = -1;
    // luam frunza prima frunza cea mai mica
    for (int i = 0; i < numarNoduri; i++) {
        grad[i] = (int)adiacenta[i].size(); //initializam gradul fiecarui nod
        if (grad[i] == 1 && primulNodFrunza == -1) {
            primulNodFrunza = i;
        }
    }

    // avem nevoie de un vector rezultat de marime numarNoduri - 2, pentru ca atata va iesi codarea
    vector<int> cod(numarNoduri - 2);
    int nodFrunza = primulNodFrunza;

    for (int i = 0; i < numarNoduri - 2; i++) {
        // aflam nodul parinte al frunzei
        int nodParinte = parinte[nodFrunza];
        // il punem in rezultat
        cod[i] = nodParinte;
        // modificam gradul pentru ca suntem pe cale sa 'stergem' frunza
        grad[nodParinte]--;

        // daca parintele a devenit frunza si are indice mai mic decat primulNodFrunza
        if (grad[nodParinte] == 1 && nodParinte < primulNodFrunza) { 
            //parintele devine frunza
            nodFrunza = nodParinte;
        }
        else {
            // cautam urmatoarea frunza cea mai mica
            primulNodFrunza++;
            while (grad[primulNodFrunza] != 1)
                primulNodFrunza++;
            nodFrunza = primulNodFrunza;
        }
    }

    return cod;
}

vector<pair<int, int>> decodeaza_codul_pruefer(const vector<int>& cod_pruefer) {

    int numar_noduri = (int)cod_pruefer.size() + 2;  // numar de noduri din arbore

    vector<int> grad_nod(numar_noduri, 1); // toate sunt considerate frunze la inceput

    for (int nod : cod_pruefer)
        grad_nod[nod]++;   //fiecare are cel putin o legatura externa, stim asta din codarea pruefer

    // luam frunzele ramase dupa ce am eliminat alea care sigur nu sunt frunze
    set<int> frunze_disponibile;
    for (int nod = 0; nod < numar_noduri; nod++) {
        if (grad_nod[nod] == 1)
            frunze_disponibile.insert(nod);
    }

    // lista de muchii - practic rezultatul
    vector<pair<int, int>> lista_muchii;

    for (int parinte : cod_pruefer) { //parcurgem codarea prufer 

        // iau frunza cea mai mica
        int frunza_aleasa = *frunze_disponibile.begin();  
        // stergem ce am selectat
        frunze_disponibile.erase(frunza_aleasa);          

        lista_muchii.emplace_back(frunza_aleasa, parinte); // frunza minima, parintele e din codul prufer, adaug legatura in rezulatt

        // scad gradul parintelui, daca devine frunza il adaug in frunza
        if (--grad_nod[parinte] == 1)
            frunze_disponibile.insert(parinte);
    }

    // am mai ramas 2 noduri neconectate 
    int nod1 = *frunze_disponibile.begin(); // luam cel mai mic nod rams
    frunze_disponibile.erase(frunze_disponibile.begin()); // il stergem din multime
    int nod2 = *frunze_disponibile.begin(); // luam si pe celalat
    lista_muchii.emplace_back(nod1, nod2); // punem muchia in rezultat

    // returnam decodarea
    return lista_muchii;
}

int main() {

    int n;
    f >> n;

    adiacenta.resize(n);

    for (int copil = 0; copil < n; copil++) {
        int parinte;
        f >> parinte;

        if (parinte != -1) {
          
            adiacenta[parinte].push_back(copil);
            adiacenta[copil].push_back(parinte);
        }
    }

    vector<int> rezultat = codPruefer();

    g << "CODARE : " << endl;
    for (int i = 0; i < rezultat.size(); i++) {
        g << rezultat[i] << " ";
    }
    g << endl;

    vector<pair<int, int>> decodare = decodeaza_codul_pruefer(rezultat);

    g << "DECODARE : " << endl;
    for (const auto& muchie : decodare) {
        g << muchie.first << " - " << muchie.second << endl;
    }

   
    return 0;
}
