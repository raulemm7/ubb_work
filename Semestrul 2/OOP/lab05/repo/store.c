
#include <string.h>
#include <stdlib.h>
#include "../domain/domain.h"
#include "store.h"

Lista* creare_lista(void(*destructor)(void*), void* (*egetter)(void*))
{
    Lista* l = (Lista*)malloc(sizeof(Lista));
    if (l) {
        l->lista_produse = (void**)malloc(2 * sizeof(void*));

        l->lg = 0;
        l->cp = 2;

        l->destroy_entity = destructor;
        l->elem_get = egetter;
    }
    return l;
}

void distruge_lista(Lista* l) {
    for (int i = 0; i < l->lg; i++)
        l->destroy_entity(l->lista_produse[i]);
    free(l->lista_produse);

    free(l);
}

void distruge_last_elem(Lista* l)
{
    l->lg--;
    l->destroy_entity(l->lista_produse[l->lg]);
}

void redimensionare(Lista* l) {
    void** l_prods = l->lista_produse;

    l->lista_produse = (void**)malloc(2 * l->cp * sizeof(void*));
    l->cp *= 2;

    if (l->lista_produse)
        for (int i = 0; i < l->lg; i++)
            l->lista_produse[i] = l_prods[i];

    free(l_prods);
}

Produs* find(Lista* list, int id) {
    Produs* p = NULL;
    for (int i = 0; i < list->lg; i++)
        if (get_id(list->lista_produse[i]) == id)
            p = list->lista_produse[i];
    return p;
}

void adaugare_produs(Lista* lista, Produs* p) {
    int id = get_id(p), cant = get_cantitate(p);
    Produs* p_local = find(lista, id);
    if (p_local != NULL) {
        int new_cant = p_local->cantitate + cant;
        set_cantitate(p_local, new_cant);
    }
    else {
        if (lista->lg == lista->cp)
            redimensionare(lista);
        lista->lista_produse[lista->lg] = p;
        lista->lg++;
    }
}

void add(Lista* lista, void* p)
{
    if (lista->lg == lista->cp)
        redimensionare(lista);
    lista->lista_produse[lista->lg] = p;
    lista->lg++;
}

Lista* copyList(Lista* lista)
{
    Lista* new = creare_lista(lista->destroy_entity, lista->elem_get);
    for (int i = 0; i < lista->lg; i++)
    {
        void* p = lista->elem_get(lista->lista_produse[i]);
        add(new, p);
    }
    return new;
}

