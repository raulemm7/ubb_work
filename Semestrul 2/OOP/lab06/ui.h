//
// Created by raulo on 4/2/2024.
//

#ifndef LAB06_UI_H
#define LAB06_UI_H

#include <iostream>
#include <string>
#include "domain.h"
#include "repository.h"
using std::string;

class ui_operations {
public:
    void show_menu();
    void show_message(const string& msg);
    void show_menu_for_filter() const;
    void print_one_med(Medicament& medicament) ;
    void print_meds(MedicamenteRepo& storage) ;

    int read_command(const int& MAX_COMMAND);
    [[nodiscard]] string citire_string(const string& msg) ;
    [[nodiscard]] int citire_pret(const string& msg1, const string& msg2) ;
    int read_id(const int& MAX_ID, const string& msg_out, const string& msg_err);

    [[nodiscard]] Medicament citire_medicament(const int& id) ;

    void show_meds_filter_by_price(MedicamenteRepo& storage, const char& criteriu, const int& suma);
    void show_meds_filter_by_subst(MedicamenteRepo& storage, const string& substanta);

    char citire_operator_filtrare(const string& msg, const string& msg_err);
};

#endif //LAB06_UI_H
