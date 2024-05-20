//
// Created by raulo on 5/14/2024.
//

#ifndef PROIECT_TAD_4_DICTIONAR_H
#define PROIECT_TAD_4_DICTIONAR_H

#define MAX 701
#define NULL_TVALOARE (-1)
typedef int TCheie;
typedef int TValoare;

class IteratorDictionar;
class Dictionar;

#include <utility>
typedef std::pair<TCheie,TValoare> TElem;

class Nod{
private:
    TElem elem;
    Nod* urm;
public:
    friend class Dictionar;
    friend class IteratorDictionar;
    Nod(TElem elem,Nod* urm);
};

class Dictionar {
    friend class IteratorDictionar;

private:
    /** aici e reprezentarea */
    /** dictionar folosind tabela de dispersie,
     * rezolvare coliziuni prin liste independente */
    int m; // capacitatea dictionarului
    Nod* comp[MAX]; // vector static cu liste independente

    int d(TCheie ch) const;  // functia de dispersie

public:
    /** constructorul implicit al dictionarului */
    Dictionar();

    /**
     * adauga un nou element in dictionar
     * @param c cheia elementului
     * @param v valoarea elementului
     * @return daca cheia exista deja in dictionar, actualizeaza valoarea si returneaza vechea valoare
     *         null_tvaloare altfel
     *
     * complexitate spatiu: θ(1)
     * complexitate timp:
     *      caz favorabil = caz defavorabil = caz mediu = θ(1)
     */
    TValoare adauga(TCheie c, TValoare v);

    /**
     * cauta o cheie intr un dictionar
     * @param c cheia dupa care se face cautarea
     * @return valoarea asociata, daca cheia se afla in dictionar
     *         null_tvaloare, altfel
     *
     * complexitate spatiu: θ(1)
     * complexitate timp:
     *      caz favorabil = θ(1), elementul se află în capul listei tabelei de dispersie
     *      caz defavorabil = θ(n), toate elementele se dispersează în aceeași locație
     *      caz mediu = θ(1)
     */
    TValoare cauta(TCheie c) const;

    /**
     * sterge o cheie dintr un dictionar
     * @param c cheia care se doreste a fi stearsa
     * @return valoarea asociata, daca cheia exista in dicitonar
     *         null_tvaloare, altfel
     *
     * complexitate spatiu: θ(1)
     * complexitate timp:
     *      caz favorabil = θ(1), elementul ce trebuie sters e in capul listei
     *      caz defavorabil = θ(n), trebuie parcursă toată lista și toate elementele se dispersează în aceeași locație
     *      caz mediu = θ(1)
     */
    TValoare sterge(TCheie c);

    /**
     * dimensiunea unui dictionar
     * @return numarul de elemente din dictionar
     *
     * complexitate spatiu: θ(1)
     * complexitate timp:
     *      caz favorabil = caz defavorabil = caz mediu = θ(1)
     */
    int dim() const;

    /**
     * verifica daca dictionarul e vid
     * @return 1, daca nu se afla elemente in dictionar
     *         0, altfel
     *
     * complexitate spatiu: θ(1)
     * complexitate timp:
     *      caz favorabil = caz defavorabil = caz mediu = θ(1)
     */
    bool vid() const;

    /**
     * creeaza un iterator pe dictionar
     * @return iterator pe dictionar
     *
     * complexitate spatiu: θ(1)
     * complexitate timp:
     *      caz favorabil = caz defavorabil = caz mediu = θ(1)
     */
    IteratorDictionar iterator() const;

    /**
     * goleste un dictionar
     *
     * complexitate spatiu: θ(1)
     * complexitate timp:
     *      caz favorabil = caz defavorabil = caz mediu = θ(n)
     */
    void golire();

    /** destructorul dictionarului */
    ~Dictionar();

};

#endif //PROIECT_TAD_4_DICTIONAR_H
