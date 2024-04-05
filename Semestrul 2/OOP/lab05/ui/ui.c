#include <stdio.h>
#include "../validari/validator.h"
#include "../service/manager.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "ui.h"

void print_m() {
    printf("p. Afisare lista produse\n");
    printf("k. Afiseaza undo\n");
    printf("u. Executa undo\n");
    printf("f. Fast add\n");
    printf("1. Adauga un produs\n");
    printf("2. Actualizare produs\n");
    printf("3. Sterge produs\n");
    printf("4. Ordonare produse\n");
    printf("5. Vizualizare lista produse filtrate dupa un criteriu\n");
    printf("6. Iesire\n");
}

void void_afisare_undo(Lista* undo)
{
    printf("Lungimea undo-ului este %d: \n", undo->lg);
    for (int i = 0; i < undo->lg; i++)
    {
        printf("Lista %d: \n", i);
        afisare_produse(undo->lista_produse[i]);
        printf("\n");
    }
}

void afisare_produse(Lista* list) {
    if (list->lg == 0)
        printf("Nu exista produse\n");
    else {
        for (int i = 0; i < list->lg; i++) {
            int id = get_id(list->lista_produse[i]);
            char* tip = get_tip(list->lista_produse[i]);
            char* producator = get_producator(list->lista_produse[i]);
            char* model = get_model(list->lista_produse[i]);
            int pret = get_pret(list->lista_produse[i]);
            int cantitate = get_cantitate(list->lista_produse[i]);
            printf("Id: %d | Tip: %s | Producator: %s | Model: %s | Pret: %d | Cantitate: %d\n", id, tip, producator, model, pret, cantitate);
        }
    }
}

void adaugare_produs_ui(Lista* list, Lista* undo) {
    int id;
    int c = 1;
    while (c == 1) {
        printf("Introduceti id-ul: ");
        scanf_s("%d", &id);
        if (validare_id(id))
            c = 2;
        else
            printf("Id invalid\n");
    }

    char tip[21];
    c = 1;
    while (c == 1) {
        printf("Introduceti tipul: ");
        scanf_s("%s", tip, 21);
        if (validare_tip(tip))
            c = 2;
        else
            printf("Tip invalid\n");
    }

    char producator[21];
    c = 1;
    while (c == 1) {
        printf("Introduceti producatorul: ");
        scanf_s("%s", producator, 21);
        if (validare_producator(producator))
            c = 2;
        else
            printf("Producator invalid\n");
    }
    char model[21];
    printf("Introduceti modelul: ");
    scanf_s("%s", model, 21);

    int pret;
    c = 1;
    while (c == 1) {
        printf("Introduceti pretul: ");
        scanf_s("%d", &pret);
        if (validare_pret(pret))
            c = 2;
        else
            printf("Pret invalid\n");
    }

    int cantitate;
    c = 1;
    while (c == 1) {
        printf("Introduceti cantitatea: ");
        scanf_s("%d", &cantitate);
        if (validare_cantitate(cantitate))
            c = 2;
        else
            printf("Cantitate invalida\n");
    }

    Produs* p = creare_produs(id, tip, producator, model, pret, cantitate);
    add(undo, copyList(list));
    adaugare_produs(list, p);
}

void actualizare_produs_ui(Lista* list, Lista* undo) {
    int id;
    int c = 1;
    while (c == 1) {
        printf("Introduceti id-ul produsului pentru care doriti actualizarea: ");
        scanf_s("%d", &id);
        if (validare_id(id))
            c = 2;
        else
            printf("Id invalid\n");
    }
    Produs* p = find(list, id);
    if (p != NULL) {
        int cmd;
        printf("Ce doriti sa actualizati?\n");
        printf("    1. Pretul\n");
        printf("    2. Cantitatea\n");
        printf("    3. Ambele\nComanda: ");
        scanf_s("%d", &cmd);
        if (cmd == 1) {
            int new_pret;
            c = 1;
            while (c == 1) {
                printf("Introduceti noul pret: ");
                scanf_s("%d", &new_pret);
                if (validare_pret(new_pret))
                    c = 2;
                else
                    printf("Pret invalid\n");
            }
            add(undo, copyList(list));
            actualizare_pret(list, id, new_pret);
        }
        else if (cmd == 2) {
            int new_cant;
            c = 1;
            while (c == 1) {
                printf("Introduceti noua cantitate: ");
                scanf_s("%d", &new_cant);
                if (validare_cantitate(new_cant))
                    c = 2;
                else
                    printf("Cantitate invalida\n");
            }
            add(undo, copyList(list));
            actualizare_cantitate(list, id, new_cant);
        }
        else if (cmd == 3) {
            int new_pret;
            c = 1;
            while (c == 1) {
                printf("Introduceti noul pret: ");
                scanf_s("%d", &new_pret);
                if (validare_pret(new_pret))
                    c = 2;
                else
                    printf("Pret invalid\n");
            }
            add(undo, copyList(list));
            actualizare_pret(list, id, new_pret);
            int new_cant;
            c = 1;
            while (c == 1) {
                printf("Introduceti noua cantitate: ");
                scanf_s("%d", &new_cant);
                if (validare_cantitate(new_cant))
                    c = 2;
                else
                    printf("Cantitate invalida\n");
            }
            add(undo, copyList(list));
            actualizare_cantitate(list, id, new_cant);
        }
        else {
            printf("Comanda invalida\n");
        }
    }
    else
        printf("Nu exista niciun produs cu id-ul dat\n");

}

