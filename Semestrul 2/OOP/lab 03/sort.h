//
// Created by raulo on 3/22/2024.
//

#ifndef LAB03_SORT_H
#define LAB03_SORT_H

#include "service.h"
#include "domain.h"
#include "repository.h"
#include "validator.h"

typedef int (*functie_cmp)(cheltuiala chelt1, cheltuiala chelt2);

/*
 * sorteaza o lista de cheltuieli in functie de un criteriu
 * tmp_storage: lista cu cheltuieli
 * functie: criteriul dupa care se face sortarea
 */
Repo sortare(Repo tmp_storage, functie_cmp functie);

/* test */
void run_sort_test();

#endif //LAB03_SORT_H
