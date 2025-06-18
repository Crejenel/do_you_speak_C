#include <iostream>
#include <vector>
#include <stdexcept>
#include <assert.h>
using namespace std;

/*
*   PARAMETRII : un vector de numere intregi
*   REZULTAT : o pereche formata din cele mai mari valori numerice din vector
*   PRECONDITII : -> lungimea vectorului sa fie strict mai mare ca 2
*                 -> numerele din vector trebuie sa fie pozitive
*/
std::pair<int, int> f(std::vector<int> l) {

    if (l.size() < 2) throw std::exception{};

    std::pair<int, int> rez{ -1,-1 };

    for (auto el : l) {

        if (el < rez.second) continue;

        if (rez.first < el) {
            rez.second = rez.first;
            rez.first = el;
        }
        else {
            rez.second = el;
        }
    }
    return rez;
}

void test_f() {

    std::vector<int> a = { 1,6,2,9,1,3,2 };
    std::pair<int, int>rez;
    rez = f(a);
    assert(rez.first = 9);
    assert(rez.second == 6);

    std::vector<int> b = { 0,9,2,9,1,7,2 };
    rez = f(b);
    assert(rez.first = 9);
    assert(rez.second == 9);

    std::vector<int> c = {0};
    try {
         rez = f(c);
         assert(false);
    }
    catch(std::exception& e){
        assert(true);
    }

    std::cout << "Testul pentru functia f a trecut!";

}

int main() {

    test_f();

    return 0;
}
