#include <iostream>
using namespace std;

class Vechicul {
public:
    Vechicul();
    ~Vechicul();
    string getNrImatriculare() {
        return nrImatriculare;
    }
    void setNrImatriculare(string x) {
        if (checkNrImatriculare(x)) {
            nrImatriculare = x;
        }
    }
private:
    string nrImatriculare;
    bool checkNrImatriculare(string nrImatriculare) {
        // Check if the number is Romanian number
        if (nrImatriculare.length() != 7) {
            return false;
        }
        if (nrImatriculare[0] < 'A' || nrImatriculare[0] > 'Z') {
            return false;
        }
        if (nrImatriculare[1] < 'A' || nrImatriculare[1] > 'Z' || !std::isdigit(nrImatriculare[1])) {
            return false;
        }
        if (!isdigit(nrImatriculare[2]) || !isdigit(nrImatriculare[3])) {
            return false;
        }
        if (nrImatriculare[4] < 'A' || nrImatriculare[4] > 'Z' || nrImatriculare[5] < 'A' || nrImatriculare[5] > 'Z' || nrImatriculare[6] < 'A' || nrImatriculare[6] > 'Z') {
            return false;
        }
        return true;
    }
};

class Motor {
public:
    Motor();
    ~Motor();
    int getCapacitate();
    void setCapacitate(int capacitate);
    int getCaiPutere();
    void setCaiPutere(int cai_putere);

private:
    int capacitate;
    int cai_putere;
};

class VechiculcuMotor : public Vechicul {
public:
    VechiculcuMotor();
    ~VechiculcuMotor();
private:
    string marca;
    Motor motor;
};

class VechiculFaraMotor : public Vechicul {
public:
    VechiculFaraMotor();
    ~VechiculFaraMotor();
};

class Masina : public VechiculcuMotor {
public:
    Masina();
    ~Masina();
private:

};

int main() {

    return 0;
}