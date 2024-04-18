//
// Created by raulo on 4/2/2024.
//

#ifndef LAB06_REPOSITORY_H
#define LAB06_REPOSITORY_H

#include "domain.h"
#include <vector>
using std::vector;

/**
 * clasa de storage a informatiilor
 */
class MedicamenteRepo {
private:
    vector<Medicament> lista_meds;
    int nr_medicamente;
public:
    /** constructorul clasei */
    MedicamenteRepo();

    /** returneaza lista propriu-zisa de medicamente */
    vector<Medicament>& get_all();

    /** returneaza numarul de medicamente inregistrate */
    const int get_last_id() const;

    /**
     * returneaza un medicament de pe o pozitie specificata
     * @param position: pozitia medicamentului din lista de medicamente
     * @return: obiect de tip Medicament
     */
    const Medicament& get_med(const int& position) const;

    /**
     * adaugare medicament in lista curenta
     * @param medicament: medicamentul care se va adauga
     */
    const void adauga_medicament(const Medicament& medicament);

    /**
     * stergerea unui medicament din lista curenta
     * @param id_med: id-ul medicamentului care se va sterge
     */
    const void sterge_medicament(const int& id_med);

    /**
     * modificarea unui medicament din lista curenta
     * @param id_med: id-ul medicamentului care se va modifica
     * @param new_pret: noul pret al medicamentului
     * @param new_subst_activa: noua substanta activa a medicamentului
     */
    const void modifica_medicament(const int& id_med, const int& new_pret, const string& new_subst_activa);

    /**
     * seteaza tuturor medicamentelor din lista curenta
     * id-ul corespunzator pozitiei lor in lista
     */
    const void set_id_correctly();
};

class repositoryTests{
public:
    const static void test_repository_functionalities();
};

#endif //LAB06_REPOSITORY_H
