#include <iostream>
#include "file_handler.hpp"
#include "structures/graph.hpp"
#include "structures/graph_matrix.hpp"
#include "structures/dynamic_array.hpp"
#include "Timer.h"
#include "algorithms/prim.hpp"
#include "algorithms/kruskal.hpp"
#include "algorithms/kruskal_matrix.hpp"
#include "algorithms/prim_matrix.hpp"

using namespace std;

int main(){
    FileHandler fileHandler("../data/prim_data.txt");
    FileHandler fileHandler2("../data/prim_data.txt");
    Graph* graph = fileHandler.getGraphListFromFile();
    GraphMatrix* graphMatrix = fileHandler2.getGraphMatrixFromFile();
    Prim prim;
    PrimMatrix primMatrix;
    Graph* prim_list = prim.run(graph);
    GraphMatrix* prim_matrix = primMatrix.run(graphMatrix);


    prim_list->printIncidenceMatrix();
    cout<<"##########################"<<endl;
    cout<<"##########################"<<endl;
    prim_matrix->printIncidenceMatrix();

    return 0;
}