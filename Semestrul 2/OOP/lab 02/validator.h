//
// Created by raulo on 3/13/2024.
//

#ifndef LAB02_VALIDATOR_H
#define LAB02_VALIDATOR_H

#include <string.h>
#include "repository.h"
#include "domain.h"

/*
 * verifica daca un anumit tip de cheltuiala
 * este unul corect
 */
int validare_tip(char *tip);

/*
 * verifica daca o cheltuiala exista deja
 * inregistrata in lista de cheltuieli
 */
int validare_cheltuiala(Repo storage, cheltuiala chelt);

/*
 * functie de test
 */
void run_validator_tests();

/*
 * functie de test
 */
void test_validare_tip();

/*
 * functie de test
 */
void test_validare_cheltuiala();

#endif //LAB02_VALIDATOR_H
