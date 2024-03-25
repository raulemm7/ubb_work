#include "repository.h"
#include "service.h"
#include "ui.h"
#include "sort.h"

/*
 * 7. Administrator imobil
 * Creati o aplicatie care petmite gestiunea de cheltuieli lunare pentru apartamentele dintr-un bloc.
 * Fiecare cheltuiala are: numarul apartamentului, suma, tipul (apa, canal, incalzire, gaz).
 * Aplicatia permite:
 * a) Adaugarea de cheltuieli pentru un apartament
 * b) Modificarea unei cheltuieli existente (tipul, suma)
 * c) Stergere cheltuiala
 * d) Vizualizare lista de cheltuieli filtrat dupa o proprietate (suma, tipul)
 * e) Vizualizare lista de cheltuieli ordonat dupa suma sau tip (crescator/descrescator)
 */

void run_app_tests() {
    run_domain_tests();
    run_repository_tests();
    run_validator_tests();
    run_service_tests();
    run_sort_test();
}

void run_app() {
    // initializare lista
    Repo* storage_cheltuieli = creeaza_repository();

    while(1) {
        menu();

        int command = citire_comanda(6, "Citeste o comanda: ");
        if(command == 1) {
            // citesc si validez date pentru o noua cheltuiala
            int id_cheltuiala = get_nr_cheltuieli(storage_cheltuieli);
            int numar_apartament = citire_nr_apartament("Citeste numarul apartamentului: ");
            int suma_cheltuiala = citire_suma_cheltuiala("Citeste suma cheltuielii: ");
            char *tip_cheltuiala = citire_tip_cheltuiala("Citeste tipul cheltuielii: ");

            storage_cheltuieli = adauga_o_noua_cheltuiala(storage_cheltuieli,
                    id_cheltuiala, numar_apartament, suma_cheltuiala, tip_cheltuiala);
        }
        else if(command == 2) {
            if(get_nr_cheltuieli(storage_cheltuieli) > 0) {
                // listez toate cheltuielile
                print_cheltuieli(storage_cheltuieli);

                // aleg id-ul cheltuielii pe care doresc sa o modific
                int id_ales = citire_id(get_nr_cheltuieli(storage_cheltuieli) - 1,
                                        "Introdu id-ul cheltuielii pe care doresti sa o modifici: ");

                // introduc noua suma si noul tip
                int suma_noua = citire_suma_cheltuiala("Introdu noua suma: ");
                char *tip_cheltuiala_nou = citire_tip_cheltuiala("Introdu noul tip: ");

                storage_cheltuieli = modifica_cheltuiala_existenta(storage_cheltuieli, id_ales,
                                                                   suma_noua, tip_cheltuiala_nou);
                print_mesaj("Cheltuiala modificata cu succes!\n");
            }
            else
                print_mesaj("Nu exista suficiente inregistrari!\n");
        }
        else if(command == 3) {
            if(get_nr_cheltuieli(storage_cheltuieli) > 0) {
                // afisez lista
                print_cheltuieli(storage_cheltuieli);

                // aleg id
                int id_ales = citire_id(get_nr_cheltuieli(storage_cheltuieli) - 1,
                                        "Introdu id-ul cheltuielii pe care doresti sa o stergi: ");

                storage_cheltuieli = sterge_cheltuiala_din_storage(storage_cheltuieli, id_ales);
                print_mesaj("Cheltuiala stearsa cu succes!\n");
            }
            else
                print_mesaj("Nu exista suficiente inregistrari!\n");
        }
        else if(command == 4) {
            if(get_nr_cheltuieli(storage_cheltuieli) > 0) {
                show_filter_menu();

                int filter_command = citire_comanda(2, "Alege tipul de filtrare: ");
                if(filter_command == 1) {
                    // dupa suma
                    afisare_cheltuieli_filtrat_suma(storage_cheltuieli);
                }
                else{
                    // dupa tip
                    afisare_cheltuieli_filtrat_tip(storage_cheltuieli);
                }
            }
            else
                print_mesaj("Nu exista suficiente inregistrari!\n");
        }
        else if(command == 5) {
            if(get_nr_cheltuieli(storage_cheltuieli) > 0) {
                show_ordonated_menu();

                int sort_command = citire_comanda(2, "Alege tipul de sortare: ");
                if(sort_command == 1) {
                    // dupa suma
                    show_ordonated_menu_for_sum();

                    int sum_command = citire_comanda(2, "Alege cum doresti sa faci sortarea: ");
                    if(sum_command == 1) {
                        // crescator
                        storage_cheltuieli = sortare(storage_cheltuieli, comparare_suma_mai_mare);
                    }
                    else{
                        //descrescator
                        storage_cheltuieli = sortare(storage_cheltuieli, comparare_suma_mai_mic);
                    }
                }
                else {
                    // dupa tip
                    show_ordonated_menu_for_type();

                    int type_command = citire_comanda(2, "Alege cum doresti sa faci sortarea: ");
                    if(type_command == 1) {
                        // crescator (alfabetic)
                        storage_cheltuieli = sortare(storage_cheltuieli, comparare_tipuri_mai_mare);
                    }
                    else {
                        // descrescator
                        storage_cheltuieli = sortare(storage_cheltuieli, comparare_tipuri_mai_mic);
                    }
                }

                print_cheltuieli(storage_cheltuieli);

                // revenire sortat dupa id
                storage_cheltuieli = sortare(storage_cheltuieli, comparare_id_crescator);
            }
            else
                print_mesaj("Nu exista inregistrari facute!\n");

        }
        else {
            // dealocare de memorie
            destroy_repository(storage_cheltuieli);

            // inchidere aplicatie
            return;
        }
    }
}

int main() {
    run_app_tests();
    run_app();
    return 0;
}
