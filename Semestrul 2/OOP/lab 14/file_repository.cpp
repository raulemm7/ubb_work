//
// Created by raulo on 5/15/2024.
//

#include "file_repository.h"
#include <fstream>
#include <iostream>
#include <cassert>
#include <cstring>

/**
 * format fisier:
 * id_med denumire pret producator substanta_activa
 */

void FileRepo::load_from_file() {
    std::ifstream fin(this->nume_fisier);

    int id, pret;
    string denumire, producator, subst_act;

    while(fin >> id >> denumire >> pret >> producator >> subst_act) {
        std::cout << denumire << " " << pret << " " << subst_act << '\n';

        Medicament med(id, denumire, pret, producator, subst_act);
        this->adauga_medicament(med);
    }


    fin.close();
}

void FileRepo::save_to_file() {
    this->clear_file();

    std::ofstream out(this->nume_fisier);
    for(const auto& med : this->get_all()) {
        string info;
        info += std::to_string(med.get_id());
        info += " ";
        info += med.get_denumire();
        info += " ";
        info += std::to_string(med.get_pret());
        info += " ";
        info += med.get_producator();
        info += " ";
        info += med.get_subst_activa();
        info += "\n";

        out << info;
    }

    out.close();
}

void FileRepo::clear_file() {
    std::ofstream out;
    out.open(this->nume_fisier, std::ofstream::out | std::ofstream::trunc);
    out.close();
}

FileRepo::FileRepo(const string &nume) {
    this->nume_fisier = nume;
}

void FileRepo::set_path(const string &path) {
    this->nume_fisier = path;
}

const void file_repository_tests::test_all() {
    file_repository_tests::test_load();
    file_repository_tests::test_adauga();
    file_repository_tests::test_sterge();
    file_repository_tests::test_modifica();
}

const void file_repository_tests::test_load() {
    FileRepo repo;
    repo.set_path("fisier_teste.txt");
    repo.clear_file();
    std::cout << "acum dau load: ";
    repo.load_from_file();

    /*assert(storage.get_last_id() == 3);
    assert(storage.get_med(0).get_denumire() == "brufen");
    assert(storage.get_med(1).get_denumire() == "lecitina");
    assert(storage.get_med(2).get_denumire() == "acc");*/

    repo.clear_file();
}

const void file_repository_tests::test_adauga() {
    FileRepo repo("fisier_teste.txt");
    repo.clear_file();

    Medicament med(0, "paracetamol", 32, "boiron", "paracetamol");
    repo.adauga_medicament(med);

    assert(repo.get_last_id() == 1);
    assert(repo.get_med(0).get_id() == 0);
    assert(repo.get_med(0).get_denumire() == "paracetamol");
    assert(repo.get_med(0).get_pret() == 32);
    assert(repo.get_med(0).get_producator() == "boiron");
    assert(repo.get_med(0).get_subst_activa() == "paracetamol");

    Medicament med1(1, "acc", 26, "pharma", "sirop");
    repo.adauga_medicament(med1);

    assert(repo.get_last_id() == 2);
    assert(repo.get_med(1).get_id() == 1);
    assert(repo.get_med(1).get_denumire() == "acc");
    assert(repo.get_med(1).get_pret() == 26);
    assert(repo.get_med(1).get_producator() == "pharma");
    assert(repo.get_med(1).get_subst_activa() == "sirop");

    repo.clear_file();
}

const void file_repository_tests::test_sterge() {
    FileRepo repo("fisier_teste.txt");
    repo.clear_file();

    Medicament med(0, "paracetamol", 32, "boiron", "paracetamol");
    repo.adauga_medicament(med);

    Medicament med1(1, "acc", 26, "pharma", "sirop");
    repo.adauga_medicament(med1);

    assert(repo.get_last_id() == 2);

    repo.sterge_medicament(0);

    assert(repo.get_last_id() == 1);
    assert(repo.get_med(0).get_id() == 0);
    assert(repo.get_med(0).get_denumire() == "acc");
    assert(repo.get_med(0).get_pret() == 26);
    assert(repo.get_med(0).get_producator() == "pharma");
    assert(repo.get_med(0).get_subst_activa() == "sirop");

    repo.clear_file();
}

const void file_repository_tests::test_modifica() {
    FileRepo repo("fisier_teste.txt");
    repo.clear_file();

    Medicament med(0, "paracetamol", 32, "boiron", "paracetamol");
    repo.adauga_medicament(med);

    Medicament med1(1, "acc", 26, "pharma", "sirop");
    repo.adauga_medicament(med1);

    repo.modifica_medicament(1, 41, "plante");
    assert(repo.get_last_id() == 2);
    assert(repo.get_med(1).get_denumire() == "acc");
    assert(repo.get_med(1).get_pret() == 41);
    assert(repo.get_med(1).get_subst_activa() == "plante");

    repo.clear_file();
}
