//
// Created by raulo on 5/23/2024.
//

#ifndef SIMULARE_ROCHIE_VALIDATOR_H
#define SIMULARE_ROCHIE_VALIDATOR_H

#include "domain.h"

class Validator{
public:
    static int compare_marime(const Rochie& rch1, const Rochie& rch2);

    static int compare_pret(const Rochie& rch1, const Rochie& rch2);
};

#endif //SIMULARE_ROCHIE_VALIDATOR_H
