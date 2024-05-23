//
// Created by raulo on 5/22/2024.
//

#ifndef SIMULARE_STOCKS_SERVICE_H
#define SIMULARE_STOCKS_SERVICE_H

#include <string>
#include "domain.h"
#include "repository.h"

using namespace std;

class Service{
public:
    string adauga_stock_service(RepoObject& storage, const string& id, const string& nume, float pret, int change);

    string sterge_stock_service(RepoObject& storage, const string& nume_stock);

    string adauga_rapid(RepoObject& storage);
};

#endif //SIMULARE_STOCKS_SERVICE_H
