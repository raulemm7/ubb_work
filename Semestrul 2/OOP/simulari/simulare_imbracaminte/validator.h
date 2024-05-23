//
// Created by raulo on 5/23/2024.
//

#ifndef SIMULARE_IMBRACAMINTE_VALIDATOR_H
#define SIMULARE_IMBRACAMINTE_VALIDATOR_H

#include "domain.h"

class Validator{
public:
    /**
     * compara doua haine in functie de tipul lor
     * @param haina1 o imbracaminte
     * @param haina2 o alta imbracaminte
     * @return 0, daca trebuie haina1.tip > haina2.tip, 1 altfel
     */
    static int compare_tip(const Imbracaminte& haina1, const Imbracaminte& haina2);

    /**
     * compara doua haine in functie de pret
     * @param haina1 o imbracaminte
     * @param haina2 o alta imbracaminte
     * @return 0, daca haina1.pret > haina2.pret, 1 altfel
     */
    static int compare_pret(const Imbracaminte& haina1, const Imbracaminte& haina2);
};

class ValidatorTest{
public:
    static void test_all();
};

#endif //SIMULARE_IMBRACAMINTE_VALIDATOR_H
