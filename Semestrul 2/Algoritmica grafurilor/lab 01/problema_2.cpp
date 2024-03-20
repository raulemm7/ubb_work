/*
#include <iostream>
#include <fstream>

using namespace std;

struct nod{
    int info;
    nod* urm;
};

int n;                  // nr de noduri
int matrice_adiacenta[105][105] = {};     // matricea de adiacenta
int viz[105];

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

void DFS(int nodCurent, int multimeCurenta)
{
    viz[nodCurent] = multimeCurenta;

    for(int i = 1; i <= n; i++)
    {
        if(!viz[i] && matrice_adiacenta[nodCurent][i])
        {
            viz[i] = multimeCurenta;

            DFS(i, multimeCurenta);
        }
    }
}

int main() {
    ifstream in("input.txt");

    int x, y, i, j, k;

    in >> n;
    // contstruiesc matricea de adiacenta
    while(in >> x >> y){
        matrice_adiacenta[x][y] = matrice_adiacenta[y][x] = 1;
    }

    // determin nodurile izolate
    nod* p = new nod;
    p = nullptr;
    for(i = 1; i <= n; i++){
        bool ok = false;

        for(j = 1; j < n; j++){
            if(matrice_adiacenta[i][j]){
                ok = true;
            }
        }

        if(!ok){
            adaugare_final(p, i);
        }
    }

    // afisez nodurile izolate
    if(p == nullptr)
        cout << "Nu exista noduri izolate!";
    else {
        while (p != nullptr){
            cout << p->info << ' ';
            p = p->urm;
        }
    }

    bool regular = true;
    int nr = 0;
    for(i = 1; i <= n; i++){
        nr += matrice_adiacenta[1][i];   // retin gradul nodului 1
    }
    for(i = 2; i <= n; i++){
        int nr_aux = 0;

        for(j = 1; j <= n; j++)
            nr_aux += matrice_adiacenta[i][j];

        if(nr != nr_aux){
            regular = false;
            i = n + 20;
        }
    }

    // afisez daca e regular sau nu
    if(regular)
        cout << "\nGraful este regular!";
    else
        cout << "\nGraful nu este regular!\n";

    // matricea distantelor
    int b[n+1][n+1];
    for(i = 1; i <= n; i++){
        for(j = 1; j <= n; j++)
            if(matrice_adiacenta[i][j])
                b[i][j] = 1;
            else b[i][j] = INT_MAX;
    }

    for(k = 1; k <= n; k++){
        for(i = 1; i <= n; i++){
            for(j = 1; j <= n; j++){
                if(b[i][k] != INT_MAX and b[k][j] != INT_MAX){
                    if(b[i][j] > b[i][k] + b[k][j])
                        b[i][j] = b[i][k] + b[k][j];
                }
            }
        }
    }

    // afisez matricea drumurilor
    for(i = 1; i <= n; i++){
        for(j = 1; j <= n; j++)
            if(b[i][j] == INT_MAX)
                cout << "inf ";
            else
                cout << b[i][j] << ' ';
        cout << '\n';
    }

    // verific daca este conex
    int nrCompConexe = 0;
    for(i = 1; i <= n; i++){
        if(!viz[i]){
            nrCompConexe++;
            DFS(i, nrCompConexe);
        }
    }

    if(nrCompConexe == 1)
        cout << "Graful este conex!";
    else
        cout << "Graful NU este conex!";

    return 0;
}
*/
