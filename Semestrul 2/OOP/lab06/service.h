//
// Created by raulo on 4/2/2024.
//

#ifndef LAB06_SERVICE_H
#define LAB06_SERVICE_H

#include "domain.h"
#include "repository.h"
#include "ui.h"
#include "validators.h"

class Service {
public:
    string adaugaMedicament(MedicamenteRepo& storage, const Medicament& medicament);
    string stergeMedicament(MedicamenteRepo& storage, const int& id_medicament);
    string modificaMedicament(MedicamenteRepo& storage, const int& id_medicament, const int& new_pret,
                              const string& new_subst_activa);
    string cautaMedicament(MedicamenteRepo& storage, const string& search);
};

class serviceTests {
private:
    static void test_adaugaMedicament();
    static void test_stergeMedicament();
    static void test_modificaMedicament();
    static void test_cautaMedicament();
public:
    static void run_all_servive_tests();
};

#endif //LAB06_SERVICE_H
