#include <iostream> 
using namespace std;

int except(bool thrEx) {

    if (thrEx) {
        throw 2;
    }
    return 3;
}

int main() {

    try {
        cout << except(1 < 1); // afiseaza 3
        cout << except(true); // se arunca 'exceptie'
        cout << except(false);
    }
    catch (int ex) { // prinde exceptia, un int
        cout << ex; // afiseaza 2
    }
    cout << 4; // afiseaza 4

    //Pe ecran se va afisa 324
    return 0;
}
