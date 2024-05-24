//
// Created by raulo on 5/24/2024.
//

#include "validators.h"
#include <cassert>

int Validator::compara_dupa_brand_crescator(const Pix &pix1, const Pix &pix2) {
    if(pix1.getBrand() > pix2.getBrand())
        return 0;
    return 1;
}

int Validator::compara_dupa_pret_descrescator(const Pix &pix1, const Pix &pix2) {
    if(pix1.getPret() < pix2.getPret())
        return 0;
    return 1;
}

void testValidator::test_all() {
    Pix pix1{1, "Bic", "albastru", 20.2};
    Pix pix2{2, "Pelican", "verde", 20.0};

    assert(Validator::compara_dupa_brand_crescator(pix1, pix2) == 1);
    assert(Validator::compara_dupa_brand_crescator(pix2, pix1) == 0);

    assert(Validator::compara_dupa_pret_descrescator(pix1, pix2) == 1);
    assert(Validator::compara_dupa_pret_descrescator(pix2, pix1) == 0);
}
