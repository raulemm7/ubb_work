//
// Created by raulo on 6/25/2024.
//

#ifndef PRACTIC_UNDO_H
#define PRACTIC_UNDO_H

#include "repository.h"

/** clasa generica de undo */
class AbstractUndo{
public:
    virtual RepoMasina& do_undo() = 0;

    virtual ~AbstractUndo() = default;
};

/** clasa de undo pentru stergere */
class UndoSterge: public AbstractUndo{
private:
    Masina masina;
    RepoMasina& storage;
public:
    /**
     * constructor
     * @param repo referinta la repo ul in care se face undo
     * @param m masina care se va adauga la apelul do_undo()
     */
    UndoSterge(RepoMasina& repo, Masina m): storage(repo), masina(m){};

    RepoMasina& do_undo() override {
        this->storage.adaugaMasina(masina);
        return this->storage;
    }
};

/** clasa de undo pentru modificare */
class UndoModifica: public AbstractUndo{
private:
    int modificare;
    std::string nr_inm;
    RepoMasina& storage;
public:
    /**
     * constructor
     * @param repo referinta la repo in care se va efectua undo-ul
     * @param nrm nr de inmatriculare al masinii pentru care se va face undo la anul fabricatiei
     * @param mod modificarea pentru anul fabricatiei {1, -1}
     */
    UndoModifica(RepoMasina& repo, std::string nrm, int mod) : storage(repo), nr_inm(nrm), modificare(mod){};

    RepoMasina& do_undo() override{
        this->storage.modificaMasina(this->nr_inm, modificare);
        return this->storage;
    }
};

#endif //PRACTIC_UNDO_H
