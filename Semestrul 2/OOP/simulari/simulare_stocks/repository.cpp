//
// Created by raulo on 5/22/2024.
//

#include "repository.h"
#include <fstream>
#include <cstring>

vector<StockObject> &RepoObject::getListaStocks() {
    return this->lista_stocks;
}

void RepoObject::adauga_stock(StockObject &stock) {
    this->lista_stocks.push_back(stock);
}

void RepoObject::sterge_stock(const string& nume_stock) {
    auto iter = this->lista_stocks.begin();
    while(iter != this->lista_stocks.end()) {
        if(iter->getNume() == nume_stock) {
            this->lista_stocks.erase(iter);
            return;
        }
        iter++;
    }
}

StockObject &RepoObject::getStock(const string& nume_stock) {
    int position = 0;
    while(position < this->lista_stocks.size()) {
        if(this->lista_stocks[position].getNume() == nume_stock) {
            return this->lista_stocks[position];
        }
        position++;
    }
}

void RepoObject::load_from_file() {
    // id nume_stock pret(float) change_ratio(int)
    std::ifstream fin(this->nume_fisier);

    string id;
    string nume;
    float pret;
    int change_ratio;

    while(fin >> id >> nume >> pret >> change_ratio) {
        StockObject stk{id, nume, pret, change_ratio};
        this->adauga_stock(stk);
    }

    fin.close();

}

void RepoObject::save_to_file() {
    this->clear_file();

    std::ofstream fout(this->nume_fisier);

    vector<StockObject> vec = this->getListaStocks();
    for(auto const & item : vec) {
        string info;
        info += item.getId() + " ";
        info += item.getNume() + " ";
        info += std::to_string(item.getPret()) + " ";
        info += std::to_string(item.getChangeRate()) + "\n";

        fout << info;
    }

    fout.close();
}

void RepoObject::clear_file() {
    std::ofstream fout(this->nume_fisier);
    fout.open(this->nume_fisier, std::ofstream::out | std::ofstream::trunc);
    fout.close();
}

