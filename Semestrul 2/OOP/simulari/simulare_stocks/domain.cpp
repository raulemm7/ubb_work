//
// Created by raulo on 5/22/2024.
//

#include "domain.h"

StockObject::StockObject(const string& id, const string &nume, float pret, int changeRate) : id(id), nume(nume), pret(pret),
                                                                                     change_rate(changeRate) {}

const string &StockObject::getId() const {
    return this->id;
}

const string &StockObject::getNume() const {
    return this->nume;
}

float StockObject::getPret() const {
    return this->pret;
}

int StockObject::getChangeRate() const {
    return this->change_rate;
}

