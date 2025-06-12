#ifndef GRAPH_GENERATOR_HPP
#define GRAPH_GENERATOR_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "structures/edge.hpp"
#include "structures/dynamic_array.hpp"

class GraphGenerator {
private:
    int numVertices;
    float density; // od 0.0 do 1.0
    int maxWeight;
    bool directed;

    bool edgeExists(DynamicArray<Edge>* edges, int u, int v) {
        for (size_t i = 0; i < edges->getSize(); ++i) {
            Edge e = edges->get(i);
            if ((e.from == u && e.to == v) || (!directed && e.from == v && e.to == u)) {
                return true;
            }
        }
        return false;
    }

public:
    GraphGenerator(int vertices, float dens, int maxW = 100, bool dir = false)
        : numVertices(vertices), density(dens), maxWeight(maxW), directed(dir) {
        srand(static_cast<unsigned int>(time(nullptr)));
    }

    void generateToFile(const std::string& filename) {
        int maxEdges;
        if (directed) {
            maxEdges = numVertices * (numVertices - 1);
        } else {
            maxEdges = (numVertices * (numVertices - 1)) / 2;
        }
        int requiredEdges = static_cast<int>(density * maxEdges);

        DynamicArray<Edge>* edges = new DynamicArray<Edge>(requiredEdges);

        // Etap 1: generowanie drzewa (spojnosc)
        for (int i = 1; i < numVertices; ++i) {
            int u = i;
            int v = rand() % i;
            int w = 1 + rand() % maxWeight;
            edges->add(Edge(u, v, w));
        }

        // Etap 2: dodanie losowych krawedzi az do uzyskania wymaganej gestosci
        while (edges->getSize() < requiredEdges) {
            int u = rand() % numVertices;
            int v = rand() % numVertices;
            if (u == v || edgeExists(edges, u, v)) continue;
            int w = 1 + rand() % maxWeight;
            edges->add(Edge(u, v, w));
        }

        // Zapis do pliku
        std::ofstream fout(filename);
        fout << edges->getSize() << "\t" << numVertices << "\n";
        for (size_t i = 0; i < edges->getSize(); ++i) {
            Edge e = edges->get(i);
            fout << e.from << "\t" << e.to << "\t" << e.weight << "\n";
        }
        fout.close();

        delete edges;
    }
};

#endif // GRAPH_GENERATOR_HPP
