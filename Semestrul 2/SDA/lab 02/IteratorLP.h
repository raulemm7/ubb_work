#pragma once
#include "Lista.h"

class IteratorLP{
    friend class Lista;
private:

    /** constructorul primeste o referinta catre Container
        iteratorul va referi primul element din container */
    IteratorLP(const Lista& lista);

    /** contine o referinta catre containerul pe care il itereaza */
    const Lista& lista;

    /** aici e reprezentarea  specifica a iteratorului */
    Nod* curent;

public:
    /**
     * seteaza pozitia iteratorului la primul element din container
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     */
    void prim();

    /**
     * muta iteratorul la urmatorul element din container
     * arunca exceptie daca iteratorul nu e valid
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     */
    void urmator();

    /**
     * verifica daca iteratorul arata la un element din container
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     * @return 1 -> iteratorul refera la un element din container
     *         0 -> altfel
     */
    bool valid() const;

    /**
     * returneaza valoarea elementului din container referit de iterator
     * arunca excecptie daca iteratorul nu e valid
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     * @return
     */
    TElem element() const;

};


