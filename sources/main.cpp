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
#include "graph_generator.hpp"

using namespace std;

int main(){
    
    FileHandler fileHandler("../data/dijkstra_data.txt");
    Graph* graph = fileHandler.getGraphListFromFile(true);
    GraphIncidenceMatrix* incidenceMatrix = fileHandler.getGraphIncidenceMatrixFromFile(true);
    Dijkstra dijkstra;
    Graph* shortestPaths = dijkstra.run(graph, 0);
    cout << "Najkrotsze sciezki (lista sasiedztwa):" << endl;
    shortestPaths->printAdjacencyList();

    cout << "\nKoszt dojscia z S (0) do l (5): ";
    cout << dijkstra.getShortestDistance(0, 2) << endl;

    DijkstraIncidenceMatrix dijkstraIncidence;
    GraphIncidenceMatrix* shortestPathsIncidence = dijkstraIncidence.run(incidenceMatrix, 0);
    cout << "\nNajkrotsze sciezki (macierz incydencji):" << endl;
    // shortestPathsIncidence->printIncidenceMatrix();
    cout << "\nKoszt dojscia z S (0) do l (5): ";
    cout << dijkstraIncidence.getShortestDistance(0, 2) << endl;
    return 0;

}