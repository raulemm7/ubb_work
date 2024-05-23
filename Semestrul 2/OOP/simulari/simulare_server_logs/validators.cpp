//
// Created by raulo on 5/23/2024.
//

#include "validators.h"

bool Validator::valideaza_log(server_log &log) {
    if(log.getId().size() != 4)
        return false;

    auto& info = log.getLevel();
    if(info != "info" and info != "warning" and info != "error" and info != "critical")
        return false;

    return true;
}

bool Validator::log_inregistrat(repository &storage, server_log &log) {
    auto vec = storage.getListaLogs();
    for(auto& item:vec){
        if(item.getContent() == log.getContent() and item.getPid() == log.getPid())
            return false;
    }

    return true;
}
