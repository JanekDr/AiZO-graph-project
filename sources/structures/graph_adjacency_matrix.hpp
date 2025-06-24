#ifndef GRAPH_ADJACENCY_MATRIX_HPP
#define GRAPH_ADJACENCY_MATRIX_HPP

#include <iostream>
#include "dynamic_array.hpp"
#include "edge.hpp"

class GraphAdjacencyMatrix {
private:
    int numVertices;
    int numEdges;
    DynamicArray<DynamicArray<int>*> adjacencyMatrix; // Macierz sasiedztwa
    bool directed;

public:
    // Konstruktor, inicjalizujący macierz sasiedztwa
    GraphAdjacencyMatrix(int vertices, int edges, bool directed = false)
        : numVertices(vertices), numEdges(edges), directed(directed),adjacencyMatrix(vertices, nullptr)
    {
        for (int i = 0; i < vertices; ++i)
            adjacencyMatrix.add(nullptr); // zwiększamy size

        for (int i = 0; i < vertices; ++i) {
            DynamicArray<int>* row = new DynamicArray<int>(edges, 0);
            for (int j = 0; j < edges; ++j)
                row->add(0);  // ręczne wypełnienie, by size == edges
            adjacencyMatrix.set(i, row);
        }
    }




    ~GraphAdjacencyMatrix() {
        for (size_t i = 0; i < adjacencyMatrix.getSize(); ++i) {
            delete adjacencyMatrix.get(i);
        }
    }

    // Dodawanie krawędzi do macierzy sasiedztwa
    void addEdge(int u, int v, int weight, bool directed = false) {
        if (u < 0 || v < 0 || u >= numVertices || v >= numVertices) {
            std::cerr << "Blad: Indeks wierzcholka poza zakresem!" << std::endl;
            return;
        }

        // W przypadku grafu skierowanego: przypisujemy wagę krawędzi (u, v)
        adjacencyMatrix.get(u)->set(v, weight);

        if (!directed) {
            // Dla grafu nieskierowanego przypisujemy wagę krawędzi w obie strony
            adjacencyMatrix.get(v)->set(u, weight);
        }
    }

    // Metoda do pobrania macierzy incydencji
    DynamicArray<int>* getAdjacencyMatrix(int vertex) const {
        if (vertex < 0 || vertex >= numVertices) {
            std::cerr << "Blad: Indeks wierzcholka poza zakresem!" << std::endl;
            return nullptr;
        }
        return adjacencyMatrix.get(vertex);
    }

    // Metoda wyświetlająca macierz incydencji
    void printAdjacencyMatrix(){
        std::cout << "Macierz sasiedztwa:\n     ";
        for (int j = 0; j < numEdges; ++j) {
            std::cout << "V" << j << "   ";
        }
        std::cout << std::endl;
        for (int i = 0; i < numVertices; ++i) {
            std::cout << "V" << i << ":  ";
            for (int j = 0; j < numEdges; ++j) {
                std::cout << adjacencyMatrix.get(i)->get(j) << "    ";
            }
            std::cout << std::endl;
        }
    }

    void printAdjacencyMatrix(std::ostream& out = std::cout) const{
        out << "Macierz sasiedztwa:\n     ";
        for (int j = 0; j < numEdges; ++j) {
            out << "V" << j << "   ";
        }
        out << std::endl;
        for (int i = 0; i < numVertices; ++i) {
            out << "V" << i << ":  ";
            for (int j = 0; j < numEdges; ++j) {
                out << adjacencyMatrix.get(i)->get(j) << "    ";
            }
            out << std::endl;
        }
    }

    // Metoda zwracająca liczbę wierzchołków
    int getNumVertices() const {
        return numVertices;
    }
};

#endif // GRAPH_ADJACENCY_MATRIX_HPP
