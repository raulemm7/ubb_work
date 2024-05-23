//
// Created by raulo on 5/23/2024.
//

#include "repository.h"
#include <fstream>
#include <cassert>

vector<Imbracaminte> &Repository::getListaHaine() {
    return this->lista_haine;
}

void Repository::adauga_imbracaminte(Imbracaminte &haina) {
    this->lista_haine.push_back(haina);
}

int Repository::getSize() {
    return this->lista_haine.size();
}

void Repository::load_from_file() {
    // tip culoare pret
    std::ifstream fin(this->nume_fisier);

    string tip, culoare;
    int pret;
    while(fin >> tip >> culoare >> pret){
        Imbracaminte haina{tip, culoare, pret};
        this->adauga_imbracaminte(haina);
    }

    fin.close();
}

void Repository::save_to_file() {
    this->clear_file();

    std::ofstream fout(this->nume_fisier);
    auto vec = this->getListaHaine();
    for(const auto& item : vec) {
        string info;
        info += item.getTip() + " ";
        info += item.getCuloare() + " ";
        info += std::to_string(item.getPret()) + "\n";

        fout << info;
    }

    fout.close();
}

void Repository::clear_file() {
    std::ofstream fout;
    fout.open(this->nume_fisier, std::ofstream::out | std::ofstream::trunc);
    fout.close();
}


void testStorage::test_all() {
    testStorage::test_func();
    testStorage::test_file_func();
}

void testStorage::test_func() {
    Repository storage("file.txt");

    Imbracaminte haina{"pantaloni", "rosu", 120};

    storage.adauga_imbracaminte(haina);

    auto vec = storage.getListaHaine();

    assert(vec.size() == 1);
    assert(storage.getSize() == 1);
    assert(vec.at(0).getTip() == haina.getTip());
    assert(vec.at(0).getPret() == haina.getPret());
    assert(vec.at(0).getCuloare() == haina.getCuloare());
}

void testStorage::test_file_func() {
    string file_name = "storage_test.txt";
    Repository storage(file_name);

    storage.load_from_file();
    assert(storage.getSize() == 3);

    auto vec = storage.getListaHaine();
    assert(vec.at(0).getCuloare() == "rosu");
    assert(vec.at(1).getPret() == 127);
    assert(vec.at(2).getTip() == "tricou");

    storage.save_to_file();
}
