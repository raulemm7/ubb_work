//
// Created by Titieni Paul on 11.03.2024.
//

#ifndef LAB2_4_UI_H
#define LAB2_4_UI_H


#include "../domain/domain.h"
#include "../repo/store.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

/*
* Functia de afisare al meniului
*/
void print_m();

/*
* Afiseaza starea listei undo
*/
void void_afisare_undo(Lista* undo);

/*
* Afiseaza informatiile unui produs
*/
void afisare_produse(Lista* list);

/*
* Citirea informatiilor unui produs si adaugarea acestuia in lista de produse
*/
void adaugare_produs_ui(Lista* list, Lista* undo);

/*
* Actualizarea informatiilor unui produs
*/
void actualizare_produs_ui(Lista* list, Lista* undo);

/*
* Citirea informatiilor unui produs care se doreste a fi sters
*/
void sterge_produs_ui(Lista* list, Lista* undo);

/*
* Citirea informatiilor despre sortare
*/
void sortare_ui(Lista* list);

/*
* Citirea informatiilor despre filtrare
*/
void filtrare_ui(Lista* list);

/*
* Executarea undo-ului
*/
void do_undo(Lista** list, Lista* undo);

/*
* Adaugarea la lista de produse a unor produse
*/
void fastadd(Lista* list, Lista* undo);

/*
* executarea programului
*/
void start_program(Lista* list, Lista* undo);

#endif //LAB2_4_UI_H
