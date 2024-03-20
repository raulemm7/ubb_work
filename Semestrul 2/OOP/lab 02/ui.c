//
// Created by raulo on 3/13/2024.
//
#include "ui.h"


void show_menu() {
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

void print_mesage(char mesaj[]) {
    printf("%s", mesaj);
}

void print_o_cheltuiala(cheltuiala chelt) {
    printf("ID: %d; ap: %d, suma: %d, tip: %s\n",
           get_id(chelt),
           get_nr_apartament(chelt),
           get_suma_cheltuiala(chelt),
           get_tip_cheltuiala(chelt));
}

void print_cheltuieli(Repo storage) {
    for(int i = 0; i < get_nr_cheltuieli(storage); i++) {
        cheltuiala chelt = get_cheltuiala(storage, i);
        print_o_cheltuiala(chelt);
    }
}

int read_command(int MAX_COMMAND) {
    while(1) {
        int command;
        printf("Introdu o comanda: ");
        scanf("%d", &command);

        if(0 < command && command <= MAX_COMMAND)
            return command;

        printf("Ai introdus o comanda gresita!");
    }
}

int citire_nr_apartament() {
    int numar;
    printf("Introdu numarul apartamentului: ");
    scanf("%d", &numar);
    return numar;
}

int citire_suma_cheltuiala() {
    int suma;
    printf("Introdu suma cheltuielii: ");
    scanf("%d", &suma);
    return suma;
}

char* citire_tip_cheltuiala() {
    while(1) {
        char *tip = (char*) malloc(sizeof(char) * 32);
        printf("Introdu tipul cheltuielii: ");
        scanf("%s", tip);

        if(validare_tip(tip) == 1)
            return tip;

        printf("Introdu un tip corect pentru cheltuiala!");
    }
}

int citire_id(int MAX_ID, char msg[]) {
    while(1) {
        int id;
        printf("%s", msg);
        scanf("%d", &id);

        if(0 <= id && id <= MAX_ID)
            return id;

        printf("Ai introdus un id gresit! ");
    }
}

int citire_suma_noua() {
    int suma;
    printf("Introdu noua suma a cheltuielii: ");
    scanf("%d", &suma);
    return suma;
}

char* citire_tip_nou() {
    while(1) {
        char *tip = (char*) malloc(sizeof(char) * 32);
        printf("Introdu noul tip al cheltuielii: ");
        scanf("%s", tip);

        if(validare_tip(tip) == 1)
            return tip;

        printf("Introdu un tip corect pentru cheltuiala!");
    }
}

char citire_operator() {
    char operatori_posibili[3] = {'<', '=', '>'};
    while(1) {
        printf("Introduceti operatorul de comparare:");
        char operator_citire;
        scanf(" %c", &operator_citire);

        for(int i = 0; i < 3; i++)
            if(operator_citire == operatori_posibili[i])
                return operator_citire;
    }
}

// functii
cheltuiala make_new_cheltuiala(int id) {
    int nr_apartament = citire_nr_apartament();
    int suma_cheltuiala = citire_suma_cheltuiala();
    char* tip = citire_tip_cheltuiala();
    char tip_cheltuiala[32];
    strcpy(tip_cheltuiala, tip);
    free(tip);

    cheltuiala chelt = create_cheltuiala(id + 1, nr_apartament, suma_cheltuiala, tip_cheltuiala);
    return chelt;
}

Repo modifica_cheltuiala(Repo storage, int id_cheltuiala) {
    // preiau cheltuiala cu id_cheltuiala
    cheltuiala chelt = get_cheltuiala(storage, id_cheltuiala);

    // introduc suma noua
    int new_suma = citire_suma_noua();

    // introduc noul tip
    char new_tip_array[32];
    char *new_tip = citire_tip_nou();
    strcpy(new_tip_array, new_tip);
    free(new_tip);

    cheltuiala new_chelt = create_cheltuiala(get_id(chelt), get_nr_apartament(chelt), new_suma, new_tip_array);
    if(validare_cheltuiala(storage, new_chelt)) {
        // modific cheltuiala
        chelt = modify_cheltuiala(chelt, new_suma, new_tip_array);

        // modific in lista de cheltuieli cheltuiala modificata
        storage = set_cheltuiala(storage, id_cheltuiala, chelt);
        return storage;
    }
    else
        print_mesage("Aceasta cheltuiala exista deja!\n");

    return storage;
}

void filtrare_suma(Repo storage, char operator, int suma) {
    int i;
    switch (operator) {
        case '=': {
            int ok = 0;
            for(i = 0; i < get_nr_cheltuieli(storage); i++) {
                cheltuiala chelt = get_cheltuiala(storage, i);
                if(get_suma_cheltuiala(chelt) == suma) {
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
                cheltuiala chelt = get_cheltuiala(storage, i);
                if(get_suma_cheltuiala(chelt) > suma) {
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
                cheltuiala chelt = get_cheltuiala(storage, i);
                if(get_suma_cheltuiala(chelt) < suma) {
                    print_o_cheltuiala(chelt);
                    ok += 1;
                }
            }

            if(!ok)
                printf("Nu exista cheltuieli care sa satisfaca conditiile!\n");

            return;
        }
    }
}

void filtrare_tip_cheltuiala(Repo storage, char *tip_filtrare) {
    int ok = 0;

    for(int i = 0; i < get_nr_cheltuieli(storage); i++) {
        cheltuiala chelt = get_cheltuiala(storage, i);
        char *tip_cheltuiala = get_tip_cheltuiala(chelt);

        if(strcmp(tip_cheltuiala, tip_filtrare) == 0) {
            print_o_cheltuiala(chelt);
            ok += 1;
        }

        free(tip_cheltuiala);
    }

    if(!ok)
        print_mesage("Nu exista cheltuieli inregistrate cu acest tip!\n");
}

void print_cheltuieli_suma_crescator(Repo storage) {
    Repo tmp_storage;
    tmp_storage = storage;

    // sortare crescatoare dupa suma
    for(int i = 0; i < get_nr_cheltuieli(tmp_storage) - 1; i++) {
        for(int j = i + 1; j < get_nr_cheltuieli(tmp_storage); j++) {
            cheltuiala chelt_i = get_cheltuiala(tmp_storage, i);
            cheltuiala chelt_j = get_cheltuiala(tmp_storage, j);

            if(get_suma_cheltuiala(chelt_i) > get_suma_cheltuiala(chelt_j)) {
                printf("swap");
                tmp_storage = set_cheltuiala(tmp_storage, i, chelt_j);
                tmp_storage = set_cheltuiala(tmp_storage, j, chelt_i);
            }
        }
    }

    // printam lista de cheltuieli dupa sortare
    print_cheltuieli(tmp_storage);
}

void print_cheltuieli_suma_descrescator(Repo storage) {
    Repo tmp_storage;
    tmp_storage = storage;

    // sortare descrescatoare dupa suma
    for(int i = 0; i < get_nr_cheltuieli(tmp_storage) - 1; i++) {
        for(int j = i + 1; j < get_nr_cheltuieli(tmp_storage); j++) {
            cheltuiala chelt_i = get_cheltuiala(tmp_storage, i);
            cheltuiala chelt_j = get_cheltuiala(tmp_storage, j);

            if(get_suma_cheltuiala(chelt_i) < get_suma_cheltuiala(chelt_j)) {
                tmp_storage = set_cheltuiala(tmp_storage, i, chelt_j);
                tmp_storage = set_cheltuiala(tmp_storage, j, chelt_i);
            }
        }
    }

    // printam lista de cheltuieli dupa sortare
    print_cheltuieli(tmp_storage);
}

void print_cheltuieli_tip_alfabetic(Repo storage) {
    Repo tmp_storage;
    tmp_storage = storage;

    // sortare crescatoare dupa tip
    for(int i = 0; i < get_nr_cheltuieli(tmp_storage) - 1; i++) {
        for(int j = i + 1; j < get_nr_cheltuieli(tmp_storage); j++) {
            cheltuiala chelt_i = get_cheltuiala(tmp_storage, i);
            cheltuiala chelt_j = get_cheltuiala(tmp_storage, j);

            char *tip_chelt_i = get_tip_cheltuiala(chelt_i);
            char *tip_chelt_j = get_tip_cheltuiala(chelt_j);

            if(strcmp(tip_chelt_i, tip_chelt_j) > 0) {
                tmp_storage = set_cheltuiala(tmp_storage, i, chelt_j);
                tmp_storage = set_cheltuiala(tmp_storage, j, chelt_i);
            }

            free(tip_chelt_i);
            free(tip_chelt_j);
        }
    }

    // printam lista de cheltuieli dupa sortare
    print_cheltuieli(tmp_storage);
}

void print_cheltuiel_tip_alfabetic_invers(Repo storage) {
    Repo tmp_storage;
    tmp_storage = storage;

    // sortare descrescatoare dupa tip
    for(int i = 0; i < get_nr_cheltuieli(tmp_storage) - 1; i++) {
        for(int j = i + 1; j < get_nr_cheltuieli(tmp_storage); j++) {
            cheltuiala chelt_i = get_cheltuiala(tmp_storage, i);
            cheltuiala chelt_j = get_cheltuiala(tmp_storage, j);

            char *tip_chelt_i = get_tip_cheltuiala(chelt_i);
            char *tip_chelt_j = get_tip_cheltuiala(chelt_j);

            if(strcmp(tip_chelt_i, tip_chelt_j) < 0) {
                tmp_storage = set_cheltuiala(tmp_storage, i, chelt_j);
                tmp_storage = set_cheltuiala(tmp_storage, j, chelt_i);
            }

            free(tip_chelt_i);
            free(tip_chelt_j);
        }
    }

    // printam lista de cheltuieli dupa sortare
    print_cheltuieli(tmp_storage);
}