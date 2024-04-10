//
// Created by raulo on 4/2/2024.
//

#include "service.h"
#include <cassert>

const string Service::adaugaMedicament(VectorDinamic<Medicament>& storage, const Medicament& medicament) {
    Validator vali;
    if(vali.valideaza_med(storage, medicament)) {
        storage.adauga_element(medicament);
        return "Medicament adaugat cu succes!";
    }
    return "Acest medicament exista deja!";
}

const string Service::stergeMedicament(VectorDinamic<Medicament> &storage, const int &id_medicament) {
    storage.sterge_element(id_medicament);
    return "Medicament sters cu succes!";
}

const string Service::modificaMedicament(VectorDinamic<Medicament> &storage, const int &id_medicament, const int& new_pret,
                                   const string& new_subst_activa) {
    storage.modifica_element(id_medicament, new_pret, new_subst_activa);
    return "Medicament modificat cu succes!";
}

const string Service::cautaMedicament(const VectorDinamic<Medicament> &storage, const string &search) {
    for(int i = 0; i < storage.get_last_id_vd(); i++) {
        const Medicament& med = storage.get_element(i);

        if(med.get_denumire() == search) {
            ui_operations ui;
            ui.show_message("  ID  |  DENUMIRE  |  PRET  |  PRODUCATOR  |  SUBST. ACTIVA");
            ui.print_one_med(med);
            return "Medicament gasit si afisat cu succes!";
        }
    }
    return "Nu am gasit niciun medicament inregistrat cu aceasta denumire!";
}

const void serviceTests::run_all_servive_tests() {
    test_adaugaMedicament();
    test_cautaMedicament();
    test_modificaMedicament();
    test_stergeMedicament();
}

const void serviceTests::test_adaugaMedicament() {
    Service service;

    VectorDinamic<Medicament> storage;
    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");

    assert(service.adaugaMedicament(storage, med) == "Medicament adaugat cu succes!");
    assert(service.adaugaMedicament(storage, med) == "Acest medicament exista deja!");
}

const void serviceTests::test_stergeMedicament() {
    VectorDinamic<Medicament> storage;
    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");

    Service service;
    service.adaugaMedicament(storage, med);

    assert(service.stergeMedicament(storage, 0) == "Medicament sters cu succes!");
}

const void serviceTests::test_modificaMedicament() {
    VectorDinamic<Medicament> storage;
    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");

    Service service;
    service.adaugaMedicament(storage, med);

    assert(service.modificaMedicament(storage, 0, 26, "alta_substanta") == "Medicament modificat cu succes!");
}

const void serviceTests::test_cautaMedicament() {
    VectorDinamic<Medicament> storage;
    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");

    Service service;
    service.adaugaMedicament(storage, med);

    assert(service.cautaMedicament(storage, "algolcalmin") == "Medicament gasit si afisat cu succes!");
    assert(service.cautaMedicament(storage, "paramataciol") == "Nu am gasit niciun medicament inregistrat cu aceasta denumire!");
}
