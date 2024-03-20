//
// Created by raulo on 3/13/2024.
//

#ifndef LAB02_SERVICE_H
#define LAB02_SERVICE_H

#include <string.h>
#include "domain.h"
#include "ui.h"
#include "repository.h"

/*
 * adauga o cheltuiala la finalul listei de cheltuieli
 */
Repo adauga_cheltuiala(Repo storage, cheltuiala new_cheltuiala);

/*
 * sterge o cheltuiala existenta cu un anumit id
 */
Repo sterge_cheltuiala(Repo storage, int id_cheltuiala);

/*
 * functiile de mai jos sunt functii care
 * opereaza cu scrierea in consola
 */

// functii de test
void run_all_tests_service();
void test_adauga_cheltuiala_serv();
void test_sterge_cheltuiala_serv();

#endif //LAB02_SERVICE_H
