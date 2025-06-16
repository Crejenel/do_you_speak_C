#include <iostream> 
using namespace std;

class A {

public:

    A() { cout << "A" << endl; }

    ~A() { cout << "~A" << endl; }

    void print() {
        cout << "print" << endl;
    }
};

void f() {

    A a[2];  // se construiesc 2 entitati A. Se va afisa 'A' (linie noua) 'A' (linie noua)
    a[1].print(); // se apeleaza o metoda a entitatii A. Se va afisa 'print' (linie noua)

} // cele 2 entitati se vor distruge. Se va afisa : '~A' (linie noua) '~A' (linie noua)

int main() {

    f();

    return 0;
}
