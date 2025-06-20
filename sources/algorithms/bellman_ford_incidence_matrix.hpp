#ifndef BELLMAN_FORD_INCIDENCE_MATRIX_HPP
#define BELLMAN_FORD_INCIDENCE_MATRIX_HPP

#include <limits>
#include "../structures/graph_incidence_matrix.hpp"

class BellmanFordIncidenceMatrix {
private:
    int* distances = nullptr;
    int numVertices = 0;
    bool negativeCycle = false;

public:
    ~BellmanFordIncidenceMatrix() {
        if (distances) delete[] distances;
    }

    GraphIncidenceMatrix* run(GraphIncidenceMatrix* graph, int start) {
        if (!graph) return nullptr;

        numVertices = graph->getNumVertices();
        int edgeCount = graph->getNumEdges();
        distances = new int[numVertices];
        for (int i = 0; i < numVertices; ++i)
            distances[i] = std::numeric_limits<int>::max();
        distances[start] = 0;

        for (int i = 1; i < numVertices; ++i) {
            for (int e = 0; e < edgeCount; ++e) {
                int from = -1, to = -1, weight = 0;

                for (int v = 0; v < numVertices; ++v) {
                    int val = graph->getIncidenceValue(v, e);
                    if (val < 0) {
                        from = v;
                        weight = -val;
                    } else if (val > 0) {
                        to = v;
                    }
                }

                if (from != -1 && to != -1 &&
                    distances[from] != std::numeric_limits<int>::max() &&
                    distances[from] + weight < distances[to]) {
                    distances[to] = distances[from] + weight;
                }
            }
        }

        // Wykrywanie cyklu ujemnego
        negativeCycle = false;
        for (int e = 0; e < edgeCount; ++e) {
            int from = -1, to = -1, weight = 0;

            for (int v = 0; v < numVertices; ++v) {
                int val = graph->getIncidenceValue(v, e);
                if (val < 0) {
                    from = v;
                    weight = -val;
                } else if (val > 0) {
                    to = v;
                }
            }

            if (from != -1 && to != -1 &&
                distances[from] != std::numeric_limits<int>::max() &&
                distances[from] + weight < distances[to]) {
                negativeCycle = true;
                return nullptr;
            }
        }

        auto* result = new GraphIncidenceMatrix(numVertices, edgeCount, graph->isDirected());
        for (int e = 0; e < edgeCount; ++e) {
            int from = -1, to = -1, weight = 0;

            for (int v = 0; v < numVertices; ++v) {
                int val = graph->getIncidenceValue(v, e);
                if (val < 0) {
                    from = v;
                    weight = -val;
                } else if (val > 0) {
                    to = v;
                }
            }

            if (from != -1 && to != -1 &&
                distances[to] == distances[from] + weight) {
                result->addEdge(from, to, weight);
            }
        }

        return result;
    }

    int getShortestDistance(int v) const {
        return (v >= 0 && v < numVertices) ? distances[v] : -1;
    }

    bool hasNegativeCycle() const {
        return negativeCycle;
    }
};

#endif
