#ifndef GRAPH_MATRIX_HPP
#define GRAPH_MATRIX_HPP

#include <iostream>
#include "dynamic_array.hpp"
#include "edge.hpp"

class GraphMatrix {
private:
    int numVertices;
    int numEdges;
    DynamicArray<DynamicArray<int>*> incidenceMatrix; // Macierz incydencji
    bool directed;

public:
    // Konstruktor, inicjalizujący macierz incydencji
    GraphMatrix(int vertices, int edges, bool directed = false)
        : numVertices(vertices), numEdges(edges), directed(directed),incidenceMatrix(vertices, nullptr)
    {
        for (int i = 0; i < vertices; ++i)
            incidenceMatrix.add(nullptr); // zwiększamy size

        for (int i = 0; i < vertices; ++i) {
            DynamicArray<int>* row = new DynamicArray<int>(edges, 0);
            for (int j = 0; j < edges; ++j)
                row->add(0);  // ręczne wypełnienie, by size == edges
            incidenceMatrix.set(i, row);
        }
    }




    ~GraphMatrix() {
        for (size_t i = 0; i < incidenceMatrix.getSize(); ++i) {
            delete incidenceMatrix.get(i);
        }
    }

    // Dodawanie krawędzi do macierzy incydencji
    void addEdge(int u, int v, int weight, bool directed = false) {
        if (u < 0 || v < 0 || u >= numVertices || v >= numVertices) {
            std::cerr << "Blad: Indeks wierzcholka poza zakresem!" << std::endl;
            return;
        }

        // W przypadku grafu skierowanego: przypisujemy wagę krawędzi (u, v)
        incidenceMatrix.get(u)->set(v, weight);

        if (!directed) {
            // Dla grafu nieskierowanego przypisujemy wagę krawędzi w obie strony
            incidenceMatrix.get(v)->set(u, weight);
        }
    }

    // Metoda do pobrania macierzy incydencji
    DynamicArray<int>* getIncidenceMatrix(int vertex) const {
        if (vertex < 0 || vertex >= numVertices) {
            std::cerr << "Blad: Indeks wierzcholka poza zakresem!" << std::endl;
            return nullptr;
        }
        return incidenceMatrix.get(vertex);
    }

    // Metoda wyświetlająca macierz incydencji
    void printIncidenceMatrix() {
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numEdges; ++j) {
                std::cout << incidenceMatrix.get(i)->get(j) << " ";
            }
            std::cout << std::endl;
        }
    }

    // Metoda zwracająca liczbę wierzchołków
    int getNumVertices() const {
        return numVertices;
    }
};

#endif // GRAPH_MATRIX_HPP
