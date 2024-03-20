/*
#include <iostream>
#include <fstream>

#define INFINIT (INT_MAX/2 - 10000)

using namespace std;

ifstream in("fisier_in_graf_orientat.txt");

// 1. Implementați algoritmul lui Moore pentru un graf orientat neponderat
// (algoritm bazat pe Breath-first search, vezi cursul 2).
// !!!! ATENTIE !!!!
// Algortimul este implementat pentru un graf orientat;
// nodul sursa si nodul destinatie sunt citite de la tastatura;

int nr_varfuri, matrice[256][256];
int lungime[256], parinte[256];

void alg_moore(int nod_sursa) {
    // initializare
    lungime[nod_sursa] = 0;
    parinte[nod_sursa] = 0;
    for(int i = 1; i <= nr_varfuri; i++) {
        if(i != nod_sursa)
            lungime[i] = INFINIT;
    }

    // initializare coada
    int coada[256] = {};
    int st, dr;
    st = dr = 1;
    coada[1] = nod_sursa;

    // parcurgere
    while(st <= dr) {
        int x = coada[st];
        for(int i = 1; i <= nr_varfuri; i++) {
            if(matrice[x][i] and lungime[i] == INFINIT) {
                lungime[i] = lungime[x] + 1;
                parinte[i] = x;
                dr++;
                coada[dr] = i;
            }
        }
        st++;
    }
}

void reconstituire_drum(int nod_destinatie) {
    if(nod_destinatie) {
        reconstituire_drum(parinte[nod_destinatie]);
        cout << nod_destinatie << " ";
    }
}

int main() {
    int x, y;
    in >> nr_varfuri;
    while(in >> x >> y) {
        matrice[x][y] = 1;
    }

    int nod_sursa;
    cout << "Dati nodul sursa: ";
    cin >> nod_sursa;

    alg_moore(nod_sursa);

    int nod_destinatie;
    cout << "Dati nodul destinatie: ";
    cin >> nod_destinatie;

    if(lungime[nod_destinatie] == INFINIT) {
        cout << "Nu exista un lant catre acest nod!";
    }
    else {
        cout << "Lantul de la nodul " << nod_sursa << " la nodul " << nod_destinatie;
        cout << " are lungimea " << lungime[nod_destinatie] << '\n';

        cout << "Lantul: ";
        reconstituire_drum(nod_destinatie);
    }
    return 0;
}*/
