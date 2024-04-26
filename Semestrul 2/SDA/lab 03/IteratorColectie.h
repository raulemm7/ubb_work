#pragma once
#include "Colectie.h"

class Colectie;
typedef int TElem;

class IteratorColectie
{
    friend class Colectie;
private:
    /**
     * constructorul clasei
     * iteratorul va referi primul element din container
     * @param c referinta catre container pe care iteratorul il refera
     */
    IteratorColectie(const Colectie& c);

    /** contine o referinta catre containerul pe care il itereaza */
    const Colectie& col;

    /** aici e reprezentarea pecifica a iteratorului */
    int curent;
    int frecv_curent;

public:

    /**
     * reseteaza pozitia iteratorului la inceputul containerului
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     */
    void prim();

    /**
     * muta iteratorul in container
     * arunca exceptie daca iteratorul nu e valid
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     */
    void urmator();

    /**
     * verifica daca iteratorul e valid (indica un element al containerului)
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     * @return
     */
    bool valid() const;

    /**
     * returneaza valoarea elementului din container referit de iterator
     * arunca exceptie daca iteratorul nu e valid
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     * @return
     */
    TElem element() const;
};

