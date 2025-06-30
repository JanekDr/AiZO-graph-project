#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP

#include <iostream>
#include "../structures/graph.hpp"
#include "../structures/dynamic_array.hpp"
#include "../structures/edge.hpp"

class Kruskal {
private:
    int lastCost; // przechowuje koszt ostatniego MST

public:
    Kruskal() : lastCost(-1) {}
    ~Kruskal() = default;

    // Zwraca koszt ostatniego MST
    int getLastCost() const {
        return lastCost;
    }

    // Zwraca MST lub nullptr
    Graph* run(Graph* graph) {
        lastCost = -1; // Resetuj koszt przed obliczeniami
        
        if (!graph) return nullptr;

        int n = graph->getNumVertices();
        if (n == 0) return nullptr;

        // 1. lista krawedzi
        DynamicArray<Edge>* edges = new DynamicArray<Edge>(n * (n - 1) / 2);
        for (int u = 0; u < n; ++u) {
            DynamicArray<Edge>* neighbors = graph->getAdjacencyList(u);
            for (size_t i = 0; i < neighbors->getSize(); ++i) {
                Edge e = neighbors->get(i);
                if (u < e.to) {  // Unikamy duplikatów dla grafów nieskierowanych
                    edges->add(Edge(u, e.to, e.weight));
                }
            }
        }

        // 2. Sortujemy krawędzie po wagach (rosnąco)
        for (size_t i = 0; i < edges->getSize(); ++i) {
            for (size_t j = i + 1; j < edges->getSize(); ++j) {
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

        // 4. Tworzymy MST i liczymy koszt
        Graph* mst = new Graph(n);
        lastCost = 0; // Inicjalizujemy koszt
        
        for (size_t i = 0; i < edges->getSize(); ++i) {
            int u = edges->get(i).from;
            int v = edges->get(i).to;
            int weight = edges->get(i).weight;
            
            // Jeśli nie tworzymy cyklu, dodajemy krawędź do MST
            if (find(u, parent) != find(v, parent)) {
                mst->addEdge(u, v, weight);
                lastCost += weight; // Dodaj wagę do kosztu
                unionSets(u, v, parent, rank);
            }
        }

        // Czyszczenie pamięci
        delete[] parent;
        delete[] rank;
        delete edges;

        return mst;
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

#endif // KRUSKAL_HPP
