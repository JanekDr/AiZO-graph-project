#include <iostream>
#include "file_handler.hpp"
#include "structures/graph.hpp"
#include "structures/dynamic_array.hpp"
#include "Timer.h"

using namespace std;

int main(){
    FileHandler fileHandler("../data/test_graph.txt");
    Timer timer;
    timer.start();
    Graph* graph = fileHandler.readGraphFromFile();
    timer.stop();
    cout<< "Time taken to read the graph: " << timer.result() << " ms" << endl;
    graph->printGraph();
    return 0;
};