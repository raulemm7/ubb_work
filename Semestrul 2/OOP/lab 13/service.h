//
// Created by raulo on 4/2/2024.
//

#ifndef LAB06_SERVICE_H
#define LAB06_SERVICE_H

#include "domain.h"
#include "repository.h"
#include "ui.h"
#include "validators.h"
#include "domain.h"
#include <functional>
#include <memory>
#include <locale>
#include "undo.h"
#include "file_repository.h"
#include "Observer.h"

#define REPO_TYPE MedicamenteRepoProbabilitate

using std::function;

class Service : public Observable{
private:
    std::vector<std::unique_ptr<generic_undo>> undo_list;
public:
    /**
     * functionalitatea de adaugare
     * @param storage: storage-ul in care se adauga
     * @param medicament: medicamentul care se adauga
     * @return: string ce reprezinta rezultatul operatiei efectutate
     */
    const string adaugaMedicament(AbstractRepo& storage, const Medicament& medicament);

    /**
     * adauga medicamente intr o reteta
     * @param storage : storage-ul in care se adauga
     * @param med : medicamentul care se adauga
     * @return : string ce reprezinta rezultatul operatiei efectutate
     */
    const string adaugaMedicamentReteta(AbstractRepo& storage, const Medicament& med);

    /**
     * functionalitatea de stergere
     * @param storage: storage-ul din care se sterge un medicament
     * @param id_medicament: id-ul medicamentului care se va sterge
     * @return: string ce reprezinta rezultatul operatiei efectutate
     */
    const string stergeMedicament(AbstractRepo& storage, const int& id_medicament);

    /**
     * sterge toate medicamentele dintr o lista
     * @param storage lista de medicamente din care se vor sterge toate medicamentele
     * @return string ce reprezinta rezultatul operatiei efectuate
     */
    const string stergeToateMedicamentele(AbstractRepo& storage);

    /**
     * functionalitatea de modificare a unui medicament
     * @param storage: storage-ul cu medicamente in care se va modifica un medicament
     * @param id_medicament: id-ul medicamentului care se va modifica
     * @param new_pret: noul pret al medicamentului
     * @param new_subst_activa: noua substanta activa a medicamentului
     * @return: string ce reprezinta rezultatul operatiei efectutate
     */
    const string modificaMedicament(AbstractRepo& storage, const int& id_medicament, const int& new_pret,
                              const string& new_subst_activa);

    /**
     * functionalitatea de cautare a unui medicament
     * @param storage: storage-ul in care se face cautarea
     * @param search: string ce reprezinta denumirea medicamentului cautat
     * @return: string ce reprezinta rezultatul operatiei efectutate
     */
    int cautaMedicament(AbstractRepo& storage, const string& search);

    /**
     * adauga 10 medicamente in storage
     */
    const string adaugaMedicamenteRapid(AbstractRepo& storage);

    /**
     * sortarea listei de medicamente dupa un criteriu
     * @param storage repo-ul cu elemente
     * @param functie_comparare criteriul dupa care se face sortarea
     * @return vector cu medicamente sortate dupa un criteriu
     */
    vector<Medicament> sortare_generica(AbstractRepo &storage,
                                function<int(const Medicament &, const Medicament &)> functie_comparare);

    /**
     * filtrare medicamente dupa substanta
     * @param storage repo-ul cu elemente
     * @param subst substanta dupa care se face filtrarea
     * @return vector cu medicamentele filtrate
     */
    vector<Medicament> filtrare_dupa_substanta(AbstractRepo& storage, const string& subst);

    /**
     * filtrare medicamente dupa pret
     * @param storage repo-ul cu elemente
     * @param pret pretul dupa care se face filtrarea
     * @param op >, = sau <
     * @return vector cu medicamentele filtrate
     */
    vector<Medicament> filtrare_dupa_pret(AbstractRepo& storage, int pret, char op);

    /**
     * exporta informatiile medicamentelor intr un fisier html
     * @param storage lista cu medicamente
     * @param file_name numele fisierului care se va creea
     * @param prescription_number numarul retetei care se va scrie
     * @return string ce reprezinta rezultatul operatiei efectuate
     */
    const string exportDataInHTMLformat(AbstractRepo& storage, const string& file_name, int prescription_number);

    /**
     * adauga random medicamente dintr o lista in alta
     * @param storage_with_meds lista de unde se vor lua medicamente
     * @param reteta lista in care se vor stoca medicamentele alese random
     * @param numar_medicamente numarul de medicamente care se vor introduce in lista de medicamente
     * @return string ce reprezinta rezultatul operatiei efectuate
     */
    const string adaugareRandom(AbstractRepo& storage_with_meds, AbstractRepo& reteta, int numar_medicamente);

    /**
     * genereaza un raport al medicamentelor curente din stod
     * @param storage lista cu medicamente
     * @return unordered_map cu 2 campuri: string (substanta activa) si MedicamentDTO
     *          (retine informatii pentru raport)
     */
    std::unordered_map<string, MedicamentDTO> generareRaport(AbstractRepo& storage);

    /**
     * merge la forma anterioara a listei de medicamente
     * @param storage lista medicamente care va reveni la forma anterioara
     * @return mesaj ce reprezinta statusul operatiei efectuate
     */
    const string executa_undo(AbstractRepo& storage);

    /**
     * incarca medicamente din fisier
     * @param storage repository-ul in care vor fi incarcate medicamentele
     * @return mesaj ce reprezinta statusul operatiei
     */
    const string load_data_from_txt(FileRepo& storage);

    /**
     * salveaza medicamente in fisier
     * @param storage repository-ul cu medicamentele care vor fi incarcate medicamentele
     * @return mesaj ce reprezinta statusul operetiei
     */
    const string store_data_in_txt(FileRepo& storage);
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
    const static void test_generareRaport();
    const static void test_executa_undo();
    const static void test_load_from_txt();
    const static void test_upload_to_txt();
public:
    const static void run_all_servive_tests();
};

#endif //LAB06_SERVICE_H
