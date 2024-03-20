#include <iostream>
#include <fstream>

using namespace std;

ifstream in("fisier_in.txt");

 // 5. Pentru un graf dat să se afișeze pe ecran vârfurile descoperite de
 // apelul recursiv al procedurii DFS (apadurea descoperită de DFS).
 // !!!!!! ATENTIE !!!!!!
 // Algortim implementat pentru grafuri neorientate

int matrice[256][256], nr_noduri;
int vizitat[256];

void dfs(int nod_curent) {
    vizitat[nod_curent] = 1;
    for(int i = 1; i <= nr_noduri; i++) {
        if(matrice[nod_curent][i] && !vizitat[i]) {
            cout << i << " ";
            dfs(i);
        }
    }
}

int main() {
    in >> nr_noduri;

    int x, y;
    while(in >> x >> y)
        matrice[x][y] = matrice[y][x] = 1;
    in.close();

    int nod_de_start;
    cout << "Dati varful din care doriti sa inceapa parcurgerea DFS: ";
    cin >> nod_de_start;
    cout << nod_de_start << " ";

    dfs(nod_de_start);
    return 0;
}
