#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../service/manager.h"
#include "../validari/validator.h"
#include "teste.h"

void test_creare_produs(){
    Produs* p=creare_produs(1,"tractor","John","F90",100,2);
    assert(get_id(p)==1);
    assert(strcmp(get_tip(p),"tractor")==0);
    assert(strcmp(get_producator(p),"John")==0);
    assert(strcmp(get_model(p),"F90")==0);
    assert(get_pret(p)==100);
    assert(get_cantitate(p)==2);
    distruge_produs(p);
}

void test_get_set(){
    Produs* p=creare_produs(1,"tractor","John Deere","F90",100,2);
    assert(get_id(p)==1);
    assert(strcmp(get_tip(p),"tractor")==0);
    assert(strcmp(get_producator(p),"John Deere")==0);
    assert(strcmp(get_model(p),"F90")==0);
    assert(get_pret(p)==100);
    assert(get_cantitate(p)==2);
    set_cantitate(p,5);
    assert(get_cantitate(p)==5);
    assert(get_pret(p)==100);
    set_pret(p,125);
    assert(get_pret(p)==125);
    distruge_produs(p);
}

void test_actualizare_pret(){
    Lista* l=creare_lista(distruge_produs, getcopy);
    Produs* p=creare_produs(1,"laptop","apple","pro22",65,1);
    add(l,p);
    assert(get_pret(l->lista_produse[0])==65);
    actualizare_pret(l,1,74);
    assert(get_pret(l->lista_produse[0])==74);
    distruge_lista(l);
}

void test_actualizare_cantitate(){
    Lista* l=creare_lista(distruge_produs, getcopy);
    Produs* p=creare_produs(1,"laptop","apple","pro22",65,1);
    adaugare_produs(l,p);
    assert(get_cantitate(l->lista_produse[0])==1);
    actualizare_cantitate(l,1,2);
    assert(get_cantitate(l->lista_produse[0])==2);
    distruge_lista(l);
}

void test_sterge_produs(){
    Lista* l=creare_lista(distruge_produs, getcopy);
    Produs* p=creare_produs(1,"laptop","apple","pro22",65,1);
    Produs* p2= creare_produs(2,"telefon","apple","12",47,1);
    adaugare_produs(l,p);
    adaugare_produs(l,p2);
    assert(l->lg==2);
    sterge_produs(l,3);
    assert(l->lg==2);
    sterge_produs(l,1);
    assert(l->lg==1);
    assert(get_id(l->lista_produse[0])==2);
    distruge_lista(l);
}

void test_sortare_dupa_pret(){
    Lista* l=creare_lista(distruge_produs, getcopy);
    Produs* p1=creare_produs(1,"laptop","apple","pro22",65,3);
    Produs* p2=creare_produs(2,"laptop","asus","rog",32,1);
    Produs* p3=creare_produs(3,"laptop","hp","legion",76,5);
    adaugare_produs(l,p1);
    adaugare_produs(l,p2);
    adaugare_produs(l,p3);
    assert(l->lg==3);
    sortare(l,comparare_pret,1);
    assert(get_id(l->lista_produse[0])==2);
    assert(get_id(l->lista_produse[1])==1);
    assert(get_id(l->lista_produse[2])==3);
    sortare(l,comparare_pret,2);
    assert(get_id(l->lista_produse[0])==3);
    assert(get_id(l->lista_produse[1])==1);
    assert(get_id(l->lista_produse[2])==2);
    distruge_lista(l);
}

void test_sortare_dupa_cantiate(){
    Lista* l=creare_lista(distruge_produs, getcopy);
    Produs* p1=creare_produs(1,"laptop","apple","pro22",65,3);
    Produs* p2=creare_produs(2,"laptop","asus","rog",32,1);
    Produs* p3=creare_produs(3,"laptop","hp","legion",76,5);
    adaugare_produs(l,p1);
    adaugare_produs(l,p2);
    adaugare_produs(l,p3);
    assert(l->lg==3);
    sortare(l,comparare_cantitate,1);
    assert(get_id(l->lista_produse[0])==2);
    assert(get_id(l->lista_produse[1])==1);
    assert(get_id(l->lista_produse[2])==3);
    sortare(l,comparare_cantitate,2);
    assert(get_id(l->lista_produse[0])==3);
    assert(get_id(l->lista_produse[1])==1);
    assert(get_id(l->lista_produse[2])==2);
    distruge_lista(l);
}

