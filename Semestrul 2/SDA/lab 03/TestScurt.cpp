#include "TestScurt.h"
#include <assert.h>
#include "Colectie.h"
#include "IteratorColectie.h"

void testAll() { //apelam fiecare functie sa vedem daca exista
    Colectie c;
    assert(c.vida() == true);
    assert(c.dim() == 0); //adaug niste elemente
    c.adauga(5);
    c.adauga(1);
    c.adauga(10);
    c.adauga(7);
    c.adauga(1);
    c.adauga(11);
    c.adauga(-3);
    assert(c.dim() == 7);
    assert(c.cauta(10) == true);
    assert(c.cauta(16) == false);
    assert(c.nrAparitii(1) == 2);
    assert(c.nrAparitii(7) == 1);
    assert(c.sterge(1) == true);
    assert(c.sterge(6) == false);
    assert(c.dim() == 6);
    assert(c.nrAparitii(1) == 1);
    IteratorColectie ic = c.iterator();
    ic.prim();
    while (ic.valid()) {
        TElem e = ic.element();
        ic.urmator();
    }

    // testare transformaInMultime
    Colectie c2;
    assert(c2.dim() == 0);

    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 3; j++)
            c2.adauga(i);
    }
    assert(c2.dim() == 60);

    int k = c2.transformaInMultime();
    assert(c2.dim() == 20);
    assert(k == 40);

    k = c2.transformaInMultime();
    assert(c2.dim() == 20);
    assert(k == 0);
}