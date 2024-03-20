/*
#include <iostream>
#include <fstream>

using namespace std;

ifstream in("fisier_in.txt");

 // 4. Pentru un graf dat să se afișeze pe ecran vârfurile descoperite
 // de algoritmul BFS și distanța față de vârful sursă (arborele descoperit).
 // !!!!!! ATENTIE !!!!!!
 // Algortim implementat pentru grafuri neorientate



int main() {
    int i;

    int nr_varfuri;
    in >> nr_varfuri;

    // alocare memorie
    int** matrice = (int**)malloc(sizeof(int*) * (nr_varfuri + 1));
    for(i = 0; i <= nr_varfuri; i++) {
        matrice[i] = (int*)malloc(sizeof(int) * (nr_varfuri + 1));
    }
    // initializare matrice
    for(i = 0; i <= nr_varfuri; i++) {
        for(int j = i; j <= nr_varfuri; j++)
            matrice[i][j] = matrice[j][i] = 0;
    }

    // citire matrice din fisier
    int x, y;
    while(in >> x >> y) {
        matrice[x][y] = matrice[y][x] = 1;
    }

    // executie probleme
    int start;
    cout << "Introduceti varful de start: ";
    cin >> start;
    //problema_4(matrice, start, nr_varfuri);

    // BFS
    int coada[1024] = {};
    int vizitat[1024] = {};
    int distanta[1024] = {};
    int k, st, dr;
    //initializez coada
    st = dr = 1;
    coada[1] = start;
    vizitat[start] = 1;                                  //vizitez varful initial
    distanta[1] = 0;

    while(st <= dr)                                      //cat timp coada nu este vida
    {
        k = coada[st];                                   //preiau un element din coada
        for(i = 1; i <= nr_varfuri; i++)                 //parcurg varfurile
            if(vizitat[i] == 0 && matrice[k][i] == 1)    //daca i este vecin cu k si nu este vizitat
            {
                vizitat[i] = 1;                            //il vizitez
                coada[++dr] = i;                           //il adaug in coada
                distanta[i] = distanta[k] + 1;
            }
        st++;                                            //sterg din coada
    }

    cout << "Au fost descoperite " << dr - 1 << " varfuri din totalul de " << nr_varfuri - 1 << ";\n";
    for(i = 2; i <= dr; i++) {
        cout << "distanta de la vf sursa la vf " << coada[i] << ": " << distanta[coada[i]] << '\n';
    }

    // eliberare memorie
    for(i = 0; i <= nr_varfuri; i++)
        free(matrice[i]);
    free(matrice);
    return 0;
}
*/
