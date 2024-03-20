#include <iostream>
#include <fstream>

using namespace std;

struct nod{
    int info;
    nod* urm;
};

int matrice_adiacenta[105][105] = {};     // matricea de adiacenta

void adaugare_final(nod* &p, int val){
    // creez un nod nou
    nod* q = new nod;
    q->info = val;
    q->urm = nullptr;

    if(p == nullptr){
        p = q;
    }
    else{
        nod* t = p;
        while(t->urm != nullptr)
            t = t->urm;
        t->urm = q;
    }
}

int main() {
    ifstream in("input.txt");

    int n;                  // nr de noduri
    nod *lista_adiacenta[15];         // liste de adiacenta
    int x, y, i;

    in >> n;
    // contstruiesc matricea de adiacenta
    while(in >> x >> y){
        matrice_adiacenta[x][y] = matrice_adiacenta[y][x] = 1;
    }

    cout << "Matricea de adiacenta: \n";
    for(i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++)
            cout << matrice_adiacenta[i][j] << ' ';
        cout << '\n';
    }

    // construiesc lista de adiacenta
    for(i = 1; i <= n; i++){
        nod* p = new nod;
        p = nullptr;

        for(int j = 1; j <= n; j++){
            if(matrice_adiacenta[i][j]){
                adaugare_final(p, j);
            }
        }

        lista_adiacenta[i] = p;
    }

    cout << "Lista de adiacenta: \n";
    for(i = 1; i <= n; i++){
        cout << i << ": ";
        nod *p;
        p = lista_adiacenta[i];

        while(p != nullptr){
            cout << p->info << ' ';
            p = p->urm;
        }
        cout << '\n';
    }

    // construiesc matricea de incidenta din lista de adiacenta
    // in implementarea asta este posibila schimbarea ordinii muchiilor citite din fisier
    int nr_muchii = 0;
    int matrice_incidenta[105][105] = {};
    int nr_noduri = 0;
    for(i = 1; i <= n; i++){
        nr_noduri++;
        nod *q = lista_adiacenta[i];

        while(q != nullptr){
            int nod = q->info;

            // verific daca am deja muchia dintre aceste doua noduri
            bool ok = true;
            for(int coloana = 1; coloana <= nr_muchii; coloana++){
                if(matrice_incidenta[nr_noduri]
                [coloana] and matrice_incidenta[nod][coloana]){
                    ok = false;
                    coloana += 200;
                }
            }
            if(ok){
               // inseamna ca nu exista muchia, o adaug
               nr_muchii++;
               matrice_incidenta[nr_noduri][nr_muchii] = matrice_incidenta[nod][nr_muchii] = 1;
            }

            q = q->urm;
        }
    }

    // afisez matricea de incidenta
    cout << "Matricea de incidenta: \n";
    for(i = 1; i <= n; i++){
        for(int j = 1; j <= nr_muchii; j++)
            cout << matrice_incidenta[i][j] << ' ';
        cout << '\n';
    }

    // construiesc lista de adiacenta din matricea de incidenta
    nod *lista_adiacenta_2[20] = {};
    for(i = 1; i <= n; i++) {
        lista_adiacenta_2[i] = nullptr;
    }
    for(int j = 1; j <= n; j++) {
        int nod1, nod2;
        nod1 = nod2 = 0;

        for(i = 1; i <= n; i++) {
            if(matrice_incidenta[i][j]) {
                if(!nod1)
                    nod1 = i;
                else {
                    nod2 = i;
                    i = n + 20;
                }
            }
        }
        adaugare_final(lista_adiacenta_2[nod1], nod2);
        adaugare_final(lista_adiacenta_2[nod2], nod1);

    }

    // afisez lista de adiacenta nou construita
    cout << "Lista de adiacenta din matricea de incidenta: \n";
    for(i = 1; i <= n; i++) {
        cout << i << ": ";
        nod *p;
        p = lista_adiacenta_2[i];

        while(p != nullptr){
            cout << p->info << ' ';
            p = p->urm;
        }
        cout << '\n';
    }

    // matricea de adiacenta din lista de adiacenta:
    int matrice_adiacenta_2[105][105] = {};
    for(i = 1; i <= n; i++) {
        nod *p = lista_adiacenta_2[i];

        while(p != nullptr) {
            matrice_adiacenta_2[i][p->info] = 1;
            p = p->urm;
        }
    }

    cout << "Matricea de adiacenta din lista de adiacenta: \n";
    for(i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++)
            cout << matrice_adiacenta_2[i][j] << ' ';
        cout << '\n';
    }

    // lista txt din matricea de adiacenta
    cout << "Lista din fisierul .txt:\n";
    cout << n << '\n';
    for(i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            if(matrice_adiacenta_2[i][j])
                cout << i << " " << j << '\n';
        }
    }

    return 0;
}
