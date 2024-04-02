//
// Created by raulo on 4/2/2024.
//

#include "service.h"
#include <cassert>

string Service::adaugaMedicament(MedicamenteRepo &storage, const Medicament &medicament) {
    Validator vali;
    if(vali.valideaza_med(storage, medicament)) {
        storage.adauga_medicament(medicament);
        return "Medicament adaugat cu succes!";
    }
    return "Acest medicament exista deja!";
}

string Service::stergeMedicament(MedicamenteRepo &storage, const int &id_medicament) {
    storage.sterge_medicament(id_medicament);
    return "Medicament sters cu succes!";
}

string Service::modificaMedicament(MedicamenteRepo &storage, const int &id_medicament, const int& new_pret,
                                   const string& new_subst_activa) {
    storage.modifica_medicament(id_medicament, new_pret, new_subst_activa);
    return "Medicament modificat cu succes!";
}

string Service::cautaMedicament(MedicamenteRepo &storage, const string &search) {
    for(int i = 0; i < storage.get_last_id(); i++) {
        Medicament med = storage.get_med(i);

        if(med.get_denumire() == search) {
            ui_operations ui;
            ui.print_one_med(med);
            return "Medicament gasit si afisat cu succes!";
        }
    }
    return "Nu am gasit niciun medicament inregistrat cu aceasta denumire!";
}

void serviceTests::run_all_servive_tests() {
    test_adaugaMedicament();
    test_cautaMedicament();
    test_modificaMedicament();
    test_stergeMedicament();
}

void serviceTests::test_adaugaMedicament() {
    Service service;

    MedicamenteRepo storage;
    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");

    assert(service.adaugaMedicament(storage, med) == "Medicament adaugat cu succes!");
    assert(service.adaugaMedicament(storage, med) == "Acest medicament exista deja!");
}

void serviceTests::test_stergeMedicament() {
    MedicamenteRepo storage;
    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");

    Service service;
    service.adaugaMedicament(storage, med);

    assert(service.stergeMedicament(storage, 0) == "Medicament sters cu succes!");
}

void serviceTests::test_modificaMedicament() {
    MedicamenteRepo storage;
    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");

    Service service;
    service.adaugaMedicament(storage, med);

    assert(service.modificaMedicament(storage, 0, 26, "alta_substanta") == "Medicament modificat cu succes!");
}

void serviceTests::test_cautaMedicament() {
    MedicamenteRepo storage;
    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");

    Service service;
    service.adaugaMedicament(storage, med);

    assert(service.cautaMedicament(storage, "algolcalmin") == "Medicament gasit si afisat cu succes!");
    assert(service.cautaMedicament(storage, "paramataciol") == "Nu am gasit niciun medicament inregistrat cu aceasta denumire!");
}
