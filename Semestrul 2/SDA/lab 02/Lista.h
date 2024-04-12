#pragma once

typedef int TElem;

class Nod{
private:
    TElem e;
    Nod* urm;
public:
    friend class Lista;

    /** constructor */
    Nod(TElem e, Nod* urm): e{e}, urm{urm}{
    }

    /**
     * retueneaza valoarea unui element
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     */
    TElem element() const{
        return e;
    }

    /**
     * trece la urmatorul element din container
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     */
    Nod* urmator(){
        return urm;
    }
};

class IteratorLP;

class Lista {
private:
    friend class IteratorLP;
    /** aici e reprezentarea */
    Nod* primulNod;

public:
    /**
     * constructor
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     */
    Lista ();

    /**
     * returneaza dimensiunea containerului (numarul de elemente)
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     * @return int
     */
    int dim() const;

    /**
     * verifica daca containerul e vid (nu contine niciun element)
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     * @return 1 -> containerul e vid
     *         0 -> altfel
     */
    bool vida() const;

    /**
     * seteaza un iterator pe prima pozitie din container
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     * @return IteratorLP*
     */
    IteratorLP prim() const;

    /**
     * returneaaza elementul de pe pozitia curenta a iteratorului
     * arunca exceotie daca poz nu e valid
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     * @param poz iterator
     * @return element de tip TElem
     */
    TElem element(IteratorLP poz) const;

    /**
     * modifica elementul de pe pozitia poz si returneaza vechea valoare
     * arunca exceptie daca poz nu e valid
     * complexitate timp:
     *      caz favorabil: θ(1) -> cand este pe prima pozitie
     *      caz defavorabil: θ(n) -> cand nu exista
     *      caz mediu: O(n)
     *      complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     * @param poz pozitia elementului ce urmeaza a fi modificat
     * @param e noua valoare a elementului de pe pozitia poz
     * @return vechea valoare a elementului respectiv
     */
    TElem modifica(IteratorLP poz, TElem e);

    /**
     * adauga un element la inceputul containerului
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     * @param e noul element ce va fi adaugat
     */
    void adaugaInceput(TElem e);

    /**
     * adauga un element la sfarsitul containerului
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(n)
     * complexitate spatiu: θ(1)
     * @param e noul element ce va fi adaugat
     */
    void adaugaSfarsit(TElem e);

    /**
     * adauga element dupa o pozitie data
     * dupa adaugare, iteratorul poz refera la elementul nou adaugat
     * arunca exceptie daca poz nu e valid
     * complexitate timp:
     *      caz favorabil: θ(1) -> cand se adauga pe prima pozitie
     *      caz defavorabil: θ(n) -> cand se adauga pe ultima pozitie
     *      caz mediu: O(n)
     * complexitate spatiu: θ(1)
     * @param poz iterator
     * @param e noul element ce va fi adaugat
     */
    void adauga(IteratorLP& poz, TElem e);

    /**
     * sterge elementul de pe o pozitie poz si returneaza elementul sters
     * dupa stergere, iteratorul poz este pozitionat pe urmatorul element
     * arunca exceptie daca poz nu e valid
     * complexitate timp:
     *      caz favorabil: θ(1) -> cand se adauga pe prima pozitie
     *      caz defavorabil: θ(n) -> cand se adauga pe ultima pozitie
     *      caz mediu: O(n)
     * complexitate spatiu: θ(1)
     * @param poz iterator
     * @return valoarea elementului sters
     */
    TElem sterge(IteratorLP& poz);

    /**
     * cauta un element si returneaza prima pozitie pe care acesta apare
     * sau un iterator invalid
     * complexitate timp:
     *      caz favorabil: θ(1) -> cand se adauga pe prima pozitie
     *      caz defavorabil: θ(n) -> cand se adauga pe ultima pozitie
     *      caz mediu: O(n)
     * complexitate spatiu: θ(1)
     * @param e elementul ce se cauta
     * @return pozitia elementului (iterator)
     */
    IteratorLP cauta(TElem e) const;

    /**
     * destructor
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
    */
    ~Lista();

    /**
     * functionalitate implementata in timpul laboratorului
     * elimina toate elementele unei liste
     * complexitate timp: caz favorabil = caz defavorabil = caz mediu = θ(n)
     * complexitate spatiu: θ(1)
     * @param lista lista in care se vor sterge elementele
     * @return ultimul element sters din lista
     */
     int eliminaToate(Lista &lista);
};
