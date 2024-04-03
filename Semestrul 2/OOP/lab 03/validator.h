@ -0,0 +1,37 @@
//
// Created by raulo on 3/21/2024.
//

#ifndef LAB03_VALIDATOR_H
#define LAB03_VALIDATOR_H

#include <string.h>
#include "repository.h"

/* valideaza un tip de cheltuiala
 * return: 1 (daca e un tip corect), 0 (altfel)
 * */
int validare_tip(char *tip);

/*
 * verifica daca o cheltuiala exista deja in storage
 * storage: lista cu cheltuieli
 * numar_ap, suma_chelt, tip_chelt: informatii care se vor verifica
 */
int validare_cheltuiala_existenta(Repo storage, int numar_ap, int suma_chelt, char *tip_chelt);

/* criterii de comparare */
int comparare_suma_mai_mare(cheltuiala chelt1, cheltuiala chelt2);
int comparare_suma_mai_mic(cheltuiala chelt1, cheltuiala chelt2);
int comparare_tipuri_mai_mare(cheltuiala chelt1, cheltuiala chelt2);
int comparare_tipuri_mai_mic(cheltuiala chelt1, cheltuiala chelt2);

/*
 * tests
 */
void run_validator_tests();
void test_validare_tip();
void test_validare_cheltuiala_existenta();
void test_comparari();

#endif //LAB03_VALIDATOR_H
