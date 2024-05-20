//
// Created by raulo on 5/14/2024.
//

#ifndef PROIECT_TAD_4_ITERATORDICTIONAR_H
#define PROIECT_TAD_4_ITERATORDICTIONAR_H

#include "Dictionar.h"

class IteratorDictionar
{
    friend class Dictionar;
private:

    /** constructorul primeste o referinta catre Container
     * iteratorul va referi primul element din container
     * */
    IteratorDictionar(const Dictionar& d);

    /** contine o referinta catre containerul pe care il itereaza */
    const Dictionar& dict;

    /** aici e reprezentarea specifica a iteratorului */
    int poz;
    Nod* act;

public:
    /**
     * reseteaza pozitia iteratorului la inceputul containerului
     *
     * complexitate spatiu: θ(1)
     * complexitate timp:
     *      caz favorabil = caz defavorabil = caz mediu = θ(1)
     */
    void prim();

    /**
     * muta iteratorul pe urmatoarea pozitie in container
     * arunca exceptie daca iteratorul nu e valid
     *
     * complexitate spatiu: θ(1)
     * complexitate timp:
     *      caz favorabil = caz defavorabil = caz mediu = θ(1)
     */
    void urmator();

    /**
     * verifica daca iteratorul e valid (indica un element al containerului)
     * @return 1, iteratorul e valid
     *         0, altfel
     *
     * complexitate spatiu: θ(1)
     * complexitate timp:
     *      caz favorabil = caz defavorabil = caz mediu = θ(1)
     */
    bool valid() const;

    /**
     * returneaza elementul din container referit de iterator
     * arunca exceptie daca iteratorul nu e valid
     * @return elementul din container indicat de iterator
     *
     * complexitate spatiu: θ(1)
     * complexitate timp:
     *      caz favorabil = caz defavorabil = caz mediu = θ(1)
     */
    TElem element() const;
};

#endif //PROIECT_TAD_4_ITERATORDICTIONAR_H
