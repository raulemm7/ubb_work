//
// Created by raulo on 4/25/2024.
//

#ifndef LAB06_UNDO_H
#define LAB06_UNDO_H

#include "domain.h"
#include "repository.h"

#define REPO_TYPE MedicamenteRepoProbabilitate

class generic_undo {
public:
    virtual AbstractRepo& do_undo() = 0;

    virtual ~generic_undo() = default;
};

class undo_adauga : public generic_undo {
    int id_med;
    AbstractRepo& storage;
public:
    undo_adauga(AbstractRepo& storage, int id_med) : storage {storage}, id_med {id_med} {};

    AbstractRepo& do_undo() override {
        storage.sterge_medicament(this->id_med);
        return storage;
    }
};

class undo_sterge : public generic_undo {
    Medicament med;
    AbstractRepo& storage;
public:
    undo_sterge(AbstractRepo& storage, const Medicament& med) : storage {storage}, med {med} {};

    AbstractRepo& do_undo() override {
        this->med.set_id(this->storage.get_last_id());
        storage.adauga_medicament(this->med);
        return storage;
    }
};

class undo_modifica : public generic_undo {
    const Medicament& med;
    const int price;
    const string subst;
    AbstractRepo& storage;
public:
    undo_modifica(AbstractRepo& storage, const Medicament& med, const int price, const string& subst) :
        storage {storage}, med {med}, price {price}, subst {subst} {};

    AbstractRepo& do_undo() override {
        storage.modifica_medicament(med.get_id(), this->price, this->subst);
        return storage;
    }
};

#endif //LAB06_UNDO_H
