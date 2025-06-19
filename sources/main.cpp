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
#include "graph_generator.hpp"

using namespace std;

int main(){
    
    GraphGenerator gen;
    Graph* g = gen.generateGraph(500, 0.99);
    gen.saveGraphToFile(g, "../data/generate_graph.txt");
    FileHandler fileHandler("../data/generate_graph.txt");
    GraphIncidenceMatrix* incidenceMatrix = fileHandler.getGraphIncidenceMatrixFromFile(false);
    Timer timer1;
    PrimIncidenceMatrix mstMatrix;
    timer1.start();
    mstMatrix.run(incidenceMatrix);
    timer1.stop();
    cout<<"Prim Incidence Matrix Time: " << timer1.result() << " ms" << endl;

    return 0;
}