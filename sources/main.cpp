#include <iostream>
#include "file_handler.hpp"
#include "structures/graph.hpp"
#include "structures/graph_adjacency_matrix.hpp"
#include "structures/dynamic_array.hpp"
#include "structures/graph_incidence_matrix.hpp"
#include "Timer.h"
#include "algorithms/prim.hpp"
#include "algorithms/kruskal.hpp"
#include "algorithms/kruskal_matrix.hpp"
#include "algorithms/prim_matrix.hpp"
#include "graph_generator.hpp"

using namespace std;

int main(){
    FileHandler fileHandler3("../data/generated_graph_test.txt");
    Graph* generatedGraph = fileHandler3.getGraphListFromFile(true);

    FileHandler fileHandler4("../data/generated_graph_test.txt");
    GraphAdjacencyMatrix* generatedGraphAdjacencyMatrix = fileHandler4.getGraphMatrixFromFile(true);

    FileHandler fileHandler5("../data/generated_graph_test.txt");
    GraphIncidenceMatrix* generatedGraphIncidenceMatrix = fileHandler5.getGraphIncidenceMatrixFromFile(true);

    generatedGraph->printAdjacencyList();
    cout<<"##########################"<<endl;
    generatedGraphAdjacencyMatrix->printAdjacencyMatrix();
    cout<<"##########################"<<endl;
    generatedGraphIncidenceMatrix->printIncidenceMatrix();


    return 0;
}