//
// Created by raulo on 5/23/2024.
//

#ifndef SIMULARE_ROCHIE_SERVICE_H
#define SIMULARE_ROCHIE_SERVICE_H

#include "repository.h"
#include <string>
#include <functional>

using namespace std;

class Service{
public:
    string set_disponibilitate_rochie(Repository& storage, int cod);

    vector<Rochie> generic_sort(Repository& storage, function<int(const Rochie&, const Rochie&)> functie_cmp);
};

#endif //SIMULARE_ROCHIE_SERVICE_H
