#include <iostream> 
#include <vector> 

struct A {
    A() { std::cout << "A"; }
    virtual void print() {
        std::cout << "A";
    }
};

struct B : public A {
    B() { std::cout << "B"; }
    void print() override {
        std::cout << "B";
    }
};

int main() {

    std::vector<A> v;
    v.push_back(A{}); // constructorul lui A
    v.push_back(B{}); // constructorul lui A, apoi lui B. Ramane doar felia A din B
    for (auto& el : v) el.print(); // va afisa 2 de A
    return 0;
}

// AABAA
