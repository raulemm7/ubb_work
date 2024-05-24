//
// Created by raulo on 5/24/2024.
//

#ifndef SIMULARE_OOP_VALIDATORS_H
#define SIMULARE_OOP_VALIDATORS_H

#include "domain.h"

class Validator{
public:
    /**
     * compara doua pixuri in functie de brand
     * @param pix1 un obiect de tip pix
     * @param pix2 un obiect de tip pix
     * @return 0, brand pix1 > brand pix2, 1 altfel
     */
    static int compara_dupa_brand_crescator(const Pix& pix1, const Pix& pix2);

    /**
     * compara doua pixuri in functie de pret
     * @param pix1 un obiect de tip pix
     * @param pix2 un obiect de tip pix
     * @return 0, pret pix1 < pret pix2, 1 altfel
     */
    static int compara_dupa_pret_descrescator(const Pix& pix1, const Pix& pix2);
};

class testValidator{
public:
    static void test_all();
};

#endif //SIMULARE_OOP_VALIDATORS_H
