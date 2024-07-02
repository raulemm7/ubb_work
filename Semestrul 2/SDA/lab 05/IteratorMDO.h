#pragma once

#include "MDO.h"


class IteratorMDO{
    friend class MDO;
private:

    //constructorul primeste o referinta catre Container
    //iteratorul va referi primul element din container
    explicit IteratorMDO(const MDO& dictionar);

    //contine o referinta catre containerul pe care il itereaza
    const MDO& dict;
    /* aici e reprezentarea  specifica a iteratorului */
    int act;

public:
    /**
     * reseteaza pozitia iteratorului la inceputul containerului
     *
     * complexitate timp:
     *      caz favorabil = θ(1)
     *      caz defavorabil = θ(h)
     *      caz mediu = O(h)
     * complexitate spatiu: θ(1)
     */
    void prim();

    /**
     * muta iteratorul pe urmatorul element in container
     * arunca exceptie daca iteratorul nu e valid
     *
     * complexitate timp:
     *      caz favorabil = θ(1)
     *      caz defavorabil = θ(h)
     *      caz mediu = O(h)
     * complexitate spatiu: θ(1)
     */
    void urmator();

    /**
     * verifica daca iteratorul e valid
     * @return 1 -> iteratorul refera un element al containerului
     *         0 -> altfel
     *
     * complexitate timp:
     *      caz favorabil = caz defavorabil = caz mediu = θ(n)
     * complexitate spatiu: θ(1)
     */
    bool valid() const;

    /**
     * returneaza valoarea elementului din container referit de iterator
     * arunca exceptie daca iteratorul nu e valid
     * @return element reprezentand o pereche (cheie, valoare)
     *
     * complexitate timp:
     *      caz favorabil = caz defavorabil = caz mediu = θ(n)
     * complexitate spatiu: θ(1)
     */
    TElem element() const;
};
