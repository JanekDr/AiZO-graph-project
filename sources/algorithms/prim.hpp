#ifndef PRIM_HPP
#define PRIM_HPP

#include <limits>
#include "../structures/graph.hpp"
#include "../structures/dynamic_array.hpp"
#include "../structures/edge.hpp"

class Prim {
public:
    Prim() = default;
    ~Prim() = default;

    // Zwraca MST lub nullptr
    Graph* run(Graph* graph) {
        if (!graph) return nullptr;

        int n = graph->getNumVertices();
        if (n == 0) return nullptr;

        // Tablice pomocnicze
        bool* inMST = new bool[n]{false};
        int* key = new int[n];
        int* parent = new int[n];

        for (int i = 0; i < n; ++i) {
            key[i] = std::numeric_limits<int>::max();
            parent[i] = -1;
        }

        key[0] = 0;  // Startujemy od wierzchołka 0

        for (int count = 0; count < n - 1; ++count) {
            // Znajdź wierzchołek spoza MST o najmniejszym kluczu
            int u = -1;
            int minKey = std::numeric_limits<int>::max();
            for (int v = 0; v < n; ++v) {
                if (!inMST[v] && key[v] < minKey) {
                    minKey = key[v];
                    u = v;
                }
            }

            if (u == -1) {
                // Graf niespójny
                delete[] inMST;
                delete[] key;
                delete[] parent;
                return nullptr;
            }

            inMST[u] = true;

            // Aktualizuj klucze sąsiadów
            DynamicArray<Edge>* neighbors = graph->getAdjacencyList(u);
            for (size_t i = 0; i < neighbors->getSize(); ++i) {
                Edge e = neighbors->get(i);
                int v = e.to;  // Nowe podejście: używamy 'to' jako sąsiada
                int w = e.weight;  // Nowe podejście: używamy 'weight' jako wagi krawędzi

                if (!inMST[v] && w < key[v]) {
                    key[v] = w;
                    parent[v] = u;
                }
            }
        }

        // Zbuduj MST
        Graph* mst = new Graph(n);
        for (int v = 1; v < n; ++v) {
            if (parent[v] != -1) {
                mst->addEdge(parent[v], v, key[v]);
            }
        }

        delete[] inMST;
        delete[] key;
        delete[] parent;

        return mst;
    }
};

#endif
