@ -0,0 +1,72 @@
//
// Created by raulo on 3/21/2024.
//

#ifndef LAB03_REPOSITORY_H
#define LAB03_REPOSITORY_H

#include "domain.h"

typedef struct {
    cheltuiala *lista_cheltuieli;
    int nr_cheltuieli;
    int capacitate_maxima;
}Repo;

/*
 * creeaza si returneaza un repo
 */
Repo creeaza_repository();

/*
 * dealocheaza memoria utilizata de un storage
 */
void destroy_repository(Repo storage);

/*
 * realocheaza (adauga) memorie unui storage
 */
Repo realocare_memorie(Repo storage);

/* getters */
cheltuiala get_cheltuiala_by_id(Repo storage, int id_cheltuiala);
int get_nr_cheltuieli(Repo storage);
int get_capacitate_maxima(Repo storage);

/*
 * adauga o cheltuiala la finalul listei de cheltuieli
 * storage: lista cu cheltuieli
 * chelt: cheltuiala care se adauga
 */
Repo adauga_cheltuiala_la_storage(Repo storage, cheltuiala chelt);

/*
 * pune pe o pozitie precizata o cheltuiala in lista de cheltuieli
 * storage: lista de cheltuieli
 * chelt: cheltuiala care se va aloca
 * id_position: pozitia pe care se va aloca
 */
Repo set_cheltuiala_pe_pozitie(Repo storage, cheltuiala chelt, int id_position);

/*
 * sterge o cheltuiala din lista de cheltuieli
 * storage: lista de cheltuieloi
 * id_position: pozitia cheltuielii care se doreste a fi stearsa
 */
Repo delete_cheltuiala(Repo storage, int id_position);

/*
 * copiaza un repo vechi si returneaza unul
 * nou, avand aceleasi informatii
 */
Repo copiaza_repo(Repo new_storage, Repo storage);

/* teste */
void run_repository_tests();
void test_storage_operations();
void test_realocare_memorie();
void test_set_cheltuiala_pe_pozitie();
void test_delete_cheltuiala();
void test_copiaza_repo();

#endif //LAB03_REPOSITORY_H
