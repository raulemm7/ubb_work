#pragma once

#define NULL_TELEM -1
#define INIT_CAPACITY 60028
typedef int TElem;

class IteratorColectie;

class Colectie
{
    friend class IteratorColectie;

private:
    /* aici e reprezentarea */
    int capacitate;
    TElem* elemente;
    int* frecventa;
    int* urmator;
    int prim;
    int primLiber;

    /** functii pentru alocare/dealocare */
    void realocare_memorie();
    int aloca();
    void dealoca(int pozitie);

    /** creeaza un nou nod */
    void creeaza_nod(TElem e);
public:
    //constructorul implicit
    Colectie();

    //adauga un element in colectie
    void adauga(TElem e);

    //sterge o aparitie a unui element din colectie
    //returneaza adevarat daca s-a putut sterge
    bool sterge(TElem e);

    //verifica daca un element se afla in colectie
    bool cauta(TElem elem) const;

    //returneaza numar de aparitii ale unui element in colectie
    int nrAparitii(TElem elem) const;


    //intoarce numarul de elemente din colectie;
    int dim() const;

    //verifica daca colectia e vida;
    bool vida() const;

    //returneaza un iterator pe colectie
    IteratorColectie iterator() const;

    // destructorul colectiei
    ~Colectie();

    void afiseaza_elemente();
    int nr_elemente_distincte();

};

