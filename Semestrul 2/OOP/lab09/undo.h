//
// Created by raulo on 4/25/2024.
//

#ifndef LAB06_UNDO_H
#define LAB06_UNDO_H

#include "domain.h"
#include "repository.h"

class generic_undo {
public:
    virtual MedicamenteRepo& do_undo() = 0;

    virtual ~generic_undo() = default;
};

class undo_adauga : public generic_undo {
    int id_med;
    MedicamenteRepo& storage;
public:
    undo_adauga(MedicamenteRepo& storage, int id_med) : storage {storage}, id_med {id_med} {};

    MedicamenteRepo& do_undo() override {
        storage.sterge_medicament(this->id_med);
        return storage;
    }
};

class undo_sterge : public generic_undo {
    Medicament med;
    MedicamenteRepo& storage;
public:
    undo_sterge(MedicamenteRepo& storage, const Medicament& med) : storage {storage}, med {med} {};

    MedicamenteRepo& do_undo() override {
        storage.adauga_medicament(this->med);
        return storage;
    }
};

class undo_modifica : public generic_undo {
    const Medicament& med;
    const int price;
    const string subst;
    MedicamenteRepo& storage;
public:
    undo_modifica(MedicamenteRepo& storage, const Medicament& med, const int price, const string subst) :
        storage {storage}, med {med}, price {price}, subst {subst} {};

    MedicamenteRepo& do_undo() override {
        storage.modifica_medicament(med.get_id(), price, subst);
        return storage;
    }
};

#endif //LAB06_UNDO_H
