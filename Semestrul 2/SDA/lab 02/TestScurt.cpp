#include "TestScurt.h"
#include <assert.h>
#include <exception>
#include "Lista.h"
#include "IteratorLP.h"

#include <iostream>

using namespace std;

void testAll(){
    std::cout << "Incepere test scurt...\n";

    Lista lista = Lista();
    assert(lista.dim() == 0);
    assert(lista.vida());

    lista.adaugaSfarsit(1);
    assert(lista.dim() == 1);
    assert(!lista.vida());

    IteratorLP it = lista.cauta(1);
    assert(it.valid());
    assert(it.element() == 1);
    it.urmator();
    assert(!it.valid());
    it.prim();
    assert(it.valid());
    assert(it.element() == 1);

    assert(lista.sterge(it) == 1);
    assert(lista.dim() == 0);
    assert(lista.vida());

    lista.adaugaInceput(1);
    assert(lista.dim() == 1);
    assert(!lista.vida());

    std::cout << "Test scurt trecut cu succes!\n";

    /** teste pentru functionalitatea eliminaToate() */
    std::cout << "Incepere test eliminaToate()\n";

    Lista lista_1 = Lista();
    for(int i = 1; i <= 105; i++)
        lista_1.adaugaSfarsit(i);
    assert(lista_1.dim() == 105);

    int lValue = lista_1.eliminaToate(lista_1);
    assert(lista_1.dim() == 0);
    assert(lValue == 105);

    for(int i = 0; i <= 1234; i++)
        lista_1.adaugaInceput(i);
    assert(lista_1.dim() == 1235);

    lValue = lista_1.eliminaToate(lista_1);
    assert(lista_1.dim() == 0);
    assert(lValue == 0);

    lValue = lista_1.eliminaToate(lista_1);
    assert(lValue == -1);

    std::cout << "Test eliminaToate() trecut cu succes!\n";
}

