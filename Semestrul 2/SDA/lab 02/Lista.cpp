
#include <exception>
#include "IteratorLP.h"
#include "Lista.h"

Lista::Lista() {
    primulNod = nullptr;
}

int Lista::dim() const {
    Nod* p = primulNod;
    int cnt = 0;
    while(p != nullptr){
        ++cnt;
        p = p->urm;
    }
    return cnt;
}


bool Lista::vida() const {
    if (primulNod == nullptr)
        return true;
    return false;
}

IteratorLP Lista::prim() const {
    return IteratorLP(*this);
}

TElem Lista::element(IteratorLP poz) const {
    if (!poz.valid())
        throw std::exception();
    return poz.curent->element();
}

TElem Lista::sterge(IteratorLP& poz) {
    if (!poz.valid())
        throw std::exception();
    Nod *el = poz.curent;
    TElem e = -1;
    if (poz.curent == primulNod){
        e = primulNod->e;
        poz.urmator();
        primulNod = poz.curent;
    }
    else {
        Nod *p = primulNod;
        while (p->urm != poz.curent && p->urm != nullptr)
            p = p->urm;
        if (p->urm == poz.curent) {
            e = poz.curent->e;
            p->urm = poz.curent->urm;
            poz.urmator();
        }
    }
    delete el;
    return e;
}

IteratorLP Lista::cauta(TElem e) const{
    IteratorLP poz = *this;
    while (poz.valid() && poz.curent->e != e)
        poz.urmator();
    return poz;
}

TElem Lista::modifica(IteratorLP poz, TElem e) {
    if (!poz.valid())
        throw std::exception();
    Nod* p = primulNod;
    TElem ve = -1;
    while(p != nullptr){
        if (p == poz.curent){
            ve = p->e;
            p->e = e;
            break;
        }
        p = p->urm;
    }
    return ve;
}

void Lista::adauga(IteratorLP& poz, TElem e) {
    if (!poz.valid())
        throw std::exception();
    IteratorLP p = *this;
    while(p.curent->urm != poz.curent)
        p.curent = p.curent->urm;

    Nod* nou = new Nod(e, poz.curent);
    p.curent->urm = nou;
    poz.curent = nou;
}

void Lista::adaugaInceput(TElem e) {
    Nod* nou = new Nod(e, nullptr);
    if (primulNod == nullptr){
        primulNod = nou;
    }
    else{
        nou->urm = primulNod;
        primulNod = nou;
    }
}

void Lista::adaugaSfarsit(TElem e) {
    Nod* nou = new Nod(e, nullptr);
    if (primulNod == nullptr){
        primulNod = nou;
    }
    else{
        Nod* p = primulNod;
        while(p->urm != nullptr)
            p = p->urm;
        p->urm = nou;
    }
}

Lista::~Lista() {
    Nod* p = primulNod;
    while (p != nullptr){
        Nod* p1 = p;
        p = p->urm;
        delete p1;
    }
}

int Lista::eliminaToate(Lista &lista) {
    TElem lastValue = -1;

    IteratorLP poz = lista.prim();
    while(poz.valid()) {
        lastValue = sterge(poz);
    }

    return lastValue;
}