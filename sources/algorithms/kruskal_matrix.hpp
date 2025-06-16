#ifndef KRUSKAL_MATRIX_HPP
#define KRUSKAL_MATRIX_HPP

#include <iostream>
#include "../structures/graph_adjacency_matrix.hpp"
#include "../structures/edge.hpp"
#include "../structures/dynamic_array.hpp"

class KruskalMatrix {
public:
    KruskalMatrix() = default;
    ~KruskalMatrix() = default;

    GraphAdjacencyMatrix* run(GraphAdjacencyMatrix* graphAdjacencyMatrix) {
        if (!graphAdjacencyMatrix) return nullptr;

        int 
      n = graphAdjacencyMatrix->getNumVertices();
        if (n == 0) return nullptr;

        // Zbieramy wszystkie krawedzie z macierzy incydencji
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

        // Sortowanie krawędzi po wagach rosnąco
        for (int i = 0; i < edges->getSize(); ++i) {
            for (int j = i + 1; j < edges->getSize(); ++j) {
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

        // Tworzymy wynikowy graf
        GraphAdjacencyMatrix* mst = new GraphAdjacencyMatrix(n, edges->getSize(), false);
        for (size_t i = 0; i < edges->getSize(); ++i) {
            int u = edges->get(i).from;
            int v = edges->get(i).to;
            if (find(u, parent) != find(v, parent)) {
                mst->addEdge(u, v, edges->get(i).weight);
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
