#ifndef KRUSKAL_MATRIX_HPP
#define KRUSKAL_MATRIX_HPP

#include <iostream>
#include "../structures/graph_adjacency_matrix.hpp"
#include "../structures/edge.hpp"
#include "../structures/dynamic_array.hpp"

class KruskalMatrix {
private:
    int lastCost;

public:
    KruskalMatrix() : lastCost(-1) {}
    ~KruskalMatrix() = default;

    int getLastCost() const {
        return lastCost;
    }

    GraphAdjacencyMatrix* run(GraphAdjacencyMatrix* graphAdjacencyMatrix) {
        lastCost = -1; 

        if (!graphAdjacencyMatrix) return nullptr;

        int n = graphAdjacencyMatrix->getNumVertices();
        if (n == 0) return nullptr;

        DynamicArray<Edge>* edges = new DynamicArray<Edge>(n * (n - 1) / 2);
        for (int u = 0; u < n; ++u) {
            DynamicArray<int>* row = graphAdjacencyMatrix->getAdjacencyMatrix(u);
            for (int v = u + 1; v < n; ++v) {
                int weight = row->get(v);
                if (weight > 0) {
                    edges->add(Edge(u, v, weight));
                }
            }
        }

        for (size_t i = 0; i < edges->getSize(); ++i) {
            for (size_t j = i + 1; j < edges->getSize(); ++j) {
                if (edges->get(i).weight > edges->get(j).weight) {
                    edges->swap(i, j);
                }
            }
        }

        // Union-Find struktura
        int* parent = new int[n];
        int* rank = new int[n];
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }

        GraphAdjacencyMatrix* mst = new GraphAdjacencyMatrix(n, edges->getSize(), false);
        lastCost = 0; // Inicjalizujemy koszt

        for (size_t i = 0; i < edges->getSize(); ++i) {
            int u = edges->get(i).from;
            int v = edges->get(i).to;
            int weight = edges->get(i).weight;
            if (find(u, parent) != find(v, parent)) {
                mst->addEdge(u, v, weight);
                lastCost += weight; // Dodajemy wagę do kosztu MST
                unionSets(u, v, parent, rank);
            }
        }

        delete[] parent;
        delete[] rank;
        delete edges;

        return mst;
    }

private:
    int find(int u, int* parent) {
        if (parent[u] != u) {
            parent[u] = find(parent[u], parent);
        }
        return parent[u];
    }

    void unionSets(int u, int v, int* parent, int* rank) {
        int rootU = find(u, parent);
        int rootV = find(v, parent);
        if (rootU != rootV) {
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

#endif // KRUSKAL_MATRIX_HPP
