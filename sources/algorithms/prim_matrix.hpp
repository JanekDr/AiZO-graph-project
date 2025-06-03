#ifndef PRIM_MATRIX_HPP
#define PRIM_MATRIX_HPP

#include <limits>
#include "../structures/graph_matrix.hpp"
#include "../structures/dynamic_array.hpp"
#include "../structures/edge.hpp"

class PrimMatrix {
public:
    PrimMatrix() = default;
    ~PrimMatrix() = default;

    GraphMatrix* run(GraphMatrix* graphMatrix) {
        if (!graphMatrix) return nullptr;

        int n = graphMatrix->getNumVertices();
        if (n == 0) return nullptr;

        // Tablice pomocnicze
        bool* inMST = new bool[n]{false};
        int* key = new int[n];
        int* parent = new int[n];

        for (int i = 0; i < n; ++i) {
            key[i] = std::numeric_limits<int>::max();
            parent[i] = -1;
        }

        key[0] = 0; // Start od wierzchołka 0

        for (int count = 0; count < n - 1; ++count) {
            int u = -1;
            int minKey = std::numeric_limits<int>::max();
            for (int v = 0; v < n; ++v) {
                if (!inMST[v] && key[v] < minKey) {
                    minKey = key[v];
                    u = v;
                }
            }

            if (u == -1) {
                delete[] inMST;
                delete[] key;
                delete[] parent;
                return nullptr;
            }

            inMST[u] = true;

            DynamicArray<int>* row = graphMatrix->getIncidenceMatrix(u);
            for (int v = 0; v < n; ++v) {
                int weight = row->get(v);
                if (weight > 0 && !inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                }
            }
        }

        GraphMatrix* mst = new GraphMatrix(n, n, false);
        for (int v = 0; v < n; ++v) {
            if (parent[v] != -1) {
                std::cout<< "Adding edge: " << parent[v] << " - " << v << " with weight: " << key[v] << std::endl;
                mst->addEdge(parent[v], v, key[v]);
            }
        }

        delete[] inMST;
        delete[] key;
        delete[] parent;

        return mst;
    }
};

#endif // PRIM_MATRIX_HPP
