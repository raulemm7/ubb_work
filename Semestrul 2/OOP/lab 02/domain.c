//
// Created by raulo on 3/12/2024.
//

#include "domain.h"

cheltuiala create_cheltuiala(int id, int nr_apartament, int suma, char tip_cheltuiala[]) {
    cheltuiala new_cheltuiala;
    new_cheltuiala.id = id;
    new_cheltuiala.numar_apartament = nr_apartament;
    new_cheltuiala.suma = suma;
    strcpy(new_cheltuiala.tip_cheltuiala, tip_cheltuiala);

    return new_cheltuiala;
}

cheltuiala modify_cheltuiala(cheltuiala chelt, int new_suma, char new_tip[20]) {
    chelt.suma = new_suma;
    strcpy(chelt.tip_cheltuiala, new_tip);
    return chelt;
}

int get_id(cheltuiala chelt) {
    return chelt.id;
}

int get_suma_cheltuiala(cheltuiala chelt) {
    return chelt.suma;
}

char* get_tip_cheltuiala(cheltuiala chelt) {
    char *p = (char*)malloc(sizeof(char) * 32);
    strcpy(p, chelt.tip_cheltuiala);
    return p;
}

int get_nr_apartament(cheltuiala chelt) {
    return chelt.numar_apartament;
}

cheltuiala set_id(cheltuiala chelt, int id) {
    chelt.id = id;
    return chelt;
}

// functii de test
void test_create_and_get_cheltuiala() {
    cheltuiala chelt = create_cheltuiala(0, 12, 1200, "internet");

    assert(get_id(chelt) == 0);
    assert(get_nr_apartament(chelt) == 12);
    assert(get_suma_cheltuiala(chelt) == 1200);
    assert(strcmp(get_tip_cheltuiala(chelt), "internet") == 0);
}

void test_modify_cheltuiala() {
    cheltuiala chelt = create_cheltuiala(0, 12, 1200, "internet");
    chelt = modify_cheltuiala(chelt, 3400, "gaz");

    assert(get_suma_cheltuiala(chelt) == 3400);
    assert(strcmp(get_tip_cheltuiala(chelt), "gaz") == 0);
}