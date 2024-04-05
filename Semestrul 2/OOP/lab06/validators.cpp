//
// Created by raulo on 4/2/2024.
//

#include "validators.h"
#include <cassert>

const bool Validator::valideaza_med(const MedicamenteRepo& storage, const Medicament &medicament) {
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

const void validatorTests::test_valideaza_med() {
    MedicamenteRepo storage;
    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");
    storage.adauga_medicament(med);

    Medicament med2(1, "algolcalmin", 25, "Pharma", "paracetamol");

    // instantiem un validator
    Validator vali;
    assert(vali.valideaza_med(storage, med2) == false);

    Medicament med3(2, "brufen", 25, "Pharma", "paramataciol");
    assert(vali.valideaza_med(storage, med3) == true);
}
