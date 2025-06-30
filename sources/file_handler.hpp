#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "structures/graph.hpp"
#include "structures/graph_adjacency_matrix.hpp"
#include "structures/graph_incidence_matrix.hpp"

class FileHandler {
private:
    std::ifstream inputFile;

public:
    FileHandler(const std::string& inputFilename) {
        inputFile.open(inputFilename);
        if (!inputFile) {
            std::cerr << "Błąd: Nie można otworzyć pliku wejściowego!" << std::endl;
        }
    }

    ~FileHandler() {
        if (inputFile.is_open()) inputFile.close();
    }

    Graph* getGraphListFromFile(bool directed = false) {
        if (!inputFile) {
            std::cerr << "Błąd: Plik wejściowy nie jest otwarty!" << std::endl;
            return nullptr;
        }

        int numEdges, numVertices;
        inputFile >> numEdges >> numVertices;

        Graph* graph = new Graph(numVertices);

        for (int i = 0; i < numEdges; ++i) {
            int from, to, weight;
            inputFile >> from >> to >> weight;
            if (inputFile.fail()) {
                std::cerr << "Błąd: Niepoprawny format danych krawędzi!" << std::endl;
                delete graph;
                return nullptr;
            }
            graph->addEdge(from, to, weight, directed);
        }

        return graph;
    }

    GraphAdjacencyMatrix* getGraphMatrixFromFile(bool directed = false) {
        if (!inputFile) {
            std::cerr << "Błąd: Plik wejściowy nie jest otwarty!" << std::endl;
            return nullptr;
        }

        // Reset pozycji pliku na początek (jeśli plik był już czytany wcześniej)
        inputFile.clear();
        inputFile.seekg(0, std::ios::beg);

        int numEdges, numVertices;
        inputFile >> numEdges >> numVertices;

        // UWAGA: przekazujemy numVertices jako oba pierwsze argumenty!
        GraphAdjacencyMatrix* graphAdjacencyMatrix = new GraphAdjacencyMatrix(numVertices, numVertices, directed);

        int u, v, weight;
        for (int i = 0; i < numEdges; ++i) {
            inputFile >> u >> v >> weight;
            if (inputFile.fail()) {
                std::cerr << "Błąd: Niepoprawny format danych krawędzi!" << std::endl;
                delete graphAdjacencyMatrix;
                return nullptr;
            }
            graphAdjacencyMatrix->addEdge(u, v, weight, directed);
        }

        return graphAdjacencyMatrix;
    }

    // NOWA METODA: Tworzenie macierzy incydencji
    GraphIncidenceMatrix* getGraphIncidenceMatrixFromFile(bool directed = false) {
        if (!inputFile) {
            std::cerr << "Błąd: Plik wejściowy nie jest otwarty!" << std::endl;
            return nullptr;
        }

        // Resetujemy pozycję pliku na początek, jeśli plik był już czytany
        inputFile.clear();
        inputFile.seekg(0, std::ios::beg);

        int numEdges, numVertices;
        inputFile >> numEdges >> numVertices;

        GraphIncidenceMatrix* incidenceMatrix = new GraphIncidenceMatrix(numVertices, numEdges, directed);

        int u, v, weight;
        for (int i = 0; i < numEdges; ++i) {
            inputFile >> u >> v >> weight;
            if (inputFile.fail()) {
                std::cerr << "Błąd: Niepoprawny format danych krawędzi!" << std::endl;
                delete incidenceMatrix;
                return nullptr;
            }
            incidenceMatrix->addEdge(u, v, weight);
        }

        return incidenceMatrix;
    }
};

#endif // FILEHANDLER_HPP
