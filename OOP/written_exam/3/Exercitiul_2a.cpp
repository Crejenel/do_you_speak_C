#include <iostream> 
using namespace std;

class A {
public:
    A() { cout << "A()" << endl; }
    void print() {
        cout << "printA" <<
            endl;
    }
};

class B : public A {
public:
    B() { cout << "B()" << endl; }
    void print() {
        cout << "printB" <<
            endl;
    }
};

int main() {

    A* o1 = new A(); // se afiseaza A() (linie noua)
    B* o2 = new B(); // se afiseaza A() (linie noua) B() (linie noua)
    o1->print(); // se afiseaza printA (linie noua)
    o2->print(); // se afiseaza printB (linie noua)
    delete o1; delete o2;

    return 0;
}
