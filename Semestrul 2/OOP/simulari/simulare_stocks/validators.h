//
// Created by raulo on 5/22/2024.
//

#ifndef SIMULARE_STOCKS_VALIDATORS_H
#define SIMULARE_STOCKS_VALIDATORS_H

#include "domain.h"
#include "repository.h"

class Validator{
public:
    bool validare_stock(StockObject& stock);

    bool validare_inregistrare(RepoObject& storage, StockObject& stock);

    bool cautare_nume_in_storage(RepoObject &storage, const string &nume_stock);
};

#endif //SIMULARE_STOCKS_VALIDATORS_H
