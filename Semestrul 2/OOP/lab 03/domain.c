//
// Created by raulo on 3/21/2024.
//

#include "domain.h"

cheltuiala* create_cheltuiala(int id_chelt, int nr_ap, int suma_chelt, char *tip_chelt) {
    cheltuiala* chelt = (cheltuiala*)malloc(sizeof(cheltuiala));
    chelt->id_cheltuiala = id_chelt;
    chelt->nr_apartament = nr_ap;
    chelt->suma_cheltuiala = suma_chelt;

    chelt->tip_cheltuiala = (char*)malloc(sizeof(char) * 32);
    strcpy(chelt->tip_cheltuiala, tip_chelt);
    free(tip_chelt);

    return chelt;
}

void destroy_cheltuiala(cheltuiala* chelt) {
    chelt->id_cheltuiala = -1;
    chelt->nr_apartament = -1;
    chelt->suma_cheltuiala = -1;
    free(chelt->tip_cheltuiala);
    free(chelt);
}

cheltuiala* copiaza_noua_cheltuiala(cheltuiala* chelt) {
    cheltuiala* new_chelt = (cheltuiala*)malloc(sizeof(cheltuiala));
    new_chelt->id_cheltuiala = chelt->id_cheltuiala;
    new_chelt->nr_apartament = chelt->nr_apartament;
    new_chelt->suma_cheltuiala = chelt->suma_cheltuiala;

    new_chelt->tip_cheltuiala = (char*)malloc(sizeof(char) * 32);
    strcpy(new_chelt->tip_cheltuiala, chelt->tip_cheltuiala);

    return new_chelt;
}

int get_id_cheltuiala(cheltuiala* chelt) {
    return chelt->id_cheltuiala;
}

int get_numar_apartament(cheltuiala* chelt) {
    return chelt->nr_apartament;
}

int get_suma_cheltuiala(cheltuiala* chelt) {
    return chelt->suma_cheltuiala;
}

char* get_tip_cheltuiala(cheltuiala* chelt) {
    char *tip_chelt = (char*)malloc(sizeof(char) * 32);
    strcpy(tip_chelt, chelt->tip_cheltuiala);
    return tip_chelt;
}

cheltuiala* modifica_informatii_cheltuiala(cheltuiala* chelt, int new_suma, char *new_tip_cheltuiala) {
    chelt->suma_cheltuiala = new_suma;
    strcpy(chelt->tip_cheltuiala, new_tip_cheltuiala);
    return chelt;
}

void run_domain_tests() {
    test_create_and_getters_cheltuiala();
    test_modifica_informatii_cheltuiala();
    test_copiaza_cheltuiala();
}

void test_create_and_getters_cheltuiala() {
    char *tip = (char*)malloc(sizeof(char) * 32);
    strcpy(tip, "internet");
    cheltuiala* chelt = create_cheltuiala(0, 12, 250, tip);

    assert(get_id_cheltuiala(chelt) == 0);
    assert(get_numar_apartament(chelt) == 12);
    assert(get_suma_cheltuiala(chelt) == 250);
    char *tip_from_cheltuiala = get_tip_cheltuiala(chelt);
    assert(strcmp(tip_from_cheltuiala, "internet") == 0);
    free(tip_from_cheltuiala);

    destroy_cheltuiala(chelt);
}

void test_modifica_informatii_cheltuiala() {
    char *tip = (char*)malloc(sizeof(char) * 32);
    strcpy(tip, "internet");
    cheltuiala* chelt = create_cheltuiala(0, 12, 250, tip);

    char *tip_nou = (char*)malloc(sizeof(char) * 32);
    strcpy(tip_nou, "gaz");
    chelt = modifica_informatii_cheltuiala(chelt, 560, tip_nou);
    free(tip_nou);

    char* tip_from_cheltuiala = get_tip_cheltuiala(chelt);

    assert(get_suma_cheltuiala(chelt) == 560);
    assert(strcmp(tip_from_cheltuiala, "gaz") == 0);

    free(tip_from_cheltuiala);
    destroy_cheltuiala(chelt);
}

void test_copiaza_cheltuiala() {
    char *tip = (char*)malloc(sizeof(char) * 32);
    strcpy(tip, "internet");
    cheltuiala* chelt = create_cheltuiala(0, 12, 250, tip);

    cheltuiala* new_chelt = copiaza_noua_cheltuiala(chelt);

    assert(get_id_cheltuiala(new_chelt) == 0);
    assert(get_numar_apartament(new_chelt) == 12);
    assert(get_suma_cheltuiala(new_chelt) == 250);

    char *tip_chelt = get_tip_cheltuiala(new_chelt);
    assert(strcmp(tip_chelt, "internet") == 0);
    free(tip_chelt);

    destroy_cheltuiala(chelt);
    destroy_cheltuiala(new_chelt);
}

