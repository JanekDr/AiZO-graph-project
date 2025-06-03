#include <iostream>
#include "file_handler.hpp"
#include "structures/graph.hpp"
#include "structures/graph_matrix.hpp"
#include "structures/dynamic_array.hpp"
#include "Timer.h"
#include "algorithms/prim.hpp"
#include "algorithms/kruskal.hpp"
#include "algorithms/kruskal_matrix.hpp"

using namespace std;

int main(){
    FileHandler fileHandler("../data/prim_data.txt");
    FileHandler fileHandler2("../data/prim_data.txt");
    Graph* graph = fileHandler.getGraphListFromFile();
    GraphMatrix* graphMatrix = fileHandler2.getGraphMatrixFromFile();
    Kruskal kruskal;
    KruskalMatrix kruskalMatrix;
    Graph* kruskal_list = kruskal.run(graph);
    GraphMatrix* kruskal_matrix = kruskalMatrix.run(graphMatrix);


    kruskal_list->printIncidenceMatrix();
    cout<<"##########################"<<endl;

    graphMatrix->printIncidenceMatrix();
    cout<<"##########################"<<endl;
    kruskal_matrix->printIncidenceMatrix();

    return 0;
};