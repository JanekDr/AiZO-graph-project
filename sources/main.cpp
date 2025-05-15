#include <iostream>
#include "file_handler.hpp"
#include "structures/graph.hpp"
#include "structures/dynamic_array.hpp"

using namespace std;

int main(){
    FileHandler fileHandler("../data/test_graph.txt");
    Graph* graph = fileHandler.readGraphFromFile();
    graph->printGraph();
    return 0;
};