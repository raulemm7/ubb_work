//
// Created by raulo on 3/13/2024.
//

#ifndef LAB02_UI_H
#define LAB02_UI_H

#include <stdlib.h>
#include <stdio.h>
#include "repository.h"
#include "validator.h"
#include "domain.h"

/*
 * afiseaza meniul aplicatiei
 */
void show_menu();

/*
 * afiseaza meniul pentru functionalitatea de filtrare
 */
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
 * afiseaza pe ecran un mesaj
 */
void print_mesage(char mesaj[]);

/*
 * afiseaza pe ecran o cheltuiala formatat
 */
void print_o_cheltuiala(cheltuiala chelt);

/*
 * afiseaza o lista de cheltuieli pe ecran
 */
void print_cheltuieli(Repo storage);

/*
 * citeste o comanda corecta in functie
 * de numarul total de comenzi specificat
 */
int read_command(int MAX_COMMAND);

/*
 * citeste de la tastatura numarul apartamentului unei cheltuieli
 */
int citire_nr_apartament();

/*
 * citeste de la tastatura suma unei cheltuieli
 */
int citire_suma_cheltuiala();

/*
 * citeste de la tastatura tipul unei cheltuieli
 */
char* citire_tip_cheltuiala();

/*
 * citeste de la tastatura un id in functie de numarul maxim
 * care poate fi citit
 */
int citire_id(int MAX_ID, char msg[]);

/*
 * citeste de la tastatura o noua suma a unei cheltuieli
 */
int citire_suma_noua();

/*
 * citeste de la tastatura un nou tip al unei cheltuieli
 */
char *citire_tip_nou();

/*
 * citeste de la tastatura un caracter
 * reprezentand un operator in functie de care
 * se va face afisarea ordonata
 */
char citire_operator();

/*
 * creeaza o noua cheltuiala
 */
cheltuiala make_new_cheltuiala(int id);

/*
 * modifica o cheltuiala existenta cu un anumit id
 */
Repo modifica_cheltuiala(Repo storage, int id_cheltuiala);

/*
 * filtreaza si afiseaza lista de cheltuieli
 * in functie de suma si de un criteriu de ordonare
 */
void filtrare_suma(Repo storage, char operator, int suma);

/*
 * filtreaza si afiseaza lista de cheltuieli
 * in functie de un tip specificat
 */
void filtrare_tip_cheltuiala(Repo storage, char tip[]);

/*
 * afiseaza ordonat crescator dupa suma
 * o lista de cheltuieli
 */
void print_cheltuieli_suma_crescator(Repo storage);

/*
 * afiseaza ordonat descrescator dupa suma
 * o lista de cheltuieli
 */
void print_cheltuieli_suma_descrescator(Repo storage);

/*
 * afiseaza ordonat crescator dupa tip
 * o lista de cheltuieli
 */
void print_cheltuieli_tip_alfabetic(Repo storage);

/*
 * afiseaza ordonat descrescator dupa tip
 * o lista de cheltuieli
 */
void print_cheltuiel_tip_alfabetic_invers(Repo storage);

#endif //LAB02_UI_H
