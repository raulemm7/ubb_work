//
// Created by raulo on 4/2/2024.
//

#include "validators.h"
#include <cassert>

const bool Validator::valideaza_med(const AbstractRepo& storage, const Medicament& medicament) {
    for(int i = 0; i < storage.get_last_id(); i++) {
        const Medicament& med = storage.get_med(i);

        if(med.get_denumire() == medicament.get_denumire() and
           med.get_pret() == medicament.get_pret() and
           med.get_producator() == medicament.get_producator() and
           med.get_subst_activa() == medicament.get_subst_activa())
            return false;
    }
    return true;
}

const int Validator::valideaza_med_dupa_denumire(AbstractRepo &storage, const string &denumire) {
    vector<Medicament>& vec = storage.get_all();
    int pos = 0;
    for(const auto& med : vec) {
        if(med.get_denumire() == denumire)
            return pos;
        pos++;
    }
    return -1;
}

const bool Validator::compare_denumire(const Medicament &med1, const Medicament &med2) {
    return med1.get_denumire() < med2.get_denumire();
}

const bool Validator::compare_producator(const Medicament &med1, const Medicament &med2) {
    return med1.get_producator() < med2.get_producator();
}

const bool Validator::compare_subst_activa_and_pret(const Medicament &med1, const Medicament &med2) {
    if(!compare_subst_activa(med1, med2)) {
        if(!compare_pret(med1, med2))
            return true;
        return false;
    }
    else if(compare_subst_activa(med1, med2) == -1)
        return true;
    else
        return false;
}

const bool Validator::compare_pret(const Medicament &med1, const Medicament &med2) {
    return med1.get_pret() > med2.get_pret();
}

const int Validator::compare_subst_activa(const Medicament &med1, const Medicament &med2) {
    if(med1.get_subst_activa() > med2.get_subst_activa())
        return 1;
    if(med1.get_subst_activa() == med2.get_subst_activa())
        return 0;
    return -1;
}

const bool Validator::validare_nume_fisier(string nume_fisier) {
    return nume_fisier.find(".html") != std::string::npos;
}

const void validatorTests::validator_all_tests() {
    test_valideaza_med();
    test_compare_denumire();
    test_compare_producator();
    test_compare_pret();
    test_compare_subst_activa();
    test_compare_subst_activa_and_pret();
    test_validare_nume_fisier();
    test_valideaza_med_dupa_denumire();
}

const void validatorTests::test_valideaza_med() {
    REPO_TYPE storage;
    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");
    storage.adauga_medicament(med);

    Medicament med2(1, "algolcalmin", 25, "Pharma", "paracetamol");

    // instantiem un validator
    Validator vali;
    assert(vali.valideaza_med(storage, med2) == false);

    Medicament med3(2, "brufen", 25, "Pharma", "paramataciol");
    assert(vali.valideaza_med(storage, med3) == true);
}

const void validatorTests::test_compare_denumire() {
    const Medicament med1(1, "algolcalmin", 12, "boiron", "paracetamol");
    const Medicament med2(2, "brufen", 25, "catena", "paracetamol");
    assert(Validator::compare_denumire(med1, med2) == 1);
    assert(Validator::compare_denumire(med2, med1) == 0);
}

const void validatorTests::test_compare_producator() {
    const Medicament med1(1, "algolcalmin", 12, "boiron", "paracetamol");
    const Medicament med2(2, "brufen", 25, "catena", "paracetamol");
    assert(Validator::compare_producator(med1, med2) == 1);
    assert(Validator::compare_producator(med2, med1) == 0);
}

const void validatorTests::test_compare_pret() {
    const Medicament med1(1, "algolcalmin", 12, "boiron", "paracetamol");
    const Medicament med2(2, "brufen", 25, "catena", "paracetamol");
    assert(Validator::compare_pret(med1, med2) == 0);
    assert(Validator::compare_pret(med2, med1) == 1);
}

const void validatorTests::test_compare_subst_activa() {
    Medicament med1(1, "algolcalmin", 12, "boiron", "paracetamol");
    const Medicament med2(2, "brufen", 25, "catena", "paracetamol");
    assert(Validator::compare_subst_activa(med1, med2) == 0);

    med1.set_subst_activa("paramataciol");
    assert(Validator::compare_subst_activa(med1, med2) == 1);
    assert(Validator::compare_subst_activa(med2, med1) == -1);
}

const void validatorTests::test_compare_subst_activa_and_pret() {
    Medicament med1(1, "algolcalmin", 12, "boiron", "paracetamol");
    Medicament med2(2, "brufen", 25, "catena", "paracetamol");
    assert(Validator::compare_subst_activa_and_pret(med1, med2) == true);
    assert(Validator::compare_subst_activa_and_pret(med2, med1) == false);

    Medicament med3(3, "acc", 43, "pharma", "plante");
    assert(Validator::compare_subst_activa_and_pret(med1, med3) == true);
    assert(Validator::compare_subst_activa_and_pret(med3, med1) == false);
}

const void validatorTests::test_validare_nume_fisier() {
    string nume_fisier = "nume_fisier";
    assert(Validator::validare_nume_fisier(nume_fisier) == 0);

    nume_fisier += ".html";
    assert(Validator::validare_nume_fisier(nume_fisier) == 1);
}

const void validatorTests::test_valideaza_med_dupa_denumire() {
    REPO_TYPE storage;
    Medicament med1(1, "algolcalmin", 12, "boiron", "paracetamol");
    storage.adauga_medicament(med1);

    assert(Validator::valideaza_med_dupa_denumire(storage, "algolcalmin") == 0);
    assert(Validator::valideaza_med_dupa_denumire(storage, "brufen") == -1);
}
