//
// Created by raulo on 5/14/2024.
//

#include "Dictionar.h"
#include <iostream>
#include "IteratorDictionar.h"
#include <cmath>
#include <stack>

using namespace std;

int hashCode(TCheie val){
    return abs(val);
}

Dictionar::Dictionar() {
    /* de adaugat */
    this->m=MAX;
    for(int i=0; i<this->m; ++i){
        this->comp[i]= nullptr;
    }
}

Dictionar::~Dictionar() {
    /* de adaugat */
    for(int i=0; i<this->m; ++i){
        if(this->comp[i]!= nullptr){
            stack<Nod*> st;
            auto head=this->comp[i];
            while(head!= nullptr){
                st.push(head);
                head=head->urm;
            }
            while(!st.empty()){
                delete st.top();
                st.pop();
            }
        }
    }
}

TValoare Dictionar::adauga(TCheie c, TValoare v){
    /* de adaugat */
    TElem to_add=make_pair(c,v);
    TCheie d_val=d(c);
    if(this->comp[d_val]== nullptr){
        auto nod=new Nod(to_add, nullptr);
        this->comp[d_val]=nod;
        return NULL_TVALOARE;
    }
    auto head=this->comp[d_val];
    while(head->elem.first!=c){
        head=head->urm;
        if(head== nullptr){
            break;
        }
    }
    if(head== nullptr){
        auto nod=new Nod(to_add, this->comp[d_val]);
        this->comp[d_val]=nod;
        return NULL_TVALOARE;
    }
    TValoare ret= head->elem.second;
    head->elem.second=v;
    return ret;
}



//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare Dictionar::cauta(TCheie c) const{
    /* de adaugat */
    TCheie d_val=d(c);
    auto head=this->comp[d_val];
    if(head== nullptr){
        return NULL_TVALOARE;
    }
    while(head->elem.first!=c){
        head=head->urm;
        if(head== nullptr){
            break;
        }
    }
    if(head== nullptr) {
        return NULL_TVALOARE;
    }
    return head->elem.second;
}


TValoare Dictionar::sterge(TCheie c){
    /* de adaugat */
    TCheie d_val=d(c);
    auto head=this->comp[d_val];
    if(head== nullptr){
        return NULL_TVALOARE;
    }
    Nod* pre= nullptr;
    while(head->elem.first!=c){
        pre=head;
        head=head->urm;
        if(head== nullptr){
            break;
        }
    }
    if(head== nullptr) {
        return NULL_TVALOARE;
    }
    auto victim=head;
    if(pre!= nullptr) {
        pre->urm = head->urm;
    } else {
        this->comp[d_val]=head->urm;
    }
    TValoare ret=victim->elem.second;
    delete victim;
    return ret;
}


int Dictionar::dim() const {
    /* de adaugat */
    int ln=0;
    for(int i=0; i<this->m; ++i){
        if(this->comp[i]== nullptr){
            continue;
        }
        auto head=this->comp[i];
        while(head!= nullptr){
            head=head->urm;
            ++ln;
        }
    }
    return ln;
}

bool Dictionar::vid() const{
    /* de adaugat */
    bool ok=true;
    for(int i=0; i<this->m && ok; ++i){
        if(this->comp[i]!= nullptr){
            ok=false;
        }
    }
    return ok;
}


IteratorDictionar Dictionar::iterator() const {
    return  IteratorDictionar(*this);
}

int Dictionar::d(TCheie ch) const{
    return hashCode(ch)%this->m;
}

void Dictionar::golire() {
    auto it = this->iterator();

    while(this->dim()) {
        it.prim();
        TCheie c = it.element().first;
        this->sterge(c);
    }
}

Nod::Nod(TElem elem, Nod *urm) {
    this->elem=elem;
    this->urm=urm;
}