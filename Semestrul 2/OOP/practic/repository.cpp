//
// Created by raulo on 6/25/2024.
//

#include "repository.h"
#include <fstream>
#include <cassert>
#include <iostream>

std::vector<Masina> &RepoMasina::getListaMasina() {
    return this->lista_masini;
}

void RepoMasina::modificaMasina(const std::string &nr_inmatriculare, int modificare) {
    for(auto& masina : this->lista_masini) {
        if(masina.getNrInmatriculare() == nr_inmatriculare) {
            masina.setAnFabricatie(modificare);
            return;
        }
    }
}

void RepoMasina::stergeMasina(const std::string &nr_inmatriculare) {
    // determin pozitia;
    int poz = 0;
    for(auto& masina : this->lista_masini) {
        if(masina.getNrInmatriculare() == nr_inmatriculare) {
            break;
        }
        poz++;
    }

    // efectuez stergerea
    this->lista_masini.erase(this->lista_masini.begin() + poz);
}

void RepoMasina::load_from_file() {
    std::string nrInmatriculare, denumire, tip;
    int anFabricatie;

    std::ifstream fin(this->file_name);
    while(fin >> nrInmatriculare >> denumire >> anFabricatie >> tip) {
        Masina m{nrInmatriculare, denumire, anFabricatie, tip};
        this->lista_masini.push_back(m);
    }

    fin.close();
}

void RepoMasina::save_to_file() {
    this->clear_file();
    std::ofstream out(this->file_name);

    for(const auto& m : this->lista_masini) {
        std::string info = m.getNrInmatriculare() + " ";
        info += m.getDenumire() + " ";
        info += std::to_string(m.getAnFabricatie()) + " ";
        info += m.getTip() + "\n";

        out << info;
    }

    out.close();
}

void RepoMasina::clear_file() {
    std::ofstream out;
    out.open(this->file_name, std::ofstream::out | std::ofstream::trunc);
    out.close();
}

void RepoMasina::adaugaMasina(Masina& masina) {
    this->lista_masini.push_back(masina);
}

void TestRepo::test_all() {
    TestRepo::test_getListaMasina_adaugaMasina();
    TestRepo::test_modificaMasina();
    TestRepo::test_stergeMasina();
    TestRepo::test_fileOperations();

    std::cout << "Passed repo tests\n";
}

void TestRepo::test_getListaMasina_adaugaMasina() {
    RepoMasina repo;

    Masina m1{"1", "skoda", 2010, "sedan"};
    Masina m2{"2", "audi", 2023, "suv"};

    repo.adaugaMasina(m1);
    repo.adaugaMasina(m2);

    auto& vec = repo.getListaMasina();
    assert(vec[0].getNrInmatriculare() == "1");
    assert(vec[0].getAnFabricatie() == 2010);
    assert(vec[1].getNrInmatriculare() == "2");
    assert(vec[1].getAnFabricatie() == 2023);
}

void TestRepo::test_modificaMasina() {
    RepoMasina repo;

    Masina m1{"1", "skoda", 2010, "sedan"};

    repo.adaugaMasina(m1);

    repo.modificaMasina(m1.getNrInmatriculare(), +5);
    assert(repo.getListaMasina()[0].getAnFabricatie() == 2015);
}

void TestRepo::test_stergeMasina() {
    RepoMasina repo;
    Masina m1{"1", "skoda", 2010, "sedan"};
    repo.adaugaMasina(m1);

    Masina m2{"2", "audi", 2023, "suv"};
    repo.adaugaMasina(m2);

    assert(repo.getListaMasina().size() == 2);

    repo.stergeMasina(m1.getNrInmatriculare());
    assert(repo.getListaMasina()[0].getNrInmatriculare() == m2.getNrInmatriculare());
    assert(repo.getListaMasina().size() == 1);

    repo.stergeMasina(m2.getNrInmatriculare());
    assert(repo.getListaMasina().empty());
}

void TestRepo::test_fileOperations() {
    std::string filename = "test_file.txt";
    RepoMasina repo{filename};

    Masina m1{"1", "skoda", 2010, "sedan"};
    repo.adaugaMasina(m1);
    repo.save_to_file();          // salvez in fisier o singura masina

    repo.stergeMasina(m1.getNrInmatriculare());    // sterg masina din repo, am 0 masini
    assert(repo.getListaMasina().empty());

    repo.load_from_file();
    repo.clear_file();

    assert(!repo.getListaMasina().empty());
    assert(repo.getListaMasina().size() == 1);
    assert(repo.getListaMasina()[0].getNrInmatriculare() == "1");
}
