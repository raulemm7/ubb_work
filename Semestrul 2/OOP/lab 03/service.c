//
// Created by raulo on 3/21/2024.
//

#include "service.h"

Repo* adauga_o_noua_cheltuiala(Repo* storage, int id_cheltuiala, int numar_apartament, int suma_cheltuiala,
                              char* tip_cheltuiala) {
    // verific daca aceasta cheltuiala exista deja
    if(validare_cheltuiala_existenta(storage, numar_apartament, suma_cheltuiala, tip_cheltuiala)) {
        // creez o noua cheltuiala
        cheltuiala* chelt = create_cheltuiala(id_cheltuiala, numar_apartament, suma_cheltuiala, tip_cheltuiala);

        // adaug cheltuiala in storage
        // verific daca mai am loc, daca nu realoc memorie pentru storage
        if(get_nr_cheltuieli(storage) == get_capacitate_maxima(storage))
            storage = realocare_memorie(storage);

        // append cheltuiala
        storage = adauga_cheltuiala_la_storage(storage, chelt);
    }
    else {
        // cheltuiala exista deja, signalez eroarea
        print_mesaj("Aceasta cheltuiala exista deja!\n");

        // eliberare memorie suplimentara
        free(tip_cheltuiala);
    }

    // returnez storage
    return storage;
}

Repo* modifica_cheltuiala_existenta(Repo* storage, int id_ales, int suma_noua,
                                   char *tip_cheltuiala_nou) {
    // verific daca pentru datele introduse exista deja inregistrari
    int numar_ap = get_numar_apartament(get_cheltuiala_by_id(storage, id_ales));
    if(validare_cheltuiala_existenta(storage, numar_ap, suma_noua, tip_cheltuiala_nou)) {
        // actualizez cheltuiala
        cheltuiala* chelt = get_cheltuiala_by_id(storage, id_ales);
        chelt = modifica_informatii_cheltuiala(chelt, suma_noua, tip_cheltuiala_nou);

        // actualizez storage-ul
        storage = set_cheltuiala_pe_pozitie(storage, chelt, id_ales);
    }
    else {
        print_mesaj("Cheltuiala nou modificata este deja inregistrata!");
    }

    // eliberez memoria
    free(tip_cheltuiala_nou);

    // returnez informatiile updatate
    return storage;
}

Repo* sterge_cheltuiala_din_storage(Repo* storage, int id_ales) {
    // sterg efectiv
    storage = delete_cheltuiala(storage, id_ales);

    // returnez storage
    return storage;
}

void run_service_tests() {
    test_adaugare();
    test_modificare();
    test_stergere();
}

void test_adaugare() {
    Repo* storage = creeaza_repository();

    char *tip = (char*)malloc(sizeof(char) * 32);
    strcpy(tip, "internet");
    storage = adauga_o_noua_cheltuiala(storage, 0, 12, 250, tip);
    assert(get_nr_cheltuieli(storage) == 1);

    char *new_tip = (char*)malloc(sizeof(char) * 32);
    strcpy(new_tip, "internet");
    storage = adauga_o_noua_cheltuiala(storage, 0, 12, 250, new_tip);
    assert(get_nr_cheltuieli(storage) == 1);

    destroy_repository(storage);
}

void test_modificare() {
    Repo* storage = creeaza_repository();

    char *tip = (char*)malloc(sizeof(char) * 32);
    strcpy(tip, "internet");
    storage = adauga_o_noua_cheltuiala(storage, 0, 12, 250, tip);

    char *new_tip = (char*)malloc(sizeof(char) * 32);
    strcpy(new_tip, "apa");
    storage = modifica_cheltuiala_existenta(storage, 0, 460, new_tip);

    cheltuiala* chelt = get_cheltuiala_by_id(storage, 0);

    assert(get_suma_cheltuiala(chelt) == 460);
    char *tip_from_chelt = get_tip_cheltuiala(chelt);
    assert(strcmp(tip_from_chelt, "apa") == 0);
    free(tip_from_chelt);

    destroy_repository(storage);
}

void test_stergere() {
    Repo* storage = creeaza_repository();

    char *tip = (char*)malloc(sizeof(char) * 32);
    strcpy(tip, "internet");
    storage = adauga_o_noua_cheltuiala(storage, 0, 12, 250, tip);

    storage = sterge_cheltuiala_din_storage(storage, 0);

    assert(get_nr_cheltuieli(storage) == 0);

    destroy_repository(storage);
}