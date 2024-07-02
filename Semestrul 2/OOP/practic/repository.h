//
// Created by raulo on 6/25/2024.
//

#ifndef PRACTIC_REPOSITORY_H
#define PRACTIC_REPOSITORY_H

#include "domain.h"
#include <vector>

class RepoMasina{
private:
    std::vector<Masina> lista_masini;
    std::string file_name;
public:
    /**
     * constructor default (in cazul in care nu se da fisierul de date)
     */
    RepoMasina() = default;

    /**
     * constructor
     * @param nume_fisier numele fisierului in care sunt stocate informatiile despre masini
     */
    explicit RepoMasina(const std::string& nume_fisier): file_name(nume_fisier){};

    /**
     * @return o lista de masini
     */
    std::vector<Masina>& getListaMasina();

    /**
     * efectueaza modificare pentru o singura masina
     * @param nr_inmatriculare nr de inmatriculare al masinii pentru care se face modificarea
     * @param modificare modificarea adusa anului fabricatiei al masinii
     */
    void modificaMasina(const std::string& nr_inmatriculare, int modificare);

    /**
     * adauga masina la un repo
     * @param masina masina care se doreste a fi adaugata
     */
    void adaugaMasina(Masina& masina);

    /**
     * sterge o masina dintr un repo
     * @param nr_inmatriculare nr de inamtriculare al masinii pentru care se face stergerea
     */
    void stergeMasina(const std::string& nr_inmatriculare);

    /**
     * functii de operare al informatiilor din fisier
     */
    void load_from_file();
    void save_to_file();
    void clear_file();

    /**
     * destructor
     */
    virtual ~RepoMasina() = default;
};

class TestRepo{
public:
    static void test_all();
private:
    /** testez functionalitatile clasei RepoMasina */
    static void test_getListaMasina_adaugaMasina();
    static void test_modificaMasina();
    static void test_stergeMasina();
    static void test_fileOperations();
};

#endif //PRACTIC_REPOSITORY_H
