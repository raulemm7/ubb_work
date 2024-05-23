//
// Created by raulo on 5/23/2024.
//

#ifndef SIMULARE_IMBRACAMINTE_DOMAIN_H
#define SIMULARE_IMBRACAMINTE_DOMAIN_H

#include <string>

using namespace std;

class Imbracaminte{
private:
    string tip;
    string culoare;
    int pret;
public:
    /** constructor */
    Imbracaminte(const string &tip, const string &culoare, int pret) : tip(tip), culoare(culoare),
                                                                         pret(pret) {};

    /** returneaza tipul unei imbracaminte */
    const string &getTip() const {
        return this->tip;
    }

    /** returneaza culoarea unei imbracaminte */
    const string &getCuloare() const {
        return this->culoare;
    }

    /** returneaza pretul unei imbracaminte */
    int getPret() const {
        return this->pret;
    }

    /** destructor */
    virtual ~Imbracaminte() = default;
};

class testDomain{
public:
    static void test_all();
};

#endif //SIMULARE_IMBRACAMINTE_DOMAIN_H
