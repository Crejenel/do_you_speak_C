#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

class Nod {

public:

    char caracter;      
    int frecventa;      
    Nod* stanga;       
    Nod* dreapta;       

    // Constructor: inițializează nodul cu caracter și frecvență
    Nod(char c, int f) : caracter(c), frecventa(f), stanga(nullptr), dreapta(nullptr) {}
};

struct Comparator {

    bool operator()(Nod* a, Nod* b) {
        return a->frecventa > b->frecventa;
    }
};

Nod* construireArbore(unordered_map<char, int>& frecvente) {

    priority_queue<Nod*, vector<Nod*>, Comparator> coada;

    for (auto& pereche : frecvente) {
        coada.push(new Nod(pereche.first, pereche.second));
    }

    while (coada.size() > 1) {

        Nod* nod1 = coada.top(); coada.pop(); 
        Nod* nod2 = coada.top(); coada.pop(); 

        Nod* nodNou = new Nod('\0', nod1->frecventa + nod2->frecventa);
        nodNou->stanga = nod1;   
        nodNou->dreapta = nod2;  

        coada.push(nodNou);
    }

    return coada.top();
}

void construireCoduri(Nod* radacina, string cod, unordered_map<char, string>& coduri) {

    if (!radacina) return;

    if (!radacina->stanga && !radacina->dreapta) {
        coduri[radacina->caracter] = cod;
    }

    construireCoduri(radacina->stanga, cod + "0", coduri);
    construireCoduri(radacina->dreapta, cod + "1", coduri);
}

string decodificaText(const string& textCodificat, Nod* radacina){

    string rezultat = "";
    Nod* curent = radacina;

    for (char bit : textCodificat) {
 
        if (bit == '0') {
            curent = curent->stanga;
        }
        else {
            curent = curent->dreapta;
        }

        if (!curent->stanga && !curent->dreapta) {
            rezultat += curent->caracter;
            curent = radacina;
        }

    }

    return rezultat;
}

int main() {

    string text = "exemplu codare huffman";

    // 1. Calculăm frecvența fiecărui caracter din text
    unordered_map<char, int> frecvente;
    for (char c : text) {
        frecvente[c]++;
    }

    // 2. Construim arborele Huffman bazat pe frecvențe
    Nod* radacina = construireArbore(frecvente);

    // 3. Construim codurile Huffman pentru fiecare caracter
    unordered_map<char, string> coduri;
    construireCoduri(radacina, "", coduri);

    // 4. Afișăm codurile Huffman
    cout << "Codurile Huffman:\n";
    for (auto& pereche : coduri) {
        cout << "'" << pereche.first << "': " << pereche.second << "\n";
    }

    // 5. Codificăm textul folosind codurile generate
    string codificat = "";
    for (char c : text) {
        codificat += coduri[c];
    }
    cout << "\nText codificat:\n" << codificat << "\n";

    string textDecodificat = decodificaText(codificat, radacina);
    cout << "\nText decodificat:\n" << textDecodificat << "\n";

    return 0;
}
