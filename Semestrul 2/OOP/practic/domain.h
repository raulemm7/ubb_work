//
// Created by raulo on 6/25/2024.
//

#ifndef PRACTIC_DOMAIN_H
#define PRACTIC_DOMAIN_H

#include <string>

class Masina{
private:
    std::string nr_inmatriculare;
    std::string denumire;
    int anFabricatie;
    std::string tip;
public:
    /** constructor */
    explicit Masina(const std::string &nrInmatriculare, const std::string &denumire, int anFabricatie, const std::string &tip)
            : nr_inmatriculare(nrInmatriculare), denumire(denumire), anFabricatie(anFabricatie), tip(tip) {};

    /** getters */
    const std::string &getNrInmatriculare() const;

    const std::string &getDenumire() const;

    int getAnFabricatie() const;

    const std::string &getTip() const;

    void setAnFabricatie(int modificareAnFabricatie);

    /** destructor */
    virtual ~Masina() = default;
};

class TestDomain{
public:
    /**
     * testez getterele si setterul
     */
    static void test_all();
};

#endif //PRACTIC_DOMAIN_H
