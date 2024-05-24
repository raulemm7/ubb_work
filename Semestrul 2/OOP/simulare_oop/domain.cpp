//
// Created by raulo on 5/24/2024.
//

#include "domain.h"
#include <cassert>

int Pix::getId() const {
    return this->id;
}

const string &Pix::getBrand() const {
    return this->brand;
}

const string &Pix::getCuloare() const {
    return this->culoare;
}

float Pix::getPret() const {
    return this->pret;
}

const string Pix::getPixString() const {
    string str_pix = this->brand + " (" + to_string(this->pret) + ")";
    return str_pix;
}

void testDomain::test_all() {
    Pix pix{1, "Bic", "albastru", 20.2};

    assert(pix.getId() == 1);
    assert(pix.getBrand() == "Bic");
    assert(pix.getCuloare() == "albastru");
    assert(pix.getPret() - 20.2 < 0.01);
}
