#include <iostream>
#include <vector>
using namespace std;

class Meniu {

private :
	int pret=0;

public :

	Meniu(int pret) : pret(pret){}

	virtual string descriere() = 0;

	int getPret() {
		return pret;
	}

	virtual ~Meniu() {}

};

class CuRacoritoare : public Meniu {

private :

	Meniu* SubMeniu;

public :

	CuRacoritoare(Meniu* SubMeniu) : SubMeniu(SubMeniu), Meniu(SubMeniu->getPret()+4){}

	string descriere() override {
		return SubMeniu->descriere() + " Cu racoritoare";
	}

	~CuRacoritoare() {
		delete SubMeniu;
	}

};

class CuCafea : public Meniu{


private:

	Meniu* SubMeniu;

public:

	CuCafea(Meniu* SubMeniu) : SubMeniu(SubMeniu), Meniu(SubMeniu->getPret()+5) {}

	string descriere() override {
		return SubMeniu->descriere() + " Cu cafea";
	}

	~CuCafea() {
		delete SubMeniu;
	}
};

class MicDejun : public Meniu {

private :

	string denumire;

public :

	MicDejun(string denumire) : denumire(denumire), Meniu(denumire == "Ochiuri" ? 10 : 15) {}

	string descriere() override{
		return denumire;
	}

};

vector<Meniu*> lista(){

	vector<Meniu*> comanda;
	Meniu* a = new CuCafea(new CuRacoritoare(new MicDejun("Omleta")));
	Meniu* b = new CuCafea(new MicDejun("Ochiuri"));
	Meniu* c = new MicDejun("Omleta");
	comanda.push_back(c);
	comanda.push_back(a);
	comanda.push_back(b);

	return comanda;

}

int main() {

	vector<Meniu*> comanda = lista();
	while (comanda.size() > 1)
	{
		int index = 0;
		for (size_t i = 0; i < comanda.size(); i++) {
			if (comanda[index]->getPret() < comanda[i]->getPret()) {
				index = (int)i;
			}
		}

		cout << comanda[index]->descriere() << " " << comanda[index]->getPret() << endl;
		delete comanda[index];
		comanda.erase(comanda.begin() + index);
	}
	cout << comanda[0]->descriere() << " " << comanda[0]->getPret() << endl;
	delete comanda[0];

	return 0;
}
