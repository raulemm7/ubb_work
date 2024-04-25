#include "domain.h"
#include "repository.h"
#include "service.h"
#include "ui.h"
#include "validators.h"
#include <functional>

using std::string;

const string NO_REGISTRATIONS_MESSAGE = "Introdu medicamente inainte de a efectua operatii!";
const string NO_MEDS_IN_PRESCRIPTION_MESSAGE = "Nu exista medicamente in reteta!";
const string NO_VALID_ID_MESSAGE = "Ai introdus un id gresit!";
const string HEADER_PRESCRIPTION = "                            RETETA";
const string HEADER_MEDS = "ID    |    DENUMIRE    |    PRET    |    PRODUCATOR    |    SUBST. ACTIVA\n";

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
    MedicamenteRepo storage;
    ui_operations ui;

    int NUMBER_OF_PRESCRIPTIONS = 0;

    while(true) {
        ui.show_menu();

        int command = ui.read_command(11);

        if(command == 0) {
            const string& rez = service.adaugaMedicamenteRapid(storage);
            ui.show_message(rez);
        }
        if(command == 1) {
            int id = storage.get_last_id();
            Medicament medicament = ui.citire_medicament(id);
            string rez = service.adaugaMedicament(storage, medicament);
            ui.show_message(rez);
        }
        if(command == 2) {
            if(storage.get_last_id() > 0) {
                ui.print_meds(storage, HEADER_MEDS);
                int id = ui.read_id(storage.get_last_id() - 1, "Introdu id-ul medicamentului pe care doresti sa il stergi: ",
                                    NO_VALID_ID_MESSAGE);
                string rez = service.stergeMedicament(storage, id);
                ui.show_message(rez);
            }
            else {
                ui.show_message(NO_REGISTRATIONS_MESSAGE);
            }

        }
        if(command == 3) {
            if(storage.get_last_id() > 0) {
                ui.print_meds(storage, HEADER_MEDS);
                int id = ui.read_id(storage.get_last_id() - 1, "Introdu id-ul medicamentului pe care doresti sa il modifici: ",
                                    NO_VALID_ID_MESSAGE);
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
            if(storage.get_last_id() > 0)
                ui.print_meds(storage, HEADER_MEDS);
            else
                ui.show_message(NO_REGISTRATIONS_MESSAGE);
        }
        if(command == 5) {
            if(storage.get_last_id() > 0) {
                string search = ui.citire_string("Introdu denumirea medicamentului pe care il cauti: ");
                string rez = service.cautaMedicament(storage, search);
                ui.show_message(rez);
            }
            else {
                ui.show_message(NO_REGISTRATIONS_MESSAGE);
            }
        }
        if(command == 6) {
            if(storage.get_last_id() > 0) {
                ui.show_menu_for_filter();
                command = ui.read_command(2);

                if(command == 1) {
                    char op = ui.citire_operator_filtrare("Introdu opreatorul de filtrare(>, <, =): ", "Ai introdus un operator gresit!");
                    int pret = ui.citire_pret("Introdu pretul dupa care faci filtrarea: ", "Ai introdus un pret gresit!");
                    ui.filterPret(storage, pret, op);
                }
                else {
                    string subst = ui.citire_string("Introdu substanta activa dupa care doresti sa faci filtrarea: ");
                    ui.filterSubstActiva(storage, subst);
                }
            }
            else {
                ui.show_message(NO_REGISTRATIONS_MESSAGE);
            }
        }
        if(command == 7) {
            if(storage.get_last_id() > 0) {
                ui.show_menu_for_sort();
                command = ui.read_command(3);
                if(command == 1) {
                    // sortare dupa denumire
                    ui.genericSort(storage, &Validator::compare_denumire);
                }
                if(command == 2) {
                    // sortare dupa producator
                    ui.genericSort(storage, &Validator::compare_producator);
                }
                if(command == 3) {
                    // sortare dupa subst activa + pret
                    ui.genericSort(storage, &Validator::compare_subst_activa_and_pret);
                }
            }
            else {
                ui.show_message(NO_REGISTRATIONS_MESSAGE);
            }
        }
        if(command == 8) {
            // initializari
            int number_of_iterations;
            if(!storage.get_last_id()) {
                ui.show_message(NO_REGISTRATIONS_MESSAGE);
                number_of_iterations = 0;
            }
            else
                number_of_iterations = 1;

            MedicamenteRepo reteta;

            while(number_of_iterations) {
                // afisarea retetei cand numarul de executie este > 1
                if(number_of_iterations > 1) {
                    if (reteta.get_last_id() > 0) {
                        ui.show_message(HEADER_PRESCRIPTION);
                        ui.print_meds(reteta, HEADER_MEDS);
                    }
                    else
                        ui.show_message(NO_MEDS_IN_PRESCRIPTION_MESSAGE);
                }
                // afisare meniu
                ui.show_menu_for_prescription();
                // alegere comanda
                command = ui.read_command(5);

                if(command == 1) {
                    /** adaugare */
                    ui.print_meds(storage, HEADER_MEDS);

                    int id_med = ui.read_id_with_string(storage, "Introdu denumirea medicamentului pe care doresti sa il introduci in reteta: ",
                                            "Nu exista niciun medicament cu aceasta denumire!\n");
                    const Medicament& medicament = storage.get_med(id_med);

                    string msg_output = service.adaugaMedicament(reteta, medicament);
                    reteta.set_id_correctly();

                    ui.show_message(msg_output);
                }
                if(command == 2) {
                    /** stergere */
                    const string& rez = service.stergeToateMedicamentele(reteta);
                    ui.show_message(rez);
                }
                if(command == 3) {
                    /** generare random */
                    int numarMeds = ui.read_id(INT16_MAX, "Introdu numarul de medicamente pe care doresti sa il \a"
                                                                      "daugi in reteta: ", "Nu exista atatea medicamente in stoc!");

                    // sterg reteta actuala
                    service.stergeToateMedicamentele(reteta);

                    // populez reteta
                    const string& rez = service.adaugareRandom(storage, reteta, numarMeds);

                    // pun id-urile corect
                    reteta.set_id_correctly();

                    ui.show_message(rez);
                }
                if(command == 4) {
                    /** export */
                    if(reteta.get_last_id() > 0) {
                        NUMBER_OF_PRESCRIPTIONS++;
                        string nameFile = ui.read_name_file();

                        string rez = service.exportDataInHTMLformat(reteta, nameFile, NUMBER_OF_PRESCRIPTIONS);

                        ui.show_message(rez);
                    }
                    else
                        ui.show_message(NO_MEDS_IN_PRESCRIPTION_MESSAGE + NO_REGISTRATIONS_MESSAGE);
                }
                if(command == 5) {
                    /** iesire */
                    number_of_iterations = -1;
                }

                number_of_iterations++;
            }
        }
        if(command == 9) {
            std::unordered_map<string, MedicamentDTO> raport = service.generareRaport(storage);
            ui.print_raport(raport);
        }
        if(command == 10) {
            const string st = service.executa_undo(storage);
            storage.set_id_correctly();
            ui.show_message(st);
        }
        if(command == 11) {
            return;
        }
    }
}

// fn + alt + insert to insert constructor, destructor, setters, getters etc.
// ctrl w select code
