//
// Created by raulo on 5/23/2024.
//

#ifndef SIMULARE_LOGS_SERVICE_H
#define SIMULARE_LOGS_SERVICE_H

#include <string>
#include "repository.h"
#include "domain.h"

using namespace std;

class Service{
public:
    string adaugare_log_nou(repository& storage, const string& id, const string& content, int pid, const string& info);
};

#endif //SIMULARE_LOGS_SERVICE_H
