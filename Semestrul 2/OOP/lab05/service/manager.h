//
// Created by Titieni Paul on 11.03.2024.
//

#ifndef LAB2_4_MANAGER_H
#define LAB2_4_MANAGER_H
#include "../domain/domain.h"
#include "../repo/store.h"

/*
    Functia actualizeaza pretul produsului, cu id ul dat din lista data, cu pretul dat
    parametrii:
        list: adresa listei in care se cauta
        id: id ul produslui pentru care se doreste actualizarea,id>0
        new_pret: noul pret al produslui cu id ul dat,new_pret>=0
    return:
*/
void actualizare_pret(Lista* list,int id,int new_pret);

/*
    Functia actualizeaza cantitatea produsului, cu id ul dat din lista data, cu cantitatea data
    parametrii:
        list: adresa listei in care se cauta
        id: id ul produslui pentru care se doreste actualizarea,id>0
        new_cant: noua cantitate a produslui cu id ul dat,new_cant>0
    return:
*/
void actualizare_cantitate(Lista* list,int id,int new_cant);

/*
    Functia sterge din lista data, produsul cu id ul dat
    parametrii:
        -list: adresa listei pentru care se doreste stergerea
        -id: id ul produsului care se doreste a fi sters,id>0
    return:
*/
void sterge_produs(Lista* list,int id);

/*
    Functia sorteaza produsele din lista data, crescator pentru ordine 1 si descrescator
    pentru ordine 2,dupa pret
    parametrii:
        -list: adresa listei care se sorteaza
        -ordine: codificator al ordinii de sortare (1=>crescator, 2=>descrescator)
    return:
*/

int comparare_pret(Produs* a,Produs* b);

int comparare_cantitate(Produs* a,Produs* b);

void sortare(Lista* list,int(*fct)(Produs*,Produs*),int ordine);

/*
    Functia filtreaza lista data in functie de producatorul dat
    parametrii:
        -list: adresa listei pentru care se realizeaza filtrarea
        -producator: producatorul in functie de care se face filtrarea
    return: functia returneaza o Lista care contine produsuele ce au producatorul dat
*/

Lista* filtrare_producator(Lista* list,char producator[]);

/*
    Functia filtreaza lista data in functie de pretul dat
    parametrii:
        -list: adresa listei pentru care se realizeaza filtrarea
        -producator: pretul in functie de care se face filtrarea,pret>=0
    return: functia returneaza o Lista care contine produsuele ce au pretul dat
*/
Lista* filtrare_pret(Lista* list,int pret);

/*
    Functia filtreaza lista data in functie de cantitatea data
    parametrii:
        -list: adresa listei pentru care se realizeaza filtrarea
        -cantitate: cantitatea in functie de care se face filtrarea,cantitate>0
    return: functia returneaza o Lista care contine produsuele ce au cantitatea data
*/
Lista* filtrare_cantitate(Lista* list,int cantitate);

/*
    Functia filtreaza lista data in functie de producatorul dat
    parametrii:
        -list: adresa listei pentru care se realizeaza filtrarea
        -producator: producatorul in functie de care se face filtrarea
    return: functia returneaza o Lista care contine produsuele ce au producatorul dat
*/

Lista* filtrare_tip(Lista* list, char tip[]);

#endif //LAB2_4_MANAGER_H
