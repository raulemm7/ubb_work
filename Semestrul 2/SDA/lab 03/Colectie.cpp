#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;


void Colectie::realocare_memorie() {
    int new_capacity = this->capacitate + 1024;

    auto* new_elemente = new TElem[new_capacity];
    int* new_frecventa = new int[new_capacity];
    int* new_urmator = new int[new_capacity];

    for(int i = 0; i < this->capacitate; i++) {
        new_elemente[i] = this->elemente[i];
        new_frecventa[i] = this->frecventa[i];
        new_urmator[i] = this->urmator[i];
    }
    new_urmator[this->capacitate - 1] = this->capacitate;
    // initializare vector de legaturi
    for(int i = this->capacitate - 1; i < new_capacity - 1; i++)
        new_urmator[i] = i + 1;
    new_urmator[new_capacity - 1] = -1;

    // delete
    delete [] this->elemente;
    delete [] this->frecventa;
    delete [] this->urmator;

    this->elemente = new_elemente;
    this->frecventa = new_frecventa;
    this->urmator = new_urmator;

    this->primLiber = this->capacitate;
    this->capacitate = new_capacity;
}

int Colectie::aloca() {
    int poz = this->primLiber;
    this->primLiber = this->urmator[this->primLiber];

    return poz;
}

void Colectie::dealoca(int pozitie) {
    this->urmator[pozitie] = this->primLiber;
    this->primLiber = pozitie;
}

void Colectie::creeaza_nod(TElem e) {
    int pozitie_disponibila = this->aloca();
    if(pozitie_disponibila == -1) {
        // realocam memorie
        this->realocare_memorie();
        pozitie_disponibila = this->aloca();
    }
    this->elemente[pozitie_disponibila] = e;
    this->frecventa[pozitie_disponibila] = 1;
}

Colectie::Colectie() {
    /* de adaugat */
    this->capacitate = INIT_CAPACITY;
    this->prim = -1;
    this->primLiber = 0;
    // initializare legaturi
    this->urmator = new int[this->capacitate];
    for(int i = 0; i < this->capacitate - 1; i++) {
        this->urmator[i] = i + 1;
    }
    this->urmator[this->capacitate - 1] = -1;
    // initializare vectori cu elemente
    this->elemente = new TElem[this->capacitate];
    this->frecventa = new int[this->capacitate];
    for(int i = 0; i < this->capacitate; i++) {
        this->frecventa[i] = 0;
    }
}


void Colectie::adauga(TElem elem) {
    /* de adaugat */
    if(this->vida())
        this->prim = this->primLiber;

    int poz = this->prim;
    while(poz != -1) {
        if(this->elemente[poz] == elem and this->frecventa[poz] > 0) {
            this->frecventa[poz]++;
            return;
        }
        poz = this->urmator[poz];
    }
    if(poz == -1) {
        this->creeaza_nod(elem);
        return;
    }
}


bool Colectie::sterge(TElem elem) {
    /* de adaugat */
    if(!this->cauta(elem))
        return false;

    for(int i = 0; i < this->capacitate; i++) {
        if(this->elemente[i] == elem) {
            if(this->frecventa[i] == 0)
                return false;
            else {
                this->frecventa[i]--;
                if(this->frecventa[i] == 0) {
                    this->dealoca(i);
                }
                return true;
            }
        }
    }

    return false;
}


bool Colectie::cauta(TElem elem) const {
    /* de adaugat */
    for(int i = 0; i < this->capacitate; i++)
        if(this->elemente[i] == elem and this->frecventa[i] > 0)
            return true;
    return false;
}

int Colectie::nrAparitii(TElem elem) const {
    /* de adaugat */
    for(int i = 0; i < this->capacitate; i++) {
        if(this->elemente[i] == elem)
            return this->frecventa[i];
    }
    return 0;
}


int Colectie::dim() const {
    /* de adaugat */
    int nr_total = 0;
    for(int i = 0; i < this->capacitate; i++) {
        nr_total += this->frecventa[i];
    }
    return nr_total;
}


bool Colectie::vida() const {
    /* de adaugat */
    return this->dim() == 0;
}

IteratorColectie Colectie::iterator() const {
    return  IteratorColectie(*this);
}


Colectie::~Colectie() {
    /* de adaugat */
}

void Colectie::afiseaza_elemente() {
    cout << this->primLiber << '\n';
    for(int i = 0; i < this->capacitate; i++) {
        if(this->frecventa[i])
            cout << i << " " << this->elemente[i] << " " << this->frecventa[i] << '\n';
    }
}

int Colectie::nr_elemente_distincte() {
    int k = 0;
    for(int i = 0; this->frecventa[i] != 0; i++)
        k++;
    return k;
}
