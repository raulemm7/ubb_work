//
// Created by raulo on 5/24/2024.
//

#include "repository.h"
#include <fstream>
#include <cassert>

vector<Pix> &Repository::getListaPixuri() {
    return this->lista_pixuri;
}

void Repository::adauga_pix(Pix &pix) {
    this->lista_pixuri.push_back(pix);
}

void Repository::load_from_file() {
    // id brand culoare pret
    this->lista_pixuri.clear();

    int id;
    float pret;
    string brand, culoare;
    std::ifstream fin(this->nume_fisier);

    while(fin >> id >> brand >> culoare >> pret) {
        Pix pix{id, brand, culoare, pret};
        this->adauga_pix(pix);
    }

    fin.close();
}

const Pix &Repository::getPix(int cod) {
    for(auto const& pix : this->lista_pixuri) {
        if(pix.getId() == cod) {
            return pix;
        }
    }
}

void testRepo::test_all() {
    testRepo::test_adauga_and_getLista();
    testRepo::test_getPix();
    testRepo::test_load_from_file();
}

void testRepo::test_adauga_and_getLista() {
    Repository repo("file.txt");

    Pix pix1{1, "Bic", "albastru", 20.0};
    Pix pix2{2, "Pelican", "verde", 20.2};

    repo.adauga_pix(pix2);
    repo.adauga_pix(pix1);

    auto vec = repo.getListaPixuri();
    assert(vec.size() == 2);
    assert(vec.at(0).getId() == pix2.getId());
    assert(vec.at(0).getBrand() == pix2.getBrand());
    assert(vec.at(0).getCuloare() == pix2.getCuloare());
    assert(vec.at(0).getPret() == pix2.getPret());

    assert(vec.at(1).getId() == pix1.getId());
    assert(vec.at(1).getBrand() == pix1.getBrand());
    assert(vec.at(1).getCuloare() == pix1.getCuloare());
    assert(vec.at(1).getPret() == pix1.getPret());
}

void testRepo::test_getPix() {
    Repository repo("file.txt");

    Pix pix{1, "Bic", "albastru", 20.0};
    repo.adauga_pix(pix);

    auto pix_from_repo = repo.getPix(1);

    assert(pix_from_repo.getId() == pix.getId());
    assert(pix_from_repo.getBrand() == pix.getBrand());
    assert(pix_from_repo.getCuloare() == pix.getCuloare());
    assert(pix_from_repo.getPret() == pix.getPret());
}

void testRepo::test_load_from_file() {
    string nume_fisier = "storage.txt";
    Repository repo{nume_fisier};

    repo.load_from_file();

    auto vec = repo.getListaPixuri();

    assert(vec.size() == 11);
    assert(repo.getPix(3).getCuloare() == "verde");
    assert(repo.getPix(6).getId() == 6);
    assert(repo.getPix(8).getPret() - 16.4 < 0.01);
    assert(repo.getPix(11).getBrand() == "Bic");
}
