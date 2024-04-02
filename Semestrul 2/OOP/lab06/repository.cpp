//
// Created by raulo on 4/2/2024.
//

#include "repository.h"
#include <cassert>

MedicamenteRepo::MedicamenteRepo() {
    this->nr_medicamente = 0;
}

void MedicamenteRepo::adauga_medicament(const Medicament &medicament) {
    this->lista_meds.push_back(medicament);
    this->nr_medicamente++;
}

int MedicamenteRepo::get_last_id() const{
    return this->nr_medicamente;
}

Medicament MedicamenteRepo::get_med(const int &position) {
    return this->lista_meds[position];
}

void MedicamenteRepo::sterge_medicament(const int &id_med) {
    for(int i = id_med; i < this->nr_medicamente - 1; i++)
        this->lista_meds[i] = this->lista_meds[i + 1];

    this->lista_meds.erase(this->lista_meds.begin() + this->nr_medicamente - 1);
    this->nr_medicamente--;

    // update id for every medicament
    for(int i = 0; i < this->nr_medicamente; i++) {
        Medicament med = this->lista_meds[i];
        med.set_id(i);
        this->lista_meds[i] = med;
    }
}

void MedicamenteRepo::modifica_medicament(const int &id_med, const int& new_pret, const string& new_subst_activa) {
    Medicament med = this->lista_meds[id_med];
    med.set_pret(new_pret);
    med.set_subst_activa(new_subst_activa);
    this->lista_meds[id_med] = med;
}

void repositoryTests::test_repository_functionalities() {
    MedicamenteRepo storage;

    assert(storage.get_last_id() == 0);

    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");
    storage.adauga_medicament(med);

    // testare adaugare
    assert(storage.get_last_id() == 1);
    Medicament med_from_storage = storage.get_med(0);
    assert(med_from_storage.get_id() == 0);
    assert(med_from_storage.get_denumire() == "algolcalmin");
    assert(med_from_storage.get_pret() == 25);
    assert(med_from_storage.get_producator() == "Pharma");
    assert(med_from_storage.get_subst_activa() == "paracetamol");

    // testare modificare
    storage.modifica_medicament(0, 34, "alta_substanta");
    med_from_storage = storage.get_med(0);
    assert(med_from_storage.get_pret() == 34);
    assert(med_from_storage.get_subst_activa() == "alta_substanta");

    // testare stergere
    // mai adaug un medicament
    Medicament med2(1, "brufen", 19, "ceva_producator", "paramataciol");
    storage.adauga_medicament(med2);

    storage.sterge_medicament(0);
    assert(storage.get_last_id() == 1);
    med_from_storage = storage.get_med(0);
    assert(med_from_storage.get_id() == 0);
    assert(med_from_storage.get_denumire() == "brufen");
    assert(med_from_storage.get_pret() == 19);
    assert(med_from_storage.get_producator() == "ceva_producator");
    assert(med_from_storage.get_subst_activa() == "paramataciol");
}
