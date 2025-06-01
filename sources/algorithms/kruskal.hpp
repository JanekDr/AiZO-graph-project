#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP

#include <iostream>
#include "../structures/graph.hpp"
#include "../structures/dynamic_array.hpp"
#include "../structures/edge.hpp"

class Kruskal {
public:
    Kruskal() = default;
    ~Kruskal() = default;

    // Zwraca MST lub nullptr
    Graph* run(Graph* graph) {
        if (!graph) return nullptr;

        int n = graph->getNumVertices();
        if (n == 0) return nullptr;

        // 1. Zbieramy wszystkie krawędzie grafu
        DynamicArray<Edge>* edges = new DynamicArray<Edge>(n * (n - 1) / 2);  // Maksymalna liczba krawędzi
        for (int u = 0; u < n; ++u) {
            DynamicArray<Edge>* neighbors = graph->getAdjacencyList(u);
            for (size_t i = 0; i < neighbors->getSize(); ++i) {
                Edge e = neighbors->get(i);
                if (u < e.to) {
                    edges->add(Edge(u, e.to, e.weight));
                }
            }
        }

        // 2. Sortujemy krawędzie po wagach (rosnąco)
        for (int i = 0; i < edges->getSize(); ++i) {
            for (int j = i + 1; j < edges->getSize(); ++j) {
                if (edges->get(i).weight > edges->get(j).weight) {
                    edges->swap(i, j);
                }
            }
        }

        // 3. Inicjalizujemy tablice dla union-find
        int* parent = new int[n];
        int* rank = new int[n];
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }

        // 4. Tworzymy MST
        Graph* mst = new Graph(n);
        for (size_t i = 0; i < edges->getSize(); ++i) {
            int u = edges->get(i).from;
            int v = edges->get(i).to;
            // Jeśli nie tworzymy cyklu, dodajemy krawędź do MST
            if (find(u, parent) != find(v, parent)) {
                mst->addEdge(u, v, edges->get(i).weight);
                unionSets(u, v, parent, rank);
            }
        }

        // Czyszczenie pamięci
        delete[] parent;
        delete[] rank;
        delete edges;

        return mst;  // Zwracamy MST
    }

private:
    // Funkcja do znajdowania korzenia zbioru w union-find
    int find(int u, int* parent) {
        if (parent[u] != u) {
            parent[u] = find(parent[u], parent);  // kompresja ścieżki
        }
        return parent[u];
    }

    // Funkcja do łączenia dwóch zbiorów
    void unionSets(int u, int v, int* parent, int* rank) {
        int rootU = find(u, parent);
        int rootV = find(v, parent);
        if (rootU != rootV) {
            // Złączenie dwóch drzew
            if (rank[rootU] < rank[rootV])
                parent[rootU] = rootV;
            else if (rank[rootU] > rank[rootV])
                parent[rootV] = rootU;
            else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

#endif
