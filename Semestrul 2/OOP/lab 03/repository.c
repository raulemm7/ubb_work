@ -0,0 +1,201 @@
//
// Created by raulo on 3/21/2024.
//

#include "repository.h"

Repo creeaza_repository() {
    Repo repo_nou;
    repo_nou.capacitate_maxima = 1024;
    repo_nou.lista_cheltuieli = (cheltuiala*)calloc(repo_nou.capacitate_maxima, sizeof(cheltuiala));
    repo_nou.nr_cheltuieli = 0;

    return repo_nou;
}

void destroy_repository(Repo storage) {
    for(int i = 0; i < storage.nr_cheltuieli; i++) {
        destroy_cheltuiala(storage.lista_cheltuieli[i]);
    }

    free(storage.lista_cheltuieli);
    storage.capacitate_maxima = -1;
    storage.nr_cheltuieli = -1;
}

Repo realocare_memorie(Repo storage) {
    // actualizare capacitate
    int capacitate = get_capacitate_maxima(storage);
    capacitate += 256;

    // creare repo nou
    Repo auxiliary_repo;
    auxiliary_repo.capacitate_maxima = capacitate;
    auxiliary_repo.lista_cheltuieli = (cheltuiala*)calloc(capacitate, sizeof(cheltuiala));
    auxiliary_repo.nr_cheltuieli = storage.nr_cheltuieli;

    // copiere repo vechi in repo noi
    if(storage.nr_cheltuieli > 0)
        for(int i = 0; i < storage.nr_cheltuieli; i++) {
            cheltuiala chelt = get_cheltuiala_by_id(storage, i);
            adauga_cheltuiala_la_storage(auxiliary_repo, chelt);
        }

    // destroy repo vechi
    destroy_repository(storage);

    // return repo nou
    return auxiliary_repo;
}

cheltuiala get_cheltuiala_by_id(Repo storage, int id_cheltuiala) {
    cheltuiala chelt = storage.lista_cheltuieli[id_cheltuiala];
    return chelt;
}

int get_nr_cheltuieli(Repo storage) {
    return storage.nr_cheltuieli;
}

int get_capacitate_maxima(Repo storage) {
    return storage.capacitate_maxima;
}

Repo adauga_cheltuiala_la_storage(Repo storage, cheltuiala chelt) {
    storage.lista_cheltuieli[storage.nr_cheltuieli] = chelt;
    storage.nr_cheltuieli++;
    return storage;
}

Repo set_cheltuiala_pe_pozitie(Repo storage, cheltuiala chelt, int id_position) {
    storage.lista_cheltuieli[id_position] = chelt;
    return storage;
}

Repo delete_cheltuiala(Repo storage, int id_position) {
    for(int i = id_position; i < storage.nr_cheltuieli - 1; i++) {
        storage.lista_cheltuieli[i] = copiaza_cheltuiala_for_delete(storage.lista_cheltuieli[i],
                                                                    storage.lista_cheltuieli[i + 1]);
    }
    destroy_cheltuiala(storage.lista_cheltuieli[storage.nr_cheltuieli - 1]);
    storage.nr_cheltuieli -= 1;

    return storage;
}

Repo copiaza_repo(Repo new_storage, Repo storage) {
    new_storage.capacitate_maxima = storage.capacitate_maxima;
    new_storage.nr_cheltuieli = storage.nr_cheltuieli;

    for(int i = 0; i < storage.nr_cheltuieli; i++) {
        new_storage.lista_cheltuieli[i] = copiaza_noua_cheltuiala(storage.lista_cheltuieli[i]);
    }

    return new_storage;
}

void run_repository_tests() {
    test_storage_operations();
    test_realocare_memorie();
    test_set_cheltuiala_pe_pozitie();
    test_delete_cheltuiala();
    test_copiaza_repo();
}

void test_storage_operations() {
    Repo storage = creeaza_repository();

    assert(get_nr_cheltuieli(storage) == 0);
    assert(get_capacitate_maxima(storage) == 1024);

    char *tip = (char*)malloc(sizeof(char) * 32);
    strcpy(tip, "internet");
    cheltuiala chelt = create_cheltuiala(0, 12, 250, tip);

    storage = adauga_cheltuiala_la_storage(storage, chelt);
    cheltuiala chelt_storage = get_cheltuiala_by_id(storage, 0);

    assert(get_nr_cheltuieli(storage) == 1);
    assert(get_id_cheltuiala(chelt) == get_id_cheltuiala(chelt_storage));
    assert(get_numar_apartament(chelt) == get_numar_apartament(chelt_storage));

    //destroy_cheltuiala(chelt_storage);

    destroy_repository(storage);
}

void test_realocare_memorie() {
    Repo storage = creeaza_repository();

    assert(get_nr_cheltuieli(storage) == 0);
    assert(get_capacitate_maxima(storage) == 1024);

    char *tip = (char*)malloc(sizeof(char) * 32);
    strcpy(tip, "internet");
    cheltuiala chelt = create_cheltuiala(0, 12, 250, tip);

    storage = adauga_cheltuiala_la_storage(storage, chelt);

    if(get_nr_cheltuieli(storage) > 0) {
        storage = realocare_memorie(storage);

        assert(get_nr_cheltuieli(storage) == 1);
        assert(get_capacitate_maxima(storage) == (1024 + 256));

        destroy_repository(storage);
    }
}

void test_set_cheltuiala_pe_pozitie() {
    Repo storage = creeaza_repository();

    char *tip = (char*)malloc(sizeof(char) * 32);
    strcpy(tip, "internet");
    cheltuiala chelt = create_cheltuiala(0, 12, 250, tip);

    storage = set_cheltuiala_pe_pozitie(storage, chelt, 0);

    cheltuiala chelt_from_storage = get_cheltuiala_by_id(storage, 0);
    assert(get_id_cheltuiala(chelt_from_storage) == get_id_cheltuiala(chelt));
    assert(get_suma_cheltuiala(chelt) == get_suma_cheltuiala(chelt_from_storage));
    assert(get_numar_apartament(chelt) == get_numar_apartament(chelt_from_storage));

    destroy_cheltuiala(chelt);
    //destroy_cheltuiala(chelt_from_storage);

    destroy_repository(storage);
}

void test_delete_cheltuiala() {
    Repo storage = creeaza_repository();

    char *tip = (char*)malloc(sizeof(char) * 32);
    strcpy(tip, "internet");
    cheltuiala chelt = create_cheltuiala(0, 12, 250, tip);

    storage = adauga_cheltuiala_la_storage(storage, chelt);

    storage = delete_cheltuiala(storage, 0);

    assert(get_nr_cheltuieli(storage) == 0);

    destroy_repository(storage);
}

void test_copiaza_repo() {
    Repo storage = creeaza_repository();

    char *tip = (char*)malloc(sizeof(char) * 32);
    strcpy(tip, "internet");
    cheltuiala chelt = create_cheltuiala(0, 12, 250, tip);

    storage = adauga_cheltuiala_la_storage(storage, chelt);

    Repo tmp_storage = creeaza_repository();
    tmp_storage = copiaza_repo(tmp_storage, storage);
    destroy_repository(storage);

    assert(get_nr_cheltuieli(tmp_storage) == 1);

    destroy_repository(tmp_storage);
}
