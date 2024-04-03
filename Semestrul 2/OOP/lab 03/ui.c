@ -0,0 +1,225 @@
//
// Created by raulo on 3/21/2024.
//

#include "ui.h"

void menu() {
    printf("1. Creeaza o noua cheltuiala;\n");
    printf("2. Modifica o cheltuiala existenta;\n");
    printf("3. Sterge o cheltuiala;\n");
    printf("4. Afiseaza lista de cheltuieli filtrata dupa un criteriu;\n");
    printf("5. Afiseaza lista de cheltuieli ordonata dupa un criteriu;\n");
    printf("6. Iesire din aplicatie;\n");
}

void show_filter_menu() {
    printf("1. Filtrare dupa suma;\n");
    printf("2. Filtrare dupa tip;\n");
}

void show_ordonated_menu() {
    printf("1. Afisare ordonata dupa suma;\n");
    printf("2. Afisare ordonata dupa tip;\n");
}

void show_ordonated_menu_for_sum() {
    printf("1. Afisare in ordine crescatoare;\n");
    printf("2. Afisare in ordine descrescatoare;\n");
}

void show_ordonated_menu_for_type() {
    printf("1. Afisare in ordine alfabetica;\n");
    printf("2. Afisare in ordine inversa alfabetica;\n");
}

void print_mesaj(char *mesaj) {
    printf("%s", mesaj);
}

void print_o_cheltuiala(cheltuiala chelt) {
    char *tip_cheltuiala = get_tip_cheltuiala(chelt);
    printf("ID: %d; ap: %d, suma: %d, tip: %s\n",
           get_id_cheltuiala(chelt),
           get_numar_apartament(chelt),
           get_suma_cheltuiala(chelt),
           tip_cheltuiala);
    free(tip_cheltuiala);
}

void print_cheltuieli(Repo storage) {
    for(int i = 0; i < get_nr_cheltuieli(storage); i++) {
        cheltuiala chelt = get_cheltuiala_by_id(storage, i);
        print_o_cheltuiala(chelt);
    }
}

int citire_comanda(int MAX_COMMAND, char *mesaj) {
    while(1) {
        int command;
        printf("%s", mesaj);
        if(scanf("%d", &command) > 0) {
            if(0 < command && command <= MAX_COMMAND)
                return command;

            printf("Ai introdus o comanda gresita!");
        }
        else {
            printf("Introdu o comanda! ");
        }
    }
}

int citire_id(int MAX_ID, char *mesaj) {
    while(1) {
        int id;
        printf("%s", mesaj);
        if(scanf("%d", &id) > 0) {
            if(0 <= id && id <= MAX_ID)
                return id;

            printf("Ai introdus un id gresit! ");
        }
        else {
            printf("Introdu un id! ");
        }
    }
}

int citire_nr_apartament(char *mesaj) {
    printf("%s", mesaj);

    int numar;
    while(1) {
        if(scanf("%d", &numar) > 0)
            return numar;
        else
            printf("Introdu un numar!");
    }
}

int citire_suma_cheltuiala(char *mesaj) {
    printf("%s", mesaj);

    int suma;
    while(1) {
        if(scanf("%d", &suma) > 0)
            return suma;
        else
            printf("Introdu o suma!");
    }
}

char* citire_tip_cheltuiala(char *mesaj) {
    while(1) {
        char *tip = (char*) malloc(sizeof(char) * 32);
        printf("%s", mesaj);
        if(scanf("%s", tip) > 0) {
            if(validare_tip(tip) == 1) {
                return tip;
            }

            printf("Introdu un tip corect pentru cheltuiala!");
        }
        else {
            printf("Introdu un tip!");
        }
    }
}

char citire_operator(char *mesaj) {
    char operatori_posibili[3] = {'<', '=', '>'};
    while(1) {
        printf("%s", mesaj);
        char operator_citire;
        if(scanf(" %c", &operator_citire) > 0) {
            for(int i = 0; i < 3; i++)
                if(operator_citire == operatori_posibili[i])
                    return operator_citire;
        }
        else {
            printf("Introdu un operator!");
        }
    }
}

void afisare_cheltuieli_filtrat_tip(Repo storage) {
    int bool_ok = 0;

    // citesc un tip
    char *tip_citit = citire_tip_cheltuiala("Introdu tipul dupa care doresti sa faci filtrarea: ");

    // fac filtrarea
    for(int i = 0; i < get_nr_cheltuieli(storage); i++) {
        cheltuiala chelt = get_cheltuiala_by_id(storage, i);

        char *tip_chelt = get_tip_cheltuiala(chelt);
        if(strcmp(tip_chelt, tip_citit) == 0) {
            bool_ok = 1;
            print_o_cheltuiala(chelt);
        }
        free(tip_chelt);
    }

    // eliberez memoria folosita
    free(tip_citit);

    if(bool_ok == 0)
        print_mesaj("Nu au fost gasite cheltuieli care sa satisfaca conditiile!\n");
}

void afisare_cheltuieli_filtrat_suma(Repo storage) {
    char operator = citire_operator("Citeste operatorul dupa care doresti sa faci filtrarea: ");
    int suma_citita = citire_suma_cheltuiala("Citeste suma dupa care doresti sa faci filtrarea: ");

    int i;
    switch (operator) {
        case '=': {
            int ok = 0;
            for(i = 0; i < get_nr_cheltuieli(storage); i++) {
                cheltuiala chelt = get_cheltuiala_by_id(storage, i);
                if(get_suma_cheltuiala(chelt) == suma_citita) {
                    print_o_cheltuiala(chelt);
                    ok += 1;
                }
            }

            if(!ok)
                printf("Nu exista cheltuieli care sa satisfaca conditiile!\n");

            return;
        }
        case '>': {
            int ok = 0;
            for(i = 0; i < get_nr_cheltuieli(storage); i++) {
                cheltuiala chelt = get_cheltuiala_by_id(storage, i);
                if(get_suma_cheltuiala(chelt) > suma_citita) {
                    print_o_cheltuiala(chelt);
                    ok += 1;
                }
            }

            if(!ok)
                printf("Nu exista cheltuieli care sa satisfaca conditiile!\n");

            return;
        }
        case '<': {
            int ok = 0;
            for(i = 0; i < get_nr_cheltuieli(storage); i++) {
                cheltuiala chelt = get_cheltuiala_by_id(storage, i);
                if(get_suma_cheltuiala(chelt) < suma_citita) {
                    print_o_cheltuiala(chelt);
                    ok += 1;
                }
            }

            if(!ok)
                printf("Nu exista cheltuieli care sa satisfaca conditiile!\n");

            return;
        }
        default:
            return;
    }
}
