#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

/**
 * Constructorul clasei Colectie
 * Initializeaza un obiect de tip Colectie
 * preconditii: true
 * postconditii: c = obiect de tip Colectie, c = colectie vida (dim(c) == 0)
 * complexitate timp: caz favorabil = caz defavorabil = caz mediu = Θ(1)
 * complexitate spatiu: Θ(14 + 128 * 2) = Θ(1)
 */
Colectie::Colectie() {
    /* de adaugat */
    this->vector_elemente_distincte = (TElem*)calloc(128, sizeof(TElem));
    this->nr_elemente = 0;
    this->capacitate_elemente = 128;

    this->vector_pozitie_aparitie = (int*)calloc(128, sizeof(int));
    this->nr_pozitii = 0;
    this->capacitate_pozitii = 128;
}

/**
 * Redimensioneaza spatiul de memorare el elementelor distincte din colectie
 * preconditii: true
 * postconditii: true
 * complexitate timp: caz favorabil = caz defavorabil = caz mediu = Θ(nr_elemente_distincte)
 * complexitate spatiu: O(nr_elemente_distincte)
 */
void Colectie::redimensionare_vector_elemente() {
    this->capacitate_elemente += 128;
    TElem* new_vector = (TElem*)calloc(this->capacitate_elemente, sizeof(TElem));

    for(int i = 0; i < this->nr_elemente; i++) {
        TElem e = this->vector_elemente_distincte[i];
        new_vector[i] = e;
    }

    free(this->vector_elemente_distincte);
    this->vector_elemente_distincte = new_vector;
}

/**
 * Redimensioneaza spatiul de memorare al pozitiilor elementelor colectiei
 * preconditii: true
 * postconditii: true
 * complexitate timp: caz favorabil = caz defavorabil = caz mediu = Θ(nr_pozitii)
 * complexitate spatiu: O(nr_pozitii)
 */
void Colectie::redimensionare_vector_pozitii() {
    this->capacitate_pozitii += 128;
    int* new_vector = (int*)calloc(this->capacitate_pozitii, sizeof(int));

    for(int i = 0; i < this->nr_pozitii; i++) {
        new_vector[i] = this->vector_pozitie_aparitie[i];
    }

    free(this->vector_pozitie_aparitie);
    this->vector_pozitie_aparitie = new_vector;
}

/**
 * Adauga un element la o colectie
 * preconditii: elem = element de tipul TElem, c = colectie
 * postconditii: true
 * complexitate timp:
 *      caz favorabil: Θ(1 + 1 + 1 + 2) = Θ(5) = Θ(1)
 *      caz defavorabil: Θ(nr_elemente_distincte * 2 +
 *                         + dim())                       => O(2 * nr_elemente_distincte +
 *                                                                               + dim())
 *      caz mediu: Θ(nr_elemente_distincte * 2 +
 *                   + nr_pozitii)
 * complexitate spatiu: Θ(1)
 * @param elem
 */
void Colectie::adauga(TElem elem) {
    /* de adaugat */
    // deoarece la initializarea memoriei s a folosit calloc(), la inceputul executiei,
    // elementele din vectorul dinamic sunt egale cu 0
    // in cazul in care se introduce ca prim element un 0,
    // in momentul cand il caut in vector il gaseste pe prima pozitie, ceea ce e fals
    // deoarece nu a fost adaugat niciun element
    // de aceea, mai intai verific daca nr de elemente din colectie e mai mare ca 0
    // practic rezolv bugul: 0 introdus ca prim element in colectie
    if(this->nr_elemente > 0) {
        // verific daca elementul se afla deja inregistrat
        for(int i = 0; i < this->nr_elemente; i++) {
            if(this->vector_elemente_distincte[i] == elem) {
                // daca se afla deja, mai adaug o pozitie in vectorul de pozitii
                // verific daca mai am loc, daca nu resize la vector
                if(this->nr_pozitii == this->capacitate_pozitii){
                    this->redimensionare_vector_pozitii();
                }

                // adaug pozitia in vec de pozitii
                this->vector_pozitie_aparitie[this->nr_pozitii] = i;
                this->nr_pozitii++;

                // inchei executia
                return;
            }
        }
    }

    // pun noul element in colectie
    // verific daca mai exista loc in vectorul de elemente
    if(this->nr_elemente == this->capacitate_elemente){
        this->redimensionare_vector_elemente();
    }
    // adaug elementul in vectorul de elemente
    this->vector_elemente_distincte[this->nr_elemente] = elem;
    this->nr_elemente++;

    // adaug pozitia acestuia
    // verific daca am loc
    if(this->nr_pozitii == this->capacitate_pozitii){
        this->redimensionare_vector_pozitii();
    }

    this->vector_pozitie_aparitie[this->nr_pozitii] = this->nr_elemente - 1;

    this->nr_pozitii++;
}

/**
 * Sterge o aparitie a unui element, daca acesta se afla in colectie
 * preconditii: elem = element de tip TElem, c = colectie
 * postconditii: 1 = daca stergerea s a efectuat cu succes
 *               0 = altfel
 * complexitate timp:
 *      caz favorabil: Θ(nr_elemente_distincte)
 *      caz defavorabil: Θ(nr_elemente_distincte + 2 * dim())   => O(nr_elemente_distincte + 2 * dim())
 *      caz mediu: Θ(nr_elemente_distincte + 2 * dim())
 * complexitate spatiu: Θ(3) = Θ(1)
 * @return: bool
 */
