#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <limits>
#include "../structures/graph.hpp"
#include "../structures/edge.hpp"
#include "../structures/dynamic_array.hpp"

class Dijkstra {
public:
    Dijkstra() = default;
    ~Dijkstra() {
        if (shortestPaths) delete shortestPaths;
    }

    // Zwraca graf reprezentujący najkrótsze ścieżki z wierzchołka start
    Graph* run(Graph* graph, int start=0) {
        if (!graph) return nullptr;

        int n = graph->getNumVertices();
        if (start < 0 || start >= n) return nullptr;

        if (shortestPaths) {
            delete shortestPaths;
            shortestPaths = nullptr;
        }

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

            DynamicArray<Edge>* neighbors = graph->getAdjacencyList(u);
            for (size_t i = 0; i < neighbors->getSize(); ++i) {
                Edge e = neighbors->get(i);
                int v = e.to;
                if (!visited[v] && dist[u] != std::numeric_limits<int>::max() && dist[u] + e.weight < dist[v]) {
                    dist[v] = dist[u] + e.weight;
                    prev[v] = u;
                }
            }
        }

        shortestPaths = new Graph(n);
        for (int v = 0; v < n; ++v) {
            if (prev[v] != -1 && dist[v] != std::numeric_limits<int>::max()) {
                int u = prev[v];
                if (u >= 0 && u < n) {
                    int weight = dist[v] - dist[u];
                    shortestPaths->addEdge(u, v, weight);
                }
            }
        }

        delete[] visited;
        delete[] prev;
        delete[] dist;

        return shortestPaths;
    }


    // Zwraca koszt najkrótszej ścieżki do danego wierzchołka
    int getShortestDistance(int start, int end) {
        if (!shortestPaths) return -1;
        int n = shortestPaths->getNumVertices();
        if (start < 0 || start >= n || end >= n) return -1;
        if (end==-1) end = n-1; // jeśli end=-1, to zwracamy ostatni wierzchołek

        // BFS lub DFS w wynikowym grafie (najkrótsze ścieżki mają tylko po jednej krawędzi)
        int* dist = new int[n];
        for (int i = 0; i < n; ++i) dist[i] = std::numeric_limits<int>::max();
        dist[start] = 0;

        for (int u = 0; u < n; ++u) {
            DynamicArray<Edge>* neighbors = shortestPaths->getAdjacencyList(u);
            for (size_t i = 0; i < neighbors->getSize(); ++i) {
                Edge e = neighbors->get(i);
                if (dist[u] != std::numeric_limits<int>::max())
                    dist[e.to] = std::min(dist[e.to], dist[u] + e.weight);
            }
        }

        int result = dist[end];
        delete[] dist;
        return (result == std::numeric_limits<int>::max()) ? -1 : result;
    }

private:
    Graph* shortestPaths = nullptr;

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

#endif // DIJKSTRA_HPP
