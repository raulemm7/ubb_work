//
// Created by raulo on 5/23/2024.
//

#include "service.h"
#include <cassert>
#include "validator.h"

vector<Imbracaminte>  Service::filtrare_dupa_tip(Repository &storage, const string &tip) {
    auto vector_haine = storage.getListaHaine();
    vector<Imbracaminte> vector_filtrat;
    vector_filtrat.clear();

    for(auto const& item : vector_haine) {
        if(item.getTip() == tip) {
            vector_filtrat.push_back(item);
        }
    }

    return vector_filtrat;
}

vector<Imbracaminte>
Service::generic_sort(Repository &storage, function<int(const Imbracaminte &, const Imbracaminte &)> getter) {
    vector<Imbracaminte> vector_haine = storage.getListaHaine();

    std::sort(vector_haine.begin(), vector_haine.end(), getter);

    return vector_haine;
}

void testService::test_all() {
    testService::test_filtrare();
    testService::test_generic_sort();
}

void testService::test_filtrare() {
    Service serv;

    Repository storage{"file.txt"};

    Imbracaminte haina1{"pantaloni", "rosu", 127};
    storage.adauga_imbracaminte(haina1);

    Imbracaminte haina2{"tricou", "albastru", 120};
    storage.adauga_imbracaminte(haina2);

    auto vec = serv.filtrare_dupa_tip(storage, "pantaloni");
    assert(vec.size() == 1);
    assert(vec.at(0).getTip() == haina1.getTip());
}

void testService::test_generic_sort() {
    Service serv;

    Repository storage{"file.txt"};

    Imbracaminte haina1{"pantaloni", "rosu", 127};
    storage.adauga_imbracaminte(haina1);

    Imbracaminte haina2{"tricou", "albastru", 120};
    storage.adauga_imbracaminte(haina2);

    auto vec = serv.generic_sort(storage, Validator::compare_pret);
    assert(vec.size() == 2);
    assert(vec.at(0).getPret() == 120);
    assert(vec.at(0).getPret() == 120);
}