void test_filtrare_producator(){
    Lista* l=creare_lista(distruge_produs, getcopy);
    Produs* p1=creare_produs(1,"laptop","apple","pro22",65,3);
    Produs* p2=creare_produs(2,"laptop","asus","rog",32,1);
    Produs* p3=creare_produs(3,"laptop","apple","legion",76,5);
    adaugare_produs(l,p1);
    adaugare_produs(l,p2);
    adaugare_produs(l,p3);
    assert(l->lg==3);
    Lista* rez1=filtrare_producator(l,"apple");
    assert(get_id(rez1->lista_produse[0])==1);
    assert(get_id(rez1->lista_produse[1])==3);
    Lista* rez2=filtrare_producator(l,"hp");
    assert(rez2->lg==0);
    free(rez1->lista_produse);
    free(rez2->lista_produse);
    distruge_lista(l);
    free(rez1);
    free(rez2);
}

void test_filtrare_tip()
{
    Lista* l = creare_lista(distruge_produs, getcopy);
    Produs* p1 = creare_produs(1, "laptop", "apple", "pro22", 65, 3);
    Produs* p2 = creare_produs(2, "frigider", "asus", "rog", 32, 1);
    Produs* p3 = creare_produs(3, "laptop", "apple", "legion", 76, 5);
    adaugare_produs(l, p1);
    adaugare_produs(l, p2);
    adaugare_produs(l, p3);
    assert(l->lg == 3);
    Lista* rez1 = filtrare_tip(l, "laptop");
    assert(get_id(rez1->lista_produse[0]) == 1);
    assert(get_id(rez1->lista_produse[1]) == 3);
    Lista* rez2 = filtrare_tip(l, "televizor");
    assert(rez2->lg == 0);
    free(rez1->lista_produse);
    free(rez2->lista_produse);
    distruge_lista(l);
    free(rez1);
    free(rez2);
}

void test_filtrare_pret(){
    Lista* l=creare_lista(distruge_produs, getcopy);
    Produs* p1=creare_produs(1,"laptop","apple","pro22",65,3);
    Produs* p2=creare_produs(2,"laptop","asus","rog",32,1);
    Produs* p3=creare_produs(3,"laptop","apple","legion",32,5);
    adaugare_produs(l,p1);
    adaugare_produs(l,p2);
    adaugare_produs(l,p3);
    assert(l->lg==3);
    Lista* rez1=filtrare_pret(l,32);
    assert(get_id(rez1->lista_produse[0])==2);
    assert(get_id(rez1->lista_produse[1])==3);
    Lista* rez2=filtrare_pret(l,123);
    assert(rez2->lg==0);
    free(rez1->lista_produse);
    free(rez2->lista_produse);
    distruge_lista(l);
    free(rez1);
    free(rez2);
}

void test_filtrare_cantitate(){
    Lista* l=creare_lista(distruge_produs, getcopy);
    Produs* p1=creare_produs(1,"laptop","apple","pro22",65,3);
    Produs* p2=creare_produs(2,"laptop","asus","rog",32,3);
    Produs* p3=creare_produs(3,"laptop","hp","legion",32,5);
    adaugare_produs(l,p1);
    adaugare_produs(l,p2);
    adaugare_produs(l,p3);
    assert(l->lg==3);
    Lista* rez1=filtrare_cantitate(l,3);
    assert(get_id(rez1->lista_produse[0])==1);
    assert(get_id(rez1->lista_produse[1])==2);
    Lista* rez2=filtrare_cantitate(l,7);
    assert(rez2->lg==0);
    free(rez1->lista_produse);
    free(rez2->lista_produse);
    distruge_lista(l);
    free(rez1);
    free(rez2);
}

//teste repo
void test_creare_lista(){
    Lista* l=creare_lista(distruge_produs, getcopy);
    assert(l->lg==0);
    distruge_lista(l);
}

void test_adaugare_produs(){
    Lista* list=creare_lista(distruge_produs, getcopy);
    Produs* p1=creare_produs(1,"tractor","John Deere","F90",100,2);
    Produs* p2=creare_produs(2,"masina","Porche","991",300,1);
    Produs* p3=creare_produs(1,"tractor","John Deere","F90",100,5);
    assert(list->lg==0);
    adaugare_produs(list,p1);
    assert(list->lg==1);
    assert(get_cantitate(list->lista_produse[0])==2);
    adaugare_produs(list,p2);
    assert(list->lg==2);
    adaugare_produs(list,p3);
    assert(list->lg==2);
    assert(get_id(list->lista_produse[0])==1);
    assert(get_cantitate(list->lista_produse[0])==7);
    assert(get_id(list->lista_produse[1])==2);
    distruge_lista(list);
    distruge_produs(p3);
}

