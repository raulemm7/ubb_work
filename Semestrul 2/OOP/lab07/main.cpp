#include "domain.h"
#include "repository.h"
#include "service.h"
#include "ui.h"
#include "validators.h"
#include "definedVector.h"

using std::string;

string NO_REGISTRATIONS_MESSAGE = "Introdu medicamente inainte de a efectua operatii!";
string INVALID_ID_MESSAGE = "Ai introdus un id gresit!";

void run_all_tests();

void run_app();

int main() {
    run_all_tests();
    run_app();
    return 0;
}

void run_all_tests() {
    serviceTests::run_all_servive_tests();
    domainTests::test_getters_and_setters();
    repositoryTests::test_repository_functionalities();
    validatorTests::validator_all_tests();
}

void run_app() {
    // initializari
    Service service;
    VectorDinamic<Medicament> storage;
    ui_operations ui;

    while(true) {
        ui.show_menu();

        int command = ui.read_command(8);

        if(command == 0) {
            int id = storage.get_last_id_vd();
            string rez;

            // adaugare rapida
            Medicament med1(id, "brufen", 25, "pharma", "paracetamol");
            rez = service.adaugaMedicament(storage, med1);
            if(rez == "Medicament adaugat cu succes!")
                id++;

            Medicament med2(id, "lecitina", 34, "boiron", "boabe de soia");
            rez = service.adaugaMedicament(storage, med2);
            if(rez == "Medicament adaugat cu succes!")
                id++;

            Medicament med3(id, "algolcalmin", 19, "walmark", "paracetamol");
            service.adaugaMedicament(storage, med3);
        }
        if(command == 1) {
            int id = storage.get_last_id_vd();
            Medicament medicament = ui.citire_medicament(id);
            string rez = service.adaugaMedicament(storage, medicament);
            ui.show_message(rez);
        }
        if(command == 2) {
            if(storage.get_last_id_vd() > 0) {
                ui.print_meds(storage);
                int id = ui.read_id(storage.get_last_id_vd() - 1, "Introdu id-ul medicamentului pe care doresti sa il stergi: ",
                                    INVALID_ID_MESSAGE);
                string rez = service.stergeMedicament(storage, id);
                ui.show_message(rez);
            }
            else {
                ui.show_message(NO_REGISTRATIONS_MESSAGE);
            }

        }
        if(command == 3) {
            if(storage.get_last_id_vd() > 0) {
                ui.print_meds(storage);
                int id = ui.read_id(storage.get_last_id_vd() - 1, "Introdu id-ul medicamentului pe care doresti sa il modifici: ",
                                    INVALID_ID_MESSAGE);
                int new_pret = ui.citire_pret("Introdu noul pret al medicamentului: ", "Ai introdus un pret gresit!");
                string new_subst_activa = ui.citire_string("Introdu noua substanta activa a medicamentului: ");
                string rez = service.modificaMedicament(storage, id, new_pret, new_subst_activa);
                ui.show_message(rez);
            }
            else {
                ui.show_message(NO_REGISTRATIONS_MESSAGE);
            }
        }
        if(command == 4) {
            if(storage.get_last_id_vd() > 0)
                ui.print_meds(storage);
            else
                ui.show_message(NO_REGISTRATIONS_MESSAGE);
        }
        if(command == 5) {
            if(storage.get_last_id_vd() > 0) {
                string search = ui.citire_string("Introdu denumirea medicamentului pe care il cauti: ");
                string rez = service.cautaMedicament(storage, search);
                ui.show_message(rez);
            }
            else {
                ui.show_message(NO_REGISTRATIONS_MESSAGE);
            }
        }
        if(command == 6) {
            if(storage.get_last_id_vd() > 0) {
                ui.show_menu_for_filter();
                command = ui.read_command(2);

                if(command == 1) {
                    char op = ui.citire_operator_filtrare("Introdu opreatorul de filtrare: ", "Ai introdus un operator gresit!");
                    int pret = ui.citire_pret("Introdu pretul dupa care faci filtrarea: ", "Ai introdus un pret gresit!");
                    ui.show_meds_filter_by_price(storage, op, pret);
                }
                else {
                    string subst = ui.citire_string("Introdu substanta activa dupa care doresti sa faci filtrarea: ");
                    ui.show_meds_filter_by_subst(storage, subst);
                }
            }
            else {
                ui.show_message(NO_REGISTRATIONS_MESSAGE);
            }
        }
        if(command == 7) {
            if(storage.get_last_id_vd() > 0) {
                ui.show_menu_for_sort();
                command = ui.read_command(3);
                if(command == 1) {
                    // sortare dupa denumire
                    ui.oneCriteriaSort(storage, &Validator::compare_denumire);
                }
                if(command == 2) {
                    // sortare dupa producator
                    ui.oneCriteriaSort(storage, &Validator::compare_producator);
                }
                if(command == 3) {
                    // sortare dupa subst activa + pret
                    ui.twoCriteriaSort(storage, &Validator::compare_subst_activa, &Validator::compare_pret);
                }
            }
            else {
                ui.show_message(NO_REGISTRATIONS_MESSAGE);
            }
        }
        if(command == 8) {
            return;
        }
    }
}
