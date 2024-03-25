//
// Created by raulo on 3/21/2024.
//

#include "repository.h"

Repo* creeaza_repository() {
    Repo *repo_nou = (Repo*)malloc(sizeof(Repo));
    repo_nou->capacitate_maxima = 1024;
    repo_nou->lista_cheltuieli = (cheltuiala*)calloc(repo_nou->capacitate_maxima, sizeof(cheltuiala));
    repo_nou->nr_cheltuieli = 0;

    return repo_nou;
}

void destroy_repository(Repo* storage) {
    for(int i = 0; i < storage->nr_cheltuieli; i++) {
        destroy_cheltuiala(storage->lista_cheltuieli[i]);
    }

    free(storage->lista_cheltuieli);
    storage->capacitate_maxima = -1;
    storage->nr_cheltuieli = -1;

    free(storage);
}

Repo* realocare_memorie(Repo* storage) {
    // actualizare capacitate
    storage->capacitate_maxima += 256;

    cheltuiala* lista_noua_cheltuieli = (cheltuiala*)malloc(sizeof(cheltuiala) * storage->capacitate_maxima);
    for(int i = 0; i < storage->nr_cheltuieli; i++) {
        lista_noua_cheltuieli[i] = storage->lista_cheltuieli[i];
    }
    free(storage->lista_cheltuieli);

    storage->lista_cheltuieli = lista_noua_cheltuieli;

    return storage;
}

cheltuiala get_cheltuiala_by_id(Repo* storage, int id_cheltuiala) {
    cheltuiala chelt = storage->lista_cheltuieli[id_cheltuiala];
    return chelt;
}

int get_nr_cheltuieli(Repo* storage) {
    return storage->nr_cheltuieli;
}

int get_capacitate_maxima(Repo* storage) {
    return storage->capacitate_maxima;
}

Repo* adauga_cheltuiala_la_storage(Repo* storage, cheltuiala chelt) {
    storage->lista_cheltuieli[storage->nr_cheltuieli] = chelt;
    storage->nr_cheltuieli++;
    return storage;
}

Repo* set_cheltuiala_pe_pozitie(Repo* storage, cheltuiala chelt, int id_position) {
    storage->lista_cheltuieli[id_position] = chelt;
    return storage;
}

Repo* delete_cheltuiala(Repo* storage, int id_position) {
    for(int i = id_position; i < storage->nr_cheltuieli - 1; i++) {
        storage->lista_cheltuieli[i] = copiaza_cheltuiala_for_delete(storage->lista_cheltuieli[i],
                                                                    storage->lista_cheltuieli[i + 1]);
    }
    destroy_cheltuiala(storage->lista_cheltuieli[storage->nr_cheltuieli - 1]);
    storage->nr_cheltuieli -= 1;

    return storage;
}

void run_repository_tests() {
    test_storage_operations();
    test_realocare_memorie();
    test_set_cheltuiala_pe_pozitie();
    test_delete_cheltuiala();
}

void test_storage_operations() {
    Repo* storage = creeaza_repository();

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
    Repo* storage = creeaza_repository();

    assert(get_nr_cheltuieli(storage) == 0);
    assert(get_capacitate_maxima(storage) == 1024);

    char *tip = (char*)malloc(sizeof(char) * 32);
    strcpy(tip, "internet");
    cheltuiala chelt = create_cheltuiala(0, 12, 250, tip);

    storage = adauga_cheltuiala_la_storage(storage, chelt);

    if(get_nr_cheltuieli(storage) > 0) {
        Repo* new_storage = realocare_memorie(storage);

        assert(get_nr_cheltuieli(new_storage) == 1);
        assert(get_capacitate_maxima(new_storage) == (1024 + 256));

        destroy_repository(new_storage);
    }
}

void test_set_cheltuiala_pe_pozitie() {
    Repo* storage = creeaza_repository();

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
    Repo* storage = creeaza_repository();

    char *tip = (char*)malloc(sizeof(char) * 32);
    strcpy(tip, "internet");
    cheltuiala chelt = create_cheltuiala(0, 12, 250, tip);

    storage = adauga_cheltuiala_la_storage(storage, chelt);

    storage = delete_cheltuiala(storage, 0);

    assert(get_nr_cheltuieli(storage) == 0);

    destroy_repository(storage);
}
