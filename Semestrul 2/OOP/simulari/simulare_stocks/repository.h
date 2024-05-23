//
// Created by raulo on 5/22/2024.
//

#ifndef SIMULARE_STOCKS_REPOSITORY_H
#define SIMULARE_STOCKS_REPOSITORY_H

#include <vector>
#include "domain.h"

class RepoObject {
private:
    vector<StockObject> lista_stocks;
    string nume_fisier;
public:
    explicit RepoObject(const string& file_name):nume_fisier{file_name}{}

    vector<StockObject> &getListaStocks();

    StockObject& getStock(const string& nume_stock);

    void adauga_stock(StockObject& stock);

    void sterge_stock(const string& nume_stock);

    void load_from_file();
    void save_to_file();
    void clear_file();

    ~RepoObject() = default;
};

#endif //SIMULARE_STOCKS_REPOSITORY_H
