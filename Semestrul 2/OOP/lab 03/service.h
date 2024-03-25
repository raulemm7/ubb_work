//
// Created by raulo on 3/21/2024.
//

#ifndef LAB03_SERVICE_H
#define LAB03_SERVICE_H

#include <string.h>
#include "validator.h"
#include "repository.h"
#include "ui.h"

/*
 * adauga o noua cheltuiala la un storage
 * storage: locul unde se va adauga cheltuiala
 * id_cheltuiala, numar_apartament, suma_cheltuiala,
 * tip_cheltuiala: informatii despre noua cheltuiala
 */
Repo adauga_o_noua_cheltuiala(Repo storage, int id_cheltuiala, int numar_apartament, int suma_cheltuiala,
                              char* tip_cheltuiala);

/*
 * modifica o cheltuiala
 * storage: lista cu cheltuieli
 * id_ales: id-ul cheltuielii care va suferi modificari
 * suma_noua, tip_cheltuiala_nou: informatii noi despre cheltuiala
 */
Repo modifica_cheltuiala_existenta(Repo storage, int id_ales, int suma_noua,
                                   char *tip_cheltuiala_nou);

/*
 * sterge o cheltuiala de pe o pozitie
 * storage: lista cu cheltuieli
 * id_ales: id-ul cheltuielii care se va sterge
 */
Repo sterge_cheltuiala_din_storage(Repo storage, int id_ales);

/* tests */
void run_service_tests();
void test_adaugare();
void test_modificare();
void test_stergere();

#endif //LAB03_SERVICE_H
