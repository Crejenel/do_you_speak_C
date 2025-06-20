#include <iostream>
#include <time.h>
using namespace std;

class Channel {

public:
    virtual void send(string msg) = 0;
    virtual ~Channel() = default;
};

class Telefon : public Channel {

private:
    int nrTel;

public:

    Telefon(int nrTel) : nrTel(nrTel) {}

    void send(string msg) override {
        if (rand() % 2 == 0) {
            throw runtime_error("LINIA ESTE OCUPATA!");
        }
        else {
            cout << "[Telefon] Apelează " << nrTel
                << " cu mesajul: \"" << msg << "\"" << endl;
        }
    }
};

class Fax : public Telefon {
public:
    Fax(int nr) : Telefon(nr) {}
    void send(string msg) override {
        cout << "[Fax] Trimite fax cu mesajul: \"" << msg << "\"" << endl;
    }
};

class SMS : public Telefon {
public:
    SMS(int nr) : Telefon(nr) {}
    void send(string msg) override {
        cout << "[SMS] Trimite SMS cu mesajul: \"" << msg << "\"" << endl;
    }
};

class Failover : public Channel {
private:
    Channel* a;
    Channel* b;
public:
    Failover(Channel* a, Channel* b) : a(a), b(b) {}
    void send(string msg) override {
        try {
            a->send(msg);
        }
        catch (exception& e) {
            try {
                b->send(msg);
            }
            catch (exception& E) {
                cout << "[Failover] Eroare secundar: " << E.what() << endl;
            }
        }
    }
    ~Failover() {
        delete a;
        delete b;
    }
};

class Contact : public Channel {
private:
    Channel* a;
    Channel* b;
    Channel* c;
public:
    Contact(Channel* a, Channel* b, Channel* c) : a(a), b(b), c(c) {}
    void send(string msg) override {
        try {
            a->send(msg);
        }
        catch (exception& e) {
            cout << "[Contact] Eroare primar: " << e.what() << endl;
            try {
                b->send(msg);
            }
            catch (exception& E) {
                try {
                    c->send(msg);
                }
                catch (exception& Ee) {
                    throw runtime_error("Nu s-a reusit pe nicio cale!");
                }
            }
        }
    }
    void sendAlarm(string msg) {
        while (1) {
            try {
                send(msg);
                break;
            }
            catch (exception& e) {
                cout << "[Contact] Toate căile au căzut: " << e.what()
                    << ". Reîncerc..." << endl;
            }
        }
    }
    ~Contact() {
        delete a;
        delete b;
        delete c;
    }
};

Contact* f() {
    Telefon* t = new Telefon(778234716);
    Fax* fch = new Fax(1234567);
    SMS* s1 = new SMS(9875432);
    Failover* c1 = new Failover(fch, s1);

    Fax* f2 = new Fax(131767);
    SMS* s2 = new SMS(92455432);
    SMS* s3 = new SMS(1829356);
    Failover* c2 = new Failover(f2, s2);
    Failover* c3 = new Failover(s3, c2);

    return new Contact(t, c1, c3);
}

int main() {
    srand(time(NULL));

    Contact* c = f();
    c->sendAlarm("Buna!");  cout << endl;
    c->sendAlarm("Hi!");    cout << endl;
    c->sendAlarm("Holla!"); cout << endl;

    delete c;
    return 0;
}
