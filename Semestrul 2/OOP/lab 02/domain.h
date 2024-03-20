//
// Created by raulo on 3/12/2024.
//

#ifndef LAB02_DOMAIN_H
#define LAB02_DOMAIN_H

#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int id;
    int numar_apartament;
    int suma;
    char tip_cheltuiala[20];
}cheltuiala;

/*
 * functie ce creeaza un element de tip cheltuiala
 */
cheltuiala create_cheltuiala(int id, int nr_apartament, int suma, char tip_cheltuiala[]);

/*
 * functie care modifica suma si tipul unei cheltuieli
 */
cheltuiala modify_cheltuiala(cheltuiala chelt, int new_suma, char new_tip[20]);

/*
 * functie ce returneaza id-ul unei cheltuieli
 */
int get_id(cheltuiala chelt);

/*
 * functie ce returneaza suma unei cheltuieli
 */
int get_suma_cheltuiala(cheltuiala chelt);

/*
 * functie ce returneaza tipul unei cheltuieli
 */
char* get_tip_cheltuiala(cheltuiala chelt);

/*
 * functie ce returneaza nr apartamentului pt care s-a inregistrat cheltuiala
 */
int get_nr_apartament(cheltuiala chelt);

/*
 * setter
 */
cheltuiala set_id(cheltuiala chelt, int id);

/*
 * functie de test
 */
void test_create_and_get_cheltuiala();

/*
 * functie de test
 */
void test_modify_cheltuiala();

/*
 * functie de test
 */
void test_delete_cheltuiala();

#endif //LAB02_DOMAIN_H