//
// Created by raulo on 4/2/2024.
//

#include "domain.h"
#include <cassert>
//#include <utility>

/*Medicament::Medicament(int id_med, string denumire, int pret, string producator, string subst_activa) {
    this->id_med = id_med;
    this->denumire = std::move(denumire);
    this->pret = pret;
    this->producator = std::move(producator);
    this->subst_activa = std::move(subst_activa);
}*/

const int Medicament::get_id() const {
    return this->id_med;
}

const string& Medicament::get_denumire() const{
    return this->denumire;
}

const int Medicament::get_pret() const{
    return this->pret;
}

const string& Medicament::get_producator() const {
    return this->producator;
}

const string& Medicament::get_subst_activa() const {
    return this->subst_activa;
}

void Medicament::set_id(const int& id) {
    this->id_med = id;
}

void Medicament::set_pret(const int &new_pret) {
    this->pret = new_pret;
}

void Medicament::set_subst_activa(const string &new_subst_activa) {
    this->subst_activa = new_subst_activa;
}

void domainTests::test_getters_and_setters() {
    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");

    assert(med.get_id() == 0);
    assert(med.get_denumire() == "algolcalmin");
    assert(med.get_pret() == 25);
    assert(med.get_producator() == "Pharma");
    assert(med.get_subst_activa() == "paracetamol");

    med.set_id(1);
    med.set_pret(34);
    med.set_subst_activa("alta_substanta");

    assert(med.get_id() == 1);
    assert(med.get_pret() == 34);
    assert(med.get_subst_activa() == "alta_substanta");
}
