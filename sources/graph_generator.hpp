#ifndef GRAPH_GENERATOR_HPP
#define GRAPH_GENERATOR_HPP

#include <cstdlib>
#include <ctime>
#include <fstream>
#include "structures/graph.hpp"
#include "structures/dynamic_array.hpp"
#include "structures/edge.hpp"

class GraphGenerator {
public:
    GraphGenerator() {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

    Graph* generateGraph(int numVertices, double density) {
        if (numVertices < 2) return nullptr;

        int maxEdges = numVertices * (numVertices - 1) / 2;
        int minEdges = numVertices - 1;
        int targetEdges = minEdges + static_cast<int>(density * (maxEdges - minEdges));

        Graph* graph = new Graph(numVertices);

        // Tworzenie spójnego drzewa
        for (int i = 1; i < numVertices; ++i) {
            int u = i;
            int v = std::rand() % i;
            int weight = 1 + std::rand() % 10;
            graph->addEdge(u, v, weight);
        }

        // Dodawanie losowych dodatkowych krawędzi
        int edgesAdded = numVertices - 1;
        while (edgesAdded < targetEdges) {
            int u = std::rand() % numVertices;
            int v = std::rand() % numVertices;
            if (u == v || edgeExists(graph, u, v)) continue;

            int weight = 1 + std::rand() % 10;
            graph->addEdge(u, v, weight);
            ++edgesAdded;
        }

        return graph;
    }

    void saveGraphToFile(Graph* graph, const std::string& filename) {
        if (!graph) return;

        int numVertices = graph->getNumVertices();
        int numEdges = 0;
        DynamicArray<Edge> edgeList(numVertices * (numVertices - 1));

        for (int u = 0; u < numVertices; ++u) {
            DynamicArray<Edge>* neighbors = graph->getAdjacencyList(u);
            for (size_t i = 0; i < neighbors->getSize(); ++i) {
                Edge e = neighbors->get(i);
                if (u < e.to) {
                    edgeList.add(Edge(u, e.to, e.weight));
                    numEdges++;
                }
            }
        }

        std::ofstream fout(filename);
        if (!fout.is_open()) {
            std::cerr << "Blad: Nie mozna otworzyc pliku do zapisu!" << std::endl;
            return;
        }

        fout << numEdges << "\t" << numVertices << "\n";
        for (size_t i = 0; i < edgeList.getSize(); ++i) {
            Edge e = edgeList.get(i);
            fout << e.from << "\t" << e.to << "\t" << e.weight << "\n";
        }

        fout.close();
    }

private:
    bool edgeExists(Graph* graph, int u, int v) {
        DynamicArray<Edge>* neighbors = graph->getAdjacencyList(u);
        for (size_t i = 0; i < neighbors->getSize(); ++i) {
            if (neighbors->get(i).to == v) return true;
        }
        return false;
    }
};

#endif // GRAPH_GENERATOR_HPP
