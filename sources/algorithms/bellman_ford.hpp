#ifndef BELLMAN_FORD_HPP
#define BELLMAN_FORD_HPP

#include <limits>
#include "../structures/graph.hpp"
#include "../structures/edge.hpp"

class BellmanFord {
private:
    int* distances = nullptr;
    int numVertices = 0;
    bool negativeCycle = false;

public:
    ~BellmanFord() {
        if (distances) delete[] distances;
    }

    Graph* run(Graph* graph, int start) {
        if (!graph) return nullptr;

        numVertices = graph->getNumVertices();
        distances = new int[numVertices];
        for (int i = 0; i < numVertices; ++i)
            distances[i] = std::numeric_limits<int>::max();
        distances[start] = 0;

        for (int i = 1; i < numVertices; ++i) {
            for (int u = 0; u < numVertices; ++u) {
                auto* neighbors = graph->getAdjacencyList(u);
                for (int j = 0; j < neighbors->getSize(); ++j) {
                    Edge e = neighbors->get(j);
                    if (distances[u] != std::numeric_limits<int>::max() &&
                        distances[u] + e.weight < distances[e.to]) {
                        distances[e.to] = distances[u] + e.weight;
                    }
                }
            }
        }

        // Ostateczne sprawdzenie cyklu ujemnego
        negativeCycle = false;
        for (int u = 0; u < numVertices; ++u) {
            auto* neighbors = graph->getAdjacencyList(u);
            for (int j = 0; j < neighbors->getSize(); ++j) {
                Edge e = neighbors->get(j);
                if (distances[u] != std::numeric_limits<int>::max() &&
                    distances[u] + e.weight < distances[e.to]) {
                    negativeCycle = true;
                    return nullptr;
                }
            }
        }

        Graph* result = new Graph(numVertices);
        for (int u = 0; u < numVertices; ++u) {
            auto* neighbors = graph->getAdjacencyList(u);
            for (int j = 0; j < neighbors->getSize(); ++j) {
                Edge e = neighbors->get(j);
                if (distances[e.to] == distances[u] + e.weight) {
                    result->addEdge(u, e.to, e.weight);
                }
            }
        }

        return result;
    }

    int getShortestDistance(int v) const {
        if (v==-1) v = numVertices - 1;
        return (v >= 0 && v < numVertices) ? distances[v] : -1;
    }

    bool hasNegativeCycle() const {
        return negativeCycle;
    }
};

#endif
