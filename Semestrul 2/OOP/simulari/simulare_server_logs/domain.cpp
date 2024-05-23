//
// Created by raulo on 5/23/2024.
//

#include "domain.h"
#include <cassert>

const string server_log::getId() const {
    return this->id;
}

const string &server_log::getContent() const {
    return this->content;
}

int server_log::getPid() const {
    return this->pid;
}

const string &server_log::getLevel() const {
    return this->level;
}

void test_domain::test_all() {
    server_log log{"1a6d", "Connected", 23, "info"};

    assert(log.getId() == "1a6d");
    assert(log.getContent() == "Connected");
    assert(log.getLevel() == "info");
    assert(log.getPid() == 23);
}
