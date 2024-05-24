//
// Created by raulo on 5/24/2024.
//

#ifndef SIMULARE_OOP_DOMAIN_H
#define SIMULARE_OOP_DOMAIN_H

#include <string>

using namespace std;

class Pix{
private:
    int id;
    string brand;
    string culoare;
    float pret;
public:
    Pix(int id, const string &brand, const string &culoare, float pret) : id(id), brand(brand), culoare(culoare),
                                                                        pret(pret) {};

    int getId() const;

    const string &getBrand() const;

    const string &getCuloare() const;

    float getPret() const;

    /** returneaza informatii despre pix formatat */
    const string getPixString() const;

    virtual ~Pix() = default;
};

class testDomain{
public:
    static void test_all();
};

#endif //SIMULARE_OOP_DOMAIN_H
