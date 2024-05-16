//
// Created by raulo on 4/2/2024.
//

#include "repository.h"
#include "validators.h"
#include <fstream>
#include <cassert>
#include <sstream>

MedicamenteRepo::MedicamenteRepo() {
    this->nr_medicamente = 0;
}

vector<Medicament> &MedicamenteRepo::get_all() {
    return this->lista_meds;
}

const void MedicamenteRepo::adauga_medicament(const Medicament& medicament) {
    this->lista_meds.push_back(medicament);
    this->nr_medicamente++;
}

const int MedicamenteRepo::get_last_id() const{
    return this->nr_medicamente;
}

const Medicament& MedicamenteRepo::get_med(const int &position) const {
    return this->lista_meds[position];
}

const void MedicamenteRepo::sterge_medicament(const int &id_med) {
    for(int i = id_med; i < this->nr_medicamente - 1; i++)
        this->lista_meds[i] = this->lista_meds[i + 1];

    this->lista_meds.erase(this->lista_meds.begin() + this->nr_medicamente - 1);
    this->nr_medicamente--;

    // update id for every medicament
    for(int i = 0; i < this->nr_medicamente; i++) {
        this->lista_meds[i].set_id(i);
    }
}

const void MedicamenteRepo::modifica_medicament(const int &id_med, const int& new_pret, const string& new_subst_activa) {
    this->lista_meds[id_med].set_pret(new_pret);
    this->lista_meds[id_med].set_subst_activa(new_subst_activa);
}

const void MedicamenteRepo::set_id_correctly() {
    for(int i = 0; i < this->nr_medicamente; i++) {
        this->lista_meds[i].set_id(i);
    }
}

MedicamenteRepoProbabilitate::MedicamenteRepoProbabilitate(float prob) {
    this->nr_probabilitate = prob;
    this->medicamente.clear();
    this->lista_meds.clear();
    this->nr_meds = 0;
}

void MedicamenteRepoProbabilitate::probabilitate() const {
    auto pb = int(this->nr_probabilitate * 10);
    srand(time(NULL));
    int numar = rand() % 10 + 1;

    if(numar <= pb) {
        return;
    }
    throw BadLuckException("NU S-A PUTUT EFECTUA OPERATIA, BAD LUCK I GUESS...");
}

vector<Medicament> &MedicamenteRepoProbabilitate::get_all() {
    this->medicamente.clear();
    for(auto elem : this->lista_meds) {
        this->medicamente.push_back(elem.second);
    }
    return this->medicamente;
}

const int MedicamenteRepoProbabilitate::get_last_id() const {
    return this->lista_meds.size();
}

const Medicament &MedicamenteRepoProbabilitate::get_med(const int &position) const {
    for(auto &elem: this->lista_meds) {
        if(elem.second.get_id() == position) {
            return elem.second;
        }
    }
}

const void MedicamenteRepoProbabilitate::adauga_medicament(const Medicament &medicament) {
    try {
        this->probabilitate();
        this->lista_meds.insert(std::make_pair(this->lista_meds.size(), medicament));
        this->set_id_correctly();
        this->nr_meds++;

        return;
    }
    catch(BadLuckException& ex) {
        std::cout << ex;
        return;
    }
}

const void MedicamenteRepoProbabilitate::sterge_medicament(const int &id_med) {
    try {
        this->probabilitate();

        // setez corect valorile din primul camp
        std::map<int, Medicament> new_list;
        new_list.clear();
        for(auto &elem : this->lista_meds) {
            if(elem.second.get_id() != id_med) {
                const auto& med = elem.second;
                new_list.insert(std::make_pair(new_list.size(), med));
            }
        }

        this->lista_meds.clear();
        this->lista_meds = new_list;

        this->set_id_correctly();

        this->nr_meds--;
    }
    catch(BadLuckException& ex) {
        std::cout << ex;
        return;
    }
}

const void MedicamenteRepoProbabilitate::modifica_medicament(const int &id_med, const int &new_pret,
                                                             const string &new_subst_activa) {
    try {
        this->probabilitate();

        for(auto &elem : this->lista_meds) {
            if(elem.second.get_id() == id_med) {
                elem.second.set_pret(new_pret);
                elem.second.set_subst_activa(new_subst_activa);
                return;
            }
        }
    }
    catch(BadLuckException& ex) {
        std::cout << ex;
        return;
    }
}

