#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include "dynamic_array.hpp"
#include "edge.hpp"


class Graph {
private:
    int numVertices;
    DynamicArray<DynamicArray<Edge>*> adjacencyList;
    bool directed;
    public:
        // W graph.hpp
    Graph(int vertices) : numVertices(vertices), adjacencyList(vertices) {
        // POPRAWKA: Użyj większej pojemności dla wyższych gęstości
        int capacityPerVertex = vertices; // Każdy wierzchołek może mieć maksymalnie n-1 krawędzi
        
        for (int i = 0; i < vertices; ++i) {
            adjacencyList.add(new DynamicArray<Edge>(capacityPerVertex));
        }
    }

    ~Graph() {
        for (size_t i = 0; i < adjacencyList.getSize(); ++i) {
            // std::cerr << "Destruktor GraphAdjacencyList!" << std::endl;
            delete adjacencyList.get(i);
        }
    }

    void addEdge(int u, int v, int weight, bool directed = false) {
        adjacencyList.get(u)->add({u, v, weight});
        if (!directed)adjacencyList.get(v)->add({v, u, weight}); // dla grafu nieskierowanego
    }

    int getNumVertices() const {
        return numVertices;
    }

    DynamicArray<Edge>* getAdjacencyList(int vertex) const {
        if (vertex < 0 || vertex >= numVertices) {
            std::cerr << "Blad: Indeks wierzcholka poza zakresem!" << std::endl;
            return nullptr;
        }
        return adjacencyList.get(vertex);
    }

    void printAdjacencyList() {
        std::cout<<"Lista sasiedztwa:\n";
        for (int i = 0; i < numVertices; ++i) {
            std::cout << "V" << i << ": ";
            DynamicArray<Edge>* list = adjacencyList.get(i);
            for (size_t j = 0; j < list->getSize(); ++j) {
                Edge e = list->get(j);
                std::cout << "(" << e.to << ", " << e.weight << ") ";
            }
            std::cout << std::endl;
        }
    }

    void printAdjacencyList(std::ostream& out = std::cout) const{
        out<<"Lista sasiedztwa:\n";
        for (int i = 0; i < numVertices; ++i) {
            // std::cerr << "adjacencyList.getSize() = " << adjacencyList.getSize() << ", i = " << i << std::endl;
            out << "V" << i << ": ";
            DynamicArray<Edge>* list = adjacencyList.get(i);
            if (list == nullptr) {
                std::cerr << "adjacencyList[" << i << "] == nullptr!" << std::endl;
            }
            for (size_t j = 0; j < list->getSize(); ++j) {
                Edge e = list->get(j);
                out << "(" << e.to << ", " << e.weight << ") ";
            }
            out << std::endl;
        }
    }

    void printIncidenceMatrix() {
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                if (i == j) {
                    std::cout << "0 ";
                } else {
                    bool found = false;
                    DynamicArray<Edge>* list = adjacencyList.get(i);
                    for (size_t k = 0; k < list->getSize(); ++k) {
                        if (list->get(k).to == j) {
                            std::cout << list->get(k).weight << " ";
                            found = true;
                            break;
                        }
                    }
                    if (!found) std::cout << "0 ";
                }
            }
            std::cout << std::endl;
        }
    }
};

#endif
