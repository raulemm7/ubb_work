//
// Created by raulo on 5/22/2024.
//

#ifndef SIMULARE_STOCKS_DOMAIN_H
#define SIMULARE_STOCKS_DOMAIN_H

#include <string>

using namespace std;

class StockObject{
private:
    string id;
    string nume;
    float pret;
    int change_rate;
public:
    StockObject(const string& id, const string &nume, float pret, int changeRate);

    const string &getId() const;

    const string &getNume() const;

    float getPret() const;

    int getChangeRate() const;

    ~StockObject() = default;
};

// fn + alt + insert

#endif //SIMULARE_STOCKS_DOMAIN_H
