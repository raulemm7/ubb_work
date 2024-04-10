//
// Created by raulo on 4/2/2024.
//

#ifndef LAB06_VALIDATORS_H
#define LAB06_VALIDATORS_H

#include "repository.h"
#include "domain.h"
#include "definedVector.h"

class Validator {
public:
    /**
     * valideaza daca un medicament a fost deja inregistrat intr o lista de medicamente
     * @param storage: lista de medicamente actuala
     * @param medicament: medicamentul pentru care se face validarea
     * @return: 1 => medicamentul NU se afla in lista (poate fi adaugat in lista)
     *          0 => altfel
     */
    const bool valideaza_med(const VectorDinamic<Medicament>& storage, const Medicament& medicament);

    static const bool compare_denumire(const Medicament& med1, const Medicament& med2);
    static const bool compare_producator(const Medicament& med1, const Medicament& med2);
    static const bool compare_pret(const Medicament& med1, const Medicament& med2);
    static const int compare_subst_activa(const Medicament& med1, const Medicament& med2);
};

class validatorTests {
public:
    const static void validator_all_tests();
private:
    const static void test_valideaza_med();
    const static void test_compare_denumire();
    const static void test_compare_producator();
    const static void test_compare_pret();
    const static void test_compare_subst_activa();
};

#endif //LAB06_VALIDATORS_H
