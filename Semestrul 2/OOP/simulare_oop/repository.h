//
// Created by raulo on 5/24/2024.
//

#ifndef SIMULARE_OOP_REPOSITORY_H
#define SIMULARE_OOP_REPOSITORY_H

#include <string>
#include <vector>
#include "domain.h"

using namespace std;

class Repository{
private:
    vector<Pix> lista_pixuri;
    string nume_fisier;
public:
    /** constructor */
    explicit Repository(const string &numeFisier) : nume_fisier(numeFisier) {};

    /**
     * @return lista cu elemenete
     */
    vector<Pix> &getListaPixuri();

    /**
     * returneaza un pix dupa codul lui
     * @param cod codul pixului
     * @return obiect de tip pix
     */
    const Pix& getPix(int cod);

    /**
     * adauga un obiect pix la lista de elemente
     * @param pix obiectul care se doreste a fi adaugat
     */
    void adauga_pix(Pix& pix);

    /**
     * preia informatii despre pixuri din fisier
     */
    void load_from_file();

    /** destructor */
    virtual ~Repository() = default;
};

class testRepo{
public:
    static void test_all();
private:
    static void test_adauga_and_getLista();
    static void test_getPix();
    static void test_load_from_file();
};

#endif //SIMULARE_OOP_REPOSITORY_H
