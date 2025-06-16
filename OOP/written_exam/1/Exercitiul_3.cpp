#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// --------------- Diagrama UML (Cerinta 3) ---------------

class Smoothy {
private:
    int pret;
public:
    Smoothy(int p) : pret(p) {}
    virtual int getPrice() { return pret; }
    virtual string descriere() = 0;
    virtual ~Smoothy() = default;
};

class DecoratorSmoothy : public Smoothy {
private:
    Smoothy* component;
public:
    DecoratorSmoothy(Smoothy* s)
        : Smoothy(s->getPrice()), component(s) {
    }

    // delegam apelurile la obiectul agregat
    int getPrice() override {
        return component->getPrice();
    }
    string descriere() override {
        return component->descriere();
    }

    ~DecoratorSmoothy() {
        delete component;
    }
};

class BasicSmoothy : public Smoothy {
private:
    string nume;
public:
    BasicSmoothy(const string& n, int p)
        : Smoothy(p), nume(n) {
    }

    string descriere() override {
        return nume;
    }
};

class SmoothyCuFrisca : public DecoratorSmoothy {
public:
    SmoothyCuFrisca(Smoothy* s)
        : DecoratorSmoothy(s) {
    }

    int getPrice() override {
        return DecoratorSmoothy::getPrice() + 2;
    }
    string descriere() override {
        return DecoratorSmoothy::descriere() + " cu frisca";
    }
};

class SmoothyCuUmbreluta : public DecoratorSmoothy {
public:
    SmoothyCuUmbreluta(Smoothy* s)
        : DecoratorSmoothy(s) {
    }

    int getPrice() override {
        return DecoratorSmoothy::getPrice() + 3;
    }
    string descriere() override {
        return DecoratorSmoothy::descriere() + " cu umbreluta";
    }
};

// --------------- Cerinta 2: Lista de smoothy-uri ---------------

vector<Smoothy*> lista() {

    vector<Smoothy*> v;
    // 1) kiwi cu frisca si umbreluta
    v.push_back( new SmoothyCuUmbreluta( new SmoothyCuFrisca( new BasicSmoothy("kiwi", 5) )  ) );

    // 2) capsuni cu frisca
    v.push_back( new SmoothyCuFrisca( new BasicSmoothy("capsuni", 5) ) );

    // 3) simplu de kiwi
    v.push_back( new BasicSmoothy("kiwi", 5) );

    return v;
}

// --------------- Cerinta 3: Main + sortare + afisare ---------------

int main() {

    auto v = lista();

    // sortam dupa descriere (lexicografic)
    sort(v.begin(), v.end(), [](Smoothy* a, Smoothy* b) { return a->descriere() < b->descriere();});

    // afisam si eliberam memoria
    for (auto s : v) {
        cout << s->descriere() << ": " << s->getPrice() << " lei\n";
        delete s;
    }

    return 0;
}
