#ifndef GRAPH_INCIDENCE_MATRIX_HPP
#define GRAPH_INCIDENCE_MATRIX_HPP

#include <iostream>
#include "dynamic_array.hpp"
#include "edge.hpp"

class GraphIncidenceMatrix {
private:
    int numVertices;
    int maxEdges;
    int currentEdgeIndex;
    DynamicArray<DynamicArray<int>*> incidenceMatrix;
    DynamicArray<Edge> edges;
    bool directed;

public:
    GraphIncidenceMatrix(int vertices, int maxEdges, bool directed = false)
        : numVertices(vertices),
        maxEdges(maxEdges),
        currentEdgeIndex(0),
        incidenceMatrix(vertices),
        edges(maxEdges),
        directed(directed)
    {
        for (int i = 0; i < vertices; ++i) {
            auto* row = new DynamicArray<int>(maxEdges, 0);
            incidenceMatrix.add(row);
        }
    }

    ~GraphIncidenceMatrix() {
        for (size_t i = 0; i < incidenceMatrix.getSize(); ++i) {
            delete incidenceMatrix.get(i);
        }
    }


    void addEdge(int u, int v, int weight) {
        if (currentEdgeIndex >= maxEdges) {
            std::cerr << "Przekroczono maksymalną liczbę krawędzi!" << std::endl;
            return;
        }

        edges.add(Edge(u, v, weight));
        
        if (directed) {
            // Graf skierowany: -waga dla wierzchołka wychodzącego, +waga dla wchodzącego
            incidenceMatrix.get(u)->set(currentEdgeIndex, -weight);
            incidenceMatrix.get(v)->set(currentEdgeIndex, weight);
        } else {
            // Graf nieskierowany: waga dla obu wierzchołków
            incidenceMatrix.get(u)->set(currentEdgeIndex, weight);
            incidenceMatrix.get(v)->set(currentEdgeIndex, weight);
        }
        
        currentEdgeIndex++;
    }

    void printIncidenceMatrix() {
        std::cout << "Macierz incydencji:\n     ";
        for (int j = 0; j < currentEdgeIndex; ++j) {
            std::cout << "E" << j << "   ";
        }
        std::cout << std::endl;

        for (int i = 0; i < numVertices; ++i) {
            std::cout << "V" << i << ": ";
            for (int j = 0; j < currentEdgeIndex; ++j) {
                int value = incidenceMatrix.get(i)->get(j);
                if (value >= 0) {
                    std::cout << " " << value << "   ";
                } else {
                    std::cout << value << "   ";
                }
            }
            std::cout << std::endl;
        }
    }
    
    void printIncidenceMatrix(std::ostream& out = std::cout) const{
        out << "Macierz incydencji:\n     ";
        for (int j = 0; j < currentEdgeIndex; ++j) {
            out << "E" << j << "   ";
        }
        out << std::endl;

        for (int i = 0; i < numVertices; ++i) {
            out << "V" << i << ": ";
            for (int j = 0; j < currentEdgeIndex; ++j) {
                int value = incidenceMatrix.get(i)->get(j);
                if (value >= 0) {
                    out << " " << value << "   ";
                } else {
                    out << value << "   ";
                }
            }
            out << std::endl;
        }
    }

    void printEdges() {
        std::cout << "Lista krawędzi:" << std::endl;
        for (int i = 0; i < currentEdgeIndex; ++i) {
            Edge e = edges.get(i);
            std::cout << "E" << i << ": " << e.from << " -> " << e.to 
                      << " (waga: " << e.weight << ")" << std::endl;
        }
    }

    // void printDetailedMatrix() {
    //     std::cout << "\nSzczegółowa macierz incydencji:" << std::endl;
    //     std::cout << "Legenda: ";
    //     if (directed) {
    //         std::cout << "wartość ujemna = wierzchołek źródłowy, wartość dodatnia = wierzchołek docelowy" << std::endl;
    //     } else {
    //         std::cout << "wartość dodatnia = wierzchołek incydentny z krawędzią" << std::endl;
    //     }
        
    //     printIncidenceMatrix();
    //     std::cout << std::endl;
    //     printEdges();
    // }

    int getNumVertices() const { return numVertices; }
    int getNumEdges() const { return currentEdgeIndex; }
    int isDirected() const { return directed; }
    
    // Metoda pomocnicza do sprawdzenia wartości w macierzy
    int getIncidenceValue(int vertex, int edge) const {
        if (vertex >= 0 && vertex < numVertices && edge >= 0 && edge < currentEdgeIndex) {
            return incidenceMatrix.get(vertex)->get(edge);
        }
        return 0;
    }
};

#endif // GRAPH_INCIDENCE_MATRIX_HPP
