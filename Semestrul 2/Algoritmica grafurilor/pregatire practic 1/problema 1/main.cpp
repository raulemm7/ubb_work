#include <iostream>
#include <fstream>

using namespace std;

int nrCopii, nrRelatii;
int mat[1005][1005];

int vizitat[1005];

void dfs(int nod_curent, int grup_nod) {
    vizitat[nod_curent] = grup_nod;
    for(int i = 1; i <= nrCopii; i++) {
        if(mat[nod_curent][i] and !vizitat[i])
            dfs(i, grup_nod);
    }
}

int main() {
    int x, y;

    ifstream fin("input.txt");
    fin >> nrCopii >> nrRelatii;
    for(int i = 1; i <= nrRelatii; i++) {
        fin >> x >> y;
        mat[x][y] = mat[y][x] = 1;
    }

    int nr_grupuri = 0;
    for(int i = 1; i <= nrCopii; i++) {
        if(!vizitat[i]) {
            nr_grupuri++;
            dfs(i, nr_grupuri);
        }
    }
    cout << "Exista " << nr_grupuri << " de prieteni\n";
    for(int i = 1; i <= nr_grupuri; i++) {
        cout << "Grupul " << i << ": ";
        for(int j = 1; j <= nrCopii; j++) {
            if(vizitat[j] == i) {
                cout << j << " ";
            }
        }
        cout << '\n';
    }

    fin.close();
    return 0;
}