const void MedicamenteRepoProbabilitate::set_id_correctly() {
    int k = 0;
    for(auto &elem : this->lista_meds) {
        elem.second.set_id(k);
        k++;
    }
}

const void repositoryTests::test_repository_functionalities() {
    MedicamenteRepo storage;

    std::cout << storage.get_last_id();
    assert(storage.get_last_id() == 0);

    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");
    storage.adauga_medicament(med);

    // testare adaugare
    assert(storage.get_last_id() == 1);
    Medicament med_from_storage = storage.get_med(0);
    assert(med_from_storage.get_id() == 0);
    assert(med_from_storage.get_denumire() == "algolcalmin");
    assert(med_from_storage.get_pret() == 25);
    assert(med_from_storage.get_producator() == "Pharma");
    assert(med_from_storage.get_subst_activa() == "paracetamol");

    // testare modificare
    storage.modifica_medicament(0, 34, "alta_substanta");
    med_from_storage = storage.get_med(0);
    assert(med_from_storage.get_pret() == 34);
    assert(med_from_storage.get_subst_activa() == "alta_substanta");

    // testare stergere
    // mai adaug un medicament
    Medicament med2(1, "brufen", 19, "ceva_producator", "paramataciol");
    storage.adauga_medicament(med2);

    storage.sterge_medicament(0);
    assert(storage.get_last_id() == 1);
    med_from_storage = storage.get_med(0);
    assert(med_from_storage.get_id() == 0);
    assert(med_from_storage.get_denumire() == "brufen");
    assert(med_from_storage.get_pret() == 19);
    assert(med_from_storage.get_producator() == "ceva_producator");
    assert(med_from_storage.get_subst_activa() == "paramataciol");

    // testare setare id corect
    storage.sterge_medicament(0);

    storage.adauga_medicament(med2);   // pun pe prima pozitie medicament cu id 1
    storage.adauga_medicament(med);    // pun pe a doua pozitie medicament cu id 0

    storage.set_id_correctly();

    med_from_storage = storage.get_med(0);
    assert(med_from_storage.get_id() == 0);
    assert(med_from_storage.get_denumire() == "brufen");

    med_from_storage = storage.get_med(1);
    assert(med_from_storage.get_id() == 1);
    assert(med_from_storage.get_denumire() == "algolcalmin");
}

const void repositoryTests::test_new_repo_funct() {
    MedicamenteRepoProbabilitate new_storage(1.0);

    assert(new_storage.get_last_id() == 0);

    Medicament med(0, "algolcalmin", 25, "Pharma", "paracetamol");
    new_storage.adauga_medicament(med);

    // testare adaugare
    assert(new_storage.get_last_id() == 1);
    Medicament med_from_storage = new_storage.get_med(0);
    assert(med_from_storage.get_id() == 0);
    assert(med_from_storage.get_denumire() == "algolcalmin");
    assert(med_from_storage.get_pret() == 25);
    assert(med_from_storage.get_producator() == "Pharma");
    assert(med_from_storage.get_subst_activa() == "paracetamol");

    // testare modificare
    new_storage.modifica_medicament(0, 34, "alta_substanta");
    med_from_storage = new_storage.get_med(0);
    assert(med_from_storage.get_pret() == 34);
    assert(med_from_storage.get_subst_activa() == "alta_substanta");

    // testare stergere
    // mai adaug un medicament
    Medicament med2(1, "brufen", 19, "ceva_producator", "paramataciol");
    new_storage.adauga_medicament(med2);

    new_storage.sterge_medicament(0);
    assert(new_storage.get_last_id() == 1);
    med_from_storage = new_storage.get_med(0);
    assert(med_from_storage.get_id() == 0);
    assert(med_from_storage.get_denumire() == "brufen");
    assert(med_from_storage.get_pret() == 19);
    assert(med_from_storage.get_producator() == "ceva_producator");
    assert(med_from_storage.get_subst_activa() == "paramataciol");

    // testare setare id corect
    new_storage.sterge_medicament(0);

    new_storage.adauga_medicament(med2);   // pun pe prima pozitie medicament cu id 1
    new_storage.adauga_medicament(med);    // pun pe a doua pozitie medicament cu id 0

    new_storage.set_id_correctly();

    med_from_storage = new_storage.get_med(0);
    assert(med_from_storage.get_id() == 0);
    assert(med_from_storage.get_denumire() == "brufen");

    med_from_storage = new_storage.get_med(1);
    assert(med_from_storage.get_id() == 1);
    assert(med_from_storage.get_denumire() == "algolcalmin");
}
