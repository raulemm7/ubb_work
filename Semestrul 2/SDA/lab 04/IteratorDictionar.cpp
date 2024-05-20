//
// Created by raulo on 5/14/2024.
//

#include "IteratorDictionar.h"
#include "Dictionar.h"
#include <exception>

using namespace std;

IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict(d){
    /* de adaugat */
    this->poz=0;
    while(dict.comp[this->poz]== nullptr && this->poz<dict.m){
        ++this->poz;
    }
    if(this->poz==dict.m){
        this->act= nullptr;
    } else {
        this->act=dict.comp[this->poz];
    }
}


void IteratorDictionar::prim() {
    /* de adaugat */
    this->poz=0;
    while(dict.comp[this->poz]== nullptr && this->poz<dict.m){
        ++this->poz;
    }
    if(this->poz==dict.m){
        this->act= nullptr;
    } else {
        this->act=dict.comp[this->poz];
    }
}


void IteratorDictionar::urmator() {
    /* de adaugat */
    if(!valid()){
        throw exception();
    }
    if(this->act->urm!= nullptr){
        this->act=this->act->urm;
    } else {
        ++this->poz;
        while(dict.comp[this->poz]== nullptr && this->poz<dict.m){
            ++this->poz;
        }
        if(this->poz==dict.m){
            this->act= nullptr;
            return;
        }
        this->act=dict.comp[this->poz];
    }
}


TElem IteratorDictionar::element() const{
    /* de adaugat */
    if(!valid()){
        throw exception();
    }
    TElem ret= this->act->elem;
    return ret;
}


bool IteratorDictionar::valid() const {
    /* de adaugat */
    if(this->act!= nullptr){
        return true;
    }
    return false;
}