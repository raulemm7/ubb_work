//
// Created by raulo on 5/23/2024.
//

#include "repository.h"
#include <fstream>
#include <cassert>

using namespace std;

void repository::adauga_log(server_log &log) {
    this->lista_logs.push_back(log);
}

void repository::load_from_file() {
    // sterg toate datele curente
    this->lista_logs.clear();

    // id content pid info
    std::ifstream fin(this->nume_fisier);

    string id, content, info;
    int pid;

    while(fin >> id >> content >> pid >> info) {
        server_log log{id, content, pid, info};
        this->adauga_log(log);
    }

    fin.close();
}

void repository::save_to_file() {
    this->clear_file();
    std::ofstream fout(this->nume_fisier);

    auto vec = this->getListaLogs();
    for(auto& item : vec) {
        string info;
        info += item.getId() + " ";
        info += item.getContent() + " ";
        info += std::to_string(item.getPid()) + " ";
        info += item.getLevel() + "\n";

        fout << info;
    }

    fout.close();
}

void repository::clear_file() {
    std::ofstream fout;
    fout.open(this->nume_fisier, std::ofstream::out | std::ofstream::trunc);
    fout.close();
}

void test_repository::test_all() {
    test_repository::test_add_and_get_all();
    test_repository::test_file_func();
}

void test_repository::test_add_and_get_all() {
    repository storage("info.txt");

    server_log log{"0000", "content", 0, "info"};

    storage.adauga_log(log);

    auto vec = storage.getListaLogs();
    assert(vec.size() == 1);
    assert(vec.at(0).getId() == log.getId());
    assert(vec.at(0).getContent() == log.getContent());
    assert(vec.at(0).getPid() == log.getPid());
    assert(vec.at(0).getLevel() == log.getLevel());
}

void test_repository::test_file_func() {
    string file_name = "storage_test.txt";
    repository storage{file_name};

    storage.load_from_file();

    auto vec = storage.getListaLogs();
    assert(vec.size() == 3);
    assert(vec.at(1).getPid() == 1);

    storage.save_to_file();

    storage.load_from_file();

    auto vec2 = storage.getListaLogs();
    assert(vec2.size() == 3);
    assert(vec2.at(1).getPid() == 1);

    storage.save_to_file();
}
