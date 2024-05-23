//
// Created by raulo on 5/22/2024.
//

#include "validators.h"

bool Validator::validare_stock(StockObject &stock) {
    if(stock.getId().size() != 4)
        return false;
    if(stock.getPret() <= -100 and stock.getPret() >= 300)
        return false;

    return true;
}

bool Validator::validare_inregistrare(RepoObject &storage, StockObject &stock) {
    auto stocks = storage.getListaStocks();
    for(auto& verf_stock : stocks) {
        if(verf_stock.getNume() == stock.getNume())
            return false;
    }

    return true;
}

bool Validator::cautare_nume_in_storage(RepoObject &storage, const string &nume_stock) {
    auto stocks = storage.getListaStocks();
    for(auto& stock : stocks) {
        if(stock.getNume() == nume_stock)
            return true;
    }

    return false;
}
