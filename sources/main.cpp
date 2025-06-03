#include <iostream>
#include "file_handler.hpp"
#include "structures/graph.hpp"
#include "structures/graph_matrix.hpp"
#include "structures/dynamic_array.hpp"
#include "Timer.h"
#include "algorithms/prim.hpp"
#include "algorithms/kruskal.hpp"

using namespace std;

int main(){
    FileHandler fileHandler("../data/prim_data.txt");
    Timer timer;
    Graph* graph = fileHandler.getGraphListFromFile(true);
    Prim prim;
    Kruskal kruskal;
    timer.start();
    Graph* mst = prim.run(graph);
    Graph* mstKruskal = kruskal.run(graph);
    timer.stop();

    cout<<"Time: "<<timer.result()<<"ms"<<endl;
    mst->printAdjacencyList();
    // cout<<"MST Prim: "<<endl;
    // mstKruskal->printAdjacencyList();
    FileHandler fileHandler2("../data/prim_data.txt");
    GraphMatrix* graphMatrix = fileHandler2.getGraphMatrixFromFile(true);
    graphMatrix->printIncidenceMatrix();
    return 0;
};