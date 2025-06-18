#include <iostream>
#include <vector>
using namespace std;

class Examen {

	string a;
	string b;

public :

	Examen(string a, string b) : a(a), b(b) {}

	string getDescriere() {
		return a + " " + b;
	}

};

template<typename unkown>
class ToDo {

private :

	vector<unkown> ent;

public :

	ToDo& operator<<(const unkown& other) {
		ent.push_back(other);
		return *this;
	}

	void printToDoList(ostream& os) {

		os << "de facut : ";
		for (auto toDo : ent) {
			os << toDo.getDescriere() << ";";
		}

	}


};

void todolist() {

	ToDo<Examen> todo;
	Examen oop{ "oop scris","8:00" };
	todo << oop << Examen{ "oop practic", "11:00" };
	//Adauga 2 examene la todo 
	std::cout << oop.getDescriere(); //tipareste la consola: oop scris ora 8:00 
	//itereaza elementele adaugate si tipareste la consola lista de activitati 
	//in acest caz tipareste: De facut:oop scris ora 8:00;oop practic ora 11:00 
	todo.printToDoList(std::cout);
}


int main() {

	todolist();

	return 0;
}
