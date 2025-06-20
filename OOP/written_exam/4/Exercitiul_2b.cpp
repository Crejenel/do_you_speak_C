#include <iostream> 
#include <vector>
using namespace std;
class A {
public:
    A() { cout << "A" << endl; }
    ~A() { cout << "~A" << endl; }
    void print() {
        cout << "print" <<
            endl;
    }
};
void f() {

    vector<A> v[2];    // nu se afiseaza
    v->push_back(A()); // se creeaza 1

    A a[2];     //A A print ~A ~A
    a[0].print();
}
int main() {
    f();
    return 0;
}
