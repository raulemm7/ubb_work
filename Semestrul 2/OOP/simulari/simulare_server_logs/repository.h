//
// Created by raulo on 5/23/2024.
//

#ifndef SIMULARE_LOGS_REPOSITORY_H
#define SIMULARE_LOGS_REPOSITORY_H

#include <string>
#include <vector>
#include "domain.h"

using namespace std;

class repository{
private:
    string nume_fisier;
    vector<server_log> lista_logs;
public:
    explicit repository(const string &numeFisier):nume_fisier(numeFisier) {};

    vector<server_log> &getListaLogs() {
        return this->lista_logs;
    }

    int getSize(){
        return this->lista_logs.size();
    }

    void adauga_log(server_log& log);

    void load_from_file();
    void save_to_file();
    void clear_file();

    virtual ~repository() = default;
};

class test_repository{
public:
    static void test_all();
private:
    static void test_add_and_get_all();
    static void test_file_func();
};

#endif //SIMULARE_LOGS_REPOSITORY_H
