#pragma once

#include <vector>
#define MAX_CAP 10
#define NULL_TCHEIE 0
#define NULL_TVALOARE 0

typedef int TCheie;
typedef int TValoare;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

typedef struct{
    TElem elem;
    int left;
    int right;
    int parent;
}NodABC;

class MDO {
    friend class IteratorMDO;
private:
    /* aici e reprezentarea */
    int capacity;
    int root;
    int firstFree;

    NodABC* elems;

    Relatie comp;

    NodABC aloca(TElem info);

    int tree_min(int node) const;

    void translate(int to,int from);

    void del_node(int index);

    int succesor(int index) const;

    void redim();

public:

    /** constructorul implicit al MultiDictionarului Ordonat */
    explicit MDO(Relatie r);

    /**
     * adauga un nou element in MDO
     * @param c cheie
     * @param v valoare
     *
     * complexitate timp:
     *      caz favorabil = θ(1)
     *      caz defavorabil = θ(h)
     *      caz mediu = O(h)
     * complexitate spatiu: θ(1)
     */
    void adauga(TCheie c, TValoare v);

    /**
     * cauta valorile asociate unei chei in MDO
     * @param c cheia dupa care se face cautarea
     * @return vector cu valori asociate cheii respective
     *
     * complexitate timp:
     *      caz favorabil = θ(1)
     *      caz defavorabil = θ(h)
     *      caz mediu = O(h)
     * complexitate spatiu: θ(1)
     */
    vector<TValoare> cauta(TCheie c) const;

    /**
     * sterge o cheie si valoarea ei din MDO
     * @param c cheia care se doreste a fi stearsa
     * @param v valorea asociata cheii
     * @return 1 -> s-a gasit cheia si valoarea si stergerea a fost efectuata
     *         0 -> altfel
     *
     * complexitate timp:
     *      caz favorabil = θ(1)
     *      caz defavorabil = θ(h)
     *      caz mediu = O(h)
     * complexitate spatiu: θ(1)
     */
    bool sterge(TCheie c, TValoare v);

    /**
     * @return numarul de perechi (cheie, valoare) din MDO
     *
     * complexitate timp:
     *      caz favorabil = caz defavorabil = caz mediu = θ(n)
     * complexitate spatiu: θ(1)
     */
    int dim() const;

    /**
     * verifica daca MDO e vid
     * @return 1 -> MDO nu are niciun element
     *         0 -> altfel
     *
     * complexitate timp:
     *      caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     */
    bool vid() const;

    /**
     * initializeaza un iterator pe MDO
     * @return iterator peste MDO
     *
     * complexitate timp:
     *      caz favorabil = caz defavorabil = caz mediu = θ(1)
     * complexitate spatiu: θ(1)
     */
    IteratorMDO iterator() const;

    /**
     * @return nr de ap al celei mai frecvente chei din MDO
     *
     * complexitate timp:
     *      caz favorabil = caz defavorabil = caz mediu = θ(n)
     * complexitate spatiu: θ(n)
     */
    TCheie ceaMaiFreqCheie() const;

    /** destructorul MDO */
    ~MDO();
};