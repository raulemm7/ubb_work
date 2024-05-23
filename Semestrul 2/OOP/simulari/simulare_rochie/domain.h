//
// Created by raulo on 5/23/2024.
//

#ifndef SIMULARE_ROCHIE_DOMAIN_H
#define SIMULARE_ROCHIE_DOMAIN_H

#include <string>

using namespace std;

class Rochie{
private:
    int cod;
    string denumire;
    string marime;
    int pret;
    bool disponibilitate;
public:
    Rochie(int cod, const string &denumire, const string &marime, int pret, bool disponibilitate) : cod(cod),
                                                                                                    denumire(denumire),
                                                                                                    marime(marime),
                                                                                                    pret(pret),
                                                                                                    disponibilitate(
                                                                                                            disponibilitate) {};

    int getCod() const;

    const string &getDenumire() const;

    const string &getMarime() const;

    int getPret() const;

    bool isDisponibilitate() const;

    void setDisponibilitate();

    const string rochieString() const;

    virtual ~Rochie() = default;
};

class testDomain{
public:
    static void test_all();
};

#endif //SIMULARE_ROCHIE_DOMAIN_H
