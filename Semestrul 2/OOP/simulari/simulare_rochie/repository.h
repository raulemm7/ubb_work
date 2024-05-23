//
// Created by raulo on 5/23/2024.
//

#ifndef SIMULARE_ROCHIE_REPOSITORY_H
#define SIMULARE_ROCHIE_REPOSITORY_H

#include <string>
#include <vector>
#include "domain.h"

using namespace std;

class Repository{
private:
    vector<Rochie> lista_rochii;
    string nume_fisier;
public:
    explicit Repository(const string &numeFisier) : nume_fisier(numeFisier) {};

    vector<Rochie> &getListaRochii();

    string set_disponibilitate(int cod);

    void load_from_file();
    void save_to_file();
    void clear_file();

    virtual ~Repository() = default;
};

#endif //SIMULARE_ROCHIE_REPOSITORY_H
