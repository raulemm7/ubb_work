//
// Created by raulo on 3/22/2024.
//
#include "sort.h"

Repo sortare(Repo tmp_storage, functie_cmp functie) {
    for(int i = 0; i < get_nr_cheltuieli(tmp_storage) - 1; i++) {
        for(int j = i + 1; j < get_nr_cheltuieli(tmp_storage); j++) {
            cheltuiala chelt_i = get_cheltuiala_by_id(tmp_storage, i);
            cheltuiala chelt_j = get_cheltuiala_by_id(tmp_storage, j);

            if(functie(chelt_i, chelt_j)) {
                tmp_storage = set_cheltuiala_pe_pozitie(tmp_storage, chelt_j, i);
                tmp_storage = set_cheltuiala_pe_pozitie(tmp_storage, chelt_i, j);
            }
        }
    }

    return tmp_storage;
}

void run_sort_test() {
    Repo storage = creeaza_repository();

    char *tip = (char*)malloc(sizeof(char) * 32);
    strcpy(tip, "internet");
    storage = adauga_o_noua_cheltuiala(storage, 0, 12, 360, tip);

    char *tip2 = (char*)malloc(sizeof(char) * 32);
    strcpy(tip2, "apa");
    storage = adauga_o_noua_cheltuiala(storage, 1, 13, 250, tip2);

    storage = sortare(storage, comparare_suma_mai_mare);

    cheltuiala chelt1 = get_cheltuiala_by_id(storage, 0);
    assert(get_id_cheltuiala(chelt1) == 1);
    assert(get_numar_apartament(chelt1) == 13);
    assert(get_suma_cheltuiala(chelt1) == 250);

    cheltuiala chelt2 = get_cheltuiala_by_id(storage, 1);
    assert(get_id_cheltuiala(chelt2) == 0);
    assert(get_numar_apartament(chelt2) == 12);
    assert(get_suma_cheltuiala(chelt2) == 360);

    //destroy_cheltuiala(chelt1);
    //destroy_cheltuiala(chelt2);

    destroy_repository(storage);
}