#include <iostream> 
using namespace std;

class A {

    int x;

public:

    A(int x) : x{ x } {}
    void print() { cout << x << endl; }
};

A f(A a) {

    a.print(); // afiseaza 4
    a = A{ 10 };
    a.print(); // afiseaza 10
    return a;
}

int main() {

    A a{ 4 };
    a.print(); // afiseaza 4
    f(a);
    a.print(); // afiseaza 4 ( nu s-a transmis prin referinta )
}

// 4 (linie noua) 4 (linie noua) 10 (linie noua) 4 (linie noua)
