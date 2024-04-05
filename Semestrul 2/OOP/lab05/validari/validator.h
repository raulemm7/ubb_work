//
// Created by Titieni Paul on 11.03.2024.
//

#ifndef LAB2_4_VALIDATOR_H
#define LAB2_4_VALIDATOR_H

int validare_id(int id);
/*
    Functia valideaza un id dat
    param id: id ul care se valideaza
    return: 1 daca id ul este >0 si 0 in caz contrar
*/

int validare_tip(char tip[]);
/*
    Functia valideaza un tip dat
    param tip: tip ul care se valideaza
    return: 1 daca tip ul este unul valid si 0 in caz contrar
*/

int validare_producator(char producator[]);
/*
    Functia valideaza un producator dat
    param producator: producator ul care se valideaza
    return: 1 daca producator ul este unul valid si 0 in caz contrar
*/

int validare_pret(int pret);
/*
    Functia valideaza un pret dat
    param pret: pret ul care se valideaza
    return: 1 daca pret ul este >=0 si 0 in caz contrar
*/

int validare_cantitate(int cantitiate);
/*
    Functia valideaza un cantitiate data
    param cantitiate: cantitiate care se valideaza
    return: 1 daca cantitiatea este >0 si 0 in caz contrar
*/

#endif //LAB2_4_VALIDATOR_H
