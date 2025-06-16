#include <iostream>
#include "file_handler.hpp"
#include "structures/graph.hpp"
#include "structures/graph_adjacency_matrix.hpp"
#include "structures/dynamic_array.hpp"
#include "structures/graph_incidence_matrix.hpp"
#include "Timer.h"
#include "algorithms/prim.hpp"
#include "algorithms/prim_matrix.hpp"
#include "algorithms/prim_incidence_matrix.hpp"
#include "algorithms/kruskal.hpp"
#include "algorithms/kruskal_matrix.hpp"
#include "graph_generator.hpp"

using namespace std;

int main(){
    string inputFilename = "../data/prim_data.txt";
    FileHandler fileHandler3(inputFilename);
    Graph* generatedGraph = fileHandler3.getGraphListFromFile();

    FileHandler fileHandler4(inputFilename);
    GraphAdjacencyMatrix* generatedGraphAdjacencyMatrix = fileHandler4.getGraphMatrixFromFile();

    FileHandler fileHandler5(inputFilename);
    GraphIncidenceMatrix* generatedGraphIncidenceMatrix = fileHandler5.getGraphIncidenceMatrixFromFile();

    generatedGraph->printAdjacencyList();
    cout<<"##########################"<<endl;
    generatedGraphAdjacencyMatrix->printAdjacencyMatrix();
    cout<<"##########################"<<endl;
    generatedGraphIncidenceMatrix->printIncidenceMatrix();

    cout<<"##########################"<<endl;
    Prim primAlgorithm;
    Graph* mstList = primAlgorithm.run(generatedGraph);
    mstList->printAdjacencyList();
    
    cout<<"##########################"<<endl;
    PrimMatrix primMatrixAlgorithm;
    GraphAdjacencyMatrix* mstMatrix = primMatrixAlgorithm.run(generatedGraphAdjacencyMatrix);
    mstMatrix->printAdjacencyMatrix();

    cout<<"##########################"<<endl;
    PrimIncidenceMatrix primIncidenceAlgorithm;
    GraphIncidenceMatrix* mstIncidenceMatrix = primIncidenceAlgorithm.run(generatedGraphIncidenceMatrix);
    mstIncidenceMatrix->printIncidenceMatrix();

    return 0;
}