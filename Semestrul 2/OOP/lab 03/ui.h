@ -0,0 +1,84 @@
//
// Created by raulo on 3/21/2024.
//

#ifndef LAB03_UI_H
#define LAB03_UI_H

#include <stdio.h>
#include <stdlib.h>
#include "validator.h"

/*
 * Afiseaza meniul aplicatiei
 */
void menu();

void show_filter_menu();

/*
 * afiseaza meniul pentru functionalitatea de afisare ordonata
 */
void show_ordonated_menu();

/*
 * afiseaza meniul pentru functionalitatea de afisare ordonata
 * in functie de suma unei cheltuieli
 */
void show_ordonated_menu_for_sum();

/*
 * afiseaza meniul pentru functionalitatea de afisare ordonata
 * in functie de tipul unei cheltuieli
 */
void show_ordonated_menu_for_type();

/*
 * Afiseaza un mesaj
 */
void print_mesaj(char *mesaj);

/*
 * afiseaza pe ecran o cheltuiala formatat
 */
void print_o_cheltuiala(cheltuiala chelt);

/*
 * afiseaza o lista de cheltuieli pe ecran
 */
void print_cheltuieli(Repo storage);

/*
 * Citeste de la tastatura o comanda
 * MAX_COMMAND = nr maxim al unei comenzi care poate fi aleasa a fi executata
 */
int citire_comanda(int MAX_COMMAND, char *mesaj);

/*
 * citeste id de la tastatura
 * MAX_ID = nr maxim ce poate fi citit de la tastatura
 */
int citire_id(int MAX_ID, char *mesaj);

/*
 * citeste de la tastatura numarul apartamentului unei cheltuieli
 */
int citire_nr_apartament(char *mesaj);

/*
 * citeste de la tastatura suma unei cheltuieli
 */
int citire_suma_cheltuiala(char *mesaj);

/*
 * citeste de la tastatura tipul unei cheltuieli
 */
char* citire_tip_cheltuiala(char *mesaj);

char citire_operator(char *mesaj);

void afisare_cheltuieli_filtrat_tip(Repo storage);

void afisare_cheltuieli_filtrat_suma(Repo storage);

#endif //LAB03_UI_H
