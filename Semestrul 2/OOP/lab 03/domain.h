//
// Created by raulo on 3/21/2024.
//

#ifndef LAB03_DOMAIN_H
#define LAB03_DOMAIN_H

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "stdio.h"

typedef struct {
    int id_cheltuiala;
    int nr_apartament;
    int suma_cheltuiala;
    char *tip_cheltuiala;
}cheltuiala;

/*
 * creeaza o noua cheltuiala
 * id_chelt = id-ul cheltuielii
 * nr_ap = numarul apartamentului
 * suma_chelt = suma cheltuielii
 * tip_chelt = pointer catre tipul cheltuielii
 */
cheltuiala* create_cheltuiala(int id_chelt, int nr_ap, int suma_chelt, char *tip_chelt);

/*
 * dealocheaza memoria folosita de o cheltuiala
 */
void destroy_cheltuiala(cheltuiala* chelt);

/*
 * copiaza intr o noua cheltuiala o cheltuiala deja inregistrata
 * si o returneaza
 */
cheltuiala* copiaza_noua_cheltuiala(cheltuiala* chelt);

/* getters */
int get_id_cheltuiala(cheltuiala* chelt);
int get_numar_apartament(cheltuiala* chelt);
int get_suma_cheltuiala(cheltuiala* chelt);
char* get_tip_cheltuiala(cheltuiala* chelt);

/*
 * modifica informatiile unei cheltuieli
 * chelt: cheltuiala care se doreste a fi modificata
 * new_suma, new_tip_cheltuiala: noi informatii
 */
cheltuiala* modifica_informatii_cheltuiala(cheltuiala* chelt, int new_suma, char *new_tip_cheltuiala);

/* teste */
void run_domain_tests();
void test_create_and_getters_cheltuiala();
void test_modifica_informatii_cheltuiala();
void test_copiaza_cheltuiala();

#endif //LAB03_DOMAIN_H
