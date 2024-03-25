//
// Created by raulo on 3/21/2024.
//

#include "validator.h"

int validare_tip(char *tip) {
    if(strcmp(tip, "apa") == 0)
        return 1;
    if(strcmp(tip, "gaz") == 0)
        return 1;
    if(strcmp(tip, "curent") == 0)
        return 1;
    if(strcmp(tip, "incalzire") == 0)
        return 1;
    if(strcmp(tip, "canal") == 0)
        return 1;
    if(strcmp(tip, "internet") == 0)
        return 1;

    return 0;
}

int validare_cheltuiala_existenta(Repo* storage, int numar_ap, int suma_chelt, char *tip_chelt) {
    for(int i = 0; i < get_nr_cheltuieli(storage); i++) {
        cheltuiala chelt = get_cheltuiala_by_id(storage, i);

        char *tip_chelt_curenta = get_tip_cheltuiala(chelt);
        if(numar_ap == get_numar_apartament(chelt) &&
           suma_chelt == get_suma_cheltuiala(chelt) &&
           strcmp(tip_chelt, tip_chelt_curenta) == 0) {
            free(tip_chelt_curenta);
            return 0;
        }
        free(tip_chelt_curenta);
    }
    return 1;
}

int comparare_suma_mai_mare(cheltuiala chelt1, cheltuiala chelt2) {
    return (get_suma_cheltuiala(chelt1) > get_suma_cheltuiala(chelt2));
}

int comparare_suma_mai_mic(cheltuiala chelt1, cheltuiala chelt2) {
    return (get_suma_cheltuiala(chelt1) < get_suma_cheltuiala(chelt2));
}

int comparare_tipuri_mai_mare(cheltuiala chelt1, cheltuiala chelt2) {
    char *tip_chelt_1 = get_tip_cheltuiala(chelt1);
    char *tip_chelt_2 = get_tip_cheltuiala(chelt2);

    if(strcmp(tip_chelt_1, tip_chelt_2) > 0) {
        free(tip_chelt_1);
        free(tip_chelt_2);

        return 1;
    }
    free(tip_chelt_1);
    free(tip_chelt_2);
    return 0;
}

int comparare_tipuri_mai_mic(cheltuiala chelt1, cheltuiala chelt2) {
    char *tip_chelt_1 = get_tip_cheltuiala(chelt1);
    char *tip_chelt_2 = get_tip_cheltuiala(chelt2);

    if(strcmp(tip_chelt_1, tip_chelt_2) < 0) {
        free(tip_chelt_1);
        free(tip_chelt_2);

        return 1;
    }
    free(tip_chelt_1);
    free(tip_chelt_2);
    return 0;
}

int comparare_id_crescator(cheltuiala chelt1, cheltuiala chelt2) {
    return get_id_cheltuiala(chelt1) > get_id_cheltuiala(chelt2);
}

// functii de test
void run_validator_tests() {
    test_validare_tip();
    test_validare_cheltuiala_existenta();
    test_comparari();
}

void test_validare_tip() {
    assert(validare_tip("dadad") == 0);
    assert(validare_tip("internet") == 1);
    assert(validare_tip("gaz") == 1);
    assert(validare_tip("apa") == 1);
    assert(validare_tip("curent") == 1);
    assert(validare_tip("incalzire") == 1);
    assert(validare_tip("canal") == 1);
    assert(validare_tip("ceva") == 0);
}

void test_validare_cheltuiala_existenta() {
    Repo* storage = creeaza_repository();

    char *tip = (char*)malloc(sizeof(char) * 32);
    strcpy(tip, "apa");
    cheltuiala chelt = create_cheltuiala(0, 12, 250, tip);

    storage = adauga_cheltuiala_la_storage(storage, chelt);

    char *new_tip = (char*)malloc(sizeof(char) * 32);
    strcpy(new_tip, "apa");
    assert(validare_cheltuiala_existenta(storage, 12, 250, new_tip) == 0);
    assert(validare_cheltuiala_existenta(storage, 21, 342, new_tip) == 1);
    free(new_tip);

    destroy_repository(storage);
}

void test_comparari() {
    char *tip1 = (char*)malloc(sizeof(char) * 32);
    strcpy(tip1, "apa");
    cheltuiala chelt1 = create_cheltuiala(0, 12, 250, tip1);

    char *tip2 = (char*)malloc(sizeof(char) * 32);
    strcpy(tip2, "internet");
    cheltuiala chelt2 = create_cheltuiala(1, 23, 360, tip2);

    assert(comparare_suma_mai_mare(chelt1, chelt2) == 0);
    assert(comparare_suma_mai_mic(chelt1, chelt2) == 1);

    assert(comparare_tipuri_mai_mare(chelt1, chelt2) == 0);
    assert(comparare_tipuri_mai_mic(chelt1, chelt2) == 1);

    assert(comparare_id_crescator(chelt1, chelt2) == 0);

    destroy_cheltuiala(chelt1);
    destroy_cheltuiala(chelt2);

    char *tip3 = (char*)malloc(sizeof(char) * 32);
    strcpy(tip3, "internet");
    cheltuiala chelt3 = create_cheltuiala(0, 12, 360, tip3);

    char *tip4 = (char*)malloc(sizeof(char) * 32);
    strcpy(tip4, "apa");
    cheltuiala chelt4 = create_cheltuiala(1, 12, 250, tip4);

    assert(comparare_suma_mai_mare(chelt3, chelt4) == 1);
    assert(comparare_suma_mai_mic(chelt3, chelt4) == 0);

    assert(comparare_tipuri_mai_mare(chelt3, chelt4) == 1);
    assert(comparare_tipuri_mai_mic(chelt3, chelt4) == 0);

    assert(comparare_id_crescator(chelt4, chelt3) == 1);

    destroy_cheltuiala(chelt3);
    destroy_cheltuiala(chelt4);
}