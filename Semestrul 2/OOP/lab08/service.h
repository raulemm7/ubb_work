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
    const string adaugaMedicament(MedicamenteRepo& storage, const Medicament& medicament);

    /**
     * functionalitatea de stergere
     * @param storage: repo-ul din care se sterge un medicament
     * @param id_medicament: id-ul medicamentului care se va sterge
     * @return: string ce reprezinta rezultatul operatiei efectutate
     */
    const string stergeMedicament(MedicamenteRepo& storage, const int& id_medicament);

    /**
     * sterge toate medicamentele dintr o lista
     * @param storage lista de medicamente din care se vor sterge toate medicamentele
     * @return string ce reprezinta rezultatul operatiei efectuate
     */
    const string stergeToateMedicamentele(MedicamenteRepo& storage);

    /**
     * functionalitatea de modificare a unui medicament
     * @param storage: repo-ul cu medicamente in care se va modifica un medicament
     * @param id_medicament: id-ul medicamentului care se va modifica
     * @param new_pret: noul pret al medicamentului
     * @param new_subst_activa: noua substanta activa a medicamentului
     * @return: string ce reprezinta rezultatul operatiei efectutate
     */
    const string modificaMedicament(MedicamenteRepo& storage, const int& id_medicament, const int& new_pret,
                              const string& new_subst_activa);

    /**
     * functionalitatea de cautare a unui medicament
     * @param storage: repo-ul in care se face cautarea
     * @param search: string ce reprezinta denumirea medicamentului cautat
     * @return: string ce reprezinta rezultatul operatiei efectutate
     */
    const string cautaMedicament(MedicamenteRepo& storage, const string& search);

    /**
     * adauga 10 medicamente in storage
     */
    const string adaugaMedicamenteRapid(MedicamenteRepo& storage);

    /**
     * exporta informatiile medicamentelor intr un fisier html
     * @param storage lista cu medicamente
     * @param file_name numele fisierului care se va creea
     * @param prescription_number numarul retetei care se va scrie
     * @return string ce reprezinta rezultatul operatiei efectuate
     */
    const string exportDataInHTMLformat(MedicamenteRepo& storage, const string& file_name, int prescription_number);

    /**
     * adauga random medicamente dintr o lista in alta
     * @param storage_with_meds lista de unde se vor lua medicamente
     * @param reteta lista in care se vor stoca medicamentele alese random
     * @param numar_medicamente numarul de medicamente care se vor introduce in lista de medicamente
     * @return string ce reprezinta rezultatul operatiei efectuate
     */
    const string adaugareRandom(MedicamenteRepo& storage_with_meds, MedicamenteRepo& reteta, int numar_medicamente);
};

class serviceTests {
private:
    const static void test_adaugaMedicament();
    const static void test_stergeMedicament();
    const static void test_stergeToateMedicamentele();
    const static void test_modificaMedicament();
    const static void test_cautaMedicament();
    const static void test_exportDataInHTMLformat();
    const static void test_adaugareRapida_and_adaugareRandom();
public:
    const static void run_all_servive_tests();
};

#endif //LAB06_SERVICE_H
