#pragma once

#define INIT_CAPACITY 21000
typedef int TElem;

class IteratorColectie;

class Colectie
{
    friend class IteratorColectie;

private:
    /** aici e reprezentarea */
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
    /** constructorul implicit */
    Colectie();

    /**
     * adauga un element in colectie
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1) amortizat (din cauza redimensionarii)
     * complexitate spatiu: θ(1)
     * @param e elementul ce se va adauga in colectie
     */
    void adauga(TElem e);

    /**
     * sterge o aparitie a unui element din colectie
     * complexitate timp: caz favorabil = θ(1)
     *                    caz defavorabil = θ(1)
     *                    caz mediu = O(n)
     * complexitate spatiu: θ(1)
     * @param e elementul care se va sterge din colectie
     * @return true -> daca s-a putut sterge din colectie
     *         false -> altfel
     */
    bool sterge(TElem e);

    /**
     * verifica daca un element se afla in colectie
     * complexitate timp: caz favorabil = θ(1)
     *                    caz defavorabil = θ(1)
     *                    caz mediu = O(n)
     * complexitate spatiu: θ(1)
     * @param elem elementul pentru care se face cautarea
     * @return 1 -> elementul se afla in colectie
     *         0 -> altfel
     */
    bool cauta(TElem elem) const;

    /**
     * returneaza numarul de aparitii ale unui element in colectie
     * complexitate timp: caz favorabil = θ(1)
     *                    caz defavorabil = θ(1)
     *                    caz mediu = O(n)
     * complexitate spatiu: θ(1)
     * @param elem elementul pentru care se cauta numaul de aparitii
     * @return int ce reprezinta nr de aparitii a elementului elem in colectie
     */
    int nrAparitii(TElem elem) const;

    /**
     * intoarce numarul de elemente din colectie
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(n)
     * complexitate spatiu: θ(1)
     * @return int ce reprezinta dimensiunea colectiei
     */
    int dim() const;

    /**
     * verifica daca colectia este vida
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     * @return 1 -> colectie e vida
     *         0 -> altfel
     */
    bool vida() const;

    /**
     * returneaza un iterator pe colectie
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     * @return iterator
     */
    IteratorColectie iterator() const;

    /** destructorul colectiei */
    ~Colectie();

    /**
     * transforma colectie in multime
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     * @return nr de elemente sterse din colectie
     */
     int transformaInMultime();

//     void afiseaza_elemente();
};
