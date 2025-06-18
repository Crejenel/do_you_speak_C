#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class Transformer {

public:

	virtual void transform(vector<int>& nrs) = 0;

	virtual ~Transformer() {}

};

class Number {

private :

	vector<int> numere;
	Transformer* transformer;

public :

	Number(Transformer* transformer) : transformer(transformer) {}

	vector<int>& transform() {

		sort(numere.begin(), numere.end(), [](int a, int b) { return a > b; });
		transformer->transform(numere);
		
		return numere;

	}

	void addd(int nr) {
		numere.push_back(nr);
	}

	~Number() {
		delete transformer;
	}

};

class Composite : public Transformer{

private :
	Transformer* transformer_1;
	Transformer* transformer_2;

public :

	Composite(Transformer* transformer_1,Transformer* transformer_2) : transformer_1(transformer_1), transformer_2(transformer_2) {}

	void transform(vector<int>& nrs) override {
		transformer_1->transform(nrs);
		transformer_2->transform(nrs);
	}

	~Composite() {
		delete transformer_1;
		delete transformer_2;
	}
};

class Adder : public Transformer{

private :

	int cat;

public:

	Adder(int cat) : cat(cat) {}

	void transform(vector<int>& nrs) override {

		for (size_t i = 0; i < nrs.size(); i++) {
			nrs[i] += cat;
		}
	}

};

class Nuller : public Adder{

public :

	Nuller(int nr) : Adder(nr) {}

	void transform(vector<int>& nrs) override {
		
		for (size_t i = 0; i < nrs.size(); i++) {
			if (nrs[i] > 10) {
				nrs[i] = 0;
			}
		}
	}

};

class Swapper : public Transformer{

public:

	void transform(vector<int>& nrs) override {

		for (size_t i = 0; i < nrs.size() && nrs.size()-i>=2; i+=2) {
			int aux = nrs[i];
			nrs[i] = nrs[i + 1];
			nrs[i + 1] = aux;
		}

	}

};

Number* functie() {

	Number* number = new Number(new Composite(new Nuller(9), new Composite(new Swapper, new Adder(3))));
	return number;
}

int main() {

	Number* number = functie();

	number->addd(1);
	number->addd(2);
	number->addd(3);
	number->addd(4);
	number->addd(5);

	vector<int> numere = number->transform();
	delete number;

	for (auto nr : numere) {
		cout << nr << " ";
	}

	return 0;
}
