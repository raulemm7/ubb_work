//
// Created by raulo on 5/23/2024.
//

#include "validator.h"

int Validator::compare_marime(const Rochie &rch1, const Rochie &rch2) {
    if(rch1.getMarime() > rch2.getMarime())
        return 0;
    return 1;
}

int Validator::compare_pret(const Rochie &rch1, const Rochie &rch2) {
    if(rch1.getPret() > rch2.getPret())
        return 0;
    return 1;
}
