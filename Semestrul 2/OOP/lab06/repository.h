//
// Created by raulo on 4/2/2024.
//

#ifndef LAB06_REPOSITORY_H
#define LAB06_REPOSITORY_H

#include "domain.h"
#include <vector>
using std::vector;

class MedicamenteRepo {
private:
    vector<Medicament> lista_meds;
    int nr_medicamente;
public:
    // constructor
    MedicamenteRepo();

    [[nodiscard]] int get_last_id() const;
    Medicament get_med(const int& position);

    void adauga_medicament(const Medicament& medicament);
    void sterge_medicament(const int& id_med);
    void modifica_medicament(const int& id_med, const int& new_pret, const string& new_subst_activa);
};

class repositoryTests{
public:
    static void test_repository_functionalities();
};

#endif //LAB06_REPOSITORY_H
