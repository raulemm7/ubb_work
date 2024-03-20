//
// Created by raulo on 3/13/2024.
//

#include "validator.h"

int validare_tip(char *tip) {
    if(strcmp(tip, "apa") == 0)
        return 1;
    if(strcmp(tip, "gaz") == 0)
        return 1;
    if(strcmp(tip, "curent") == 0)
        return 1;
    if(strcmp(tip, "incalzire") == 0)
        return 1;
    if(strcmp(tip, "canal") == 0)
        return 1;
    if(strcmp(tip, "internet") == 0)
        return 1;

    return 0;
}

int validare_cheltuiala(Repo storage, cheltuiala chelt) {
    for(int i = 0; i < get_nr_cheltuieli(storage); i++) {
        cheltuiala chelt_verificare = get_cheltuiala(storage, i);

        if(get_nr_apartament(chelt) == get_nr_apartament(chelt_verificare) &&
        get_suma_cheltuiala(chelt) == get_suma_cheltuiala(chelt_verificare) &&
        strcmp(get_tip_cheltuiala(chelt), get_tip_cheltuiala(chelt_verificare)) == 0)
            return 0;
    }
    return 1;
}

// functii de test
void run_validator_tests() {
    test_validare_tip();
    test_validare_cheltuiala();
}

void test_validare_tip() {
    assert(validare_tip("dadad") == 0);
    assert(validare_tip("internet") == 1);
    assert(validare_tip("gaz") == 1);
    assert(validare_tip("apa") == 1);
    assert(validare_tip("curent") == 1);
    assert(validare_tip("incalzire") == 1);
    assert(validare_tip("canal") == 1);
    assert(validare_tip("ceva") == 0);
}

void test_validare_cheltuiala() {
    Repo storage;
    storage = creeare_repo();

    cheltuiala chelt = create_cheltuiala(0, 12, 1200, "internet");
    cheltuiala chelt2 = create_cheltuiala(1, 12, 240, "gaz");

    storage = append_cheltuiala(storage, chelt);

    assert(validare_cheltuiala(storage, chelt2) == 1);
    assert(validare_cheltuiala(storage, chelt) == 0);
}
