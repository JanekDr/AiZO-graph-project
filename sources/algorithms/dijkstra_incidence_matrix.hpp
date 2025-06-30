#ifndef DIJKSTRA_INCIDENCE_MATRIX_HPP
#define DIJKSTRA_INCIDENCE_MATRIX_HPP

#include <limits>
#include "../structures/graph.hpp"
#include "../structures/edge.hpp"
#include "../structures/graph_incidence_matrix.hpp"
#include "../structures/dynamic_array.hpp"

class DijkstraIncidenceMatrix {
public:
    DijkstraIncidenceMatrix() = default;
    ~DijkstraIncidenceMatrix() = default;

    // Zwraca nowy graf reprezentujący najkrótsze ścieżki z wierzchołka start
    GraphIncidenceMatrix* run(GraphIncidenceMatrix* graphMatrix, int start) {
        if (!graphMatrix) return nullptr;

        int n = graphMatrix->getNumVertices();
        int m = graphMatrix->getNumEdges();
        if (start < 0 || start >= n) return nullptr;

        int* dist = new int[n];
        bool* visited = new bool[n];
        int* prev = new int[n];

        for (int i = 0; i < n; ++i) {
            dist[i] = std::numeric_limits<int>::max();
            visited[i] = false;
            prev[i] = -1;
        }
        dist[start] = 0;

        for (int count = 0; count < n - 1; ++count) {
            int u = minDistance(dist, visited, n);
            if (u == -1) break;
            visited[u] = true;

            for (int e = 0; e < m; ++e) {
                int valueFromU = graphMatrix->getIncidenceValue(u, e);
                if (valueFromU == 0) continue;

                for (int v = 0; v < n; ++v) {
                    if (v == u) continue;
                    int valueFromV = graphMatrix->getIncidenceValue(v, e);

                    bool isEdge = false;
                    if (graphMatrix->isDirected()) {
                        if (valueFromU < 0 && valueFromV > 0) isEdge = true;
                    } else {
                        if (valueFromV != 0) isEdge = true;
                    }

                    if (isEdge) {
                        int weight = std::abs(valueFromU);
                        if (!visited[v] && dist[u] != std::numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                            dist[v] = dist[u] + weight;
                            prev[v] = u;
                        }
                    }
                }
            }
        }

        GraphIncidenceMatrix* result = new GraphIncidenceMatrix(n, n * n, graphMatrix->isDirected());
        for (int v = 0; v < n; ++v) {
            if (prev[v] != -1) {
                int weight = dist[v] - dist[prev[v]];
                result->addEdge(prev[v], v, weight);
            }
        }

        delete[] dist;
        delete[] visited;
        delete[] prev;

        return result;
    }

    // Zwraca koszt najkrótszej ścieżki do danego wierzchołka w grafie wynikowym
    int getShortestDistance(const GraphIncidenceMatrix* shortestPaths, int start, int end) const {
        if (!shortestPaths) return -1;
        int n = shortestPaths->getNumVertices();
        if (start < 0 || start >= n || end >= n) return -1;
        if (end < 0) end = n - 1;

        int* dist = new int[n];
        for (int i = 0; i < n; ++i) dist[i] = std::numeric_limits<int>::max();
        dist[start] = 0;

        for (int u = 0; u < n; ++u) {
            for (int e = 0; e < shortestPaths->getNumEdges(); ++e) {
                int valueFromU = shortestPaths->getIncidenceValue(u, e);
                if (valueFromU == 0) continue;

                for (int v = 0; v < n; ++v) {
                    if (v == u) continue;
                    int valueFromV = shortestPaths->getIncidenceValue(v, e);

                    bool isEdge = false;
                    if (shortestPaths->isDirected()) {
                        if (valueFromU < 0 && valueFromV > 0) isEdge = true;
                    } else {
                        if (valueFromV != 0) isEdge = true;
                    }

                    if (isEdge) {
                        int weight = std::abs(valueFromU);
                        if (dist[u] != std::numeric_limits<int>::max())
                            dist[v] = std::min(dist[v], dist[u] + weight);
                    }
                }
            }
        }

        int result = dist[end];
        delete[] dist;
        return (result == std::numeric_limits<int>::max()) ? -1 : result;
    }

private:
    int minDistance(int* dist, bool* visited, int n) {
        int min = std::numeric_limits<int>::max(), min_index = -1;
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                min_index = v;
            }
        }
        return min_index;
    }
};

#endif // DIJKSTRA_INCIDENCE_MATRIX_HPP
