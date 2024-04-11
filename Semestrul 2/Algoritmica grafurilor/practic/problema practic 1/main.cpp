#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("input.txt");

const int nmax = 50000;
vector <int> Graf[nmax];
vector <int> grafInversat[nmax];
vector <int> noduri;
bool vizitat[nmax];

void dfs(int nod){
    vizitat[nod] = true;
    for (int vecin : Graf[nod]){
        if (!vizitat[vecin]){
            dfs(vecin);
        }
    }
    noduri.push_back(nod);
}

void dfs2(int nod, vector<int> &grup){
    if (vizitat[nod]){
        return;
    }
    grup.push_back(nod);
    vizitat[nod] = true;
    for (int vecin : grafInversat[nod]){
        if (!vizitat[vecin]){
            dfs2(vecin, grup);
        }
    }
}

void alg_kosaraju(int n, vector <vector<int>> &grupuri){
    for(int i = 0; i< n; i++){
        if(!vizitat[i]){
            dfs(i);
        }
    }

    for(int i = 0; i < n; i++){
        vizitat[i] = false;
    }

    for(int i = noduri.size() - 1; i>= 0; i--){
        if(!vizitat[noduri[i]]){
            vector<int> grup;
            dfs2(noduri[i], grup);
            grupuri.push_back(grup);
        }

    }
}

int main() {
    int n, m;
    fin >> n >> m;
    for (int i = 0; i < m; ++i){
        int x, y;
        fin >> x >> y;
        Graf[x].push_back(y);
        grafInversat[y].push_back(x);
    }
    vector <vector<int>> grupuri;
    alg_kosaraju(n, grupuri);
    for (int i = 0; i < grupuri.size(); ++i){
        cout << "grup " << i + 1 << ": ";
        for (int nod : grupuri[i]){
            cout << nod << " ";
        }
        cout << "\n";
    }
    return 0;
}