void test_find(){
    Lista* list=creare_lista(distruge_produs, getcopy);
    Produs* p1=creare_produs(1,"tractor","John Deere","F90",100,2);
    Produs* p2=creare_produs(2,"masina","Porche","991",300,1);
    adaugare_produs(list,p1);
    adaugare_produs(list,p2);
    Produs* p1_test=find(list,1);
    assert(get_id(p1_test)==1);
    assert(get_cantitate(p1_test)==2);
    assert(get_pret(p1_test)==100);
    Produs* p2_test=find(list,3);
    assert(p2_test==NULL);
    distruge_lista(list);
}

void test_redimensionare(){
    Lista* l=creare_lista(distruge_produs, getcopy);
    Produs* p1=creare_produs(1,"laptop","apple","pro22",65,3);
    Produs* p2=creare_produs(2,"laptop","asus","rog",32,1);
    Produs* p3=creare_produs(3,"laptop","hp","legion",76,5);
    Produs* p4=creare_produs(4,"laptop","asus","rog",32,1);
    Produs* p5=creare_produs(5,"laptop","hp","legion",76,5);
    adaugare_produs(l,p1);
    adaugare_produs(l,p2);
    assert(l->cp==2);
    add(l,p3);
    assert(l->cp==4);
    adaugare_produs(l,p4);
    adaugare_produs(l,p5);
    assert(l->cp==8);
    assert(l->lg==5);
    distruge_last_elem(l);
    distruge_lista(l);
}

void test_copylist()
{
    Lista* l = creare_lista(distruge_produs, getcopy);
    Produs* p1 = creare_produs(1, "laptop", "apple", "pro22", 65, 3);
    Produs* p2 = creare_produs(2, "laptop", "asus", "rog", 32, 1);
    adaugare_produs(l, p1);
    adaugare_produs(l, p2);
    Lista* aux = copyList(l);

    assert(aux->lg == 2);
    distruge_lista(l);
    distruge_lista(aux);
}

void test_list_of_list()
{
    Lista* undo = creare_lista(distruge_lista, copyList);
    Lista* l = creare_lista(distruge_produs, getcopy);
    Produs* p1 = creare_produs(1, "laptop", "apple", "pro22", 65, 3);
    Produs* p2 = creare_produs(2, "laptop", "asus", "rog", 32, 1);
    adaugare_produs(l, p1);
    adaugare_produs(l, p2);
    add(undo, l);

    assert(undo->lg == 1);
    Lista* p = undo->lista_produse[0];
    assert(get_pret(p->lista_produse[1]) == 32);
    add(undo, copyList(l));
    assert(undo->lg == 2);

    p = undo->lista_produse[1];
    assert(get_pret(p->lista_produse[1]) == 32);
    distruge_lista(undo);
}

//teste validari

void test_validare_id(){
    int id=-1;
    assert(validare_id(id)==0);
    id=1;
    assert(validare_id(id)==1);
}

void test_validare_tip(){
    char tip1[]="masina";
    assert(validare_tip(tip1)==0);
    char tip2[]="telefon";
    assert(validare_tip(tip2)==1);
}

void test_validare_producator(){
    char tip1[]="dd";
    assert(validare_producator(tip1)==0);
    char tip2[]="apple";
    assert(validare_producator(tip2)==1);
}

void test_validare_pret(){
    int pret=-1;
    assert(validare_pret(pret)==0);
    pret=1;
    assert(validare_pret(pret)==1);
}

void test_validare_cantitate(){
    int cantitate=-1;
    assert(validare_cantitate(cantitate)==0);
    cantitate=1;
    assert(validare_cantitate(cantitate)==1);
}

//run teste
void run_teste(){
    //teste service
    test_creare_produs();
    test_get_set();
    test_actualizare_pret();
    test_actualizare_cantitate();
    test_sterge_produs();
    test_sortare_dupa_pret();
    test_sortare_dupa_cantiate();
    test_filtrare_producator();
    test_filtrare_pret();
    test_filtrare_cantitate();
    ////teste repo
    test_adaugare_produs();
    test_find();
    test_creare_lista();
    test_redimensionare();
    //teste validari
    test_validare_id();
    test_validare_tip();
    test_validare_producator();
    test_validare_pret();
    test_validare_cantitate();
    //new tests
    test_copylist();
    test_list_of_list();
    test_filtrare_tip();
}
