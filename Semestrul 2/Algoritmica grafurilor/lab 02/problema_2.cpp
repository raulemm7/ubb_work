#include <iostream>
#include <fstream>

using namespace std;

ifstream in("fisier_in_graf_orientat.txt");

// 2. Sa se determine închiderea transitivă a unui graf orientat.
// (Închiderea tranzitivă poate fi reprezentată ca matricea care descrie,
// pentru fiecare vârf în parte, care sunt vârfurile accesibile din acest vârf.
// Matricea inchiderii tranzitive arată unde se poate ajunge din fiecare vârf.)
// ex. figura inchidere_tranzitiva.png - pentru graful de sus se construieste matricea
// de jos care arata inchiderea tranzitiva.
// !!!! ATENTIE !!!!
// Algortimul este implementat pentru un GRAF ORIENTAT, nodurile
// acestuia fiind notate de la 1 la n

int n, mat[101][101];
int coada[1001], inc, sf;

int d[101][101];

int main() {
    int x, y;
    in >> n;
    while(in >> x >> y) {
        mat[x][y] = 1;
    }

    for(int i = 1; i <= n; i++) {
        inc = 0;
        coada[0] = i;
        sf = 1;

        while(sf > inc) {
            for(int k = 1; k <= n; k++)
                if(mat[coada[inc]][k])
                    coada[sf++] = k;
            inc++;
            if(inc != sf)
                d[i][coada[inc]] = 1;
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++)
            cout << d[i][j] << " ";
        cout << endl;
    }

    return 0;
}
