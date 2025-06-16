#include <iostream>
#include "file_handler.hpp"
#include "structures/graph.hpp"
#include "structures/graph_matrix.hpp"
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
    // FileHandler fileHandler("../data/prim_data.txt");
    // FileHandler fileHandler2("../data/prim_data.txt");
    // Graph* graph = fileHandler.getGraphListFromFile();
    // GraphMatrix* graphMatrix = fileHandler2.getGraphMatrixFromFile();
    // Prim prim;
    // PrimMatrix primMatrix;
    // Graph* prim_list = prim.run(graph);
    // GraphMatrix* prim_matrix = primMatrix.run(graphMatrix);


    // prim_list->printIncidenceMatrix();
    // cout<<"##########################"<<endl;
    // cout<<"##########################"<<endl;
    // prim_matrix->printIncidenceMatrix();


    // GraphGenerator graphGenerator(5,0.8);
    // graphGenerator.generateToFile("../data/generated_graph_test.txt");
    FileHandler fileHandler3("../data/generated_graph_test.txt");
    Graph* generatedGraph = fileHandler3.getGraphListFromFile();

    FileHandler fileHandler4("../data/generated_graph_test.txt");
    GraphMatrix* generatedGraphMatrix = fileHandler4.getGraphMatrixFromFile();

    FileHandler fileHandler5("../data/generated_graph_test.txt");
    GraphIncidenceMatrix* generatedGraphIncidenceMatrix = fileHandler5.getGraphIncidenceMatrixFromFile();

    generatedGraph->printAdjacencyList();
    cout<<"##########################"<<endl;
    generatedGraphMatrix->printIncidenceMatrix();
    cout<<"##########################"<<endl;
    generatedGraphIncidenceMatrix->printIncidenceMatrix();
    return 0;
}