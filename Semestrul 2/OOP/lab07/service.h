//
// Created by raulo on 4/2/2024.
//

#ifndef LAB06_SERVICE_H
#define LAB06_SERVICE_H

#include "domain.h"
#include "repository.h"
#include "ui.h"
#include "validators.h"
#include "definedVector.h"
#include "domain.h"
#include <functional>

using std::function;

class Service {
public:
    /**
     * functionalitatea de adaugare
     * @param storage: repo-ul in care se adauga
     * @param medicament: medicamentul care se adauga
     * @return: string ce reprezinta rezultatul operatiei efectutate
     */
    const string adaugaMedicament(VectorDinamic<Medicament>& storage, const Medicament& medicament);

    /**
     * functionalitatea de stergere
     * @param storage: repo-ul din care se sterge un medicament
     * @param id_medicament: id-ul medicamentului care se va sterge
     * @return: string ce reprezinta rezultatul operatiei efectutate
     */
    const string stergeMedicament(VectorDinamic<Medicament>& storage, const int& id_medicament);

    /**
     * functionalitatea de modificare a unui medicament
     * @param storage: repo-ul cu medicamente in care se va modifica un medicament
     * @param id_medicament: id-ul medicamentului care se va modifica
     * @param new_pret: noul pret al medicamentului
     * @param new_subst_activa: noua substanta activa a medicamentului
     * @return: string ce reprezinta rezultatul operatiei efectutate
     */
    const string modificaMedicament(VectorDinamic<Medicament>& storage, const int& id_medicament, const int& new_pret,
                              const string& new_subst_activa);

    /**
     * functionalitatea de cautare a unui medicament
     * @param storage: repo-ul in care se face cautarea
     * @param search: string ce reprezinta denumirea medicamentului cautat
     * @return: string ce reprezinta rezultatul operatiei efectutate
     */
    const string cautaMedicament(const VectorDinamic<Medicament>& storage, const string& search);
};

class serviceTests {
private:
    const static void test_adaugaMedicament();
    const static void test_stergeMedicament();
    const static void test_modificaMedicament();
    const static void test_cautaMedicament();
public:
    const static void run_all_servive_tests();
};

#endif //LAB06_SERVICE_H
