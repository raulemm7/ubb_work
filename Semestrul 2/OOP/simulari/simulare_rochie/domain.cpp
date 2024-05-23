//
// Created by raulo on 5/23/2024.
//

#include "domain.h"
#include <cassert>

int Rochie::getCod() const {
    return this->cod;
}

const string &Rochie::getDenumire() const {
    return this->denumire;
}

const string &Rochie::getMarime() const {
    return this->marime;
}

int Rochie::getPret() const {
    return this->pret;
}

bool Rochie::isDisponibilitate() const {
    return this->disponibilitate;
}

const string Rochie::rochieString() const {
    // denumirea, marimea si pretul
    string info = this->getDenumire() + ", " + this->getMarime() + ", " + to_string(this->getPret()) + "\n";
    return info;
}

void Rochie::setDisponibilitate()  {
    if(this->disponibilitate)
        this->disponibilitate = false;
    else
        this->disponibilitate = true;
}

void testDomain::test_all() {
    Rochie r{1, "Gucci dress", "S", 120, true};

    assert(r.getCod() == 1);
    assert(r.getPret() == 120);
    assert(r.getDenumire() == "Gucci dress");
    assert(r.getMarime() == "S");
    assert(r.isDisponibilitate() == true);
}
