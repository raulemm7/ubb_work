//
// Created by raulo on 5/15/2024.
//

#ifndef LAB06_FILE_REPOSITORY_H
#define LAB06_FILE_REPOSITORY_H

#include "repository.h"

class FileRepo: public MedicamenteRepo {
private:
    string nume_fisier;
public:
    /** constructor default */
    FileRepo() = default;

    /** constructor explicit */
    explicit FileRepo(const string& nume);

    /** incarca medicamente dintr-un fisier text */
    void load_from_file();
    /** salveaza medicamente intr-un fisier text*/
    void save_to_file();
    /** goleste fisierul */
    void clear_file();
    /** seteaza calea catre fisier */
    void set_path(const string& path);

    const void adauga_medicament(const Medicament& medicament) override {
        MedicamenteRepo::adauga_medicament(medicament);
    }

    const void sterge_medicament(const int& id_med) override {
        MedicamenteRepo::sterge_medicament(id_med);
    }

    const void modifica_medicament(const int& id_med, const int& new_pret, const string& new_subst_activa) override {
        MedicamenteRepo::modifica_medicament(id_med, new_pret, new_subst_activa);
    }

    /** destructor */
    ~FileRepo() override = default;
};

class file_repository_tests{
public:
    const static void test_all();
private:
    const static void test_load();
    const static void test_adauga();
    const static void test_sterge();
    const static void test_modifica();
};

#endif //LAB06_FILE_REPOSITORY_H
