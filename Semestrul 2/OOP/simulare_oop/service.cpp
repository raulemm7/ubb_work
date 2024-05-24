//
// Created by raulo on 5/24/2024.
//

#include "service.h"
#include "validators.h"
#include <cassert>

vector<Pix> Service::generic_sort(Repository &storage, function<int(const Pix &, const Pix &)> functie_cmp) {
    auto vec = storage.getListaPixuri();

    std::sort(vec.begin(), vec.end(), functie_cmp);

    return vec;
}

void testService::test_all() {
    Service service;

    Repository repo("file.txt");

    Pix pix1{1, "Bic", "albastru", 20.0};
    repo.adauga_pix(pix1);
    Pix pix2{2, "Pelican", "verde", 20.2};
    repo.adauga_pix(pix2);

    auto vec = service.generic_sort(repo, Validator::compara_dupa_pret_descrescator);

    assert(vec.at(0).getId() == pix2.getId());
    assert(vec.at(0).getBrand() == pix2.getBrand());
    assert(vec.at(0).getCuloare() == pix2.getCuloare());
    assert(vec.at(0).getPret() == pix2.getPret());

    assert(vec.at(1).getId() == pix1.getId());
    assert(vec.at(1).getBrand() == pix1.getBrand());
    assert(vec.at(1).getCuloare() == pix1.getCuloare());
    assert(vec.at(1).getPret() == pix1.getPret());
}
