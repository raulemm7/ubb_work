//
// Created by raulo on 3/13/2024.
//

#ifndef LAB02_REPOSITORY_H
#define LAB02_REPOSITORY_H

#include "domain.h"
#include <assert.h>

typedef struct {
    cheltuiala lista_cheltuieli[1024];
    int nr_cheltuieli;
}Repo;

/*
 * creeaza o variabila de tip Repo
 */
Repo creeare_repo();

/*
 * adauga o noua cheltuiala la finalul listei de cheltuieli
 */
Repo append_cheltuiala(Repo storage, cheltuiala chelt);

/*
 * returneaza cheltuiala de pe o pozitie specifica
 * din lista de cheltuieli
 */
cheltuiala get_cheltuiala(Repo storage, int id_cheltuiala);

/*
 * retine o cheltuiala pe o pozitie specifica in lista de cheltuieli
 */
Repo set_cheltuiala(Repo storage, int id_cheltuiala, cheltuiala chelt);

/*
 * returneaza numarul total de cheltuieli inregistrate
 */
int get_nr_cheltuieli(Repo storage);

/*
 * sterge o cheltuiala de pe o pozitie specificata
 */
Repo delete_cheltuiala(Repo storage, int id_cheltuiala);

/*
 * functie de test
 */
void run_repo_all_tests();

/*
 * functie de test
 */
void test_create_repo();

/*
 * functie de test
 */
void test_adauga_cheltuiala();

/*
 * functie de test
 */
void test_set_cheltuiala();

/*
 * functie de test
 */
void test_delete_cheltuiala();

#endif //LAB02_REPOSITORY_H
