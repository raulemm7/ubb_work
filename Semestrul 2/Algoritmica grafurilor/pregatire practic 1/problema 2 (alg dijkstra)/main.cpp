#include <iostream>
#include <fstream>

using namespace std;

#define INFINIT 24500000

/**
 * problema cu configuratia de case
 * cu drumuri unidirectionale (grafuri orientate)
 * se da:
 * n -> numarul de case
 * x, y -> drumul pe care treubie sa il determin de la casa x la casa y
 *      -> configuratia grafului
 */

int nrNoduri;
int matrice[1005][1005];
int distanta[1005], parinte[1005], vizitat[1005];

void matrix_initialization() {
    for(int i = 1; i <= nrNoduri; i++)
        for(int j = 1; j <= nrNoduri; j++)
            matrice[i][j] = INFINIT;
}

void dijkstra_initialization(int sourceNode) {
    for(int i = 1; i <= nrNoduri; i++) {
        distanta[i] = matrice[sourceNode][i];
        vizitat[i] = 0;
        if(matrice[sourceNode][i] != INFINIT)
            parinte[i] = sourceNode;
        else
            parinte[i] = INFINIT;
    }
    distanta[sourceNode] = 0;
    vizitat[sourceNode] = 1;
    parinte[sourceNode] = 0;
}

int findMinimum() {
    int min = INFINIT, min_index;
    for(int i = 1; i <= nrNoduri; i++) {
        if(!vizitat[i] and distanta[i] < min) {
            min = distanta[i];
            min_index = i;
        }
    }
    return min_index;
}

void dijkstra_algorithm(int sourceNode) {
    dijkstra_initialization(sourceNode);

    for(int i = 1; i < nrNoduri; i++) {
        int nod_curent = findMinimum();
        vizitat[nod_curent] = 1;
        for(int j = 1; j <= nrNoduri; j++) {
            if(matrice[nod_curent][j] != INFINIT and !vizitat[j]) {
                if(distanta[j] > distanta[nod_curent] + matrice[nod_curent][j]) {
                    distanta[j] = distanta[nod_curent] + matrice[nod_curent][j];
                    parinte[j] = nod_curent;
                }
            }
        }
    }
}

void reconstituire_traseu(int nod_curent) {
    if(nod_curent != 0) {
        reconstituire_traseu(parinte[nod_curent]);
        cout << nod_curent << " ";
    }
}

int main() {
    // citire
    // nrNoduri, casax, casay
    // celelalte infos
    int casa_x, casa_y;
    int x, y, lungime;

    ifstream fin("input.txt");
    fin >> nrNoduri >> casa_x >> casa_y;
    matrix_initialization();

    while(fin >> x >> y >> lungime)
        matrice[x][y] = lungime;

    dijkstra_algorithm(casa_x);

    if(distanta[casa_y] != INFINIT) {
        cout << "Distanta drumului este: " << distanta[casa_y];
        cout << "\nReconstituire traseu: ";
        reconstituire_traseu(casa_y);
    }
    else
        cout << "Nu exista drum de la casa " << casa_x << " la casa " << casa_y;
    
    return 0;
}
