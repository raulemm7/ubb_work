//
// Created by raulo on 5/23/2024.
//

#include "validator.h"
#include <cassert>

int Validator::compare_tip(const Imbracaminte &haina1, const Imbracaminte &haina2) {
    if(haina1.getTip() > haina2.getTip())
        return 0;
    return 1;
}

int Validator::compare_pret(const Imbracaminte &haina1, const Imbracaminte &haina2) {
    if(haina1.getPret() > haina2.getPret())
        return 0;
    return 1;
}

void ValidatorTest::test_all() {
    Imbracaminte haina1{"pantaloni", "rosu", 127};

    Imbracaminte haina2{"tricou", "albastru", 120};

    assert(Validator::compare_tip(haina1, haina2) == 1);
    assert(Validator::compare_tip(haina2, haina1) == 0);

    assert(Validator::compare_pret(haina1, haina2) == 0);
    assert(Validator::compare_pret(haina2, haina1) == 1);
}
