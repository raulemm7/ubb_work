//
// Created by raulo on 3/13/2024.
//

#include "repository.h"

Repo creeare_repo() {
    Repo repo_nou;
    repo_nou.nr_cheltuieli = 0;
    return repo_nou;
}

Repo append_cheltuiala(Repo storage, cheltuiala new_cheltuiala) {
    storage.lista_cheltuieli[storage.nr_cheltuieli] = new_cheltuiala;
    storage.nr_cheltuieli += 1;

    return storage;
}

cheltuiala get_cheltuiala(Repo storage, int id_cheltuiala) {
    return storage.lista_cheltuieli[id_cheltuiala];
}

Repo set_cheltuiala(Repo storage, int id_cheltuiala, cheltuiala chelt) {
    chelt = set_id(chelt, id_cheltuiala);
    storage.lista_cheltuieli[id_cheltuiala] = chelt;
    return storage;
}

int get_nr_cheltuieli(Repo storage) {
    return storage.nr_cheltuieli;
}

Repo delete_cheltuiala(Repo storage, int id_cheltuiala) {
    for(int i = id_cheltuiala; i < storage.nr_cheltuieli - 1; i++) {
        // translatez si modific id -ul
        cheltuiala chelt = storage.lista_cheltuieli[i + 1];
        chelt.id = i;
        storage.lista_cheltuieli[i] = chelt;
    }
    // modific numarul de componente ale storage-ului
    storage.nr_cheltuieli -= 1;

    return storage;
}

void run_repo_all_tests() {
    test_create_repo();
    test_adauga_cheltuiala();
    test_set_cheltuiala();
    test_delete_cheltuiala();
}

void test_create_repo() {
    Repo storage;
    storage = creeare_repo();

    assert(get_nr_cheltuieli(storage) == 0);
}

void test_adauga_cheltuiala() {
    Repo storage;
    storage = creeare_repo();

    cheltuiala chelt = create_cheltuiala(0, 12, 1200, "internet");

    storage = append_cheltuiala(storage, chelt);

    assert(get_nr_cheltuieli(storage) == 1);

    cheltuiala cheltuiala_pr = get_cheltuiala(storage, 0);
    assert(get_id(chelt) == get_id(cheltuiala_pr));
    assert(get_suma_cheltuiala(chelt) == get_suma_cheltuiala(cheltuiala_pr));
    assert(get_nr_apartament(chelt) == get_nr_apartament(cheltuiala_pr));
    assert(strcmp(get_tip_cheltuiala(chelt), get_tip_cheltuiala(cheltuiala_pr)) == 0);
}

void test_set_cheltuiala() {
    Repo storage;
    storage = creeare_repo();

    cheltuiala chelt = create_cheltuiala(0, 12, 1200, "internet");
    cheltuiala chelt2 = create_cheltuiala(1, 12, 240, "gaz");

    storage = append_cheltuiala(storage, chelt);
    storage = set_cheltuiala(storage, 0, chelt2);

    cheltuiala chelt_retr = get_cheltuiala(storage, 0);
    assert(get_id(chelt_retr) == 0);
}

void test_delete_cheltuiala() {
    Repo storage;
    storage = creeare_repo();

    cheltuiala chelt = create_cheltuiala(0, 12, 1200, "internet");
    cheltuiala chelt2 = create_cheltuiala(1, 16, 240, "gaz");

    storage = append_cheltuiala(storage, chelt);
    storage = append_cheltuiala(storage, chelt2);

    storage = delete_cheltuiala(storage, 0);

    assert(get_nr_cheltuieli(storage) == 1);

    chelt = get_cheltuiala(storage, 0);
    assert(get_id(chelt) == 0);
    assert(get_nr_apartament(chelt) == 16);
    assert(get_suma_cheltuiala(chelt) == 240);
    assert(strcmp(get_tip_cheltuiala(chelt), "gaz") == 0);
}