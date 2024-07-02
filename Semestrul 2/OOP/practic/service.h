//
// Created by raulo on 6/25/2024.
//

#ifndef PRACTIC_SERVICE_H
#define PRACTIC_SERVICE_H

#include "undo.h"
#include "repository.h"
#include <functional>
#include <memory>
#include <locale>

class Service{
private:
    std::vector<std::unique_ptr<AbstractUndo>> lista_undo;
public:
    /**
     * functie ce returneaza o masina in functie de numarul de inmatriculare
     * @param storage repo-ul cu masini
     * @param nr_inmatriculare nr de inmatriculare al masinii care se doreste a fi returnata
     * @return obiect de tip masina
     */
    Masina& get_masina(RepoMasina& storage, const std::string& nr_inmatriculare);

    /**
     * modifica anul fabricatiei al unei masini
     * @param storage repo-ul cu masini
     * @param nr_inmatriculare nr de inmatriculare al masinii pentru care se face modificarea
     * @param modificare modificarea adusa anului fabricatiei al masinii
     * @return string ce reprezinta statusul operatiei
     */
    std::string modifica_masina(RepoMasina& storage, const std::string& nr_inmatriculare, int modificare);

    /**
     * sterge o masina din repo
     * @param storage repo-ul cu masini
     * @param nr_inmatriculare nr de inmatriculare al masinii care se doreste a fi stearsa
     */
    void sterge_masina(RepoMasina& storage, const std::string& nr_inmatriculare);

    /**
     * returneaza lista de masini sortata dupa nr de inmatriculare
     * @param storage repo-ul cu masini
     * @return vector cu masini sortate dupa nr de inmatriculare
     */
    std::vector<Masina>& get_lista_sortata(RepoMasina& storage);

    /**
     * efectueaza undo pentru un repo
     * @param storage repo-ul cu masini
     * @return repo-ul dupa ce se executa undo
     */
    std::string executa_undo(RepoMasina& storage);
};

class TestService{
public:
    static void test_all();
private:
    /**
     * testez functiile din Service
     */
    static void test_getMasina();
    static void test_modifica_masina();
    static void test_sterge_masina();
    static void test_getListaSortata();
    static void test_executa_undo();
};

#endif //PRACTIC_SERVICE_H
