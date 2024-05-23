//
// Created by raulo on 5/23/2024.
//

#ifndef SIMULARE_LOGS_DOMAIN_H
#define SIMULARE_LOGS_DOMAIN_H

#include <string>

using namespace std;

class server_log{
private:
    string id;
    string content;
    int pid;
    string level;
public:
    server_log(const string &id, const string &content, int pid, const string &level):id(id),
                                                                                      content(content),
                                                                                      pid(pid),
                                                                                      level(level) {};

    const string getId() const;

    const string &getContent() const;

    int getPid() const;

    const string &getLevel() const;

    virtual ~server_log() = default;
};

class test_domain{
public:
    static void test_all();
};

#endif //SIMULARE_LOGS_DOMAIN_H
