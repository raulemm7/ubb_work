//
// Created by raulo on 4/2/2024.
//

#ifndef LAB06_VALIDATORS_H
#define LAB06_VALIDATORS_H

#include "repository.h"
#include "domain.h"

class Validator {
public:
    bool valideaza_med(MedicamenteRepo& storage, const Medicament& medicament);
};

class validatorTests {
public:
    static void test_valideaza_med();
};

#endif //LAB06_VALIDATORS_H
