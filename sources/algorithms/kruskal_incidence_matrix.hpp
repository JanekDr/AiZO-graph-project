#ifndef KRUSKAL_INCIDENCE_MATRIX_HPP
#define KRUSKAL_INCIDENCE_MATRIX_HPP

#include <iostream>
#include "../structures/graph_incidence_matrix.hpp"
#include "../structures/edge.hpp"
#include "../structures/dynamic_array.hpp"

class KruskalIncidenceMatrix {
public:
    KruskalIncidenceMatrix() = default;
    ~KruskalIncidenceMatrix() = default;

    GraphIncidenceMatrix* run(GraphIncidenceMatrix* graphIncidenceMatrix) {
        if (!graphIncidenceMatrix) return nullptr;

        int n = graphIncidenceMatrix->getNumVertices();
        int m = graphIncidenceMatrix->getNumEdges();
        if (n == 0 || m == 0) return nullptr;

        // Zbieramy wszystkie krawędzie z macierzy incydencji
        DynamicArray<Edge>* edges = new DynamicArray<Edge>(m);
        
        for (int edgeIdx = 0; edgeIdx < m; ++edgeIdx) {
            int from = -1, to = -1;
            int weight = 0;
            
            // Znajdź wierzchołki incydentne z tą krawędzią
            DynamicArray<int> incidentVertices(2);
            
            for (int vertex = 0; vertex < n; ++vertex) {
                int value = graphIncidenceMatrix->getIncidenceValue(vertex, edgeIdx);
                if (value != 0) {
                    incidentVertices.add(vertex);
                    if (weight == 0) {
                        // Ustaw wagę na podstawie wartości bezwzględnej
                        weight = (value > 0) ? value : -value;
                    }
                }
            }
            
            // Dla grafu nieskierowanego lub gdy mamy dokładnie 2 wierzchołki
            if (incidentVertices.getSize() == 2) {
                from = incidentVertices.get(0);
                to = incidentVertices.get(1);
                
                // Dla grafów skierowanych, sprawdź kierunek
                if (graphIncidenceMatrix->isDirected()) {
                    int fromValue = graphIncidenceMatrix->getIncidenceValue(from, edgeIdx);
                    int toValue = graphIncidenceMatrix->getIncidenceValue(to, edgeIdx);
                    
                    // Ujemna wartość = źródło, dodatnia = cel
                    if (fromValue > 0 && toValue < 0) {
                        // Zamień miejscami
                        int temp = from;
                        from = to;
                        to = temp;
                    }
                }
                
                edges->add(Edge(from, to, weight));
            }
        }

        // Sortowanie krawędzi po wagach rosnąco (bubble sort)
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

        // Zlicz ile krawędzi będzie w MST
        int mstEdgeCount = 0;
        DynamicArray<Edge> mstEdges(n - 1);

        // Algorytm Kruskala
        for (int i = 0; i < edges->getSize() && mstEdgeCount < n - 1; ++i) {
            int u = edges->get(i).from;
            int v = edges->get(i).to;
            
            if (find(u, parent) != find(v, parent)) {
                mstEdges.add(edges->get(i));
                unionSets(u, v, parent, rank);
                mstEdgeCount++;
            }
        }

        // Tworzymy wynikowy graf jako macierz incydencji
        GraphIncidenceMatrix* mst = new GraphIncidenceMatrix(n, mstEdgeCount, false);
        
        for (int i = 0; i < mstEdges.getSize(); ++i) {
            Edge edge = mstEdges.get(i);
            mst->addEdge(edge.from, edge.to, edge.weight);
        }

        delete[] parent;
        delete[] rank;
        delete edges;

        return mst;
    }

    // Metoda do wyświetlania posortowanych krawędzi (do debugowania)
    void printSortedEdges(GraphIncidenceMatrix* graph) {
        if (!graph) return;
        
        int n = graph->getNumVertices();
        int m = graph->getNumEdges();
        
        DynamicArray<Edge> edges(m);
        
        // Zbierz krawędzie
        for (int edgeIdx = 0; edgeIdx < m; ++edgeIdx) {
            int from = -1, to = -1, weight = 0;
            
            for (int vertex = 0; vertex < n; ++vertex) {
                int value = graph->getIncidenceValue(vertex, edgeIdx);
                if (value != 0) {
                    if (from == -1) {
                        from = vertex;
                        weight = (value > 0) ? value : -value;
                    } else {
                        to = vertex;
                        break;
                    }
                }
            }
            
            if (from != -1 && to != -1) {
                edges.add(Edge(from, to, weight));
            }
        }
        
        // Sortuj
        for (int i = 0; i < edges.getSize(); ++i) {
            for (int j = i + 1; j < edges.getSize(); ++j) {
                if (edges.get(i).weight > edges.get(j).weight) {
                    edges.swap(i, j);
                }
            }
        }
        
        std::cout << "\nKrawędzie posortowane według wagi:" << std::endl;
        for (int i = 0; i < edges.getSize(); ++i) {
            Edge e = edges.get(i);
            std::cout << "(" << e.from << " -> " << e.to << ", waga: " << e.weight << ")" << std::endl;
        }
    }

private:
    int find(int u, int* parent) {
        if (parent[u] != u) {
            parent[u] = find(parent[u], parent); // Kompresja ścieżki
        }
        return parent[u];
    }

    void unionSets(int u, int v, int* parent, int* rank) {
        int rootU = find(u, parent);
        int rootV = find(v, parent);
        
        if (rootU != rootV) {
            // Union by rank
            if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

#endif // KRUSKAL_INCIDENCE_MATRIX_HPP
