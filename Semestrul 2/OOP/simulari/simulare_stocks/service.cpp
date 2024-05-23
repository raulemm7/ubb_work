//
// Created by raulo on 5/22/2024.
//

#include "service.h"
#include "validators.h"

string Service::adauga_stock_service(RepoObject& storage, const string &id, const string &nume, float pret, int change) {
    Validator vali;

    StockObject stk(id, nume, pret, change);
    if(!vali.validare_stock(stk))
        return "Atributele stock-ului nu sunt corecte!";
    if(!vali.validare_inregistrare(storage, stk))
        return "Stock deja inregistrat!";

    storage.adauga_stock(stk);
    return "Stock adaugat cu succes!";
}

string Service::sterge_stock_service(RepoObject& storage, const string &nume_stock) {
    Validator vali;

    if(!vali.cautare_nume_in_storage(storage, nume_stock))
        return "Nu s-a gasit niciun stock cu acest nume pentru a fi sters!";

    storage.sterge_stock(nume_stock);
    return "Stock sters cu succes!";
}

string Service::adauga_rapid(RepoObject &storage) {
    StockObject stk1{"0000", "appl", 182.2, -20};
    storage.adauga_stock(stk1);

    StockObject stk2{"0001", "asus", 154.9, 3};
    storage.adauga_stock(stk2);

    StockObject stk3{"0002", "core", 23.12, -7};
    storage.adauga_stock(stk3);

    StockObject stk4{"0003", "cici", 221.1, -21};
    storage.adauga_stock(stk4);

    StockObject stk5{"0004", "adibas", 54.7, -4};
    storage.adauga_stock(stk5);

    StockObject stk6{"0005", "mike", 96.2, 4};
    storage.adauga_stock(stk6);

    StockObject stk7{"0006", "brca", 231, 6};
    storage.adauga_stock(stk7);

    StockObject stk8{"0007", "nasa", 13.2, -2};
    storage.adauga_stock(stk8);

    StockObject stk9{"0008", "nba", 99.5, -12};
    storage.adauga_stock(stk9);

    StockObject stk10{"0009", "goog", 245.2, 8};
    storage.adauga_stock(stk10);

    StockObject stk11{"0010", "spt", 79.34, 16};
    storage.adauga_stock(stk11);

    return "Stockuri adaugate cu succes!";
}
