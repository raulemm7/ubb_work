#include "IteratorLP.h"
#include "Lista.h"
#include <exception>

IteratorLP::IteratorLP(const Lista& l):lista(l) {
    curent = lista.primulNod;
}

void IteratorLP::prim(){
    curent = lista.primulNod;
}

void IteratorLP::urmator(){
    if (curent == nullptr)
        throw std::exception();
    curent = curent->urmator();
}

bool IteratorLP::valid() const{
    if (curent != nullptr)
        return true;
    return false;
}

TElem IteratorLP::element() const{
    if (!valid())
        throw std::exception();
    return curent->element();

}


