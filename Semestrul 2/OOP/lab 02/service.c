//
// Created by raulo on 3/13/2024.
//

#include "service.h"

Repo adauga_cheltuiala(Repo storage, cheltuiala new_cheltuiala) {
    // validare
    if(validare_cheltuiala(storage, new_cheltuiala)) {
        storage = append_cheltuiala(storage, new_cheltuiala);
        return storage;
    }
    else {
        print_mesage("Aceasta cheltuiala exista deja!\n");
    }

    return storage;
}

Repo sterge_cheltuiala(Repo storage, int id_cheltuiala) {
    storage = delete_cheltuiala(storage, id_cheltuiala);
    return storage;
}

void run_all_tests_service() {
    test_adauga_cheltuiala_serv();
    test_sterge_cheltuiala_serv();
}

void test_adauga_cheltuiala_serv(){
    Repo storage = creeare_repo();
    cheltuiala chelt = create_cheltuiala(0, 12, 1200, "internet");

    assert(get_nr_cheltuieli(storage) == 0);

    storage = adauga_cheltuiala(storage, chelt);
    assert(get_nr_cheltuieli(storage) == 1);

    storage = adauga_cheltuiala(storage, chelt);
    assert(get_nr_cheltuieli(storage) == 1);
}

void test_sterge_cheltuiala_serv() {
    Repo storage = creeare_repo();

    cheltuiala chelt = create_cheltuiala(0, 12, 1200, "internet");
    cheltuiala chelt2 = create_cheltuiala(1, 16, 340, "gaz");

    storage = adauga_cheltuiala(storage, chelt);
    storage = adauga_cheltuiala(storage, chelt2);

    assert(get_nr_cheltuieli(storage) == 2);

    storage = sterge_cheltuiala(storage, 0);
    assert(get_nr_cheltuieli(storage) == 1);

    cheltuiala chelt_repr = get_cheltuiala(storage, 0);
    assert(get_id(chelt_repr) == 0);
    assert(get_suma_cheltuiala(chelt_repr) == 340);
    assert(get_nr_apartament(chelt_repr) == 16);
    assert(strcmp(get_tip_cheltuiala(chelt_repr), "gaz") == 0);

    storage = sterge_cheltuiala(storage, 0);
    assert(get_nr_cheltuieli(storage) == 0);

}