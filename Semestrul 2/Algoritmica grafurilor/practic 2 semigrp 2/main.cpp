#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <fstream>

using namespace std;

const int INF = INT_MAX;

// alg pentru parcurgerea in latime
// true: daca exista o cale de la source la sink
// false: altfel
bool bfs(vector<vector<int>>& residualGraph, int source, int sink, vector<int>& parent) {
    int n = residualGraph.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; ++v) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                if (v == sink) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return false;
}

int edmondsKarp(vector<vector<int>>& graph, int source, int sink) {
    int u, v;
    int n = graph.size();
    vector<vector<int>> residualGraph = graph;
    vector<int> parent(n);
    int maxFlow = 0;

    // parcurg mai intai cu un bfs graful pentru a verifica daca mai exista
    // o cale de la sursa la destinatie
    while (bfs(residualGraph, source, sink, parent)) {
        // determin fluxul maxim ce poate fi trimis prin calea gasita
        int pathFlow = INF;

        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        // actualizez capacitatile cailor reziduale
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        // actualizez fluxul maxim
        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    std::ifstream fin("intrare.txt");

    int m, n;
    fin >> m >> n;

    vector<vector<int>> graph(m, vector<int>(m, 0));

    for (int i = 0; i < n; ++i) {
        int u, v, c;
        fin >> u >> v >> c;
        graph[u][v] += c;
    }

    int source = 0;  // Presupunem că depozitul central este la nodul 0
    int sink = m - 1;  // Presupunem că centrul de distribuție este la nodul m-1

    cout << "Fluxul maxim de marfuri este: " << edmondsKarp(graph, source, sink) << endl;

    return 0;
}
