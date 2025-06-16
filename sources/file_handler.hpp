#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "structures/graph.hpp"
#include "structures/graph_adjacency_matrix.hpp"
#include "structures/graph_incidence_matrix.hpp"

using namespace std;

class FileHandler {
private:
    ifstream inputFile;

public:
    FileHandler(const string& inputFilename) {
        inputFile.open(inputFilename);
        if (!inputFile) {
            cerr << "Błąd: Nie można otworzyć pliku wejściowego!" << endl;
        }
    }

    ~FileHandler() {
        if (inputFile.is_open()) inputFile.close();
    }

    Graph* getGraphListFromFile(bool directed = false) {
        if (!inputFile) {
            cerr << "Błąd: Plik wejściowy nie jest otwarty!" << endl;
            return nullptr;
        }

        int numEdges, numVertices;
        inputFile >> numEdges >> numVertices;

        Graph* graph = new Graph(numVertices);

        for (int i = 0; i < numEdges; ++i) {
            int from, to, weight;
            inputFile >> from >> to >> weight;
            if (inputFile.fail()) {
                cerr << "Błąd: Niepoprawny format danych krawędzi!" << endl;
                delete graph;
                return nullptr;
            }
            graph->addEdge(from, to, weight, directed);
        }

        return graph;
    }

    GraphAdjacencyMatrix* getGraphMatrixFromFile(bool directed = false) {
        if (!inputFile) {
            cerr << "Błąd: Plik wejściowy nie jest otwarty!" << endl;
            return nullptr;
        }

        int numEdges, numVertices;
        inputFile >> numEdges >> numVertices;

        GraphAdjacencyMatrix* graphAdjacencyMatrix = new GraphAdjacencyMatrix(numVertices, numEdges, directed);

        int u, v, weight;
        while (inputFile >> u >> v >> weight){
            graphAdjacencyMatrix->addEdge(u, v, weight, directed);
        }

        return graphAdjacencyMatrix;
    }

    // NOWA METODA: Tworzenie macierzy incydencji
    GraphIncidenceMatrix* getGraphIncidenceMatrixFromFile(bool directed = false) {
        if (!inputFile) {
            cerr << "Błąd: Plik wejściowy nie jest otwarty!" << endl;
            return nullptr;
        }

        // Resetujemy pozycję pliku na początek, jeśli plik był już czytany
        inputFile.clear();
        inputFile.seekg(0, ios::beg);

        int numEdges, numVertices;
        inputFile >> numEdges >> numVertices;

        GraphIncidenceMatrix* incidenceMatrix = new GraphIncidenceMatrix(numVertices, numEdges, directed);

        int u, v, weight;
        for (int i = 0; i < numEdges; ++i) {
            inputFile >> u >> v >> weight;
            if (inputFile.fail()) {
                cerr << "Błąd: Niepoprawny format danych krawędzi!" << endl;
                delete incidenceMatrix;
                return nullptr;
            }
            incidenceMatrix->addEdge(u, v, weight);
        }

        return incidenceMatrix;
    }
};

#endif