void sterge_produs_ui(Lista* list, Lista* undo) {
    int id;
    int c = 1;
    while (c == 1) {
        printf("Introduceti id-ul produsului pe care doriti sa-l stergeti: ");
        scanf_s("%d", &id);
        if (validare_id(id))
            c = 2;
        else
            printf("Id invalid\n");
    }
    Produs* p = find(list, id);
    if (p != NULL) {
        add(undo, copyList(list));
        sterge_produs(list, id);
    }
    else {
        printf("Nu exista niciun produs cu id-ul dat\n");
    }
}

void sortare_ui(Lista* list) {
    if (list->lg > 0) {
        int ord;
        int c1 = 1;
        while (c1 == 1) {
            printf("Cum doriti sa se sorteze lista?\n");
            printf("    1. Crescator\n");
            printf("    2. Descrescator\nAlegeti optiunea: ");
            scanf_s("%d", &ord);
            if (ord == 1 || ord == 2)
                c1 = 2;
            else
                printf("Optiune invalida\n");
        }
        int c2 = 1;
        int criteriu;
        int(*fct1)(Produs*, Produs*);
        fct1 = comparare_pret;
        int(*fct2)(Produs*, Produs*);
        fct2 = comparare_cantitate;
        while (c2 == 1) {
            printf("Care doriti sa fie criteriul de sortare?\n");
            printf("    1. Dupa pret\n");
            printf("    2. Dupa cantitate\nAlegeti optiunea: ");
            scanf_s("%d", &criteriu);
            if (criteriu == 1)
                sortare(list, fct1, ord), afisare_produse(list), c2 = 2;
            else if (criteriu == 2)
                sortare(list, fct2, ord), afisare_produse(list), c2 = 2;
            else
                printf("Optiune invalida\n");
        }
    }
    else
        printf("Nu exista niciun produs in lista\n");
}

void filtrare_ui(Lista* list) {
    if (list->lg > 0) {
        int criteriu;
        int c = 1;
        while (c == 1) {
            printf("Care doriti sa fie criteriul de filtrare?\n");
            printf("    1.Producator\n");
            printf("    2.Pret\n");
            printf("    3.Cantitate\n");
            printf("    4.Tip\nAlegeti optiunea: ");
            scanf_s("%d", &criteriu);
            if (criteriu == 1) {
                c = 2;
                char producator[21];
                int c1 = 1;
                while (c1 == 1) {
                    printf("Introduceti producatorul: ");
                    scanf_s("%s", producator, 21);
                    if (validare_producator(producator))
                        c1 = 2;
                    else
                        printf("Producator invalid\n");
                }
                Lista* l = filtrare_producator(list, producator);
                afisare_produse(l);
            }
            else if (criteriu == 2) {
                c = 2;
                int pret;
                int c1 = 1;
                while (c1 == 1) {
                    printf("Introduceti pretul: ");
                    scanf_s("%d", &pret);
                    if (validare_pret(pret))
                        c1 = 2;
                    else
                        printf("Pret invalid\n");
                }
                Lista* l = filtrare_pret(list, pret);
                afisare_produse(l);
            }
            else if (criteriu == 3) {
                c = 2;
                int cantitate;
                int c1 = 1;
                while (c1 == 1) {
                    printf("Introduceti cantiatea: ");
                    scanf_s("%d", &cantitate);
                    if (validare_cantitate(cantitate))
                        c1 = 2;
                    else
                        printf("Pret invalid\n");
                }
                Lista* l = filtrare_cantitate(list, cantitate);
                afisare_produse(l);
            }
            else if (criteriu == 4) {
                c = 2;
                char tip[21];
                int c1 = 1;
                while (c1 == 1) {
                    printf("Introduceti tipul: ");
                    scanf_s("%s", tip, 21);
                    if (validare_tip(tip))
                        c1 = 2;
                    else
                        printf("Tip invalid\n");
                }
                Lista* l = filtrare_tip(list, tip);
                afisare_produse(l);
            }
            else
                printf("Optiune invalida\n");
        }
    }
    else
        printf("Nu exista niciun produs in lista\n");
}

void do_undo(Lista** list, Lista* undo)
{
    if (undo->lg == 0)
        printf("Nu mai poti face undo \n");
    else
    {
        Lista* cache = *list;
        Lista* lastofundo = undo->lista_produse[undo->lg - 1];
        *list = copyList(lastofundo);
        distruge_last_elem(undo);
        distruge_lista(cache);
    }
}

void fastadd(Lista* list, Lista* undo)
{
    Produs* p = creare_produs(1, "laptop", "asus", "pro22", 3200, 25);
    add(undo, copyList(list));
    adaugare_produs(list, p);
    Produs* q = creare_produs(2, "laptop", "acer", "nitro 5", 2300, 20);
    adaugare_produs(list, q);
    Produs* r = creare_produs(3, "televizor", "apple", "mac 6", 3400, 15);
    adaugare_produs(list, r);
}

void start_program(Lista* list, Lista* undo) {
    int c = 1;
    while (c == 1) {
        char optiune;
        print_m();
        printf("Alegeti o optiune: ");
        scanf_s(" %c", &optiune, 30);
        switch (optiune)
        {
        case 'k':
            void_afisare_undo(undo);
            break;
        case 'f':
            fastadd(list, undo);
            break;
        case 'u':
            do_undo(&list, undo);
            break;
        case 'p':
            afisare_produse(list);
            break;
        case '1':
            adaugare_produs_ui(list, undo);
            break;
        case '2':
            actualizare_produs_ui(list, undo);
            break;
        case '3':
            sterge_produs_ui(list, undo);
            break;
        case '4':
            sortare_ui(list);
            break;
        case '5':
            filtrare_ui(list);
            break;
        case '6':
            c = 2;
            break;
        default:
            printf("Optiune invalida\n");
            break;
        }
    }
}
