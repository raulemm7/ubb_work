//
// Created by raulo on 5/23/2024.
//

#include "service.h"

string Service::set_disponibilitate_rochie(Repository &storage, int cod) {
    return storage.set_disponibilitate(cod);
}

vector<Rochie> Service::generic_sort(Repository &storage, function<int(const Rochie &, const Rochie &)> functie_cmp) {
    auto vec = storage.getListaRochii();

    std::sort(vec.begin(), vec.end(), functie_cmp);

    return vec;
}
