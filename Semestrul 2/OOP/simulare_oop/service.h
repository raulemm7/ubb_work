//
// Created by raulo on 5/24/2024.
//

#ifndef SIMULARE_OOP_SERVICE_H
#define SIMULARE_OOP_SERVICE_H

#include <functional>
#include <vector>
#include "domain.h"
#include "repository.h"

class Service{
public:
    /**
     * sorteaza lista de elemente in functie de un criteriu
     * @param storage repository-ul cu lista de elemente
     * @param functie_cmp criteriul dupa care se face sortarea
     * @return lista de elemente sortata dupa criteriu
     */
    vector<Pix> generic_sort(Repository& storage, function<int(const Pix&, const Pix&)> functie_cmp);
};

class testService{
public:
    static void test_all();
};

#endif //SIMULARE_OOP_SERVICE_H
