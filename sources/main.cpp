#include <iostream>
#include "file_handler.hpp"
#include "Timer.h"
#include "structures/graph.hpp"
#include "structures/graph_adjacency_matrix.hpp"
#include "structures/dynamic_array.hpp"
#include "structures/graph_incidence_matrix.hpp"
#include "algorithms/prim.hpp"
#include "algorithms/prim_matrix.hpp"
#include "algorithms/prim_incidence_matrix.hpp"
#include "algorithms/kruskal.hpp"
#include "algorithms/kruskal_matrix.hpp"
#include "algorithms/kruskal_incidence_matrix.hpp"
#include "algorithms/dijkstra.hpp"
#include "algorithms/dijkstra_incidence_matrix.hpp"
#include "algorithms/bellman_ford.hpp"
#include "algorithms/bellman_ford_incidence_matrix.hpp"
#include "graph_generator.hpp"

using namespace std;

int main(){
    
    std::string path = "../data/dijkstra_data.txt";
    int start = 0;
    int koniec = 4;
    GraphGenerator generator;
    Graph* g = generator.generateGraph(10, 0.99);
    generator.saveGraphToFile(g, "../data/dijkstra_data.txt");

    FileHandler handler(path);
    Graph* listGraph = handler.getGraphListFromFile(true);
    GraphIncidenceMatrix* matrixGraph = handler.getGraphIncidenceMatrixFromFile(true);

    std::cout << "\n### LISTA SĄSIEDZTWA:\n";
    listGraph->printAdjacencyList();

    std::cout << "\n### MACIERZ INCYDENCJI:\n";
    matrixGraph->printIncidenceMatrix();

    // Dijkstra - lista
    std::cout << "\n\n===== DIJKSTRA (lista) =====\n";
    Dijkstra dijkstra;
    Graph* shortestList = dijkstra.run(listGraph, start);
    if (shortestList) {
        shortestList->printAdjacencyList();
        std::cout << "Koszt ścieżki do 3: " << dijkstra.getShortestDistance(start, koniec) << std::endl;
        delete shortestList;
    }

    // Dijkstra - macierz incydencji
    std::cout << "\n\n===== DIJKSTRA (macierz) =====\n";
    DijkstraIncidenceMatrix dijkstraMatrix;
    GraphIncidenceMatrix* shortestMatrix = dijkstraMatrix.run(matrixGraph, start);
    if (shortestMatrix) {
        shortestMatrix->printIncidenceMatrix();
        std::cout << "Koszt ścieżki do 3: " << dijkstraMatrix.getShortestDistance(start, koniec) << std::endl;
        delete shortestMatrix;
    }

    // Bellman-Ford - lista
    std::cout << "\n\n===== BELLMAN-FORD (lista) =====\n";
    BellmanFord bellman;
    Graph* bfList = bellman.run(listGraph, start);
    if (bellman.hasNegativeCycle()) {
        std::cout << "Wykryto cykl o ujemnej wadze!" << std::endl;
    } else {
        if (bfList) {
            bfList->printAdjacencyList();
            std::cout << "Koszt ścieżki do 3: " << bellman.getShortestDistance(koniec) << std::endl;
            delete bfList;
        }
    }

    // Bellman-Ford - macierz incydencji
    std::cout << "\n\n===== BELLMAN-FORD (macierz) =====\n";
    BellmanFordIncidenceMatrix bellmanMatrix;
    GraphIncidenceMatrix* bfMatrix = bellmanMatrix.run(matrixGraph, start);
    if (bellmanMatrix.hasNegativeCycle()) {
        std::cout << "Wykryto cykl o ujemnej wadze!" << std::endl;
    } else {
        if (bfMatrix) {
            bfMatrix->printIncidenceMatrix();
            std::cout << "Koszt ścieżki do 3: " << bellmanMatrix.getShortestDistance(koniec) << std::endl;
            delete bfMatrix;
        }
    }

    delete listGraph;
    delete matrixGraph;

}