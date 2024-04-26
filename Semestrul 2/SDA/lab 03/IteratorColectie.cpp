#include "IteratorColectie.h"
#include "Colectie.h"

IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
    /* de adaugat */
    this->curent = this->col.prim;
    this->frecv_curent = this->col.frecventa[this->curent];
}

void IteratorColectie::prim() {
    /* de adaugat */
    this->curent = this->col.prim;
    this->frecv_curent = this->col.frecventa[this->curent];
}


void IteratorColectie::urmator() {
    /* de adaugat */
    if(this->frecv_curent > 1)
        this->frecv_curent--;
    else {
        this->curent = this->col.urmator[this->curent];

        while(this->col.frecventa[this->curent] == 0 and this->curent != -1) {
            this->curent = this->col.urmator[this->curent];
        }

        if(this->curent != -1)
            this->frecv_curent = this->col.frecventa[this->curent];
    }
}


bool IteratorColectie::valid() const {
    /* de adaugat */
    return this->curent != -1;
}



TElem IteratorColectie::element() const {
    /* de adaugat */
    return this->col.elemente[this->curent];
}
