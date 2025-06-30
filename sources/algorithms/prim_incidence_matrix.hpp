#ifndef PRIM_INCIDENCE_MATRIX_HPP
#define PRIM_INCIDENCE_MATRIX_HPP

#include <limits>
#include "../structures/graph_incidence_matrix.hpp"
#include "../structures/dynamic_array.hpp"
#include "../structures/edge.hpp"

class PrimIncidenceMatrix {
private:
    int lastCost; // przechowuje koszt ostatniego MST

public:
    PrimIncidenceMatrix() : lastCost(-1) {}
    ~PrimIncidenceMatrix() = default;

    // Zwraca koszt ostatniego MST
    int getLastCost() const {
        return lastCost;
    }

    GraphIncidenceMatrix* run(GraphIncidenceMatrix* graphIncidenceMatrix) {
        lastCost = -1; // Resetujemy koszt przed obliczeniami

        if (!graphIncidenceMatrix) return nullptr;

        int n = graphIncidenceMatrix->getNumVertices();
        int m = graphIncidenceMatrix->getNumEdges();
        if (n == 0 || m == 0) return nullptr;

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
            // Znajdź wierzchołek z minimalnym kluczem
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

            // Przejrzyj wszystkie krawędzie w macierzy incydencji
            for (int edgeIdx = 0; edgeIdx < m; ++edgeIdx) {
                int uValue = graphIncidenceMatrix->getIncidenceValue(u, edgeIdx);

                // Sprawdź czy wierzchołek u jest incydentny z tą krawędzią
                if (uValue != 0) {
                    // Znajdź drugi wierzchołek tej krawędzi
                    int v = -1;
                    int weight = 0;

                    for (int vertex = 0; vertex < n; ++vertex) {
                        if (vertex != u) {
                            int vValue = graphIncidenceMatrix->getIncidenceValue(vertex, edgeIdx);
                            if (vValue != 0) {
                                v = vertex;
                                // Dla grafu nieskierowanego waga to wartość bezwzględna
                                // Dla grafu skierowanego sprawdzamy kierunek
                                if (graphIncidenceMatrix->isDirected()) {
                                    weight = (uValue < 0) ? -uValue : uValue;
                                } else {
                                    weight = (uValue > 0) ? uValue : -uValue;
                                }
                                break;
                            }
                        }
                    }

                    // Aktualizuj klucz sąsiedniego wierzchołka
                    if (v != -1 && !inMST[v] && weight < key[v]) {
                        key[v] = weight;
                        parent[v] = u;
                    }
                }
            }
        }

        // Oblicz koszt MST
        lastCost = 0;
        for (int v = 0; v < n; ++v) {
            if (inMST[v]) {
                lastCost += key[v];
            }
        }

        // Tworzenie MST jako macierz incydencji
        int mstEdges = 0;
        for (int v = 0; v < n; ++v) {
            if (parent[v] != -1) {
                mstEdges++;
            }
        }

        GraphIncidenceMatrix* mst = new GraphIncidenceMatrix(n, mstEdges, false);
        for (int v = 0; v < n; ++v) {
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

#endif // PRIM_INCIDENCE_MATRIX_HPP
