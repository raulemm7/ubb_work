//
// Created by raulo on 4/2/2024.
//

#ifndef LAB06_DOMAIN_H
#define LAB06_DOMAIN_H

#include <string>
#include <iostream>
#include <utility>
using std::string;

class Medicament {
private:
    int id_med{};
    string denumire;
    int pret{};
    string producator;
    string subst_activa;
public:
    /** default constructor */
    Medicament(const int id_med, const string& denumire, const int pret, const string& producator,
               const string& subst_activa) :
    id_med{id_med}, denumire{denumire}, pret{pret}, producator{producator}, subst_activa{subst_activa}{};

    /** copy constructor */
    Medicament(const Medicament& med) : id_med{med.id_med}, denumire{med.denumire}, pret{med.pret},
                                        producator{med.producator}, subst_activa{med.subst_activa} {
        std::cout << "*\n";
    }

    /** copy assignement */
    Medicament& operator=(const Medicament& oldMed);

    /** move constructor */
    Medicament(Medicament&& oldMed) noexcept;

    /** move assignement */
//    Medicament& operator=(Medicament&& oldMed) noexcept;

    /** getters */
    const int get_id() const;
    const string& get_denumire() const;
    const int get_pret() const;
    const string& get_producator() const;
    const string& get_subst_activa() const;

    /** setters */
    const void set_id(int id);
    void set_pret(const int& new_pret);
    void set_subst_activa(const string& new_subst_activa);

    // destructor
    ~Medicament() = default;

    //Medicament() = default;
};

class domainTests {
public:
    static void test_getters_and_setters();
};

#endif //LAB06_DOMAIN_H
