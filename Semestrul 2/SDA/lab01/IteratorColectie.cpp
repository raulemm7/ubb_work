#include "IteratorColectie.h"
#include "Colectie.h"

/**
 * Constructorul clasei IteartorColectie
 * Initializeaza un indice (cu 0) care semnifica pozitia primului element din colectie
 * preconditii: c = o colectie
 * postconditii: i = iterator pe c, refera un prim element din c
 * complexitate timp: Θ(1)
 * complexitate spatiu: Θ(1)
 */
IteratorColectie::IteratorColectie(const Colectie& c): col(c){
    /* de adaugat */
    this->index_curent = 0;
}

/**
 * Seteaza iteratorul pe prima pozitie din colectie
 * preconditii: i = iterator
 * postconditii: i = iterator pe o colectie, refera primul element din colectie
 * complexitate timp: Θ(1)
 * complexitate spatiu: Θ(1)
 */
void IteratorColectie::prim() {
    /* de adaugat */
    this->index_curent = 0;
}

/**
 * Incrementeaza iteratorul
 * preconditii: i = iterator
 * postconditii: i refera la elementul succesor din colectie fata de valoarea sa initiala
 * complexitate timp: Θ(1)
 * complexitate spatiu: Θ(1)
 */
void IteratorColectie::urmator() {
    /* de adaugat */
    this->index_curent = this->index_curent + 1;
}

/**
 * Verifica daca iteratorul refera un element valid
 * (daca nu a depasit numarul maxim de elemente)
 * preconditii: i = iterator
 * postconditii: 1 = i refera la un element valid
 *               0 = altfel
 * complexitate timp: Θ(1)
 * complexitate spatiu: Θ(1)
 * @return: bool
 */
bool IteratorColectie::valid() const {
    return (this->index_curent < col.dim());
}

/**
 * Returneaza elementul din colectie indicat de iterator
 * preconditii: i = iterator
 * postconditii: element de tip TElem, element din colectie
 * complexitate timp: Θ(1)
 * complexitate spatiu: Θ(1)
 * @return: TElem
 */
TElem IteratorColectie::element() const {
    /* de adaugat */
    return col.vector_elemente_distincte[col.vector_pozitie_aparitie[this->index_curent]];
}
