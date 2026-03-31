//
// Created by ubecerril on 2/10/26.
//

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <stack>

using namespace std;

class Grafo {
private:
    int V; // número de vértices
    vector<vector<int>> adyacencia;

public:
    // Constructor
    Grafo(int vertices) {
        V = vertices;
        adyacencia.resize(V);
    }

    // Agregar una arista (grafo no dirigido)
    void agregarArista(int u, int v) {
        adyacencia[u].push_back(v);
        adyacencia[v].push_back(u);
    }

    // ===== RECORRIDO EN ANCHURA (BFS) =====
    void bfs(int inicio) {
        queue<int> q;
        vector<bool> visited (adyacencia.size(), false);

        visited[inicio] = true;
        q.push(inicio);

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            cout << v << " ";

            for (auto i : adyacencia[v]) {
                if (!visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }

    // ===== RECORRIDO EN PROFUNDIDAD (DFS) =====
    void dfs(int inicio) {
        stack<int> q;
        vector<bool> visited (adyacencia.size(), false);

        visited[inicio] = true;
        q.push(inicio);

        while (!q.empty()) {
            int v = q.top();
            q.pop();

            cout << v << " ";

            for (auto i : adyacencia[v]) {
                if (!visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }
};

int main() {
    Grafo g(6);

    g.agregarArista(0, 1);
    g.agregarArista(0, 2);
    g.agregarArista(1, 3);
    g.agregarArista(1, 4);
    g.agregarArista(2, 5);

    cout << "Recorrido BFS desde 0:" << endl;
    g.bfs(0);

    cout << "\nRecorrido DFS desde 0:" << endl;
    g.dfs(0);

    return 0;
}
