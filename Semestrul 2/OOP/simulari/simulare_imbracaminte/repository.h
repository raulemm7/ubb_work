//
// Created by raulo on 5/23/2024.
//

#ifndef SIMULARE_IMBRACAMINTE_REPOSITORY_H
#define SIMULARE_IMBRACAMINTE_REPOSITORY_H

#include <string>
#include <vector>
#include "domain.h"

using namespace std;

class Repository{
private:
    string nume_fisier;
    vector<Imbracaminte> lista_haine;
public:
    explicit Repository(const string &numeFisier) : nume_fisier(numeFisier) {};

    vector<Imbracaminte> &getListaHaine();

    void adauga_imbracaminte(Imbracaminte& haina);

    int getSize();

    void load_from_file();
    void save_to_file();
    void clear_file();

    virtual ~Repository() = default;
};

class testStorage{
public:
    static void test_all();
private:
    static void test_func();
    static void test_file_func();
};

#endif //SIMULARE_IMBRACAMINTE_REPOSITORY_H
