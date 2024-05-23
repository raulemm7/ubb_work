//
// Created by raulo on 5/23/2024.
//

#include "domain.h"
#include <cassert>

void testDomain::test_all() {
    Imbracaminte haina{"pantaloni", "rosu", 123};

    assert(haina.getTip() == "pantaloni");
    assert(haina.getCuloare() == "rosu");
    assert(haina.getPret() == 123);
}