bool Colectie::sterge(TElem elem) {
    /* de adaugat */
    // caut elementul in vector elemente
    int pozitie = -1;  // pozitie in vectorul de elemente
    for(int i = 0; i < this->nr_elemente; i++) {
        if (this->vector_elemente_distincte[i] == elem) {
            pozitie = i;
            break;
        }
    }

    if(pozitie == -1) // nu am gasit elementul in vectorul de elemente
        return false;

    int nr_aparitii = 0;
    int last_appearence = -1;  // ultima aparitie in vectorul de pozitii (in colectie)
    for(int i = 0; i < this->nr_pozitii; i++) {
        if (this->vector_pozitie_aparitie[i] == pozitie) {
            nr_aparitii++;
            last_appearence = i;
        }
    }

    if(nr_aparitii == 1) {
        // sterg elementul
        for(int i = pozitie; i < this->nr_elemente - 1; i++)
            this->vector_elemente_distincte[i] = this->vector_elemente_distincte[i + 1];
        this->nr_elemente--;

        // sterg pozitia (aparitia)
        // decrementez celelalte pozitii
        for(int i = last_appearence; i < this->nr_pozitii - 1; i++) {
            // this->vector_pozitie_aparitie[i] = this->vector_pozitie_aparitie[i + 1] - 1;
            if(this->vector_pozitie_aparitie[i + 1] > pozitie)
                this->vector_pozitie_aparitie[i] = this->vector_pozitie_aparitie[i + 1] - 1;
            else
                this->vector_pozitie_aparitie[i] = this->vector_pozitie_aparitie[i + 1];
        }
        this->nr_pozitii--;

        return true;
    }

    for(int i = last_appearence; i < this->nr_pozitii - 1; i++)
        this->vector_pozitie_aparitie[i] = this->vector_pozitie_aparitie[i + 1];
    this->nr_pozitii--;

    return true;
}

/**
 * Cauta un element dat intr o colectie
 * preconditii: elem = element de tip TElem, c = Colectie
 * postconditii: 1 = elementul cautat se afla in colectie
 *               0 = altfel
 * complexitate timp:
 *      caz favorabil: Θ(1)
 *      caz defavorabil: Θ(nr_elemente_distincte)   => O(nr_elemente_distincte)
 *      caz mediu: O(nr_elemente_distincte)
 * complexitate spatiu: Θ(1)
 * @return: bool
 */
bool Colectie::cauta(TElem elem) const {
    /* de adaugat */
    for(int i = 0; i < this->nr_elemente; i++)
        if(this->vector_elemente_distincte[i] == elem)
            return true;

    return false;
}

/**
 * Returneaza numarul de aparitii al unui element intr o colectie
 * preconditii: elem = element de tip TElem, c = Colectie
 * postconditii: count = numarul de aparitii al variabilei elem in colectie
 * complexitate timp:
 *      caz favorabil: Θ(nr_elemente_distincte)
 *      caz defavorabil: Θ(nr_elemente_distincte + dim())   => O(nr_elemente_distincte + dim())
 *      caz mediu: O(nr_elemente_distincte + dim())
 * complexitate spatiu: Θ(2) = Θ(1)
 * @return: count = numarul de aparitii
 */
int Colectie::nrAparitii(TElem elem) const {
    /* de adaugat */
    int pozitie = -1;
    for(int i = 0; i < this->nr_elemente; i++){
        if(this->vector_elemente_distincte[i] == elem) {
            pozitie = i;
            i += this->nr_elemente;
        }
    }

    if(pozitie < 0)
        return 0;

    int count = 0;
    for(int i = pozitie; i < this->nr_pozitii; i++) {
        if(this->vector_pozitie_aparitie[i] == pozitie)
            count++;
    }

    return count;
}

/**
 * Returneaza numarul de elemente dintr o colectie (dimensiunea unei colectii)
 * preconditii: c = un obiect de tip Colectie
 * postconditii: dim = numarul total de elemente din c
 * complexitate timp: caz favorabil = caz defavorabil = caz mediu = Θ(1)
 * complexitate spatiu: Θ(1) (nu utilizeaza memorie suplimnetara)
 * @return: dim
 */
int Colectie::dim() const {
    /* de adaugat */
    return this->nr_pozitii;
}

/**
 * Verifica daca o colectie este vida (nu are elemente in ea)
 * preconditii: c = un obiect de tip Colectie
 * postconditii: 1 = colectia este vida
 *               0 = colectia nu este vida
 * complexitate timp: caz favorabil = caz defavorabil = caz mediu = Θ(1)
 * complexitate spatiu: Θ(1) (nu utilizeaza memorie suplimnetara)
 * @return 0 || 1
 */
bool Colectie::vida() const {
    return this->nr_pozitii == 0;
}

/**
 * Construieste un iterator peste o colectie
 * preconditii: c = un obiect de tip Colectie
 * postconditii: i = iterator pe c, i refera un prim element al colectiei c
 * complexitate timp: caz favorabil = caz defavorabil = caz mediu = Θ(1)
 * complexitate spatiu: Θ(1)
 * @return i = iterator
 */
IteratorColectie Colectie::iterator() const {
    return  IteratorColectie(*this);
}

/**
 * Destructorul clasei Colectie
 * elibereaza memoria utilizata de un obiect de tip Colectie
 * preconditii: c = obiect de tip Colectie
 * postconditii: true
 * complexitate timp: caz favorabil = caz defavorabil = caz mediu = Θ(1)
 * complexitate spatiu: Θ(1)
 */
Colectie::~Colectie() {
    /* de adaugat */
    free(this->vector_elemente_distincte);
    this->nr_elemente = -1;
    this->capacitate_elemente = -1;

    free(this->vector_pozitie_aparitie);
    this->nr_pozitii = -1;
    this->capacitate_pozitii = -1;
}


