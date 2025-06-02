#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "structures/graph.hpp"
#include "structures/graph_matrix.hpp"

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

    GraphMatrix* getGraphMatrixFromFile(bool directed = false) {
        if (!inputFile) {
            cerr << "Błąd: Plik wejściowy nie jest otwarty!" << endl;
            return nullptr;
        }

        int numEdges, numVertices;
        inputFile >> numEdges >> numVertices;

        GraphMatrix* graphMatrix = new GraphMatrix(numVertices, numEdges, directed);

        int u, v, weight;
        while (inputFile >> u >> v >> weight){
            graphMatrix->addEdge(u, v, weight, directed);
        }

        return graphMatrix;
    }
};

#endif