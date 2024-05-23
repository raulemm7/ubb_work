//
// Created by raulo on 5/23/2024.
//

#ifndef SIMULARE_LOGS_VALIDATORS_H
#define SIMULARE_LOGS_VALIDATORS_H

#include "domain.h"
#include "repository.h"

class Validator{
public:
    bool valideaza_log(server_log& log);

    bool log_inregistrat(repository& storage, server_log& log);
};

#endif //SIMULARE_LOGS_VALIDATORS_H
