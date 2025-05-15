#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "structures/graph.hpp"

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

    Graph* readGraphFromFile() {
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
            graph->addEdge(from, to, weight);
        }

        return graph;
    }
};

#endif