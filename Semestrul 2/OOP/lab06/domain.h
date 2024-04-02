//
// Created by raulo on 4/2/2024.
//

#ifndef LAB06_DOMAIN_H
#define LAB06_DOMAIN_H

#include <string>
using std::string;

class Medicament {
private:
    int id_med;
    string denumire;
    int pret;
    string producator;
    string subst_activa;
public:
    // constructor
    Medicament(int id_med, string denumire, int pret, string producator, string subst_activa);

    // getters
    [[nodiscard]] int get_id() const;
    [[nodiscard]] string get_denumire() const;
    [[nodiscard]] int get_pret() const;
    [[nodiscard]] string get_producator() const;
    [[nodiscard]] string get_subst_activa() const;

    // setters
    void set_id(const int& id);
    void set_pret(const int& new_pret);
    void set_subst_activa(const string& new_subst_activa);
};

class domainTests {
public:
    static void test_getters_and_setters();
};

#endif //LAB06_DOMAIN_H
