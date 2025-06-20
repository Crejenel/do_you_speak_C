#include <iostream>
using namespace std;

template<typename uknow>
class Expresie {

	uknow nr;

public :

	Expresie(uknow nr) : nr(nr) {}

	Expresie& operator+(const uknow n) {

		this->nr = this->nr + n;
		return *this;
	}

	Expresie& operator-(const uknow n) {

		this->nr = this->nr -n ;
		return *this;
	}

	uknow valoare() {
		return nr;
	}

	

};


void operatii() {
	Expresie<int> exp{ 3 };//construim o expresie,pornim cu operandul 3 
	//se extinde expresia in dreapta cu operator (+ sau -)  si operand 
	exp = exp + 7 + 3;
	exp = exp - 8;
	//tipareste valoarea expresiei (in acest caz:5 rezultat din 3+7+3-8) 
	cout << exp.valoare() << "\n";
}

int main() {

	operatii();

	return 0;
}
