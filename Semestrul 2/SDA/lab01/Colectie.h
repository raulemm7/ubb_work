#pragma once

#define NULL_TELEM -1
typedef int TElem;

class IteratorColectie;

class Colectie
{
    friend class IteratorColectie;

    private:
        /* aici e reprezentarea */
        TElem* vector_elemente_distincte;
        int capacitate_elemente;
        int nr_elemente;

        int* vector_pozitie_aparitie;
        int capacitate_pozitii;
        int nr_pozitii;

        // functii de redimensionare
        void redimensionare_vector_elemente();
        void redimensionare_vector_pozitii();
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

        void adaugare_n_ori(const int x, TElem elem);

        //returneaza un iterator pe colectie
        IteratorColectie iterator() const;

        // destructorul colectiei
        ~Colectie();

};

