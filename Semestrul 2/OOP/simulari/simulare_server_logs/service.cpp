//
// Created by raulo on 5/23/2024.
//

#include "service.h"
#include "validators.h"

string
Service::adaugare_log_nou(repository &storage, const string &id, const string &content, int pid, const string &info) {
    server_log log{id, content, pid, info};

    Validator vali;
    if(!vali.valideaza_log(log)) {
        return "Inregistrare invalida!";
    }
    if(!vali.log_inregistrat(storage, log)) {
        return "Log deja inregistrat!";
    }

    storage.adauga_log(log);
    return "Log inregistrat cu succes!";
}
