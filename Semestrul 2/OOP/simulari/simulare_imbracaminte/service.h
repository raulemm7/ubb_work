//
// Created by raulo on 5/23/2024.
//

#ifndef SIMULARE_IMBRACAMINTE_SERVICE_H
#define SIMULARE_IMBRACAMINTE_SERVICE_H

#include "repository.h"
#include <string>
#include <functional>

using namespace std;

class Service{
public:
    /**
     * filtreaeza elementele din storage in functie de tip
     * @param storage repositoryul cu elemente
     * @param tip tipul dupa care se face filtrarea
     * @return vector cu imbracaminte
     */
    vector<Imbracaminte> filtrare_dupa_tip(Repository& storage, const string& tip);

    /**
     * sorteaza repo cu imbracaminte in functie de un criteriu
     * @param storage repo ul cu elemente
     * @param getter criteriul dupa care se face sortarea
     * @return vector cu imbracaminte sortat dupa criteriu
     */
    vector<Imbracaminte> generic_sort(Repository& storage, function<int(const Imbracaminte&, const Imbracaminte&)> getter);
};

class testService{
private:
    static void test_filtrare();
    static void test_generic_sort();
public:
    static void test_all();
};

#endif //SIMULARE_IMBRACAMINTE_SERVICE_H
