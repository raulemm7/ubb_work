#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int number_of_strings;

char matrix[2500][2500];
string path;

void reinit() {
    path.clear();
    for(auto & i : matrix)
        for(char & j : i)
            j = '.';
}

string alg_lui_raul(char copie_matrice[2500][2500], int start_x, int start_y, int inaltime, int lungime, int nr_copaci) {
/**
     * w - nord linie--
     * d - est coloana++
     * s - sud linie++
     * a - vest coloana--
     */

    cout << lungime << " " << inaltime << " ";
    int count = 1;
    int cur_x, cur_y;
    cur_x = start_x;
    cur_y = start_y;
    copie_matrice[start_x][start_y] = 'V';
    for(char c : path) {
        cout << c << " ";
        if(c == 'W') {
            cur_x--;
            if(copie_matrice[cur_x][cur_y] != '.')
                return "INVALID";
            if(cur_x == 0)
                return "INVALID";

            copie_matrice[cur_x][cur_y] = 'V';
            count++;
        }
        if(c == 'S') {
            cur_x++;
            if(copie_matrice[cur_x][cur_y] != '.')
                return "INVALID";
            if(cur_x > inaltime)
                return "INVALID";

            copie_matrice[cur_x][cur_y] = 'V';
            count++;
        }
        if(c == 'A') {
            cur_y--;
            if(copie_matrice[cur_x][cur_y] != '.')
                return "INVALID";
            if(cur_y == 0)
                return "INVALID";

            copie_matrice[cur_x][cur_y] = 'V';
            count++;
        }
        if(c == 'D') {
            cur_y++;
            if(copie_matrice[cur_x][cur_y] != '.')
                return "INVALID";
            if(cur_y > lungime)
                return "INVALID";

            copie_matrice[cur_x][cur_y] = 'V';
            count++;
        }
    }

    cout << "AM PORNIT DIN " << start_x << " " << start_y << '\n';
    cout << "AM PARCURS MATRICEA\n";
    for(int i = 1; i <= inaltime; i++) {
        for(int j = 1; j <= lungime; j++) {
            cout << copie_matrice[i][j];
        }
        cout << '\n';
    }
    if(count == (lungime * inaltime) - nr_copaci)
        return "VALID";
    return "INVALID";
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    fin >> number_of_strings;
    for(int j = 1; j <= number_of_strings; j++) {
        reinit();

        int nr_copaci = 0;

        int x, y;
        fin >> x >> y;
        for(int ii = 1; ii <= y; ii++) {
            for(int jj = 1; jj <= x; jj++) {
                fin >> matrix[ii][jj];

                if(matrix[ii][jj] == 'X')
                    nr_copaci++;
            }
        }
        fin >> path;

        bool ok = false;
        string mesaj;
        for(int ii = 1; ii <= y and !ok; ii++) {
            for(int jj = 1; jj <= x and !ok; jj++) {
                if(matrix[ii][jj] != 'X') {
                    // revenire la matricea dinainte
                    // copie
                    char copie_matrice[2500][2500];
                    for(int i1 = 1; i1 <= y; i1++) {
                        for(int j1 = 1; j1 <= x; j1++)
                            copie_matrice[i1][j1] = matrix[i1][j1];
                    }
                    mesaj = alg_lui_raul(copie_matrice, ii, jj, y, x, nr_copaci);
                    if(mesaj == "VALID"){
                        ok = true;
                    }
                    else
                        mesaj.clear();
                }
            }
        }
        if(!ok)
            mesaj = "INVALID";

        fout << mesaj << '\n';

    }

    return 0;
}
