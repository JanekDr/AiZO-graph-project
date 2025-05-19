#include <iostream>
#include "file_handler.hpp"
#include "structures/graph.hpp"
#include "structures/dynamic_array.hpp"
#include "Timer.h"

using namespace std;

int main(){
    FileHandler fileHandler("../data/test_directed_graph.txt");
    Timer timer;
    timer.start();
    Graph* graph = fileHandler.readGraphFromFile(true);
    timer.stop();
    cout<< "Time taken to read the graph: " << timer.result() << " ms" << endl;
    graph->printAdjacencyList();
    graph->printIncidenceMatrix();
    return 0;
};