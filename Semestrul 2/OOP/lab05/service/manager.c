#include <string.h>
#include "../domain/domain.h"
#include "../repo/store.h"
#include "manager.h"

//actualizari
void actualizare_pret(Lista* list,int id,int new_pret){
    Produs* p=find(list,id);
    set_pret(p,new_pret);
}

void actualizare_cantitate(Lista* list,int id,int new_cant){
    Produs* p=find(list,id);
    set_cantitate(p,new_cant);
}

//stergere
void sterge_produs(Lista* list,int id){
    int poz=-1;
    for (int i = 0; i < list->lg && poz == -1; i++)
        if (get_id(list->lista_produse[i]) == id)
            poz = i;
    if(poz!=-1){
        distruge_produs(list->lista_produse[poz]);
        for (int i = poz + 1; i < list->lg; i++)
            list->lista_produse[i - 1] = list->lista_produse[i];
        list->lg--;
    }
}

int comparare_pret(Produs* a,Produs* b){
    return a->pret>b->pret;
}

int comparare_cantitate(Produs* a,Produs* b){
    return a->cantitate>b->cantitate;
}

//sortare
void sortare(Lista* list,int(*fct)(Produs*,Produs*),int ordine){
    for(int i=0;i<list->lg-1;i++)
        for(int j=i+1;j<list->lg;j++)
            if(ordine==1){
                if(fct(list->lista_produse[i],list->lista_produse[j])==1){
                    Produs* p=list->lista_produse[i];
                    list->lista_produse[i]=list->lista_produse[j];
                    list->lista_produse[j]=p;
                }
            }
            else{
                Produs* p=list->lista_produse[i];
                list->lista_produse[i]=list->lista_produse[j];
                list->lista_produse[j]=p;
            }
}

//filtrare
Lista* filtrare_producator(Lista* list,char producator[]){
    Lista* rez=creare_lista(distruge_produs, getcopy);
    for(int i=0;i<list->lg;i++)
        if(strcmp(get_producator(list->lista_produse[i]),producator)==0)
            adaugare_produs(rez,list->lista_produse[i]);
    return rez;
}

Lista* filtrare_pret(Lista* list,int pret){
    Lista* rez=creare_lista(distruge_produs, getcopy);
    for(int i=0;i<list->lg;i++)
        if(get_pret(list->lista_produse[i])==pret)
            adaugare_produs(rez,list->lista_produse[i]);
    return rez;
}

Lista* filtrare_cantitate(Lista* list,int cantitate){
    Lista* rez=creare_lista(distruge_produs, getcopy);
    for(int i=0;i<list->lg;i++)
        if(get_cantitate(list->lista_produse[i])==cantitate)
            adaugare_produs(rez,list->lista_produse[i]);
    return rez;
}

Lista* filtrare_tip(Lista* list, char tip[])
{
    Lista* rez = creare_lista(distruge_produs, getcopy);
    for (int i = 0; i < list->lg; i++)
        if (strcmp(get_tip(list->lista_produse[i]), tip) == 0)
            adaugare_produs(rez, list->lista_produse[i]);
    return rez;
}

