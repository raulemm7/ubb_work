#include "domain.h"
#include "repository.h"
#include "ui.h"
#include "service.h"

void run_all_tests() {
    test_create_and_get_cheltuiala();
    test_modify_cheltuiala();
    run_repo_all_tests();
    run_validator_tests();
    run_all_tests_service();
}

void run_app() {
    // initializari
    Repo storage_cheltuieli;
    storage_cheltuieli = creeare_repo();

    while(1) {
        int last_id = get_nr_cheltuieli(storage_cheltuieli) - 1;
        show_menu();

        int command = read_command(6);

        if(command == 1) {
            cheltuiala new_chelt = make_new_cheltuiala(last_id);
            storage_cheltuieli = adauga_cheltuiala(storage_cheltuieli, new_chelt);
            print_mesage("Cheltuiala adaugata cu succes!\n");
        }
        if(command == 2) {
            if(get_nr_cheltuieli(storage_cheltuieli) > 0) {
                print_cheltuieli(storage_cheltuieli);
                // alege id-ul cheltuielii pe care doreste sa o modifice
                int id_chelt = citire_id(last_id, "Introdu ID-ul cheltuielii pe care vrei sa o modifici: ");
                storage_cheltuieli = modifica_cheltuiala(storage_cheltuieli, id_chelt);
                print_mesage("Cheltuiala modificata cu succes!");
            }
            else
                print_mesage("Nu exista inregistrari facute!\n");
        }
        if(command == 3) {
            if(get_nr_cheltuieli(storage_cheltuieli) > 0) {
                print_cheltuieli(storage_cheltuieli);
                int id_chelt = citire_id(last_id, "Introdu ID-ul cheltuielii pe care doresti sa o stergi: ");
                storage_cheltuieli = sterge_cheltuiala(storage_cheltuieli, id_chelt);
                print_mesage("Cheltuiala stearsa cu succes!\n");
            }
            else
                print_mesage("Nu exista inregistrari facute!\n");
        }
        if(command == 4) {
            if(get_nr_cheltuieli(storage_cheltuieli) > 0) {
                // fac filtrare
                show_filter_menu();
                int filter_command = read_command(2);
                if(filter_command == 1) {
                    // filtrare dupa suma
                    char operator_filtrare = citire_operator();
                    int suma = citire_suma_cheltuiala();
                    filtrare_suma(storage_cheltuieli, operator_filtrare, suma);
                }
                else {
                    // filtrare dupa tip
                    char *tip_filtrare;
                    tip_filtrare = citire_tip_cheltuiala();

                    filtrare_tip_cheltuiala(storage_cheltuieli, tip_filtrare);

                    free(tip_filtrare);
                }
            }
            else
                print_mesage("Nu exista inregistrari facute!\n");
        }
        if(command == 5) {
            if(get_nr_cheltuieli(storage_cheltuieli) > 0) {
                show_ordonated_menu();
                int alege_criteriu_command = read_command(2);
                if(alege_criteriu_command == 1) {
                    show_ordonated_menu_for_sum();
                    int sum_command = read_command(2);
                    if(sum_command == 1)
                        print_cheltuieli_suma_crescator(storage_cheltuieli);
                    else
                        print_cheltuieli_suma_descrescator(storage_cheltuieli);

                }
                else {
                    show_ordonated_menu_for_type();
                    int type_command = read_command(2);
                    if(type_command == 1)
                        print_cheltuieli_tip_alfabetic(storage_cheltuieli);
                    else
                        print_cheltuiel_tip_alfabetic_invers(storage_cheltuieli);
                }
            }
            else
                print_mesage("Nu exista inregistrari facute!\n");
        }
        if(command == 6) {
            return;
        }
    }
}

int main() {
    //teste
    run_all_tests();

    run_app();
}
