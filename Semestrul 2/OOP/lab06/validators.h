//
// Created by raulo on 4/2/2024.
//

#ifndef LAB06_VALIDATORS_H
#define LAB06_VALIDATORS_H

#include "repository.h"
#include "domain.h"

class Validator {
public:
    /**
     * valideaza daca un medicament a fost deja inregistrat intr o lista de medicamente
     * @param storage: lista de medicamente actuala
     * @param medicament: medicamentul pentru care se face validarea
     * @return: 1 => medicamentul NU se afla in lista (poate fi adaugat in lista)
     *          0 => altfel
     */
    const bool valideaza_med(const MedicamenteRepo& storage, const Medicament& medicament);
};

class validatorTests {
public:
    const static void test_valideaza_med();
};

#endif //LAB06_VALIDATORS_H
