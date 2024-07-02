//
// Created by raulo on 6/25/2024.
//

#include "service.h"
#include <algorithm>
#include <iostream>
#include <cassert>

std::string Service::modifica_masina(RepoMasina &storage, const std::string& nr_inmatriculare, int modificare) {
    this->lista_undo.push_back(std::make_unique<UndoModifica>(storage, nr_inmatriculare, modificare * -1));
    storage.modificaMasina(nr_inmatriculare, modificare);
    if(modificare == 1) {
        return "An de fabricatie incrementat cu succes!";
    }
    return "An de fabricatie decrementat cu succes!";
}

std::vector<Masina> &Service::get_lista_sortata(RepoMasina &storage) {
    auto& vec = storage.getListaMasina();

    std::sort(vec.begin(), vec.end(), [](Masina& m1, Masina& m2){
        return m1.getNrInmatriculare() < m2.getNrInmatriculare();
    });

    return vec;
}

void Service::sterge_masina(RepoMasina &storage, const std::string &nr_inmatriculare) {
    auto m = this->get_masina(storage, nr_inmatriculare);
    this->lista_undo.push_back(std::make_unique<UndoSterge>(storage, m));
    storage.stergeMasina(nr_inmatriculare);
}

Masina &Service::get_masina(RepoMasina &storage, const std::string &nr_inmatriculare) {
    auto& vec = storage.getListaMasina();
    for(auto& m : vec) {
        if(m.getNrInmatriculare() == nr_inmatriculare)
            return m;
    }
}

std::string Service::executa_undo(RepoMasina &storage) {
    if(this->lista_undo.empty()) {
        return "Nu se mai poate face undo!";
    }

    storage = this->lista_undo.back()->do_undo();
    this->lista_undo.pop_back();

    return "Undo efectuat cu succes!";
}

void TestService::test_all() {
    TestService::test_getMasina();
    TestService::test_modifica_masina();
    TestService::test_sterge_masina();
    TestService::test_getListaSortata();
    TestService::test_executa_undo();

    std::cout << "Passed service tests\n";
}

void TestService::test_getMasina() {
    Service serv;
    RepoMasina repo;
    Masina m1{"1", "skoda", 2010, "sedan"};

    repo.adaugaMasina(m1);

    std::string nr_inm = "1";
    auto masina = serv.get_masina(repo, nr_inm);
    assert(masina.getNrInmatriculare() == m1.getNrInmatriculare());
    assert(masina.getAnFabricatie() == m1.getAnFabricatie());
    assert(masina.getTip() == m1.getTip());
    assert(masina.getDenumire() == m1.getDenumire());
}

void TestService::test_modifica_masina() {
    Service serv;
    RepoMasina repo;
    Masina m1{"1", "skoda", 2010, "sedan"};

    repo.adaugaMasina(m1);

    std::string nr_inm = "1";
    serv.modifica_masina(repo, nr_inm, +5);
    assert(repo.getListaMasina()[0].getNrInmatriculare() == "1");
    assert(repo.getListaMasina()[0].getAnFabricatie() == 2015);
}

void TestService::test_sterge_masina() {
    Service serv;
    RepoMasina repo;
    Masina m1{"1", "skoda", 2010, "sedan"};

    repo.adaugaMasina(m1);

    std::string nr_inm = "1";
    serv.sterge_masina(repo, nr_inm);

    assert(repo.getListaMasina().empty());
}

void TestService::test_getListaSortata() {
    Service serv;
    RepoMasina repo;

    Masina m3{"3", "skoda", 2010, "sedan"};
    repo.adaugaMasina(m3);

    Masina m1{"1", "audi", 2022, "suv"};
    repo.adaugaMasina(m1);

    Masina m2{"2", "fiat", 2009, "hatch"};
    repo.adaugaMasina(m2);

    auto& vec = serv.get_lista_sortata(repo);

    assert(vec[0].getNrInmatriculare() == "1");
    assert(vec[0].getDenumire() == "audi");

    assert(vec[1].getNrInmatriculare() == "2");
    assert(vec[1].getDenumire() == "fiat");

    assert(vec[2].getNrInmatriculare() == "3");
    assert(vec[2].getDenumire() == "skoda");
}

void TestService::test_executa_undo() {
    Service serv;
    RepoMasina repo;

    Masina m3{"3", "skoda", 2010, "sedan"};
    repo.adaugaMasina(m3);

    std::string nrm = "3";
    serv.modifica_masina(repo, nrm, -4);
    serv.sterge_masina(repo, nrm);

    assert(repo.getListaMasina().empty());

    std::string m = serv.executa_undo(repo);
    assert(m == "Undo efectuat cu succes!");
    assert(!repo.getListaMasina().empty());
    assert(repo.getListaMasina()[0].getAnFabricatie() == 2006);

    m = serv.executa_undo(repo);
    assert(m == "Undo efectuat cu succes!");
    assert(!repo.getListaMasina().empty());
    assert(repo.getListaMasina()[0].getAnFabricatie() == 2010);

    m = serv.executa_undo(repo);
    assert(m == "Nu se mai poate face undo!");
}
