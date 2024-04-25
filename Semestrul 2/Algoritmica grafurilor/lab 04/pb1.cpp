#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct muchie{
    int i,j,cost;
};

int nrNoduri, nrMuchii, indiceSubarbore[5000];

muchie x[5000];

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    fin >> nrNoduri >> nrMuchii;

    // citesc muchiile
    for(int i = 0 ; i < nrMuchii ; ++i)
        fin >> x[i].i >> x[i].j >> x[i].cost;

    // sortez muchiile crescator dupa cost
    for(int i = 0; i < nrMuchii - 1; i++) {
        for(int j = i + 1; j < nrMuchii; j++) {
            if(x[i].cost > x[j].cost)
                swap(x[i],x[j]);
        }
    }

    // initializare fiecare nod intr un subarbore diferit
    for(int i = 0; i < nrNoduri ; i++)
        indiceSubarbore[i] = i;

    // determinare APM
    int cost_arbore = 0;
    muchie muchii_arbori[5000];
    int nr_muchii_arbori = 1;
    for(int i = 0 ; i < nrMuchii ; i++)
        if(indiceSubarbore[x[i].i] != indiceSubarbore[x[i].j]) {
            // daca extremitatile muchiei
            // fac parte din subarbori diferiti, aleg aceasta muchie
            cost_arbore += x[i].cost;
            muchii_arbori[nr_muchii_arbori].i = x[i].i;
            muchii_arbori[nr_muchii_arbori].j = x[i].j;
            muchii_arbori[nr_muchii_arbori].cost = x[i].cost;
            nr_muchii_arbori++;

            // reunim subarborii
            int ai = indiceSubarbore[x[i].i], aj = indiceSubarbore[x[i].j];
            for(int j = 0; j < nrNoduri ; j++)
                if(indiceSubarbore[j] == aj)
                    indiceSubarbore[j] = ai;
        }

    fout << cost_arbore << "\n";
    fout << nr_muchii_arbori - 1<< '\n';
    for(int i = 1; i < nr_muchii_arbori; i++) {
        fout << muchii_arbori[i].i << " " << muchii_arbori[i].j << '\n';
    }
    return 0;
}
