#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include "dynamic_array.hpp"
#include "Edge.hpp"


class Graph {
private:
    int numVertices;
    DynamicArray<DynamicArray<Edge>*> adjacencyList;
    bool directed;
public:
    Graph(int vertices) : numVertices(vertices), adjacencyList(vertices) {
        for (int i = 0; i < vertices; ++i) {
            adjacencyList.add(new DynamicArray<Edge>(vertices));
        }
    }

    ~Graph() {
        for (size_t i = 0; i < adjacencyList.getSize(); ++i) {
            delete adjacencyList.get(i);
        }
    }

    void addEdge(int u, int v, int weight, bool directed = false) {
        adjacencyList.get(u)->add({v, weight});
        if (!directed)adjacencyList.get(v)->add({u, weight}); // dla grafu nieskierowanego
    }

    void printAdjacencyList() {
        for (int i = 0; i < numVertices; ++i) {
            std::cout << "Wierzcholek " << i << ": ";
            DynamicArray<Edge>* list = adjacencyList.get(i);
            for (size_t j = 0; j < list->getSize(); ++j) {
                Edge e = list->get(j);
                std::cout << "(" << e.to << ", " << e.weight << ") ";
            }
            std::cout << std::endl;
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
