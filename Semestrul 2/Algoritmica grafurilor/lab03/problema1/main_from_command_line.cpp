#include <iostream>
#include <fstream>
using namespace std;
#define inf 999

// Vector pentru a stoca distantele minime de la sursa la fiecare nod
int d[10005];

struct bellman
{
    int x, y, c; // Nodul sursa, nodul destinatie si costul muchiei
} muchie[10005];


void relax(int u, int v, int c)
{
    if (d[v] > d[u] + c)
        d[v] = d[u] + c;
}

bool bellman_ford(int n, int v, int s)
{
    for (int i = 0; i < n; i++)
        d[i] = inf;

    d[s] = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j <= v; j++)
        {
            relax(muchie[j].x, muchie[j].y, muchie[j].c);
        }
    }

    for (int j = 1; j <= v; j++)
    {
        // Daca distanta catre nodul de destinatie al unei muchii poate fi redusa
        // mai mult prin intermediul nodului sursa al acelei muchii, atunci exista un ciclu negativ
        if (d[muchie[j].y] > d[muchie[j].x] + muchie[j].c)
            return false;
    }

    return true;
}


// creeeare executabil: g++ -std=c++17 -Wall -Wextra -onume_fisier nume_fisier.cpp
// pentru run: ./nume_problema graf.txt fisier_iesire.txt (poti rula doar executabilul 😀)
int main(int argc, char* argv[]) {
    int n, v, sursa;

    if(argc < 3) {
       cout << "Numar insuficient de argumente!";
       return 0;
    }

    std::ifstream in(argv[1]);
    std::ofstream out(argv[2]);

    // Citim numarul de noduri, numarul de muchii si nodul sursa
    in >> n >> v >> sursa;

    // Citim informatiile despre fiecare muchie si le stocam �n vectorul muchie
    for (int i = 1; i <= v; i++)
    {
        in >> muchie[i].x >> muchie[i].y >> muchie[i].c;
    }

    if (!bellman_ford(n, v, sursa))
        out << "ciclu negativ";
    else {
        // Afisam distantele minime catre fiecare nod sau "inf" in cazul in care nu exista drum intre sursa si nodul respectiv
        for (int i = 0; i < n; i++) {
            if (d[i] == inf)
                out << "inf ";
            else
                out << d[i] << ' ';
        }
    }

    in.close();
    out.close();
    return 0;
}
