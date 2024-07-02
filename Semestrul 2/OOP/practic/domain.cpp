//
// Created by raulo on 6/25/2024.
//

#include "domain.h"
#include <cassert>
#include <iostream>

const std::string &Masina::getNrInmatriculare() const {
    return this->nr_inmatriculare;
}

const std::string &Masina::getDenumire() const {
    return this->denumire;
}

int Masina::getAnFabricatie() const {
    return this->anFabricatie;
}

const std::string &Masina::getTip() const {
    return this->tip;
}

void Masina::setAnFabricatie(int modificareAnFabricatie) {
    this->anFabricatie += modificareAnFabricatie;
}

void TestDomain::test_all() {
    Masina m{"sv77vio", "skoda", 2011, "sedan"};

    assert(m.getDenumire() == "skoda");
    assert(m.getAnFabricatie() == 2011);
    assert(m.getTip() == "sedan");
    assert(m.getNrInmatriculare() == "sv77vio");

    m.setAnFabricatie(1);
    assert(m.getAnFabricatie() == 2012);

    m.setAnFabricatie(-3);
    assert(m.getAnFabricatie() == 2009);

    std::cout << "Passed domain tests\n";
}
