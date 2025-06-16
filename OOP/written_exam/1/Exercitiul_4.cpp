#include <iostream>
#include <vector>
using std::vector;
using namespace std;

template <typename uncknow>
class Geanta {

private :

    string nume;
    vector<string> obiecte;

public :

    Geanta(string nume) : nume(nume) {}

    Geanta operator+(string obiect) {
        
        Geanta copie = *this;            
        copie.obiecte.push_back(obiect); 
        return copie;               
       
    }

    Geanta& operator=(const Geanta& other) {

        if (this != &other) {
            nume = other.nume;
            obiecte = other.obiecte;
        }
        return *this;
    }

    auto begin() { return obiecte.begin(); }
    auto end() { return obiecte.end(); }
    auto begin() const { return obiecte.begin(); }
    auto end()   const { return obiecte.end(); }

};

void calatorie() {

    Geanta<string> ganta{ "Ion" };//creaza geanta pentru Ion 
    ganta = ganta + string{ "haine" }; //adauga obiect in ganta 
    ganta + string{ "pahar" };
    for (auto o : ganta) {//itereaza obiectele din geanta 
        cout << o << "\n";
    }
}

int main() {

    calatorie();

    return 0;
}
